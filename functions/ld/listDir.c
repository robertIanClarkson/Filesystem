#include "listDir.h"

int listDir(struct filesystem_volume volume, struct arguments command) {

    /* check if command.argc != 2 */
        if(command.argc < 2) {
        printf("***Not Enough Args***\n");
        return 0; // check
    }
    else if(command.argc > 2){
	printf("***TOO many Args***\n");
	return 0; //check
    }
    
    char* parentFolder = command.args[1];

    // check arg
    int parentIndex = getIndex(parentFolder, volume);

    // get parent buffer
    char* parentBuffer = malloc(volume.blockSize);
    int foo = LBAread(parentBuffer, 1, parentIndex);

    // init child buffer
    char* childBuffer = malloc(volume.blockSize);

    // init line
    char* line = malloc(16);

    // go through each line of folder
    char* name = malloc(16);
    char* type = malloc(16);
    for(int i = 48; i < volume.blockSize; i = i + 16) {
        if(getLine(parentBuffer, line, i) == 0) continue;
        foo = LBAread(childBuffer, 1, atoi(line));
        memset(type,0,16);
        memset(name,0,16);
        if(getType(childBuffer, type) == 0) {
            printf("***File has no type***\n");
            free(parentBuffer);
            free(childBuffer);
            free(line);
            free(name);
            free(type);
            return 0;
        }
        if(getName(childBuffer, name) == 0) {
            printf("***File has no name***\n");
            free(parentBuffer);
            free(childBuffer);
            free(line);
            free(name);
            free(type);
            return 0;
        }
        if(strcmp(type, "file") == 0) { // child is of type file
            printf("-- %s\n", name);   
        }
        if(strcmp(type, "folder") == 0) { // child is of type file
            printf("- %s\n", name);   
        }
        
    }

    free(parentBuffer);
    free(childBuffer);
    free(line);
    free(name);
    free(type);

    printf("***COMPLETE***\n\n"); 

    return 1;
}
