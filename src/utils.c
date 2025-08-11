/* utils.c */
#include "types.h"
#include <stdio.h>
#include <stdlib.h>

extern Mac mac;

void cleanContext() {
  if (mac.formatted_addr)
    free(mac.formatted_addr);
}

void exitWithError(const char *message) {
  fprintf(stderr, "Error: %s\n", message);

  cleanContext();

  exit(EXIT_FAILURE);
}

void printHelp() {
  printf("Usage: altermac <interface> [<custom_mac>]\n");
  printf("Change the MAC address of a network interface.\n\n");
  printf("Options:\n");
  printf("  <interface>    The name of the network interface to change.\n");
  printf(
      "  <custom_mac>   Optional custom MAC address in hexadecimal format.\n");
  printf(
      "                  If not provided, a random MAC will be generated.\n\n");
  printf("Examples:\n");
  printf("  altermac eth0\n");
  printf("  altermac eth0 00:11:22:33:44:55\n");
}
