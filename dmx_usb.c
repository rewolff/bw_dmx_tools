
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
    int i, m;
    
    for (i=1;i<513;i++) {
      if (olddata[i] == dmxdata[i]) continue;

      sprintf (tmpbuf, "dmx %d", i);

      // We do (max) 16 locations in one command. With max 4 chars 
      // per channel, that's 64, so we're staying below the 80, 0x80 
      // or whatever the limit is in the firmware... 
      for (m=15;m>0;m--) 
	if (olddata[i+m] != dmxdata[i+m]) break;
      m++; // current pos differs, so increment to first doesn't differ pos. 
      for (int j=0;(j<m) && ((i+j) < 513) ;j++) {
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
