#include "special1.h"
/* one to copy from the normal filesystem to your filesystem */
/* command = "special2 sourceFile linuxDestinationFile" */

int special1(struct filesystem_volume volume, struct arguments command) {
    ssize_t returnSource, returnDestination;
    char buffer[BUF_SIZE];

    /* check if command.argc != 2 */
    if(command.argc < 2) {
        printf("***Not Enough Args***\n");
        return 0; // check
    }
    else if(command.argc > 2) {
	    printf("***TOO many Args***\n");
	    return 0; //check
    }

    // Get args 
    char* sourceFile = command.args[1];
    char* destinationFile = command.args[2];

    // Open Linux File 
    int linuxFile = open(linuxFile, O_RDONLY);
    //negative value is returned, then there was an error opening the file
    if(linuxFile < 0)
        return 0;
    
    returnSource = read(linuxFile,&buffer,BUF_SIZE));

    if(returnSource < 1)

}