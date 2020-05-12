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
File: createFile.c
Description: This function takes 2 arguments the name you want to 
name your file and the location of you want to put it.
**************************************************************/
#include "createFile.h"

int createFile(struct filesystem_volume volume, struct arguments command) {
    // Checking argc 
    if(command.argc < 3) {
        printf("\t***Not Enough Args***\n");
        return 0; // check
    }
    else if(command.argc > 3){
	printf("\t***TOO many Args***\n");
	return 0; //check
    }

    // Get args 
    char* name = command.args[1];
    char* parent = command.args[2]; // the parent is the directory folder
    printf("\tFile name: %s\n", name);
    printf("\tTarget Directory: %s\n", parent);

    printf("\tCreating filename: %s in directory: %s\n", name, parent);

    // Get parent LBA position
    int parentIndex = getIndex(parent, volume);
    if (parentIndex < 0) {
        printf("\t***PARENT FOLDER DNE***\n");
        return 0;
    } 
    // Find the first LBA that is empty 
    int i;
    for(i = 0; i < volume.blockCount; i++)
        if(getMap(i, volume) == '0') break;

    // mark LBA as used 
    setMap(i, '1', volume);

    // Find another LBA for that is empty for metadata 
    int j;
    for(j = 0; j < volume.blockCount; j++) 
        if(getMap(j, volume) == '0') break;

    // mark LBA as used 
    setMap(j, '1', volume);

    // Create Index LBA 
    char* buffer = malloc(volume.blockSize);
    initializeLBA(buffer, '-', volume.blockSize);
    if(addName(name, buffer) != 1) return 0; // check
    if(addType("file", buffer) != 1) return 0; // check
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
    
    // update parent LBA with child LBA
    if (addChild(i, parentIndex, volume) != 1) return 0;
    
    return 1;
}
