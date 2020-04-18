#ifndef listDir_h
#define listDir_h

#include <stdio.h>
#include "../../structs.h"
#include "../../low/fsLow.h"

int listDir(struct filesystem_volume volume, struct arguments command);

#endif /* listDir_h */