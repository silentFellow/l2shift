/* platform_linux.c */

#include "../l2shift.h"

#ifdef PLATFORM_LINUX

#include "../types.h"
#include "../utils.h"
#include "platform.h"
#include <ctype.h>
#include <errno.h>
#include <linux/if.h>
#include <linux/if_arp.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <unistd.h>

bool set_interface_state(const char *, int);

bool IsRunningAsAdmin() { return geteuid() == 0; }

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

bool set_interface_state(const char *ifname, int up) {
  int sock = socket(AF_INET, SOCK_DGRAM, 0);
  if (sock < 0)
    return false;

  struct ifreq ifr;
  strncpy(ifr.ifr_ifrn.ifrn_name, ifname, IFNAMSIZ - 1);

  if (ioctl(sock, SIOCGIFFLAGS, &ifr) < 0)
    return false;

  if (up) {
    ifr.ifr_flags |= IFF_UP;
  } else {
    ifr.ifr_flags &= ~IFF_UP;
  }

  if (ioctl(sock, SIOCSIFFLAGS, &ifr) < 0)
    return false;

  close(sock);
  return true;
}

bool changeMac(Mac mac) {
  int sock = socket(AF_INET, SOCK_DGRAM, 0);
  if (sock < 0)
    return false;

  struct ifreq ifr;
  strncpy(ifr.ifr_ifrn.ifrn_name, mac.interface_name, IFNAMSIZ - 1);
  ifr.ifr_ifru.ifru_hwaddr.sa_family = ARPHRD_ETHER;

  for (int i = 0; i < 6; ++i)
    ifr.ifr_ifru.ifru_hwaddr.sa_data[i] = (mac.addr >> (8 * (5 - i))) & 0xFF;

  bool service_down = set_interface_state(mac.interface_name, 0);

  int ret = ioctl(sock, SIOCSIFHWADDR, &ifr);

  bool service_up = set_interface_state(mac.interface_name, 1);

  if (ret != 0) {
    close(sock);
    exitWithError(strerror(errno));
  }

  close(sock);
  return service_down && (ret == 0) && service_up;
}

#endif
