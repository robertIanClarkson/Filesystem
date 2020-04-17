#include "createDir.h"

/* opt newDirName parentDirName */
int createDir(struct filesystem_volume volume, struct arguments command) {
    /* Checking argc */
    if(command.argc != 3) {
        printf("***Not Enough Args***\n");
        return 0; // check
    }

    /* Get args */
    char* name     = command.args[1];
    char* parent   = command.args[2];
    printf("- NewFolder: %s\n", name);
    printf("- In Folder: %s\n", parent);

    /* Find the first LBA that is empty */
    printf("- Looking for Index LBA\n");
    int i;
    for(i = 0; i < volume.blockCount; i++) {
        if(volume.map[i] == 0) break;
    }
    printf("  - Empty LBA at: %d\n", i);

    /* mark LBA as used */
    printf("  - Marking LBA as used\n");
    volume.map[i] = 1;

    /* Find another LBA for that is empty for metadata */
    printf("- Looking for MetaData LBA\n");
    int j;
    for(j = 0; j < volume.blockCount; j++) {
        if(volume.map[j] == 0) break;
    }
    printf("  - Empty LBA at: %d\n", j);

    /* mark LBA as used */
    printf("  - Marking LBA as used\n");
    volume.map[j] = 1;

    /* Get parent LBA position */
    printf("- Looking for parent folder\n");
    int parentIndex = getIndex(parent, volume);
    if(parentIndex < 0) {
        printf("***PARENT FOLDER DNE***\n");
        return 0;
    }
    printf("  - Found parent folder\n");
     
    /* Create Index LBA */
    printf("- Creating Buffer\n");
    char* buffer = malloc(volume.blockSize);
    initializeLBA(buffer, '-', volume.blockSize);
    printf("  - Adding Name: %s\n", name);
    if(addName(name, buffer) != 1) return 0; // check
    printf("  - Adding Type: folder\n");
    if(addType("folder", buffer) != 1) return 0; // check
    printf("  - Connecting Metadata LBA index\n");
    if(connectMetaData(j, buffer) != 1) return 0; // check
    printf("  - Writing Buffer to LBA: %d\n", i);
    LBAwrite(buffer, 1, i);

    /* update parent LBA with child LBA */
    printf("- Updating parent folder\n");
    if(addChild(i, parentIndex) != 1) return 0;

    printf("- COMPLETE\n");
    return 1;
}
