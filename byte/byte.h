#ifndef BYTE_H
#define BYTE_H

#include <string.h>

/**
 * byte_chr - find a byte of a given value in data
 * @s: the data to search in
 * @len: the length of @s
 * @c: the byte to search for
 *
 * returns: the offset of the first byte with the given value, if found.
 * Otherwise, returns s + len
 */
extern unsigned int byte_chr(const char *s, unsigned int len, char c);

/**
 * byte_copy - copy data between memory regions
 * @to: destination
 * @n: number of bytes to copy
 * @from: source
 */
extern void byte_copy(char *to, unsigned int n, const char *from);

/**
 * byte_copyr - copy data between memory regions
 * @to: destination
 * @n: number of bytes to copy
 * @from: source
 *
 * Copy bytes backwards.
 */
extern void byte_copyr(char *to, unsigned int n, const char *from);

/**
 * byte_diff - a ordering function for memory regions
 * @n: the maximum offset to read from either string
 *
 * Walks the two strings and, if they differ, returns the difference between
 * the differing charactor in the first and second strings. If they don't
 * differ, returns 0.
 */
extern int byte_diff(const char *s, unsigned int n, const char *t);

/**
 * byte_zero - writes NULs to a memory region
 */
static inline void byte_zero(char *s, unsigned int n) {
  memset(s, 0, n);
}

#define byte_equal(s,n,t) (!byte_diff((s),(n),(t)))

#endif
