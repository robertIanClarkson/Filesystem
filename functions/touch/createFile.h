#ifndef createFile_h
#define createFile_h

#include <stdio.h>
#include "../../structs.h"
#include "../../low/fsLow.h"

int createFile(struct filesystem_volume volume, struct arguments command);

#endif /* createFile_h */