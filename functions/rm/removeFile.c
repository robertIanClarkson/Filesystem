#include "removeFile.h"

int removeFile(struct filesystem_volume volume, struct arguments command) {
    // Checking argc 
    if(command.argc != 3) {
        printf("***Not Enough Args***\n");
        return 0; // check
    }

    // Get args 
    char* name = command.args[1];
    char* folder = command.args[2]; // tje parent is the directory folder

    char* buffer = malloc(volume.blockSize);

    printf("Deleting filename: %s in directory: %s\n", name, folder);

    // Get index of folder 
    printf("- Looking for parent folder\n");
    int parentIndex = getIndex(folder, volume);
    if (parentIndex < 0) {
        printf("***FOLDER DNE***\n");
        return 0;
    } 
    printf("- Directory folder index: %d\n", parentIndex);

    /* Once the index of the directory is found, locate the files index and set 
       the map to 0 for body and 0 for both LBA */
    if (getName(buffer, name) == 1) {
        volume.map[parentIndex+1] = 0; // file exists so its the next index
        volume.map[parentIndex+2] = 0; // first body index
        volume.map[parentIndex+3] = 0; // second body index
    } else 
        return 0;
/////////// Different way to go about deleting the file, reset all lines back to default ///////////////////
    /*deleteName(buffer);
    deleteType(buffer);
    disconnectMetaData(buffer);*/

    printf("- COMPLETE\n");
    return 1;
}