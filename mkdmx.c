
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#include "libdmx.h"


int main (int argc, char **argv)
{
  int universe = 0;

  if (argc > 1) universe = atoi (argv[1]);

  mkuniverse (universe);
  exit (0);

}
