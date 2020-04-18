#include "createFile.h"

int createFile(struct filesystem_volume volume, struct arguments command) {
    int filesize = atoll (command.args[2]); // size in LBAs

    /* Create a buffer for of 'f' */
    char* buffer = malloc(volume.blockSize);
    printf("filesize: %d\n", filesize);
    for(int i = 0; i < volume.blockSize; i++) {
        buffer[i] = 'f';
    }

    /* Write 'f' into 'filesize' number of blocks */
    for(int j = 0; j < filesize; j++) {
        uint64_t result = LBAwrite( buffer, 1,j);
    }
    return 1;
}