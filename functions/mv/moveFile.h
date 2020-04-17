#ifndef moveFile_h
#define moveFile_h

#include <stdio.h>
#include "../../structs.h"
#include "../../low/fsLow.h"

int moveFile(struct filesystem_volume volume, struct arguments command);

#endif /* moveFile_h */