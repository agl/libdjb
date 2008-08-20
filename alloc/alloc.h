#ifndef ALLOC_H
#define ALLOC_H

/**
 * alloc - allocate bytes
 * @n: number of bytes to allocate
 * returns: (maybe-NULL) a pointer to an uninitialised buffer of @n bytes
 */
static inline char *alloc(unsigned int n) {
  return malloc(n);
}

/**
 * alloc_free - release a buffer returned from `alloc`
 * @x: (maybe-NULL) the buffer
 */
static inline void alloc_free(void *x) {
  free(x);
}

/**
 * alloc_re - reallocate a buffer
 * @ptr: (input/output) in entry, a pointer to a buffer returned by `alloc`. On
 *   successful exit, contains the new pointer
 * @m: number of bytes used in the current buffer
 * @n: the desired size of the new buffer
 * returns: 0 on success
 *
 * Allocates a new buffer of size @n and copies @m bytes from the old buffer
 * into the new buffer and frees the old buffer. If allocation fails, the old
 * buffer is unchanged.
 */
static inline int alloc_re(char **ptr, unsigned int m, unsigned int n) {
  char *ret;

  ret = malloc(n);
  if (!ret) return 0;
  memcpy(ret, *ptr, m);
  free(*ptr);
  *ptr = ret;

  return 1;
}

#endif
