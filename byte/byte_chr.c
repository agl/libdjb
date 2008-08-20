#include "byte.h"

unsigned int byte_chr(const char *s, unsigned int n, char c)
{
  const char *t = s;

  for (;;) {
    if (!n) break; if (*t == ch) break; ++t; --n;
    if (!n) break; if (*t == ch) break; ++t; --n;
    if (!n) break; if (*t == ch) break; ++t; --n;
    if (!n) break; if (*t == ch) break; ++t; --n;
  }

  return t - s;
}
