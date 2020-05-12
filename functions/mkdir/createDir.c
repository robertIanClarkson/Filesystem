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
Description: This function takes 4 arguments, source file and folder, and a destination 
file and folder.  It copies the contents of the source file to the destination file, while
keeping the original file intact.
**************************************************************/
#include "createDir.h"

/* opt newDirName parentDirName */
int createDir(struct filesystem_volume volume, struct arguments command) {
    /* Checking argc */
    if(command.argc < 3) {
        printf("\t***Not Enough Args***\n");
        return 0; // check
    }
    else if(command.argc > 3){
	printf("\t***TOO many Args***\n");
	return 0; //check
    }
    /* Get args */
    char* name     = command.args[1];
    char* parent   = command.args[2];
    printf("\tNew Folder: %s\n", name);
    printf("\tIn Folder: %s\n", parent);

    /* Find the first LBA that is empty */
    // printf("- Looking for Index LBA\n");
    int i;
    for(i = 0; i < volume.blockCount; i++) {
        if(getMap(i, volume) == '0') break;
    }
    // printf("  - Empty LBA at: %d\n", i);

    /* mark LBA as used */
    // printf("  - Marking LBA as used\n");
    setMap(i, '1', volume);

    /* Find another LBA for that is empty for metadata */
    // printf("- Looking for MetaData LBA\n");
    int j;
    for(j = 0; j < volume.blockCount; j++) {
        if(getMap(j, volume) == '0') break;
    }
    // printf("  - Empty LBA at: %d\n", j);

    /* mark LBA as used */
    // printf("  - Marking LBA as used\n");
    setMap(j, '1', volume);

    /* Get parent LBA position */
    // printf("- Looking for parent folder\n");
    int parentIndex = getIndex(parent, volume);
    if(parentIndex < 0) {
        printf("\t***PARENT FOLDER DNE***\n");
        return 0;
    }
    // printf("  - Found parent folder\n");
     
    /* Create Index LBA */
    // printf("- Creating Buffer\n");
    char* buffer = malloc(volume.blockSize);
    initializeLBA(buffer, '-', volume.blockSize);
    // printf("  - Adding Name: %s\n", name);
    if(addName(name, buffer) != 1) return 0; // check
    // printf("  - Adding Type: folder\n");
    if(addType("folder", buffer) != 1) return 0; // check
    // printf("  - Connecting Metadata LBA index\n");
    if(connectMetaData(j, buffer) != 1) return 0; // check
    // printf("  - Writing Buffer to LBA: %d\n", i);
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
    // printf("- Updating parent folder\n");
    if(addChild(i, parentIndex, volume) != 1) return 0;

    // printf("***COMPLETE***\n\n");
    return 1;
}
