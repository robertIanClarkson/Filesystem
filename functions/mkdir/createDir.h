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
File: createDir.h
Description: This is the header for the createDir function. And these are the function
declaration.
**************************************************************/
#ifndef createDir_h
#define createDir_h

#include <stdio.h>
#include "../../structs.h"
#include "../../low/fsLow.h"

int createDir(struct filesystem_volume volume, struct arguments command);

#endif /* createDir_h */
