

#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <string.h>
#include <sys/mman.h>



char *open_dmx (char *fname)
{
  int infd;

  infd = open (fname, O_RDWR); 
  if (infd < 0) {
    perror (fname);
    exit (1);
  }

  char *data = mmap (NULL, 0x200, PROT_READ | PROT_WRITE, MAP_SHARED, infd, 0);

  if (data == NULL) {
    perror ("mmap");
    exit (1);
  }
  return data;
}
