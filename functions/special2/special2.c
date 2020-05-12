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
File: special2.c
Description: This function takes 3 arguments, the source file and folder name, and the location and 
name of where you want the file to be.
**************************************************************/
#include "special2.h"
/* from your filesystem to the normal filesystem */
int special2(struct filesystem_volume volume, struct arguments command) {
    /* check if command.argc != 4 */
    if (command.argc < 4) {
        printf("\t***ERROR - TOO FEW ARGS***\n");
        return 0; // check
    }
    else if (command.argc > 4) {
        printf("\t***ERROR - TOO MANY ARGS***\n");
        return 0; //check
    }
    // Get args
    char *sourceFile = command.args[1];
    char *sourceDirectory = command.args[2];
    char *linuxDestinationFile = command.args[3];

    // check last character of path == '/'
    if (linuxDestinationFile[strlen(linuxDestinationFile) - 1] != '/') {
        printf("\t***ERROR - PATH IS NOT VALID***\n");
        return 0;
    }
    printf("\tLINUX File: %s of File: %s in Directory: %s\n", sourceFile, linuxDestinationFile, sourceDirectory);

    strcat(linuxDestinationFile, sourceFile);
    strcat(linuxDestinationFile, "\0");

    //GET FOLDER INDEX
    int folderIndex = getIndex(sourceDirectory, volume);
    if (folderIndex < 0) {
        printf("***ERROR - FOLDER NOT FOUND***\n");
        return 0;
    }

    //GET FILE INDEX
    char *folderBuffer = malloc(volume.blockSize);
    int temp = LBAread(folderBuffer, 1, folderIndex);

    char *childBuffer = malloc(volume.blockSize);
    char *name = malloc(16);
    char *type2 = malloc(16);
    char *fileIndex = malloc(16);
    for (int i = 48; i < volume.blockSize; i = i + 16) { // looking at each child of parent LBA
        if (getLine(folderBuffer, fileIndex, i) == 0)
            continue;
        /* we have child index */
        temp = LBAread(childBuffer, 1, atoi(fileIndex));
        /* checkif childBuffer is a folder or file */
        memset(type2, 0, 16);
        memset(name, 0, 16);
        getType(childBuffer, type2); // read the type from the childBuffer into "type"
        if (strcmp(type2, "file") == 0) {                               // child is a file
            getName(childBuffer, name); // read the type from the childBuffer into "type"
            if (strcmp(name, sourceFile) == 0) { // THIS IS THE ONE WE WILL COPY
                break;
            }
        }
    }

    // get/check source file index, -1 doesnt exist
    if (fileIndex < 0) {
        printf("***ERROR - FILE DOES NOT EXIST***\n");
        return 0;
    }

    // open linux file
    FILE *fp = fopen(linuxDestinationFile, "w");
    if (fp == NULL)
        printf("\t***ERROR - FILE NOT FOUND***\n");

    // create buffers
    char *metadataBuffer = malloc(volume.blockSize);
    char *bodyBuffer = malloc(volume.volumeSize);
    char *bufferWithoutTrail = malloc(volume.volumeSize);
    char *totalBytes = malloc(16);

    int metadataIndex = atoi(fileIndex) + 1;
    LBAread(metadataBuffer, 1, metadataIndex);

    for (int i = 32; i < volume.blockSize; i += 32) {
        if (metadataBuffer[i] == '^') {
            int j = i + 16;
            int temp = 0;
            while (metadataBuffer[j] != '*') {
                totalBytes[temp] = metadataBuffer[j];
                temp++;
                j++;
            }
            break;
        }
    }
    free(metadataBuffer);

    int totalSize = atoi(totalBytes);
    int totalLBA = (totalSize / volume.blockSize) + 1;

    LBAread(bodyBuffer, totalLBA, atoi(fileIndex) + 2);
    strncpy(bufferWithoutTrail, bodyBuffer, totalSize);
    fputs(bufferWithoutTrail, fp);

    free(bodyBuffer);
    free(bufferWithoutTrail);
    free(totalBytes);
    fclose(fp);

    return 1;
}
