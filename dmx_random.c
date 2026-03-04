

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

#include "libdmx.h"

int main (int argc, char **argv) 
{
  unsigned char *dmxdata;

  dmxdata = open_dmx ();

  while (1) {
    for (int i=0;i<64;i++)
      dmxdata[1+i] = random ();
    usleep (25000);
  }
  exit (0);
}
