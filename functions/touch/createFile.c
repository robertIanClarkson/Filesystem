#include "createFile.h"

int createFile(struct filesystem_volume volume, struct arguments command) {
     /* Checking argc */
    if(command.argc != 3) {
        printf("***Not Enough Args***\n");
        return 0; // check
    }

    /* Get args */
    char* name = command.args[1];
    int filesize = atoll (command.args[2]); // size in LBAs

    printf("Creating filename: %s\n", name);

    // Check to see if existing file has the same name
    filesystem_volume *temp = malloc(sizeof(filesystem_volume));

    if (strcmp(temp->name, name) == 0) {
        printf("File already exists\n");
        return -1;
    }

    /* Find the first LBA that is empty */
    printf("- Looking for Index LBA\n");
    int i;
    for(i = 0; i < volume.blockCount; i++) 
        if(volume.map[i] == 0) break;

    printf("  - Empty LBA at: %d\n", i);

    /* mark LBA as used */
    printf("  - Marking LBA as used\n");
    volume.map[i] = 1;

    /* Find another LBA for that is empty for metadata */
    printf("- Looking for MetaData LBA\n");
    int j;
    for(j = 0; j < volume.blockCount; j++) 
        if(volume.map[j] == 0) break;

    printf("  - Empty LBA at: %d\n", j);

    /* mark LBA as used */
    printf("  - Marking LBA as used\n");
    volume.map[j] = 1;

     /* Create Index LBA */
    printf("- Creating Buffer\n");
    char* buffer = malloc(volume.blockSize);
    initializeLBA(buffer, '#', volume.blockSize);
    printf("  - Adding Name: %s\n", name);
    if(addName(name, buffer) != 1) return 0; // check
    printf("  - Adding Type: file\n");
    if(addType("file", buffer) != 1) return 0; // check
    printf("  - Connecting Metadata LBA index\n");
    if(connectMetaData(j, buffer) != 1) return 0; // check
    printf("  - Writing Buffer to LBA: %d\n", i);
    LBAwrite(buffer, 1, i);
    free(buffer);

    /* create metadata block */
    char* metaBuffer = malloc(volume.blockSize);
    initializeLBA(metaBuffer, '*', volume.blockSize);
    if(addName(name, metaBuffer) != 1) return 0; // check
    if(addType("metadata", metaBuffer) != 1) return 0; // check
    LBAwrite(metaBuffer, 1, j);
    free(metaBuffer);
    /*// Create a buffer for of 'f' 
    char* buffer = malloc(volume.blockSize);
    printf("filesize: %d\n", filesize);
    int result = addName(name, buffer);
    if (result != 1) {
        printf("Fi");
        return 0;
    }
    for (int i = 0; i < volume.blockSize; i++) 
        buffer[i] = 'f';

    // Write 'f' into 'filesize' number of blocks 
    for (int j = 0; j < filesize; j++) {
        uint64_t result = LBAwrite( buffer, 1,j);
    } */
    printf("- COMPLETE\n");
    return 1;
}