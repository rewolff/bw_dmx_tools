
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>


int main (int argc, char **argv)
{
  int universe = 0;
  char fname[128];
  int fd, rv;

  if (argc > 1) universe = atoi (argv[1]);

  sprintf (fname, "%s/.dmx", getenv ("HOME"));
  rv = mkdir (fname, 0777);

  (void) rv; // If the mkdir failed, the directory probably alredy existed. 

  sprintf (fname, "%s/.dmx/universe%d", getenv ("HOME"), universe);
  fd = open (fname, O_CREAT | O_WRONLY, 0666);
  if (fd < 0) {
    perror (fname);
    exit (1);
  }

  if (ftruncate (fd, 0x201) < 0) {
    perror ("ftruncate");
    exit (1);
  }
  close (fd);
  exit (0);

}
