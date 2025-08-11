#ifndef ALTERMAC_H
#define ALTERMAC_H

#if defined(__WIN32) || defined(__WIN64)
  #define PLATFORM_WINDOWS
#elif defined(__linux__)
  #define PLATFORM_LINUX
#elif defined(__APPLE__)
  #define PLATFORM_APPLE
#else
  #error "Unsupported platform"
#endif

#endif
