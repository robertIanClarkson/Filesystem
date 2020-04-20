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

    char* buffer = malloc(volume.blockSize);

    printf("Deleting filename: %s in directory: %s\n", name, folder);

    // Reinitialize LBA
    printf("Reinitalizing the LBA back to default\n");
    initializeLBA(buffer, '.', volume.blockSize);

    // Get index of folder 
    printf("- Looking for parent folder\n");
    int parentIndex = getIndex(folder, volume);
    if (parentIndex < 0) {
        printf("***FOLDER DNE***\n");
        return 0;
    } 
    printf("- Parent directory folder index: %d\n", parentIndex);

    /*******************Robert*************************
     * 1. remove child reference from parent
     * 2. read all #s from line 3 to 32 of LBA from file we are removing
     *         - reinitialize each # (# is an index) to '.'
     *         - set volume.map[#] = 0
     * 3. Now reinitialize LBA of the file we are removing to '.'
     * 4. set volume.map[fileWeAreRemoving] = 0
     * *****************Robert*************************/

    /* Once the index of the directory is found, locate the files index and set 
       the map to 0 for body and 0 for both LBA */
    if (getName(buffer, name) == 1) {
        // Remove reference to parent 
        if (removeChild(parentIndex, volume) != 1) return 0;
        volume.map[parentIndex+1] = 0; // file exists so its the next index
        //volume.map[parentIndex+2] = 0; // first body index
        //volume.map[parentIndex+3] = 0; // second body index
    } else 
        return 0;    

    printf("- COMPLETE\n");
    return 1;
}