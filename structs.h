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
File: structs.h
Description: This is the header for the structs. And these are the function
declaration.
**************************************************************/
#ifndef stucts_h
#define stucts_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#define MAX_ARGS 8
#define ARG_LENGTH 32 // CHAR

struct filesystem_volume {
    char* filename;
    uint64_t volumeSize;
	uint64_t blockSize;
    uint64_t blockCount;
    uint64_t map_start;
    uint64_t file_start;
    int retVal;
};

struct arguments {
    char args[MAX_ARGS][ARG_LENGTH];
    char* opt;
    int argc;
};

/* initialize all bytes in 'buffer' with 'ch' where n is the size of buffer */
void initializeLBA(char* buffer, char ch, int n);

/* return the index of the LBA */
int getIndex(char* key, struct filesystem_volume volume);

/* line 1 of LBA */
/* Name can only be 16 characters long */
int addName(char* name, char* buffer);

/* line 2 of LBA */
/* Type can only be 16 characters long */
int addType(char* type, char* buffer);

/* line 3 of LBA */
int connectMetaData(int index, char* buffer);

/* line 4 to 32 of LBA */
int addChild(int child, int parent, struct filesystem_volume volume);

/* return 0 if line empty, 1 if line not empty */
int getLine(char* buffer, char* line, int startIndex);

/* return 0 if line empty, 1 if line not empty */
int getName(char* buffer, char* name);

/* return 0 if line empty, 1 if line not empty */
int getType(char* buffer, char* type);

/* returns 1 if it is the LBA, 0 if it isnt */
int LBAis(struct filesystem_volume volume, int index, char* name, char* type);

/* delete line(x16 char) at 'linestart' from 'buffer' and replace with 'initChar' */
void deleteLine(char* buffer, int lineStart, char initChar);

/* returns the next empty index in volume.map[index] */
int getNextEmptyLBA(struct filesystem_volume volume);

/* volume.map[i] = 0 */
void setMap(int at, char ch, struct filesystem_volume volume); // char

/* volume.map[i] */
char getMap(int at, struct filesystem_volume volume); // char

int LBAfreeCount(struct filesystem_volume volume);

long getFileSize(char *filename);

void readNBytes(char* buffer, char* name, int startIndex, int readAmount);

long getNumberOfBytes(const char *name);

#endif /* stucts_h */
