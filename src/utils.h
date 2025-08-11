#ifndef UTILS_H
#define UTILS_H

#include "types.h"
#include <stdbool.h>
#include <stddef.h>

Mac generateMac(char *, char *);
bool validMac(const char *);
void cleanContext(void);
void exitWithError(const char *);
void printHelp(void);

#endif
