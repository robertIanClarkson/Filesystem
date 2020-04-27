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

    // get/check source file index, -1 doesnt exist
    int fileIndex = getIndex(sourceFile, volume);
    if(fileIndex < 1) {
        printf("***ERROR FILE DOES NOT EXIST***");
        return 0;
    }

    // check last character of path == '/'
    if(linuxDestinationFile[strlen(linuxDestinationFile)-1] != '/') {
        printf("***ERROR PATH IS NOT VALID***");
        return 0;
    } 

    /* seems a little messy, might be a better way to trim '-' from fileName */
    int len = strlen(sourceFile);   	
    for(int i = 0; i < len; i++) {
        if(sourceFile[i] == '-') {
	    for(int j = i; j < len; j++) {
		sourceFile[j] = sourceFile[j + 1];
	    }
	    len--;
	    i--;	
        } 
    }
    strcat(linuxDestinationFile, sourceFile);
    strcat(linuxDestinationFile, ".txt");
    strcat(linuxDestinationFile, '\0');

    // open linux file
    FILE* fp = fopen(linuxDestinationFile, "w");
    if(fp == NULL) 
        printf("***ERROR FILE NOT FOUND***");

    printf("File successfully opened\n");

    // create buffers
    char* sourceBuffer = malloc(volume.blockSize);
    char* bodyBuffer = malloc(volume.blockSize);
    char* lineBuffer = malloc(16);

    printf("\t-buffers created\n");
   
    /* This was not a bad idea, but I dont think we need to get this information
    // get size of file from Filesystem
    long totalSize = getNumberOfBytes("/home/student/HelloWorld.txt");
    int LBAcount = ceil(((double) totalSize) / ((double) volume.blockSize)); 
    printf("Total LBA blocks of file: %d\n", LBAcount);
    */

    // LBAread the total blocks of sourceFile
    LBAread(sourceBuffer, 1, fileIndex);

    for(int i=48; i<volume.blockSize; i=i+16) {
        if(getLine(sourceBuffer, lineBuffer, i) == 0) continue;
        LBAread(bodyBuffer, 1, atoi(lineBuffer));
        fputs(bodyBuffer, fp);
    }
    
    free(sourceBuffer);
    free(bodyBuffer);
    free(lineBuffer);
    printf("\t-Memory freed\n");
    fclose(fp);
    printf("\t-File closed\n");

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
