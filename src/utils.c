/* utils.c */

#include "utils.h"
#include "platform/platform.h"
#include "types.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern Mac mac;

uint64_t generate48bitMacAddr(void);
void cleanAddr(const char *, char *, size_t);
void hexToString(int64, char *, size_t);

uint64_t generate48bitMacAddr() {
  // Get three 16-bit chunks from rand()
  uint64_t part1 = (uint64_t)(rand() & 0xFFFF);
  uint64_t part2 = (uint64_t)(rand() & 0xFFFF);
  uint64_t part3 = (uint64_t)(rand() & 0xFFFF);

  // Assemble into 48-bit value
  uint64_t mac_addr = (part1 << 32) | (part2 << 16) | part3;

  // Make sure it's locally administered and unicast:
  // Bit 0 (LSB of first byte) = 0 → unicast
  // Bit 1 (2nd LSB of first byte) = 1 → locally administered
  mac_addr &= 0xFFFFFFFFFFFFULL; // ensure only 48 bits used
  mac_addr &= ~(1ULL << 40);     // clear multicast bit
  mac_addr |= (1ULL << 41);      // set local admin bit

  return mac_addr;
}

Mac generateMac(char *interface_name, char *custom_mac) {
  Mac mac;

  mac.interface_name = interface_name;
  if (custom_mac == NULL) {
    mac.addr = generate48bitMacAddr();

    hexToString(mac.addr, mac.mac_str, sizeof(mac.mac_str));

    strcpy(mac.cleaned_addr, mac.mac_str);
  } else {
    cleanAddr(custom_mac, mac.cleaned_addr, sizeof(mac.cleaned_addr));

    strcpy(mac.mac_str, mac.cleaned_addr);

    mac.addr = strtoull(mac.cleaned_addr, NULL, 16);
  }

  mac.formatted_addr = formatAddr(mac.cleaned_addr);
  if (mac.formatted_addr == NULL)
    exitWithError("Failed to format MAC address");

  return mac;
}

void cleanAddr(const char *addr, char *buffer, size_t size) {
  char cleaned[13];

  int j = 0;
  for (int i = 0; addr[i] != '\0'; i++) {
    if (isalnum(addr[i])) {
      if (j >= 12) {
        exitWithError("MAC address too long, must be exactly 12 characters");
      }
      cleaned[j++] = addr[i];
    }
  }

  if (j != 12) {
    exitWithError("MAC address must be exactly 12 characters");
  }

  strncpy(buffer, cleaned, size - 1);
  buffer[size - 1] = '\0';
}

void hexToString(int64 hex, char *buffer, size_t size) {
  snprintf(buffer, size, "%012llx", (unsigned long long)hex);
}

bool validMac(const char *addr) {
  if (strlen(addr) != 12)
    return false;

  bool nonZero = false;
  bool nonMax = false;
  for (int i = 0; i < 12; i++) {
    if (!isxdigit(addr[i]))
      return false;

    if (addr[i] != '0')
      nonZero = true;

    if (addr[i] != 'f' && addr[i] != 'F')
      nonMax = true;
  }

  return nonZero && nonMax;
}

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
