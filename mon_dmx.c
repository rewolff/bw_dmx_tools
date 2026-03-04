
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>


#include "libdmx.h"

int main (int argc, char **argv)
{
  unsigned char *data, tdata[0x200];
  int i;

  data = open_dmx ();

  //  printf ("data=%p.\n", data);
  //dmxmode = DMX_TX;
  while (1) {
    if (memcmp (data, tdata, 0x200) != 0) {
      // the first byte should be zero indicating "DMX transfer". 
      // The DMX data starts at offset 1. 
      for (i=1;i<512;i++)
	printf ("%d,", data[i]);
      printf ("%d\n", data[i]);
      fflush (stdout);
       memcpy (tdata, data, 0x200);
    } 
    usleep (10000);
  }
  exit (0);
}
