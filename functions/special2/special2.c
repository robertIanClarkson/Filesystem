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
copy file 'foo' in directory 'bar' into '/my/local/path/on/my/computer/')
Filesystem_Prompt$ cp_to foo root /my/local/path/on/my/computer/
 /my/local/path/on/my/computer/foo
 ***Complete***

1. get/check source file index (22 or -1 --> doesnt exist) -done
2. check if PATH is valid (I think C has an isValidPath(linuxDestinationFile)) -done
   - need to check last character of path == '/'--> if != '/' then ERROR, return 0
3. get fp going with complete path --> fp = open("/my/local/path/on/my/computer/" + "foo", "w+");
4. LBAread(sourceBuffer, sourceFileIndex)
5. foreach(body line) --> i = i + 16
        LBAread(bodyBuffer, line) --> body bytes
        fp.append(bodyBuffer)
6. fp.close()
7. return 1
    

*/