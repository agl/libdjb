#ifndef TAI_H
#define TAI_H

#include "uint64.h"

/**
 * struct tai - a timestamp in TAI format
 * @x: the number of seconds since 1970 TAI (biased 2**62)
 *
 * See http://cr.yp.to/libtai/tai64.html
 */
struct tai {
  uint64 x;
} ;

/**
 * tai_unix - set a timestamp from a UNIX time
 */
#define tai_unix(t,u) ((void) ((t)->x = 4611686018427387914ULL + (uint64) (u)))

/**
 * tai_now - get the current time
 */
extern void tai_now(struct tai *output);

#define tai_approx(t) ((double) ((t)->x))

extern void tai_add(struct tai *,const struct tai *,const struct tai *);
extern void tai_sub(struct tai *,const struct tai *,const struct tai *);
#define tai_less(t,u) ((t)->x < (u)->x)

#define TAI_PACK 8
/**
 * tai_pack - export a TAI timestamp
 * @output: a pointer to an 8-byte buffer
 */
extern void tai_pack(char *output, const struct tai *t);

/**
 * tai_unpack - read an external TAI value
 * @input: a pointer to an 8-byte buffer
 */
extern void tai_unpack(const char *input, struct tai *t);

/**
 * tai_uint - set a TAI timestamp from a uint number of seconds
 */
extern void tai_uint(struct tai *output, unsigned int v);

#endif
