#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>

typedef uint8_t int8;
typedef uint16_t int16;
typedef uint32_t int32;
typedef uint64_t int64;

struct s_mac {
  char *interface_name;
  char cleaned_addr[13];
  char mac_str[13];
  char *formatted_addr;
  int64 addr : 48;
};

typedef struct s_mac Mac;

#endif
