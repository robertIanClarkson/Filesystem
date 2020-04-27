#include "special2.h"
/* from your filesystem to the normal filesystem */
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

/*
copy file 'foo' in directory 'bar' into '/my/local/path/on/my/computer/')
Filesystem_Prompt$ cp_to foo root /my/local/path/on/my/computer/
 /my/local/path/on/my/computer/foo
 ***Complete***

1. get/check source file index (22 or -1 --> doesnt exist)
2. check if PATH is valid (I think C has an isValidPath(linuxDestinationFile))
   - need to check last character of path == '/'--> if != '/' then ERROR, return 0
3. get fp going with complete path --> fp = open("/my/local/path/on/my/computer/" + "foo", "w+");
4. LBAread(sourceBuffer, sourceFileIndex)
5. foreach(body line) --> i = i + 16
        LBAread(bodyBuffer, line) --> body bytes
        fp.append(bodyBuffer)
6. fp.close()
7. return 1
    

*/
