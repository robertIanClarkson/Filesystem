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

    // get file size of the file we want to copy 
    /* http://man7.org/linux/man-pages/man2/stat.2.html */
    if(stat(sourceFile,&st) == 0) {
        // st_blocks - Number of 512B blocks allocated
        // st_size - Total size, in bytes *might be needed instead for the read function*
        totalSize = st.st_size;
        printf("totalSize: %d\n",totalSize);
    } else {
        printf("***ERROR UNABLE TO RETRIEVE SIZE***");
        return 0;
    }
    if((totalSize%512) != 0) 
        totalBlocks = (totalSize/512) + 1; 
    else
        totalBlocks = totalSize/512;

    printf("totalBlocks: %d\n",totalBlocks);

    // find empty LBA
    int freeLBAIndex = getNextEmptyLBA(volume);

    // open linux file
    int linuxFile = open(sourceFile, O_RDONLY);

    // read linux file *need to make sure this dumps contents of file into returnSource*
    char* buffer = malloc(volume.volumeSize);
    returnSource = read(linuxFile, buffer, totalSize);
    buffer[returnSource] = '\0';
    printf("returnSource: %ld\n",returnSource);
    printf("Those bytes are as follows: %s\n",buffer);

    // write buffer back to the LBA
    int temp = LBAwrite(buffer, totalBlocks, freeLBAIndex);
    printf("LBAwrite return is: %d\n", temp);

    // mark map to show LBAIndex is filled
    volume.map[freeLBAIndex] = 1;

    // add freeLBAIndex as child to new file
    if (addChild(freeLBAIndex, fileIndex, volume) != 1) {
        free(buffer);
        printf("***ERROR ADDING CHILD TO FOLDER***");
        return 0;
    }

    // free mallocs
    free(buffer);

    printf("File successfully copied from LINUX to Filesystem\n");
    return 1;
}