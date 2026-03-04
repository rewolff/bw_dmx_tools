#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>


#include "libdmx.h"

unsigned char *dmxdata;

int minpos = 0;
int maxpos = 512;

void set (int p, int v)
{
   if (p < 0) return;
   if (p > 63) return;
   dmxdata[p+1] = v;
}


int main (int argc, char **argv)
{
  int w = 10;
  int p, i;
  int s; 

  dmxdata = open_dmx ();

  s = maxpos-minpos;

  while (1) {
     for (p=-w;p<s+w;p++) {
        for (i=-w;i <= 0;i++)
           set (minpos+p+i, 255+i*(255/w));
        for (;i <= w;i++)
           set (minpos+p+i, 255-i*(255/w));
        usleep (20000);
     }
  }

}


