#ifndef special1_h
#define special1_h

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "../../structs.h"
#include "../../low/fsLow.h"

int special1(struct filesystem_volume volume, struct arguments command);

#endif /* special1_h */