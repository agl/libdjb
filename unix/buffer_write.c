#include <unistd.h>
#include <limits.h>
#include "buffer.h"

int buffer_unixwrite(int fd,const char *buf,unsigned int len)
{
  if (len > INT_MAX) len = INT_MAX;
  return write(fd,buf,len);
}
