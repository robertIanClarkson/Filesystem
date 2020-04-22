#ifndef moveFile_h
#define moveFile_h

#include <stdio.h>
#include <string.h>
#include "../../structs.h"
#include "../../low/fsLow.h"
#include "../cp/copyFile.h"
#include "../rm/removeFile.h"

int moveFile(struct filesystem_volume volume, struct arguments command);

#endif /* moveFile_h */