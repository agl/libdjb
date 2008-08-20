#ifndef STR_H
#define STR_H

/* str_diff - an ordering function for NUL terminated strings
 * returns: the difference between the first differing byte in @s and @t.
 */
extern int str_diff(const char *s, const char *t);

/**
 * str_len - find the length of a NUL terminated string
 * returns: the number of bytes before the NUL value
 */
extern unsigned int str_len(const char *);

/**
 * str_chr - locate a byte in a NUL terminated string
 * returns: the offset of the first byte with the given value, or the offset of
 *   the NUL at the end of the string on failure
 */
extern unsigned int str_chr(const char *src, int value);

/**
 * str_rchr - locate the last byte of a given value in a NUL terminated string
 * returns: the offset of the last byte with the given value. If no such byte
 *   exists, the offset of the NUL is returned.
 */
extern unsigned int str_rchr(const char *src, int value);

/**
 * str_start - check if a string is a prefix of another
 * returns: 1 if @t is a prefix of @s
 *
 * Note that if @t == @s, then @t is considered a prefix.
 */
extern int str_start(const char *s, const char *t);

#define str_equal(s,t) (!str_diff((s),(t)))

#endif
