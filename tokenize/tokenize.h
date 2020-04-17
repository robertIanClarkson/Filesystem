#ifndef tokenize_h
#define tokenize_h

#include <stdio.h>
#include <string.h>
#include "../structs.h"

#define LINE_LENGTH 256 // CHAR
#define DELIMITERS " \t\n"

void tokenize(char line[LINE_LENGTH], struct arguments *command);

#endif /* tokenize_h */