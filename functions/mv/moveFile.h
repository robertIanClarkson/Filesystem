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
File: moveFile.h
Description: This is the header for the moveFile function. And these are the function
declaration
**************************************************************/
#ifndef moveFile_h
#define moveFile_h

#include <stdio.h>
#include <string.h>
#include "../../structs.h"
#include "../../low/fsLow.h"
#include "../cp/copyFile.h"
#include "../rm/removeFile.h"

int moveFile(struct filesystem_volume volume, struct arguments command);

#endif /* moveFile_h */
