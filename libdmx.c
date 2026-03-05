

#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>

#include "libdmx.h"

volatile void fatal ( char *s,...)
{
    va_list v;
    char buf[1000];
    
    va_start (v,s);
    vsprintf (buf,s,v);

    if (errno)
        perror (buf);
    else
        fprintf (stderr,"%s\n",buf);
    exit (1);
}



unsigned char *open_dmx (void)
{
  int infd;
  char *fname;
  int universe = 0;
  char fnamebuf[256];

  if (getenv ("DMXDATA")) fname = getenv ("DMXDATA");
  else {
    if (getenv ("DMX_UNIVERSE")) universe = atoi (getenv("DMX_UNIVERSE"));
    sprintf (fnamebuf, "%s/.dmx/universe%d", 
	     getenv ("HOME"), 
	     universe);
    fname = fnamebuf;
  }

  infd = open (fname, O_RDWR); 
  if (infd < 0) fatal ("open %s", fname);

  unsigned char *data = mmap (NULL, 0x200, PROT_READ | PROT_WRITE, MAP_SHARED, infd, 0);

  if (data == NULL) fatal ("mmap %s", fname);

  return data;
}




int mkuniverse (int universe)
{
  int fd, rv;
  char fname[128];

  sprintf (fname, "%s/.dmx", getenv ("HOME"));
  rv = mkdir (fname, 0777);

  (void) rv; // If the mkdir failed, the directory probably alredy existed. 

  sprintf (fname, "%s/.dmx/universe%d", getenv ("HOME"), universe);
  fd = open (fname, O_CREAT | O_WRONLY, 0666);
  if (fd < 0) fatal ("opening %s", fname);

  if (ftruncate (fd, 0x201) < 0) fatal ("ftruncate %s", fname);
  close (fd);

  return 0; 
}

