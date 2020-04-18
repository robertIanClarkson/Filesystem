#ifndef removeFile_h
#define removeFile_h

#include <stdio.h>
#include "../../structs.h"
#include "../../low/fsLow.h"

int removeFile(struct filesystem_volume volume, struct arguments command);

#endif /* removeFile_h */