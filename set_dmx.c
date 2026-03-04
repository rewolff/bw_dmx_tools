
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include "libdmx.h"


int main (int argc, char **argv) 
{
  char *dmxdata;
  int start;
  int nn;


  if (argc <= 1) {
    fprintf (stderr, "Usage: %s [pos or range] [value]*\n", argv[0]);
    exit (1);
  }

  dmxdata = open_dmx ("dmxdata");
  
  start = atoi (argv[1]); 
  char *p = strchr (argv[1], '-');
  if (p) {
     int end = atoi (p+1);
     nn = end-start+1;
  } else 
     nn = 1;
  int d = start+1;
  //printf ("start = %d, nn = %d, d=%d.\n", start, nn, d );
  for (int i = 2;i< argc;i++) 
     for (int j = 0;j<nn;j++)
        dmxdata[d++] = atoi (argv[i]);
  exit (0);
}
