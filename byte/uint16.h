#ifndef UINT16_H
#define UINT16_H

#include <stdint.h>

typedef uint16_t uint16;

extern void uint16_pack(char *dest, uint16 value);
extern void uint16_pack_big(char *dest, uint16 value);
extern void uint16_unpack(const char *src ,uint16 *dest);
extern void uint16_unpack_big(const char *src, uint16 *dest);

#endif
