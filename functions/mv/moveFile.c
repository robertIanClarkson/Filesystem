#include "moveFile.h"

int moveFile(struct filesystem_volume volume, struct arguments command) {
    
    /* Checking argc */
    if (command.argc != 5) {
        printf("***Not Enough Args***\n");
        return 0; // check
    }

    /* copy file */
    strcpy(command.args[0], "cp");
    if (copyFile(volume, command) == 0) {
        printf("***Error Copying File***\n");
        return 0;
    }     

    /* remove file */
    strcpy(command.args[0], "rm");
    command.argc = 3;
    if (removeFile(volume, command) == 0) {
        printf("***Error Removing File***\n");
        return 0;
    }

    printf("***COMPLETE***\n\n");
    return 1;
}