
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
#ifndef createFile_h
#define createFile_h

#include <stdio.h>
#include "../../structs.h"
#include "../../low/fsLow.h"

int createFile(struct filesystem_volume volume, struct arguments command);

#endif /* createFile_h */
