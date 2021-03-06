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
File: copyFile.h
Description: This is the header for the copyFile function. And these are the function
declaration.
**************************************************************/
#ifndef copyFile_h
#define copyFile_h

#include <stdio.h>
#include "../../structs.h"
#include "../../low/fsLow.h"
#include "../touch/createFile.h"

int copyFile(struct filesystem_volume volume, struct arguments command);

#endif /* copyFile_h */
