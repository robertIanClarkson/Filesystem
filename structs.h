#ifndef stucts_h
#define stucts_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ARGS 8
#define ARG_LENGTH 32 // CHAR

struct filesystem_volume {
    char* filename;
    uint64_t volumeSize;
	uint64_t blockSize;
    uint64_t blockCount;
    int* map;
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
int connectMetaData(int index, char* buffer, struct filesystem_volume volume);

/* line 4 to 32 of LBA */
int addChild(int child, int parent);

#endif /* stucts_h */