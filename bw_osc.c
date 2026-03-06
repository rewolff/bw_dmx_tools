
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

// bw_osc (C) 2026 R.E.Wolff@BitWizard.nl
//
// This emulates ola_streaming_client for input to a DMX universe. 


#include "libdmx.h"

int main (int argc, char **argv)
{
  unsigned char *data, tdata[0x200];
  int i, p, val;

  // realistic max is 512*4 = 2k. 
#define BUFSIZE 0x8000
  char buf[BUFSIZE];

  data = open_dmx ();

  //  printf ("data=%p.\n", data);
  //dmxmode = DMX_TX;
  while (fgets (buf, BUFSIZE-1, stdin) != 0) {

    for (i=0,p=0;i<512;i++) {
      int n;
      sscanf (buf+p, "%d,%n", &val, &n);
      tdata[i] = val;
      p += n;
    }
    memcpy (data+1, tdata, 0x200);
  }
  exit (0);
}
