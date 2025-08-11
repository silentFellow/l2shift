#ifndef UTILS_H
#define UTILS_H

#include "types.h"
#include <stdbool.h>
#include <stddef.h>

Mac generateMac(char *, char *);
void cleanContext(void);
void exitWithError(const char *);
void printHelp(void);

#endif
