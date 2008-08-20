#ifndef STRALLOC_H
#define STRALLOC_H

#include "gen_alloc.h"

/**
 * struct stralloc - an allocated string
 * @s: a pointer to the charactor data
 * @len: the number of valid bytes in @s
 * @a: the number of allocated bytes
 *
 * To create a new stralloc object do:
 * <pre>stralloc mystring = {0};<pre>
 */
GEN_ALLOC_typedef(stralloc,char,s,len,a)

/**
 * stralloc_ready - make space availible in the string
 * @n: the number of bytes that must be availible in the string.
 * returns: 0 on failure.
 *
 * This function ensures that at least @n bytes are allocated for the string.
 * It does not affect the length of the string.
 */
extern int stralloc_ready(stralloc *s, unsigned int n);

/**
 * stralloc_ready - make additional space availible in the string
 * @n: the number of bytes that must be availible at the end of the string
 * returns: 0 on failure.
 *
 * This function ensures that at least @n bytes are allocated at the end of the
 * current string data, i.e. after this call returns successfully, one can
 * write @n bytes to sa->s + sa->len.
 *
 * It does not affect the length of the string.
 */
extern int stralloc_readyplus(stralloc *,unsigned int);

/**
 * stralloc_copy - replace the current string with the contents of another
 * returns: 0 on failure.
 */
extern int stralloc_copy(stralloc *dest, const stralloc *src);

/**
 * stralloc_cat - append another stralloc
 * returns: 0 on failure.
 */
extern int stralloc_cat(stralloc *dest, const stralloc *src);

/**
 * stralloc_cat - replace the current string with the contents of a NUL
 *   terminated string
 * returns: 0 on failure.
 */
extern int stralloc_copys(stralloc *dest, const char *src);

/**
 * stralloc_cat - append a NUL terminated string
 * returns: 0 on failure.
 */
extern int stralloc_cats(stralloc *,const char *);

/**
 * stralloc_copyb - replace the current string with data
 * returns: 0 on failure.
 */
extern int stralloc_copyb(stralloc *dest, const char *src, unsigned int length);

/**
 * stralloc_copyb - append data to the current string
 * returns: 0 on failure.
 */
extern int stralloc_catb(stralloc *dest, const char *src, unsigned int length);

/**
 * stralloc_append - append a single byte
 * returns: 0 on failure.
 *
 * beware: this takes a pointer to 1 char
 */
extern int stralloc_append(stralloc *dest, const char *);

/**
 * stralloc_0 - NUL terminate a string
 * returns: 0 on failure
 */
#define stralloc_0(sa) stralloc_append(sa,"")

/**
 * stralloc_catulong0 - append an unsigned long
 * @n: the number to append
 * @len: the minimum number of bytes to use
 *
 * If the number is represented with less than @len bytes, zero pad at the
 * beginning to use up @len bytes.
 */
extern int stralloc_catulong0(stralloc *, unsigned long n, unsigned int len);
extern int stralloc_catlong0(stralloc *,long,unsigned int);

#define stralloc_catlong(sa,l) (stralloc_catlong0((sa),(l),0))
#define stralloc_catuint0(sa,i,n) (stralloc_catulong0((sa),(i),(n)))
#define stralloc_catint0(sa,i,n) (stralloc_catlong0((sa),(i),(n)))
#define stralloc_catint(sa,i) (stralloc_catlong0((sa),(i),0))

#endif
