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
File: special2.h
Description: This is the header for the special2 function. And these are the function
declaration.
**************************************************************/
#ifndef special2_h
#define special2_h

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include "../../structs.h"
#include "../../low/fsLow.h"

int special2(struct filesystem_volume volume, struct arguments command);

#endif /* special2_h */
