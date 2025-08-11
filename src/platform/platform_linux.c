/* platform_linux.c */

#include "../l2shift.h"

#ifdef PLATFORM_LINUX

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

char *formatAddr(const char *addr) {
  if (strlen(addr) != 12) {
    return NULL;
  }

  char *formatted = malloc(18);
  if (formatted == NULL) {
    return NULL;
  }

  int j = 0;
  for (int i = 0; i < 12; i++) {
    if (i > 0 && i % 2 == 0)
      formatted[j++] = ':';

    formatted[j++] = toupper(addr[i]);
  }

  return formatted;
}

#endif
