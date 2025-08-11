#ifndef UTILS_H
#define UTILS_H

#include "types.h"
#include <stdbool.h>
#include <stddef.h>

void cleanContext(void);
void exitWithError(const char *);
void printHelp(void);

#endif
