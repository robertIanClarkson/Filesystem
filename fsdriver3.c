#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

#include "structs.h"
#include "./low/fsLow.h" /* (startPartitionSystem) (closePartitionSystem) (LBAwrite) (LBAread) */
#include "./tokenize/tokenize.h" /* (tokenize) (print) */

#include "./functions/cp/copyFile.h" /* (copyFile) */
#include "./functions/ld/listDir.h" /* (listDir) */
#include "./functions/mkdir/createDir.h" /* (createDir) */
#include "./functions/mv/moveFile.h" /* (moveFile) */
#include "./functions/rm/removeFile.h" /* (removeFile) */
#include "./functions/set/setMetaData.h" /* (setMetaData) */
#include "./functions/touch/createFile.h" /* (createFile) */
#include "./functions/special1/special1.h" /* (special1) */
#include "./functions/special2/special2.h" /* (special2) */

int createRoot(struct filesystem_volume volume) {
    uint64_t result;
    int rootIndex = 0;
    int metaIndex = 1;
    /* Set first LBA as used */
    volume.map[rootIndex] = 1; 

    /* Set metadata LBA as used */
    volume.map[metaIndex] = 1;

    /* create buffer */
    char* buffer = malloc(volume.blockSize);
    initializeLBA(buffer, '-', volume.blockSize);
    if(addName("root", buffer) != 1) return 0; // check
    if(addType("folder", buffer) != 1) return 0; // check
    if(connectMetaData(metaIndex, buffer) != 1) return 0; // check
    result = LBAwrite( buffer, 1, 0);
    free(buffer);
    // need to add check

    /* create metadata block */
    char* metaBuffer = malloc(volume.blockSize);
    initializeLBA(metaBuffer, '*', volume.blockSize);
    if(addName("root", metaBuffer) != 1) return 0; // check
    if(addType("metadata", metaBuffer) != 1) return 0; // check
    result = LBAwrite(metaBuffer, 1, metaIndex);
    free(metaBuffer);
    // need to add check

    printf("\n- Created Root Directory\n");
    return 1;
}

int main (int main_argc, char *main_argv[]) {
    struct filesystem_volume volume;

    /* Check for correct argc */
	if (main_argc == 4){
		volume.filename      = main_argv[1];
		volume.volumeSize    = atoll (main_argv[2]); // must be greater than 500,000 and a power of 2
		volume.blockSize     = atoll (main_argv[3]); // must be greater than 512 and a power of 2
        volume.blockCount    = (volume.volumeSize / volume.blockSize); // number of LBAs
        
        /* Initialize the map to 0 (empty) */
        volume.map           = malloc(sizeof(int) * volume.blockCount);
        for(int i = 0; i < volume.blockCount; i++) {
            volume.map[i] = 0;
        }
	} else {
        printf("Need 3 args (filename volumeSize blcokSize\n");
        return EXIT_FAILURE;
    }

    /* Create Partition */
    printf("\nOpening %s, Volume Size: %llu;  BlockSize: %llu\n", volume.filename, (ull_t)volume.volumeSize, (ull_t)volume.blockSize);
    volume.retVal = startPartitionSystem (volume.filename, &volume.volumeSize, &volume.blockSize);	
	printf("Opened  %s, Volume Size: %llu;  BlockSize: %llu; Return %d\n", volume.filename, (ull_t)volume.volumeSize, (ull_t)volume.blockSize, volume.retVal);
    if(volume.retVal == 0) {
        printf("\t- RESULT: success\n");
        if(createRoot(volume) != 1) {
            printf("\t***FAILED TO CREATE ROOT***\n");
            return EXIT_FAILURE; /* Set root directory */
        }
    } else if(volume.retVal == -1) {
        printf("\t- RESULT: file exists but can not open for write\n");
        // return EXIT_FAILURE;
    } else if(volume.retVal == -2) {
        printf("\t- RESULT: insufficient space for the volume\n");
        // return EXIT_FAILURE;
    } else {
        printf("\t- RESULT: %d\n", volume.retVal);
        // return EXIT_FAILURE;
    }

    /* MENU */
    char line[LINE_LENGTH];
    struct arguments command;
    int success = 1;

    printf("\nNOTE: type \"exit\" to exit this prompt\n");
    printf("NOTE: type \"help\" to show commands\n\n");
    do {
        printf("Filesystem_Prompt$ "); // prompt
        fgets(line, LINE_LENGTH, stdin);
        tokenize(line, &command);
        if(command.argc == 0) continue; 
        if(strcmp(command.opt, "ld") == 0) {
            success = listDir(volume, command);
        } else if(strcmp(command.opt, "mkdir") == 0) {
            success = createDir(volume, command); /* command = "mkdir newDirName parentDirName" */
        } else if(strcmp(command.opt, "touch") == 0) {
            success = createFile(volume, command);
        } else if(strcmp(command.opt, "rm") == 0) {
            success = removeFile(volume, command);
        } else if(strcmp(command.opt, "cp") == 0) {
            success = copyFile(volume, command);
        } else if(strcmp(command.opt, "mv") == 0) {
            success = moveFile(volume, command);
        } else if(strcmp(command.opt, "set") == 0) {
            success = setMetaData(volume, command);
        } else if(strcmp(command.opt, "special1") == 0) {
            // success = special1(volume, command); /* command = "special1 linuxDestinationFile sourceFile" */
        } else if(strcmp(command.opt, "special2") == 0) {
            // success = special2(volume, command); /* command = "special2 sourceFile linuxDestinationFile" */
        } else if(strcmp(command.opt, "help") == 0) {
            printf("\tlist all directories = ld\n");
            printf("\tmake a directory = mkdir\n");
            printf("\tmake a file = touch\n");
            printf("\tremove a file = rm\n");
            printf("\tcopy a file = cp\n");
            printf("\tmove a file = mv\n");
            printf("\tset metadata = set\n");
            printf("\tspecial command 1 = special1\n");
            printf("\tspecial command 2 = special2\n");
            printf("\texit prompt = exit\n");
        } else if(strcmp(command.opt, "exit") != 0) {
            printf("Invalid Command: %s\n", command.opt);
        }
        if(!success) {
            printf("******ERROR: %s ******\n", command.opt);
        }
    } while(strcmp(command.opt, "exit") != 0);

    /* Close Partition */
    free(volume.map);
    printf("\nClosing Partition\n");
    closePartitionSystem();
    printf("Closed  Partition\n");
    return EXIT_SUCCESS;
}
