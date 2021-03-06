#ifndef TAIA_H
#define TAIA_H

#include "tai.h"

/**
 * struct taia - a timestamp in TAIA format
 * @sec: the number of seconds since 1970 TAI (biased 2**62)
 * @nano: additional nanoseconds
 * @atto: additional attoseconds
 */
struct taia {
  struct tai sec;
  unsigned long nano; /* 0...999999999 */
  unsigned long atto; /* 0...999999999 */
};

/**
 * taia_tai - truncate a taia to a tai
 */
extern void taia_tai(const struct taia *src, struct tai *dest);

/**
 * taia_now - get the current time
 */
extern void taia_now(struct taia *);

/**
 * taia_approx - get the TAI number of seconds as a double
 */
extern double taia_approx(const struct taia *);

/**
 * taia_frac - get the number of fractional seconds as a double
 */
extern double taia_frac(const struct taia *);

extern void taia_add(struct taia *,const struct taia *,const struct taia *);
extern void taia_addsec(struct taia *,const struct taia *,int);
extern void taia_sub(struct taia *,const struct taia *,const struct taia *);
extern void taia_half(struct taia *,const struct taia *);
extern int taia_less(const struct taia *,const struct taia *);

#define TAIA_PACK 16
extern void taia_pack(char *,const struct taia *);
extern void taia_unpack(const char *,struct taia *);

#define TAIA_FMTFRAC 19
extern unsigned int taia_fmtfrac(char *,const struct taia *);

extern void taia_uint(struct taia *,unsigned int);

#endif
