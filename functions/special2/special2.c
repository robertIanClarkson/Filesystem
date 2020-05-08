#include "special2.h"
/* from your filesystem to the normal filesystem */
int special2(struct filesystem_volume volume, struct arguments command) {
    // Checking argc 
    if(command.argc != 4) {
        printf("***Not Enough Args***\n");
        return 0; // check
    }

    // Get args 
    char* sourceFile = command.args[1];
    char* sourceDirectory = command.args[2];
    char* linuxDestinationFile = command.args[3];

    // check last character of path == '/'
    if(linuxDestinationFile[strlen(linuxDestinationFile)-1] != '/') {
        printf("***ERROR PATH IS NOT VALID***\n");
        return 0;
    } 

    printf("sourceFile: %s\n", sourceFile);

    strcat(linuxDestinationFile, sourceFile);
    //strcat(linuxDestinationFile, ".txt");
    strcat(linuxDestinationFile, "\0");

    //GET FOLDER INDEX
    int folderIndex = getIndex(sourceDirectory, volume);
    if(folderIndex < 0) {
        printf("***ERROR - FOLDER NOT FOUND***\n");
        return 0;
    }

    //printf("file path: %s\n", linuxDestinationFile);
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
            if(strcmp(name, sourceFile) == 0) { // THIS IS THE ONE WE WILL COPY 
                break;
            }
        }
    }

    // get/check source file index, -1 doesnt exist
    //int fileIndex = getIndex(sourceFile, volume);
    if(fileIndex < 0) {
        printf("***ERROR FILE DOES NOT EXIST***\n");
        return 0;
    }


    // open linux file
    FILE* fp = fopen(linuxDestinationFile, "w");
    if(fp == NULL) 
        printf("***ERROR FILE NOT FOUND***\n");

    printf("File successfully opened\n");

    // create buffers
    char* metadataBuffer = malloc(volume.blockSize);
    char* bodyBuffer = malloc(volume.volumeSize);
    char* bufferWithoutTrail = malloc(volume.volumeSize);
    char* lineBuffer = malloc(16);
    char* totalBytes = malloc(16);

    int metadataIndex = atoi(fileIndex) + 1;
    LBAread(metadataBuffer, 1, metadataIndex); 

    for(int i = 32; i < volume.blockSize; i += 32) {
	if(metadataBuffer[i] == '^') {
	    int j = i + 16;  
            int temp = 0;
	    while (metadataBuffer[j] != '*') {
		    totalBytes[temp] = metadataBuffer[j];
		    temp++;
		    j++;
	    }
        break;
	}
    }
    free(metadataBuffer);

    int totalSize = atoi(totalBytes);
    printf("totalSize: %d\n", totalSize);
    int totalLBA = (totalSize/volume.blockSize)+1;
    printf("totalLBA: %d\n", totalLBA);

    LBAread(bodyBuffer, totalLBA, atoi(fileIndex)+2);
    printf("bodyBuffer: %s\n", bodyBuffer); 
    strncpy(bufferWithoutTrail,bodyBuffer,totalSize);
    printf("bufferWithoutTrail: %s\n", bufferWithoutTrail);
    fputs(bufferWithoutTrail, fp);
    
    free(bodyBuffer);
    free(bufferWithoutTrail);
    free(lineBuffer);
    free(totalBytes);
    fclose(fp);

    printf("File successfully copied from Filesystem to LINUX\n");
    return 1;
}


