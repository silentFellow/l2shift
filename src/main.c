/* main.c */

#include "platform/platform.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int, char **);

Mac mac = {0};

int main(int argc, char *argv[]) {
  srand(getpid());

  if (argc < 2 || strcmp(argv[1], "--help") == 0 ||
      strcmp(argv[1], "-h") == 0) {
    printHelp();
    return 0;
  }

  if (strcmp(argv[1], "--version") == 0 || strcmp(argv[1], "-v") == 0) {
    printf("l2shift version: 1.0.0\n");
    return 0;
  }

  if (!IsRunningAsAdmin()) {
    fprintf(stderr, "Error: You must run this program as root.\n");
    return 1;
  }

  if (argc == 2) {
    mac = generateMac(argv[1], NULL);
  } else {
    mac = generateMac(argv[1], argv[2]);
  }

  if (!validMac(mac.mac_str))
    exitWithError("Invalid MAC address");

  if (changeMac(mac)) {
    printf("MAC address changed successfully to %s\n", mac.formatted_addr);
  }

  return 0;
}
