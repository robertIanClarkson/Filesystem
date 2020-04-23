#include "setMetaData.h"

/* Filesystem_Prompt$ set 'hello' 'world' 'author' 'foo bar' */

int setMetaData(struct filesystem_volume volume, struct arguments command) {
    /* Checking argc */
    if(command.argc != 5) {
        printf("***Not Enough Args***\n");
        return 0; // check
    }

    /* Get args */
    char* file = command.args[1];
    char* directory = command.args[2];
    char* category = command.args[3];
    char* info = command.args[4];

    /* Get index of 'directory' */
    printf("- Looking for directory\n");
    int directoryIndex = getIndex(directory, volume);
    if(directoryIndex < 0) {
        printf("***FOLDER DNE***\n");
        return 0;
    }
    printf("- directory index: %d\n", directoryIndex);

    return 1;
}