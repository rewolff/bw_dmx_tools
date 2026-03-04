#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

#include "libdmx.h"

int base = 14;
unsigned char *dmxdata;

void set (int p, int v)
{
   if (p < 0) return;
   if (p > 63) return;

//   printf ("%d %d.\n", p, v);
   dmxdata[p+1] = v;
}

void doit (int a, int b)
{
  int i;
  for (i=0;i<255;i+=10) {
    set (base +a, 255-i);
    set (base +b,     i);
    usleep (40000);
  }
  set (base + a, 0);
  set (base + b, 255);
}

int main (int argc, char **argv)
{
  if (argc > 1) base = atoi (argv[1]);

  dmxdata = open_dmx ();

  set (10, 0);
  set (11, 0);
  set (12, 0);

  while (1) {
    doit (0, 1);
    doit (1, 2);
    doit (2, 0);
  }
}


