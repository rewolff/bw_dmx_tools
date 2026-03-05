
// makechar.c (C) R.E.Wolff@BitWizard ca 1996. 
//
// Outputs characters from the decimal integers provided on the commandline. 
// 
// Provided with the bw_dmx_tools to allow you to set a channel
// from the commandline with just this tool and standard Linux commands. 
// Since there is now "set_dmx", this is no longer really necessary. 
// 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main (int argc,char **argv)
{
  long i,ch;

  for (i=1;i<argc;i++)
    {
      //sscanf (argv[i],"%d",&ch);
      ch = strtol (argv[i], NULL, 0);
      putchar (ch);
    }
  exit (0);
}
