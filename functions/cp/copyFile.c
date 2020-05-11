#include "copyFile.h"

/**************************************************************
Class: CSC-415-03 Spring 2020
Group Name: Orphaned Zombies
Name: Stanley Brooks
Student ID: 918764527
Name: Cameron Harte
Student ID:
Name: Robert Clarkson
Student ID:
Name: Michael Zheng
Student ID:
Project: <project name, like Assignment 3 – File System
File: copyFile.c
Description: This function takes 4 arguments, source file and folder, and a destination file and folder.  It copies the contents of the source file to the destination file, while keeping the original file intact.
**************************************************************/

int copyFile(struct filesystem_volume volume, struct arguments command) {
    
    /* Checking argc */
    if(command.argc < 5) {
        printf("\t***Not Enough Args***\n");
        return 0; 
    }
    else if(command.argc > 5){
	printf("\t***TOO many Args***\n");
	return 0; 
    }

    /* Get args */
    char* oldFile = command.args[1];
    char* oldFolder = command.args[2];
    char* newFile = command.args[3];
    char* newFolder = command.args[4];

    /* Get index of 'keyFolder' */
    int oldFolderIndex = getIndex(oldFolder, volume);
    if(oldFolderIndex < 0) {
        printf("\t***FOLDER DNE***\n");
        return 0;
    }

    /* get old folder buffer */
    char* oldFolderBuffer = malloc(volume.blockSize);
    int foo = LBAread(oldFolderBuffer, 1, oldFolderIndex);

    /* init */
    char* childBuffer = malloc(volume.blockSize);
    char* name = malloc(16);
    char* type = malloc(16);
    char* childIndex = malloc(16);
    for(int i = 48; i < volume.blockSize; i = i + 16) { // looking at each child of parent LBA
        if(getLine(oldFolderBuffer, childIndex, i) == 0) continue;
        foo = LBAread(childBuffer, 1, atoi(childIndex)); /* we have child index */

        memset(type, 0, 16);
        memset(name, 0, 16);
        getType(childBuffer, type); // read the type from the childBuffer into "type"  ----checkif childBuffer is a folder or file
        if(strcmp(type, "file") == 0) { // child is a file
            getName(childBuffer, name); // read the type from the childBuffer into "type"
            if(strcmp(name, oldFile) == 0) { // THIS IS THE ONE WE WILL COPY 
                break;
            }
        }
    }
    
    /* creating the new file */
    struct arguments newArgs;
    newArgs.argc = 3;
    strcpy(newArgs.args[0], "touch");
    strcpy(newArgs.args[1], newFile);
    strcpy(newArgs.args[2], newFolder);
    if(createFile(volume, newArgs) == 0) {
        printf("\t***FAILED TO CREATE NEW FILE***\n");
        free(name);
        free(type);
        free(childBuffer);
        free(childIndex);
        free(oldFolderBuffer);
        return 0;
    }

    char* newFileBuffer = malloc(volume.blockSize);
    int newFileIndex = getIndex(newFile, volume);
    LBAread(newFileBuffer, 1, newFileIndex);

    /* copy the file */
    char* copyBuffer = malloc(volume.blockSize);
    char* oldFileLine = malloc(16);
    char* newFileLine = malloc(16);
    int newBodyIndex;
    for(int i = 48; i < volume.blockSize; i = i + 16) {/* each line oldFile's body */
        if(getLine(childBuffer, oldFileLine, i) == 0) continue; // get body index from oldFile


        foo = LBAread(copyBuffer, 1, atoi(oldFileLine));  // read old body index into buffer
        /* find an empty LBA */
        newBodyIndex = getNextEmptyLBA(volume);
        if(newBodyIndex < 0) {
            free(name);
            free(type);
            free(childBuffer);
            free(childIndex);
            free(newFileLine);
            free(newFileBuffer);
            free(copyBuffer);
            free(oldFileLine);
            free(oldFolderBuffer);
            return 0;
        }

        /* write old body index into new body index */
        LBAwrite(copyBuffer, 1, newBodyIndex);

        /* mark LBA as used */
        setMap(newBodyIndex, '1', volume);

        /* update newFile child as newBodyIndex */
        if(addChild(newBodyIndex, newFileIndex, volume) == 0) {
            free(name);
            free(type);
            free(childBuffer);
            free(childIndex);
            free(newFileLine);
            free(newFileBuffer);
            free(copyBuffer);
            free(oldFileLine);
            free(oldFolderBuffer);
		
            return 0;
        }
    }    
    free(name);
    free(type);
    free(childBuffer);
    free(childIndex);
    free(newFileLine);
    free(newFileBuffer);
    free(copyBuffer);
    free(oldFileLine);
    free(oldFolderBuffer);
	
    return 1;
}
