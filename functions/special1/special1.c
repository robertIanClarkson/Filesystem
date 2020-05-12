/**************************************************************
Class: CSC-415-03 Spring 2020
Group Name: Orphaned Zombies
Name: Stanley Brooks
Student ID: 918764527
Name: Cameron Harte
Student ID: 918245645
Name: Robert Clarkson
Student ID: 915433914
Name: Michael Zheng
Student ID: 917581488
Project: Assignment 3 – File System
File: special1.c
Description: This function takes 3 arguments source file name, the 
file from linux name and the folder name you want it to be added to.
The purpose of this function is to copy a file of any type in LINUX to our filesystem.
**************************************************************/
#include "special1.h"
/* one to copy from the normal filesystem to your filesystem */
/* command = "special1 sourceFile ourFileName ourFileDirectory" */

int special1(struct filesystem_volume volume, struct arguments command) {
    ssize_t returnSource;

    /* check if command.argc != 4 */
    if(command.argc < 4) {
        printf("\t***ERROR - TOO FEW ARGS***\n");
        return 0; // check
    }
    else if(command.argc > 4) {
	    printf("\t***ERROR - TOO MANY ARGS***\n");
	    return 0; //check
    }

    char* sourceFile = command.args[1];
    char* ourFileName = command.args[2];
    char* ourFileDirectory = command.args[3];
	
    printf("\tLINUX File: %s of File: %s in Directory: %s\n", sourceFile, ourFileName, ourFileDirectory);

    // how many blocks the file is 
    int totalSize;
    int totalBlocks;

    // declare stat variable
    struct stat st; 

    // check if linux file exists
    if(stat(sourceFile, &st) != 0) {
        printf("\t***ERROR LINUX FILE DNE***\n");
        return 0;
    }

    // a new File is created using the touch command, with the name and directory coming from args
    struct arguments newArgs;
    newArgs.argc = 3;
    strcpy(newArgs.args[0], "touch");
    strcpy(newArgs.args[1], ourFileName);
    strcpy(newArgs.args[2], ourFileDirectory);
    if(createFile(volume, newArgs) == 0)
        printf("\t***ERROR - FAILED TO CREATE NEW FILE***\n");

    // get index of new file created
    int fileIndex = getIndex(ourFileName, volume);
    if(fileIndex < 0) {
        printf("\t***ERROR - INDEX COULD NOT BE FOUND***");
        return 0;
    }

    // get filesize of linux file
    long int linuxFileSize = getFileSize(sourceFile);

    // get number of LBA we will need
    int LBAcount = ceil(((double) linuxFileSize) / ((double) volume.blockSize));
   
    // main logic loop 
    int emptyBlock;
    int startIndex;
    int readSize;
    char* buffer = malloc(volume.blockSize);
    for(int i = 0; i < LBAcount; i++) {
        // get a free block
        emptyBlock = getNextEmptyLBA(volume);
        setMap(emptyBlock, '1', volume);

        // read file into buffer
        initializeLBA(buffer, '-', volume.blockSize);
        readNBytes(buffer, sourceFile, (i * volume.blockSize), volume.blockSize);
        LBAwrite(buffer, 1, emptyBlock);

        // add block to file
        addChild(emptyBlock, fileIndex, volume);
    }

    // a new File is created using the set command, with the name, directory, and totalSize coming from args
    char totalSizeBuffer[linuxFileSize];
    sprintf(totalSizeBuffer, "%ld", linuxFileSize);
    struct arguments newArgs2;
    newArgs2.argc = 5;
    strcpy(newArgs2.args[0], "set");
    strcpy(newArgs2.args[1], ourFileName);
    strcpy(newArgs2.args[2], ourFileDirectory);
    strcpy(newArgs2.args[3], "^Total Size");
    strcpy(newArgs2.args[4], totalSizeBuffer);
    if(setMetaData(volume, newArgs2) == 0)
        printf("***ERROR - FAILED TO SET METADATA***\n");
        return 0;

    free(buffer);

    return 1;
}