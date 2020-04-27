#include "setMetaData.h"

int setMetaData(struct filesystem_volume volume, struct arguments command) {

    /* Filesystem $ set file folder category data
                  $ touch test root
                  $ set test root author stan
    

    1. find folder
    2. find file
    3. find metadata LBA
    4. write command.args[3 & 4] to next empty lines in metadata block

   */

    //CHECK ARG COUNT
   if(command.argc > 5){
       printf("***TOO MANY ARGS***\n");
   }
   else if (command.argc < 5){
       printf("***TOO FEW ARGS***\n");
   }

   //GET ARGS
    char* file = command.args[1];
    char* folder = command.args[2];
    char* type = command.args[3];
    char* data = command.args[4];

    if(strlen(type) > 16) {
        printf("***METADATA TYPE TOO LONG***\n");
        return 0;
    }
        if(strlen(type) > 16) {
        printf("***METADATA DATA TOO LONG***\n");
        return 0;
    }

    //GET FOLDER INDEX
    printf("Getting folder '%s' index...\n",folder);
    int folderIndex = getIndex(folder, volume);
    if(folderIndex < 0) {
        printf("***FOLDER DNE***\n");
        return 0;
    }
    printf("folder index: %d\n", folderIndex);

    //GET FILE INDEX

    int fileIndex = getIndex(file, volume);
    printf("file index: %d\n", fileIndex);
    
    if(fileIndex < 0) {
        printf("***ERROR INDEX COULD NOT BE FOUND***");
        return 0;
    }

    //GET METADATA INDEX

    int metadataIndex = fileIndex + 1;
    printf("metadata index: %d\n", metadataIndex);


    //WRITE ARGS 3 & 4 TO SEPERATE LINES OF METADATA LBA
    
    char* buffer = malloc(volume.blockSize); //to be written
    char* metadataBuffer = malloc(volume.blockSize); //MD block

    LBAread(metadataBuffer, 1, metadataIndex); //reads entire MD block

    //printf("metadataBuffer: %s\n\n", metadataBuffer);

    strncat(buffer, metadataBuffer, 32); // copy header lines into buffer

    // for(int test = 32; test < volume.blockSize + 32; test += 32) { printf("i = %d\n",test);}

    for(int i = 32; i < volume.blockSize; i += 32) { // search for first empty line

        //printf("\n\nmetadataBuffer[i]: %c\n i = %d\n\n",metadataBuffer[i],i);
        if(metadataBuffer[i] == '*') {
            printf("hello from first * line");
            strcat(buffer, type);
            for(int j = 0; j < (16 - strlen(type));  j++) {
                strcat(buffer, "*"); }
                //printf("\n\ntype-buffer: %s\n\n", buffer);

            strcat(buffer, data);
            for(int k = 0; k < (16 - strlen(data));  k++) {
                strcat(buffer, "*"); }
                //printf("\n\nname-buffer: %s\n\n", buffer);

            for (int cursor = i + 32; cursor < volume.blockSize; cursor++){ //adding back metadata init char
                strcat(buffer, "*");
            }
            //printf("\n\nfinal-buffer: %s\n\n", buffer);
            break;
        }
        else if(i == volume.blockSize - 32){
            //printf("***METADATA BLOCK FULL***\n");
            return 0;
        }
        else{
            strncpy(buffer, "", volume.blockSize);
            strncat(buffer, metadataBuffer, (i + 32));
            //printf("\n\nheader-buffer: %s\n\n", buffer);
        }
    }

    LBAwrite(buffer, 1, metadataIndex);

    free(buffer);
    free(metadataBuffer);

    return 1;
}
