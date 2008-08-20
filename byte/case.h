#ifndef CASE_H
#define CASE_H

/**
 * case_lowerb - lowercase a string
 * @s: string to lowercase
 * @len: number of bytes in @s
 *
 * For each byte in the string between 'A' and 'Z', replace with the lowercase
 * version of byte
 */
extern void case_lowerb(char *s, unsigned int len);

/**
 * case_diffs - a case-insensitive string ordering function
 *
 * The two strings are walked concurrently. If a byte is found to differ in
 * more than just case, then the difference between the byte in the first
 * string and the second is returned.
 *
 * The walk terminates when a NUL byte is found in the first string. Thus, if
 * the function returns 0, the strings match.
 */
extern int case_diffs(const char *a, const char *b);

/**
 * case_diffb - a case-insensitive data ordering function
 *
 * The two memory regions are walked concurrently. If a byte is found to differ
 * in more than just case, then the difference between the byte in the first
 * region and the second is returned.
 *
 * If walk terminates after @len bytes, in which case the return value is 0
 */
extern int case_diffb(const char *a ,unsigned int len, const char *b);

#define case_equals(s,t) (!case_diffs((s),(t)))

#endif
