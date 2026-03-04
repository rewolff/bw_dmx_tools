#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>


unsigned char *dmxdata;


void set (int p, int v)
{
   if (p < 0) return;
   if (p > 63) return;

//   printf ("%d %d.\n", p, v);
   dmxdata[p+1] = v;

}


int main (int argc, char **argv)
{
  int w = 10;
  int p, i;
  dmxdata = open_dmx ("dmxdata");


  while (1) {
     for (p=-w;p<64+w;p++) {
        for (i=-w;i<= 0;i++)
           set (p+i, 255+i*(255/w));
        for (;i <= w;i++)
           set (p+i, 255-i*(255/w));
        usleep (40000);
     }
  }
}


