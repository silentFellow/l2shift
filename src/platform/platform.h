/* platform.h */

#ifndef PLATFORM_H
#define PLATFORM_H

#include "../types.h"
#include <stdbool.h>

bool IsRunningAsAdmin(void);
char *formatAddr(const char *);
bool changeMac(Mac mac);

#endif
