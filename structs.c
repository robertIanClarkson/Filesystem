#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <errno.h>
#include <math.h>

#include "./low/fsLow.h"
#include "structs.h"

void initializeLBA(char* buffer, char ch, int n) {
    for(int i = 0; i < n; i++) {
        buffer[i] = ch;
    }
}

int getIndex(char* key, struct filesystem_volume volume) {
    /* create a 16 char word for comparing */
    for(int i = strlen(key); i < 16; i++) {
        key[i] = '-';
    }

    /* Find the parent LBA */
    uint64_t result;
    char* buffer = malloc(volume.blockSize);
    char* name = malloc(16);
    for(int i = 0; i < volume.blockCount; i++) { 
        result = LBAread(buffer, 1, i);
        for(int j = 0; j < 16; j++) {
            name[j] = buffer[j];
        }
        if(strcmp(name, key) == 0) {
            free(buffer);
            free(name);
            return i; 
        }
    }
    free(buffer);
    free(name);
    return -1;
}

// 1
int addName(char* name, char* buffer) {
    int len = strlen(name);
    if(len <= 16) { 
        /* first line of block */
        for(int i=0; i < strlen(name); i++) {
            buffer[i] = name[i];
        }
        return 1;
    }
    return 0;
}

// 2
int addType(char* type, char* buffer) {
    int len = strlen(type);
    if(len <= 16) {
        /* second line of block */
        for(int i=16; i < (16+strlen(type)); i++) {
            buffer[i] = type[i-16];
        }
        return 1;
    }
    return 0;
}

// 3
int connectMetaData(int index, char* buffer) {
    /* convert index int to string */
    char* str = malloc(16);
    sprintf(str, "%d", index);
    int len = strlen(str);

    /* make sure length is less than 17 chars long */
    if(len > 16){ 
        printf("***Metadata index too large (is > than 16 digits)***\n");
        free(str);
        return 0;
    } 

    /* write to buffer */
    int lineStart = (16*2);
    for(int i = lineStart; i < (lineStart + len); i++) {
        buffer[i] = str[i - lineStart];
    }

    return 1;
}

// 4
int addChild(int child, int parent, struct filesystem_volume volume) {
    /* read parent LBA  into buffer so we can alter */
    char* buffer = malloc(volume.blockSize);
    int retVal = LBAread(buffer, 1, parent);
    // need to add check
    
    /* loop through available lines */
    int lineStart = (16*3);
    int i;
    for(i = lineStart; i < volume.blockSize; i = i + 16) {
        /* find an empty line to add child index */
        if(buffer[i] == '-') { 
            printf("  - addChild at index: %d\n", i);
            break;
        }
    }

    /* get str value of line */
    char* str = malloc(16);
    sprintf(str, "%d", child);
    int len = strlen(str);

    if(len > 16){ // check
        printf("***Child index too large (is > than 16 digits)***\n");
        free(buffer);
        free(str);
        return 0;
    } 

    /* add str to buffer */
    for(int j = i; j < (i + len); j++) {
        buffer[j] = str[j - i];
    }

    /* write updated buffer */
    retVal = LBAwrite(buffer, 1, parent);

    return 1;
}



