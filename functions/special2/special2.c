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
    printf("1 index\n");

    // check last character of path == '/'
    if(linuxDestinationFile[strlen(linuxDestinationFile)-1] != '/') {
        printf("***ERROR PATH IS NOT VALID***");
        return 0;
    }  
    printf("2 path\n");
    
    printf("%ld\n",strlen(sourceFile));
    strncat(linuxDestinationFile, sourceFile, 4);
    strcat(linuxDestinationFile, ".txt");
    strcat(linuxDestinationFile, "\0");

    printf("%s\n", linuxDestinationFile);

    // open linux file
    FILE* fp = fopen("/home/student/test.txt", "w");
    if(fp == NULL) printf("we fucked");

    printf("file opened\n");

    // create buffers
    char* sourceBuffer = malloc(volume.blockSize);
    char* bodyBuffer = malloc(volume.blockSize);

    printf("buffers created\n");
   
    // get size of file from Filesystem
    long totalSize = getNumberOfBytes("/home/student/HelloWorld.txt");
    
    int LBAcount = ceil(((double) totalSize) / ((double) volume.blockSize)); 
    
    printf("before LBAread\n");

    // LBAread the total blocks of sourceFile
    LBAread(sourceBuffer, LBAcount, fileIndex);
    printf("sourceBuffer: %d\n", sourceBuffer[48]);
printf("sourceBuffer: %s\n", sourceBuffer);
    
    printf("After LBAread before loop\n");

    for(int i=48; i<volume.blockSize; i=i+16) {
        LBAread(bodyBuffer, 1, 4);
        printf("bodyBuffer: %s\n", bodyBuffer);
        fputs(bodyBuffer, fp);
        
        //if(fgets(bodyBuffer,volume.blockSize,fp) != NULL)
           // puts(bodyBuffer);
        printf("after fgets\n");
    }
    printf("did we make it here\n");
    
    fclose(fp);
    free(sourceBuffer);
    free(bodyBuffer);

    printf("File successfully copied from Filesystem to LINUX\n");
    return 1;
    
    /* Basic steps laid out by Bierman - reference simple shell assignment for guidance
    srcfd = yourOpen(sourcefile)
    destfd = open(linuxDestinationFile)
    yourRead(srcfd, buf, len)
    write(destfd, buf, len)
    repeat read/write until entire file copied
    yourClose(srcfd)
    close(destfd) */
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
