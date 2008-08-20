#include <unistd.h>
#include <limits.h>
#include "buffer.h"

int buffer_unixread(int fd,char *buf,unsigned int len)
{
  if (len > INT_MAX) len = INT_MAX;
  return read(fd,buf,len);
}
