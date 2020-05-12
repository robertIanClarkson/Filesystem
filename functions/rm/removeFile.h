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
File: removeFile.h
Description: This is the header for the removeFile function. And these are the function
declaration.
**************************************************************/
#ifndef removeFile_h
#define removeFile_h

#include <stdio.h>
#include "../../structs.h"
#include "../../low/fsLow.h"

int removeFile(struct filesystem_volume volume, struct arguments command);

#endif /* removeFile_h */
