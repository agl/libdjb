#ifndef BUFFER_H
#define BUFFER_H

/**
 * struct buffer - a buffer
 * @x: a pointer to the buffer space
 * @p: the number of bytes of @x used
 * @n: the number of bytes in @x
 * @fd: the file descriptor associated with this buffer
 * @op: a function to read/write the buffer
 *
 * In the case that a buffer is used for reading, the members change slightly.
 * @n now points to the first unread byte and @p is the number of unread bytes.
 */
typedef struct buffer {
  char *x;
  unsigned int p;
  unsigned int n;
  int fd;
  int (*op)();  // (int fd, void *buf, unsigned int len)
} buffer;

#define BUFFER_INIT(op,fd,buf,len) { (buf), 0, (len), (fd), (op) }
#define BUFFER_INSIZE 8192
#define BUFFER_OUTSIZE 8192

extern void buffer_init(buffer *dest, int (*op)(), int fd,char * buf, unsigned int len);

/**
 * buffer_flush - write all data out
 * returns: -1 on error, or the number of bytes written. Note that some bytes
 * may have been written even if -1 is returned.
 */
extern int buffer_flush(buffer *);

/**
 * buffer_put - write to a buffer
 * returns: -1 on error, 0 on success
 *
 * Copies data @len bytes from @src to the buffer. If the buffer is too small,
 * it is flushed as needed (possibly multiple times).
 */
extern int buffer_put(buffer *buf, const char *src, unsigned int len);

/**
 * buffer_putalign - write to a buffer
 * returns: -1 on error, 0 on success
 *
 * Just like `buffer_flush`, however data is always written via the buffer thus
 * any flushes happen in the expected sized chunks
 */
extern int buffer_putalign(buffer *,const char *,unsigned int);

/**
 * buffer_putflush - put data in a buffer and flush
 * returns: -1 on error, 0 on success
 *
 * Append data to a buffer and flush
 */
extern int buffer_putflush(buffer *,const char *,unsigned int);

/**
 * buffer_puts - append a NUL terminated string
 * returns: -1 on error, 0 on success
 */
extern int buffer_puts(buffer *,const char *);

/**
 * buffer_putsalign - append a NUL terminated string
 * returns: -1 on error, 0 on success
 *
 * Appends a NUL terminated string, but always writes via the buffer thus any
 * flushes involved the expected number of bytes
 */
extern int buffer_putsalign(buffer *,const char *);

/**
 * buffer_putsflush - append a NUL terminated string and flush
 * returns: -1 on error, 0 on success
 */
extern int buffer_putsflush(buffer *,const char *);

#define buffer_PUTC(s,c) \
  ( ((s)->n != (s)->p) \
    ? ( (s)->x[(s)->p++] = (c), 0 ) \
    : buffer_put((s),&(c),1) \
  )

/**
 * buffer_get - read from a buffer
 * returns: -1 on error, otherwise the number of bytes written
 *
 * Read, at most, @len bytes from the buffer. If the buffer has data, that data
 * is returned. Otherwise, IO is performed to get more data.
 */
extern int buffer_get(buffer *, char *dest, unsigned int len);

/**
 * buffer_bget - read from a buffer
 * returns: -1 on error, otherwise the number of bytes written
 *
 * Like `buffer_get`, but at most the size of the buffer is returned.
 */
extern int buffer_bget(buffer *,char *,unsigned int);

/**
 * buffer_feed - fill a buffer
 * returns: -1 on error, otherwise the number of bytes in the buffer
 *
 * If the buffer is not empty, it's current size is returned. Otherwise IO is
 * performed to fill the buffer.
 */
extern int buffer_feed(buffer *);

/**
 * buffer_peek - get a pointer to the buffer data
 * returns: a pointer to the first unread byte in the buffer
 */
extern char *buffer_peek(buffer *);

/**
 * buffer_seek - skip bytes in a buffer
 * @n: the number of bytes to skip
 *
 * @n must be less than, or equal to the number of bytes in the buffer.
 */
extern void buffer_seek(buffer *, unsigned int n);

#define buffer_PEEK(s) ( (s)->x + (s)->n )
#define buffer_SEEK(s,len) ( ( (s)->p -= (len) ) , ( (s)->n += (len) ) )

#define buffer_GETC(s,c) \
  ( ((s)->p > 0) \
    ? ( *(c) = (s)->x[(s)->n], buffer_SEEK((s),1), 1 ) \
    : buffer_get((s),(c),1) \
  )

/**
 * buffer_copy - copy from one buffer to another
 * returns: 0 on succes, -2 on input error, -3 on output error
 *
 * Perform IO as needed to transfer all the data from @src to @dest.
 */
extern int buffer_copy(buffer *dest, buffer *src);

extern int buffer_unixread(int,char *,unsigned int);
extern int buffer_unixwrite(int,const char *,unsigned int);

/* Static buffers for stdin, stdout etc. Painfully non thread safe. */
extern buffer *buffer_0;
extern buffer *buffer_0small;
extern buffer *buffer_1;
extern buffer *buffer_1small;
extern buffer *buffer_2;

#endif
