#ifndef copyFile_h
#define copyFile_h

#include <stdio.h>
#include "../../structs.h"
#include "../../low/fsLow.h"
#include "../touch/createFile.h"

int copyFile(struct filesystem_volume volume, struct arguments command);

#endif /* copyFile_h */