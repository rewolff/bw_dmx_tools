
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


#include "libdmx.h"


int main (int argc, char **argv)
{
  unsigned char *dmxdata;
  unsigned char olddata[522];

#define BUFSZ 0x80 
  // firmware has a similar limit. 
  char tmpbuf[BUFSZ];

  dmxdata = open_dmx ();

  for (int i=0;i<513;i++)
    olddata [i] = dmxdata[i]+1;
  printf ("echo 0\n");

  while (1) {
    int i;

    for (i=1;i<513;i++) {
      if (olddata[i] == dmxdata[i]) continue;

      sprintf (tmpbuf, "dmx %d", i);
      for (int j=0;j<16;j++) {
	olddata[i+j] = dmxdata[i+j];
	sprintf (tmpbuf+strlen (tmpbuf), " %d", olddata[i+j]);
      }
      printf ("%s\n", tmpbuf);
    }
    fflush (stdout);
    usleep (10000);
  }

  exit (1);
}
