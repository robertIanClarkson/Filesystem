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
File: createDir.c
Description: This function takes 2 arguments name of the folder and the 
destination of the folder. It creates a folder in the folder that you 
want to put it in.
**************************************************************/
#include "createDir.h"

/* opt newDirName parentDirName */
int createDir(struct filesystem_volume volume, struct arguments command) {
    /* Checking argc */
    if(command.argc < 3) {
        printf("\t***ERROR - TOO FEW ARGS***\n");
        return 0; // check
    }
    else if(command.argc > 3){
	printf("\t***ERROR - TOO MANY ARGS***\n");
	return 0; //check
    }
    /* Get args */
    char* name     = command.args[1];
    char* parent   = command.args[2];
    
    printf("\tCreating New Directory: %s in Directory: %s\n", name, parent);

    /* Find the first LBA that is empty */
    int i;
    for(i = 0; i < volume.blockCount; i++) {
        if(getMap(i, volume) == '0') break;
    }

    /* mark LBA as used */
    setMap(i, '1', volume);

    /* Find another LBA for that is empty for metadata */
    int j;
    for(j = 0; j < volume.blockCount; j++) {
        if(getMap(j, volume) == '0') break;
    }

    /* mark LBA as used */
    setMap(j, '1', volume);

    /* Get parent LBA position */
    int parentIndex = getIndex(parent, volume);
    if(parentIndex < 0) {
        printf("\t***ERROR - PARENT FOLDER DNE***\n");
        return 0;
    }
     
    /* Create Index LBA */
    char* buffer = malloc(volume.blockSize);
    initializeLBA(buffer, '-', volume.blockSize);
    if(addName(name, buffer) != 1) return 0; // check
    if(addType("folder", buffer) != 1) return 0; // check
    if(connectMetaData(j, buffer) != 1) return 0; // check
    LBAwrite(buffer, 1, i);
    free(buffer);

    /* create metadata block */
    char* metaBuffer = malloc(volume.blockSize);
    initializeLBA(metaBuffer, '*', volume.blockSize);
    if(addName(name, metaBuffer) != 1) return 0; // check
    if(addType("metadata", metaBuffer) != 1) return 0; // check
    LBAwrite(metaBuffer, 1, j);
    free(metaBuffer);

    /* update parent LBA with child LBA */
    if(addChild(i, parentIndex, volume) != 1) return 0;

    return 1;
}
