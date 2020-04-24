#include "special2.h"

int special2(struct filesystem_volume volume, struct arguments command) {
    // Checking argc 
    if(command.argc != 3) {
        printf("***Not Enough Args***\n");
        return 0; // check
    }

    // Get args 
    char* sourceFile = command.args[1];
    char* linuxDestinationFile = command.args[2]; 
    
    /* Basic steps laid out by Bierman - reference simple shell assignment for guidance
    srcfd = yourOpen(sourcefile)
    destfd = open(linuxDestinationFile)
    yourRead(srcfd, buf, len)
    write(destfd, buf, len)
    repeat read/write until entire file copied
    yourClose(srcfd)
    close(destfd) */
    return 1;
}