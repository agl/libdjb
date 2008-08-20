#ifndef SCAN_H
#define SCAN_H

/**
 * scan_ulong - parse leading integer
 * @s: data to parse
 * @u: (output) the result
 * returns: the number of bytes parsed
 *
 * Reads from @s until a byte outside '0'..'9' is found. Thus a return value of
 * 0 means that nothing was parsed. In this case, 0 is written to @u.
 */
extern unsigned int scan_ulong(const char *,unsigned long *);

#endif
