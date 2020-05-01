#include "special2.h"
/* from your filesystem to the normal filesystem */
int special2(struct filesystem_volume volume, struct arguments command) {
    /* check if command.argc != 4 */
    if(command.argc < 4) {
        printf("***Not Enough Args***\n");
        return 0; // check
    }
    else if(command.argc > 4) {
	    printf("***TOO many Args***\n");
	    return 0; //check
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

    //printf("sourceFile: %s\n", sourceFile);

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

    // printf("File successfully opened\n");

    // create buffers
    char* sourceBuffer = malloc(volume.blockSize);
    char* bodyBuffer = malloc(volume.blockSize);
    char* lineBuffer = malloc(16);

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
    fclose(fp);

    // printf("File successfully copied from Filesystem to LINUX\n");
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
