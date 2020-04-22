#include "removeFile.h"

int removeFile(struct filesystem_volume volume, struct arguments command) {
    // Checking argc 
    if(command.argc != 3) {
        printf("***Not Enough Args***\n");
        return 0; // check
    }

    // Get args 
    char* name = command.args[1];
    char* folder = command.args[2]; // the parent is the directory folder

    //char* buffer = malloc(volume.blockSize);

    printf("Deleting filename: %s in directory: %s\n", name, folder);

    // Reinitialize LBA
    //printf("Reinitalizing the LBA back to default\n");
    //initializeLBA(buffer, '.', volume.blockSize);

    // Get index of folder 
    printf("- Looking for parent folder\n");
    int parentIndex = getIndex(folder, volume);
    if (parentIndex < 0) {
        printf("***FOLDER DNE***\n");
        return 0;
    } 
    printf("- Parent directory folder index: %d\n", parentIndex);

    char* buffer = malloc(volume.blockSize);
    char* cleanBuffer = malloc(volume.blockSize);
    char* metaBuffer = malloc(volume.blockSize);

    initializeLBA(cleanBuffer, '.', volume.blockSize);
    char* indexOfFile = malloc(16);
    char* indexOfBody = malloc(16);
    for(int i = 48; i < volume.blockSize; i = i + 16) { // each line of parent folder
        if(getLine(buffer, indexOfFile, i) == 0) continue;
        if(LBAis(volume, atoi(indexOfFile), name, "file") == 1) { // is the index of the file we want to delete    
            LBAread(buffer, 1, atoi(indexOfFile));
            for(int j = 48; j < volume.blockSize; j = j + 16) { // each line of file we are removing
                if(getLine(buffer, indexOfBody, i) == 0) continue; // skip all empty lines
                LBAwrite(cleanBuffer, 1, atoi(indexOfBody)); // re-initializing the body LBA
                volume.map[atoi(indexOfBody)] = 0; // set body LBA to free
            }
            LBAwrite(cleanBuffer, 1, atoi(indexOfFile)); // re-initializing the file LBA
            volume.map[atoi(indexOfFile)] = 0; // set file LBA to free

            LBAread(metaBuffer,1, (atoi(indexOfFile) + 1));
            initializeLBA(metaBuffer, '.', volume.blockSize); 
            LBAwrite(metaBuffer,1,(atoi(indexOfFile) + 1));
            volume.map[atoi(indexOfFile)+1] = 0;

            free(buffer);
            free(cleanBuffer);
            free(indexOfFile);
            free(indexOfBody);

            printf("File removed!\n");
            return 1;
        }
    }
    
    free(buffer);
    free(cleanBuffer);
    free(indexOfFile);
    free(indexOfBody);

    printf("- COMPLETE\n");
    return 0; 

    
}
