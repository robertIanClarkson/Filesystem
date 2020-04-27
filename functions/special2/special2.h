#ifndef special2_h
#define special2_h

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include "../../structs.h"
#include "../../low/fsLow.h"

int special2(struct filesystem_volume volume, struct arguments command);

#endif /* special2_h */