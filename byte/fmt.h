#ifndef FMT_H
#define FMT_H

#define FMT_ULONG 40 /* enough space to hold 2^128 - 1 in decimal, plus \0 */
#define FMT_LEN ((char *) 0) /* convenient abbreviation */

/**
 * fmt_ulong - serialise an unsigned long
 * @dest: (maybe-NULL) the output
 * @value: the value to write
 * returns: the number of bytes written/needed.
 *
 * If @dest is NULL, nothing is written, but the number of bytes that would
 * have been written is still returned.
 */
extern unsigned int fmt_ulong(char *dest, unsigned long value);

#endif
