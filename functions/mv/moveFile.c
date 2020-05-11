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
File: copyFile.c
Description: This function takes 4 arguments, source file and folder, and a destination 
file and folder.  It copies the contents of the source file to the destination file, while
keeping the original file intact.
**************************************************************/
#include "moveFile.h"

int moveFile(struct filesystem_volume volume, struct arguments command) {
    
    /* Checking argc */
    if(command.argc < 5) {
        printf("\t***Not Enough Args***\n");
        return 0; // check
    }
    else if(command.argc > 5){
	printf("\t***TOO many Args***\n");
	return 0; //check
    }

    /* copy file */
    strcpy(command.args[0], "cp");
    if (copyFile(volume, command) == 0) {
        printf("\t***Error Copying File***\n");
        return 0;
    }     

    /* remove file */
    strcpy(command.args[0], "rm");
    command.argc = 3;
    if (removeFile(volume, command) == 0) {
        printf("\t***Error Removing File***\n");
        return 0;
    }

    //printf("***COMPLETE***\n\n");
    return 1;
}
