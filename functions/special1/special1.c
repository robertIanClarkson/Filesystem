#include "special1.h"
/* one to copy from the normal filesystem to your filesystem */
/* command = "special1 sourceFile ourFileName ourFileDirectory" */

int special1(struct filesystem_volume volume, struct arguments command) {
    ssize_t returnSource;

    /* check if command.argc != 4 */
    if(command.argc < 4) {
        printf("***Not Enough Args***\n");
        return 0; // check
    }
    else if(command.argc > 4) {
	    printf("***TOO many Args***\n");
	    return 0; //check
    }

    char* sourceFile = command.args[1];
    char* ourFileName = command.args[2];
    char* ourFileDirectory = command.args[3];

    // how many blocks the file is 
    int totalSize;
    int totalBlocks;

    // declare stat variable
    struct stat st; 

    // check if linux file exists
    if(stat(sourceFile, &st) != 0) {
        printf("***ERROR LINUX FILE DNE***\n");
        return 0;
    }

    // a new File is created using the touch command, with the name and directory coming from args
    struct arguments newArgs;
    newArgs.argc = 3;
    strcpy(newArgs.args[0], "touch");
    strcpy(newArgs.args[1], ourFileName);
    strcpy(newArgs.args[2], ourFileDirectory);
    if(createFile(volume, newArgs) == 0)
        printf("***FAILED TO CREATE NEW FILE***\n");

    // get index of new file created
    int fileIndex = getIndex(ourFileName, volume);
    if(fileIndex < 0) {
        printf("***ERROR INDEX COULD NOT BE FOUND***");
        return 0;
    }

    // absolute path of file should work with null terminator added
    //strcat(sourceFile, '\0');

    // get filesize of linux file
    long int linuxFileSize = getFileSize(sourceFile);
    printf("Linux FileSize: %ld\n", linuxFileSize);

    // get number of LBA we will need
    int LBAcount = ceil(((double) linuxFileSize) / ((double) volume.blockSize));
    printf("Number of LBAs we need: %d\n", LBAcount);
   
    // main logic loop 
    int emptyBlock;
    int startIndex;
    int readSize;
    char* buffer = malloc(volume.blockSize);
    for(int i = 0; i < LBAcount; i++) {
        // get a free block
        emptyBlock = getNextEmptyLBA(volume);
        // volume.map[emptyBlock] = 1;
        setMap(emptyBlock, '1', volume);
        printf("Empty LBA at: %d\n", emptyBlock);

        // read file into buffer
        initializeLBA(buffer, '-', volume.blockSize);
        readNBytes(buffer, sourceFile, (i * volume.blockSize), volume.blockSize);
        LBAwrite(buffer, 1, emptyBlock);

        // add block to file
        addChild(emptyBlock, fileIndex, volume);
        printf("Add Child at %d to file at %d\n", emptyBlock, fileIndex);

    }

    printf("File successfully copied from LINUX to Filesystem\n");
    return 1;
}

// test_files/test_small.txt
