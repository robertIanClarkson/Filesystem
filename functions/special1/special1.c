#include "special1.h"
/* one to copy from the normal filesystem to your filesystem */
/* command = "special2 sourceFile linuxDestinationFile" */

int special1(struct filesystem_volume volume, struct arguments command) {
    ssize_t returnSource, returnDestination;
    char buffer[BUF_SIZE];

    /* check if command.argc != 2 */
    if(command.argc < 4) {
        printf("***Not Enough Args***\n");
        return 0; // check
    }
    else if(command.argc > 4) {
	    printf("***TOO many Args***\n");
	    return 0; //check
    }

    // Get args 
    char* sourceFile = command.args[1];
    char* fileName = command.args[2];
    char* destinationFile = command.args[3];

    // Open Linux File 
    int linuxFile = open(linuxFile, O_RDONLY);
    // Open Destination File
    int DSFile = open(destinationFile, O_WRONLY | O_CREAT, 0644);
    //negative value is returned, then there was an error opening the file
    if(linuxFile < 0){
	printf("***ERROR CANNOT OPEN FILE***");
        return 0;
    }
    if(linuxFile > 0){
    	printf("*OPENING THE FILE*");
	FILE* newFile;
	newFile = fopen(comman.args[1], "r");
	if(newFile == NULL)
    	{
        /* File not created hence exit */
        printf("***UNABLE TO CREATE FILE.***\n");
        return 0;
    	}
	else if(newFile != NULL){
	printf("***CREATING FILE***\n")	
		while((returnSource = read (linuxFile, &buffer, BUF_SIZE)) > 0){
            		returnDestination = write (DSFile, &buffer, (ssize_t) returnSource);
            		if(returnDestination != returnSource){
                	/* Write error */
                	perror("***FILE DO NOT MATCH***");
                	return 4;
            		}
   		}
	}
	
	return 1;
    }
    returnSource = read(linuxFile,&buffer,BUF_SIZE));

    if(returnSource < 1)

}

/* 
[0] command
[1] local file path (linux)
[2] our file name
[3] file directory

1. create new file --> createFile(...)
2. get index of new file --> fileIndex = getIndex(...)
3. get file size of the file we want to copy
4. find empty LBA --> emptyLBAIndex
5. read blockSize # of bytes from linux file --> copyBuffer = malloc(blocksize) {this line might not be needed}
                                             --> FILE file = open(command.args[1])
                                             --> copyBuffer = file.readNbytes(blockSize);
6. write buffer back to the LBA --> LBAwrite(copyBuffer, 1, emptyLBAIndex)
7. add emptyLBAIndex as child to new file --> addChild(emptyLBAIndex, fileIndex, volume);
8. free(mallocs)...

NOTE: I would write a function in structs called addBody(fileIndex, blockSize, linuxFileSize) --> adds a body to a file
						 addBody(230, 512, 1024) --> for(2 LBAs) 
						 				--> find free block
						 				--> write linux buffer to LBA
										--> addChild to fileIndex
						                         	
*/
