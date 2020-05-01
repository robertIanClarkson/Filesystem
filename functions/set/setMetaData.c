#include "setMetaData.h"

int setMetaData(struct filesystem_volume volume, struct arguments command) {

    //CHECK ARG COUNT
   if(command.argc > 5){
       printf("***ERROR - TOO MANY ARGS***\n");
       return 0;
   }
   else if (command.argc < 5){
       printf("***ERROR - TOO FEW ARGS***\n");
       return 0;
   }


   //GET ARGS
    char* file = command.args[1];
    char* folder = command.args[2];
    char* type = command.args[3];
    char* data = command.args[4];

    if(strlen(type) > 16) {
        printf("***ERROR - METADATA TYPE TOO LONG***\n");
        return 0;
    }
        if(strlen(data) > 16) {
        printf("***ERROR - METADATA DATA TOO LONG***\n");
        return 0;
    }
    printf("The File: %s\n", file);
    printf("In Folder: %s\n", folder);
    printf("The Type: %s\n", type);
    printf("The Data: %s\n", data);


    //GET FOLDER INDEX
    int folderIndex = getIndex(folder, volume);
    if(folderIndex < 0) {
        printf("***ERROR - FOLDER NOT FOUND***\n");
        return 0;
    }


    //GET FILE INDEX
    char* folderBuffer = malloc(volume.blockSize);
    int temp = LBAread(folderBuffer, 1, folderIndex);

    char* childBuffer = malloc(volume.blockSize);
    char* name = malloc(16);
    char* type2 = malloc(16);
    char* fileIndex = malloc(16);
    for(int i = 48; i < volume.blockSize; i = i + 16) { // looking at each child of parent LBA
        if(getLine(folderBuffer, fileIndex, i) == 0) continue;
        /* we have child index */
        temp = LBAread(childBuffer, 1, atoi(fileIndex));
        /* checkif childBuffer is a folder or file */
        memset(type2, 0, 16);
        memset(name, 0, 16);
        getType(childBuffer, type2); // read the type from the childBuffer into "type"
        if(strcmp(type2, "file") == 0) { // child is a file
            getName(childBuffer, name); // read the type from the childBuffer into "type"
            if(strcmp(name, file) == 0) { // THIS IS THE ONE WE WILL COPY 
                break;
            }
        }
    }
    if(fileIndex < 0) {
        printf("***ERROR - FILE NOT FOUND***\n");
        return 0;
    }


    //GET METADATA INDEX
    int metadataIndex = atoi(fileIndex) + 1;


    //WRITE ARGS 3 & 4 TO SEPERATE LINES OF METADATA LBA    
    char* buffer = malloc(volume.blockSize); //to be written
    char* metadataBuffer = malloc(volume.blockSize); //MD block

    LBAread(metadataBuffer, 1, metadataIndex); //reads entire MD block

    strncat(buffer, metadataBuffer, 32); // copy header lines into buffer

    for(int i = 32; i < volume.blockSize; i += 32) { // search for first empty line
        if(metadataBuffer[i] == '*') {
            strcat(buffer, type);
            for(int j = 0; j < (16 - strlen(type));  j++) { //adding type to buffer string
                strcat(buffer, "*"); }

            strcat(buffer, data);
            for(int k = 0; k < (16 - strlen(data));  k++) { //adding data to buffer string
                strcat(buffer, "*"); }

            for (int cursor = i + 32; cursor < volume.blockSize; cursor++){ //adding back metadata init char '*'
                strcat(buffer, "*"); }
            break;
        }
        else if(i == volume.blockSize - 32){ //check if metadata is full
            printf("***METADATA BLOCK FULL***\n");
            return 0;
        }
        else{ //clear misc char from buffer
            strncpy(buffer, "", volume.blockSize);
            strncat(buffer, metadataBuffer, (i + 32));
        }
    }

    LBAwrite(buffer, 1, metadataIndex);

    free(buffer);
    free(metadataBuffer);

    return 1;
}
