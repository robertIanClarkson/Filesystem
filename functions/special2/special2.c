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

    //printf("file path: %s\n", linuxDestinationFile);

    // get/check source file index, -1 doesnt exist
    int fileIndex = getIndex(sourceFile, volume);
    if(fileIndex < 1) {
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
    char* sourceBuffer = malloc(volume.blockSize);
    char* bodyBuffer = malloc(volume.volumeSize);
    char* bufferWithoutTrail = malloc(volume.volumeSize);
    char* lineBuffer = malloc(16);
    char* totalBytes = malloc(16);

    int metadataIndex = fileIndex + 1;
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

    LBAread(sourceBuffer, 1, fileIndex);
    int totalSize = atoi(totalBytes);
    printf("totalSize: %d\n", totalSize);
    int totalLBA = (totalSize/volume.blockSize)+1;

    printf("totalLBA: %d\n", totalLBA);

    for(int i=48; i<volume.blockSize; i=i+16) {
        if(getLine(sourceBuffer, lineBuffer, i) == 0) continue;
           LBAread(bodyBuffer, totalLBA, atoi(lineBuffer));
           //printf("bodyBuffer: %s\n", bodyBuffer); 
           strncpy(bufferWithoutTrail,bodyBuffer,totalSize);
           printf("bufferWithoutTrail: %s\n", bufferWithoutTrail);
           //bufferWithoutTrail[sizeof bufferWithoutTrail] = '\0';
           fputs(bufferWithoutTrail, fp);
           break;
    }
    
    free(sourceBuffer);
    free(bodyBuffer);
    free(bufferWithoutTrail);
    free(lineBuffer);
    free(totalBytes);
    fclose(fp);

    printf("File successfully copied from Filesystem to LINUX\n");
    return 1;
}

/*
check if linux destination is valid
check if 'volume' file exist
read 'volume' file into buffer
get metadata location from buffer
open metadata file into metaBuffer
read each 'title' line from metaBuffer (line 3, 5, 7, ..., < blockSize)
if title of line X == "size" then (fileSize = line(X+1))

now just use the special2 logic we originally had except incorporate this logic...
extraBytes = fileSize % blockSize;
if(extrabytes == 0) then we just need to read (fileSize / blockSize) LBAsto fp.
else read (fileSize / blocksize) to fp then read extraBytes amount from last block to fp.
free everything up!
Hope this helps!
*/
