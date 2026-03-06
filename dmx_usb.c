
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


#include "libdmx.h"


int main (int argc, char **argv)
{
  unsigned char *dmxdata;
  unsigned char olddata[522];
  FILE *outfile;


#define BUFSZ 0x80 
  // firmware has a similar limit. 
  char tmpbuf[BUFSZ];

  dmxdata = open_dmx ();

  if (argc > 1) {
    outfile = fopen (argv[1], "w");
    if (!outfile) fatal ("open %s", argv[1]);
  } else
    outfile = stdout;

  // make sure we update all positions the first time. 
  // This is not watertight: The value might change to the 
  // "not equal" value we set it here before we get a chance
  // to update the hardware.   for (int i=0;i<513;i++)
  for (int i=0;i<0x201;i++)
    olddata [i] = dmxdata[i]+1;

  fprintf (outfile, "echo 0\n");

  while (1) {
    int i, m;
    int changed;

    changed = 0;
    
    for (i=1;i<513;i++) {
      if (olddata[i] == dmxdata[i]) continue;

      sprintf (tmpbuf, "dmx %d", i);

      // We do (max) 16 locations in one command. With max 4 chars 
      // per channel, that's 64, so we're staying below the 80, 0x80 
      // or whatever the limit is in the firmware... 
      for (m=15;m>0;m--) 
	if (olddata[i+m] != dmxdata[i+m]) break;
      m++; // current pos differs, so increment to first doesn't differ pos. 


      // Note that we're assembling a command in the tmpbuf, and printing
      // it in one go. This ensures that we don't end up sending very
      // small packets over USB. This makes explicit the buffering that 
      // stdio would otherwise probably do. 
      for (int j=0;(j<m) && ((i+j) < 513) ;j++) {
	olddata[i+j] = dmxdata[i+j];
	sprintf (tmpbuf+strlen (tmpbuf), " %d", olddata[i+j]);
      }
      changed++;
      fprintf (outfile, "%s\n", tmpbuf);
    }
    if (changed) fflush (outfile);

    usleep (10000);
  }

  exit (1);
}
