#ifndef IP4_H
#define IP4_H

/**
 * ip4_scan - parse a dotted-quad address
 * @input: a string, starting with a dotted-quad address
 * @result: a 4 byte buffer for the big-endian IP address
 * returns: 0 on failure, otherwise the number of bytes parsed.
 *
 * A dotted-quad address is read from *input. Note that input should be NUL
 * terminated.
 */
extern unsigned int ip4_scan(const char *input, char *result);

/**
 * ip4_fmt - format an IPv4 address
 * @dest: (maybe-NULL) a buffer of, at least, 16 bytes
 * @ip: a big-endian, 4 byte address
 * returns: 0 on failure, otherwise the number of bytes written.
 *
 * The address is written in dotted-quad format to @dest. No NUL is written at
 * the end.
 *
 * If @dest is NULL, nothing is written buy the number of bytes that would have
 * been written is still returned.
 */
extern unsigned int ip4_fmt(char *dest, const char *ip);

#define IP4_FMT 20

#endif
