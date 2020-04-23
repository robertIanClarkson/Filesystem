#include "copyFile.h"

/* (copy file 'foo' as 'blah' from directory 'hello' to directory 'world') */
/* Filesystem_Prompt$ mkdir hello root */
/* Filesystem_Prompt$ mkdir world root */
/* Filesystem_Prompt$ touch foo hello */
/* Filesystem_Prompt$ cp foo hello bar world */
int copyFile(struct filesystem_volume volume, struct arguments command) {
    
    /* Checking argc */
    if(command.argc != 5) {
        printf("***Not Enough Args***\n");
        return 0; // check
    }

    /* Get args */
    char* oldFile = command.args[1];
    char* oldFolder = command.args[2];
    char* newFile = command.args[3];
    char* newFolder = command.args[4];
    printf("* copy file: %s\n", oldFile);
    printf("* from folder: %s\n", oldFolder);
    printf("* as file: %s\n", newFile);
    printf("* to folder: %s\n", newFolder);

    /* Get index of 'keyFolder' */
    printf("- Looking for old folder\n");
    int oldFolderIndex = getIndex(oldFolder, volume);
    if(oldFolderIndex < 0) {
        printf("***FOLDER DNE***\n");
        return 0;
    }
    printf("- old folder index: %d\n", oldFolderIndex);

    /* get old folder buffer */
    char* oldFolderBuffer = malloc(volume.blockSize);
    int foo = LBAread(oldFolderBuffer, 1, oldFolderIndex);

    /* init */
    printf("- Getting buffer of \"%s\"\n", oldFile);
    char* childBuffer = malloc(volume.blockSize);
    char* name = malloc(16);
    char* type = malloc(16);
    char* childIndex = malloc(16);
    for(int i = 48; i < volume.blockSize; i = i + 16) { // looking at each child of parent LBA
        if(getLine(oldFolderBuffer, childIndex, i) == 0) continue;
        /* we have child index */
        foo = LBAread(childBuffer, 1, atoi(childIndex));
        /* checkif childBuffer is a folder or file */
        memset(type, 0, 16);
        memset(name, 0, 16);
        getType(childBuffer, type); // read the type from the childBuffer into "type"
        if(strcmp(type, "file") == 0) { // child is a file
            getName(childBuffer, name); // read the type from the childBuffer into "type"
            if(strcmp(name, oldFile) == 0) { // THIS IS THE ONE WE WILL COPY 
                break;
            }
        }
    }
    
    /* creating the new file */
    printf("- Creating new File \"%s\" in \"%s\"\n", newFile, newFolder);
    struct arguments newArgs;
    newArgs.argc = 3;
    strcpy(newArgs.args[0], "touch");
    strcpy(newArgs.args[1], newFile);
    strcpy(newArgs.args[2], newFolder);
    if(createFile(volume, newArgs) == 0) {
        printf("***FAILED TO CREATE NEW FILE***\n");
        free(name);
        free(type);
        free(childBuffer);
        free(childIndex);
        free(oldFolderBuffer);
        return 0;
    }

    /* childBuffer = oldFile */
    /* newFileBuffer = newFile */
    printf("- Copying body of \"%s\" to \"%s\"\n", oldFile, newFile);
    char* newFileBuffer = malloc(volume.blockSize);
    int newFileIndex = getIndex(newFile, volume);
    LBAread(newFileBuffer, 1, newFileIndex);

    /* copy the file */
    char* copyBuffer = malloc(volume.blockSize);
    char* oldFileLine = malloc(16);
    char* newFileLine = malloc(16);
    int newBodyIndex;
    for(int i = 48; i < volume.blockSize; i = i + 16) {/* each line oldFile's body */
        /* get body index from oldFile */
        if(getLine(childBuffer, oldFileLine, i) == 0) continue;

        /* read old body index into buffer */
        foo = LBAread(copyBuffer, 1, atoi(oldFileLine));

        /* find an empty LBA */
        newBodyIndex = getNextEmptyLBA(volume);
        if(newBodyIndex < 0) {
            free(name);
            free(type);
            free(childBuffer);
            free(childIndex);
            free(newFileLine);
            free(newFileBuffer);
            free(copyBuffer);
            free(oldFileLine);
            free(oldFolderBuffer);
            return 0;
        }

        /* write old body index into new body index */
        LBAwrite(copyBuffer, 1, newBodyIndex);

        /* mark LBA as used */
        volume.map[newBodyIndex] = 1;

        /* update newFile child as newBodyIndex */
        if(addChild(newBodyIndex, newFileIndex, volume) == 0) {
            free(name);
            free(type);
            free(childBuffer);
            free(childIndex);
            free(newFileLine);
            free(newFileBuffer);
            free(copyBuffer);
            free(oldFileLine);
            free(oldFolderBuffer);
            return 0;
        }
    }    
    free(name);
    free(type);
    free(childBuffer);
    free(childIndex);
    free(newFileLine);
    free(newFileBuffer);
    free(copyBuffer);
    free(oldFileLine);
    free(oldFolderBuffer);
    
    printf("***COMPLETE***\n\n");

    return 1;
}