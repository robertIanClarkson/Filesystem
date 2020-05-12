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
File: special1.h
Description: This is the header for the special1 function. And these are the function
declaration.
**************************************************************/
#ifndef special1_h
#define special1_h

#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "../../structs.h"
#include "../../low/fsLow.h"
#include "../touch/createFile.h"
#include "../set/setMetaData.h"

int special1(struct filesystem_volume volume, struct arguments command);

#endif /* special1_h */
