/* platform_mac.c */

#include "../l2shift.h"

#ifdef PLATFORM_APPLE

#include "../types.h"
#include "../utils.h"
#include <TargetConditionals.h>
#include <ctype.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

bool IsRunningAsAdmin() { return geteuid() == 0; }

char *formatAddr(const char *addr) {
  if (strlen(addr) != 12) {
    fprintf(stderr, "Invalid MAC address length: %zu\n", strlen(addr));
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

bool changeMac(Mac mac) {
#if !TARGET_OS_MAC
  return false;
#endif
  int ret;
  char cmd[128];

  snprintf(cmd, sizeof(cmd), "ifconfig %s ether %s\n", mac.interface_name,
           mac.formatted_addr);

  ret = system(cmd);
  if (ret != 0)
    exitWithError(strerror(errno));

  return true;
}

#endif
