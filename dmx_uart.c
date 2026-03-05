
/* 
 * dmx_uart.c (C) R.E.Wolff@BitWizard.nl
 * 
 * Will read a DMX universe file and output on UART. 
 * e.g. with the BitWizard raspberry pi DMX addon board. 
 *
 */ 


#define _GNU_SOURCE


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>
#include <errno.h>
#include <string.h>

#include <sys/ioctl.h>
#include <asm/termbits.h>   /* termios2, BOTHER, TCGETS2, TCSETS2, etc. */


#include "libdmx.h"


int main (int argc, char **argv)
{
  //char *thefile;
  unsigned char *data;
  int uartfd;
  char *theuart = "/dev/ttyAMA0";
  int gap = 10000; // 1ms. 
  struct termios2 tio;

  data = open_dmx ();

  if (getenv ("THEUART")) theuart = getenv ("THEUART");

  uartfd = open(theuart, O_RDWR | O_NOCTTY);
  if (uartfd < 0) fatal("open %s", theuart);

  if (ioctl(uartfd, TCGETS2, &tio) < 0) fatal("tcgets2 (get)");

  /* cfmakeraw equivalent */
  tio.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL | IXON);
  tio.c_oflag &= ~OPOST;
  tio.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
  tio.c_cflag &= ~(CSIZE | PARENB);
  tio.c_cflag |=  CS8;

  /* Your DMX port settings */
  tio.c_cflag |=  CLOCAL;          /* local, no modem control */
  tio.c_cflag &= ~CRTSCTS;         /* no RTS/CTS */
  tio.c_cflag |=  CSTOPB;          /* 2 stop bits for DMX */
  tio.c_cflag &= ~PARENB;          /* no parity (redundant but explicit) */

  /* Custom baud rate */
  tio.c_cflag &= ~CBAUD;
  tio.c_cflag |=  BOTHER;
  tio.c_ispeed = 250000;
  tio.c_ospeed = 250000;

  /* Read behaviour: block until at least 1 byte */
  tio.c_cc[VMIN]  = 1;
  tio.c_cc[VTIME] = 0;

  if (ioctl(uartfd, TCSETS2, &tio) < 0) fatal("tcsets2 (set)");

  while (1) {
    if (ioctl(uartfd, TIOCSBRK, NULL)  < 0) fatal ("TIOCCBRK");
    usleep (100);
    if (ioctl(uartfd, TIOCCBRK, NULL)  < 0) fatal ("TIOCSBRK");
    usleep (10);
    if (write (uartfd, data, 0x201) < 0) fatal ("write");

    // Note that on Linux the write effectively returns immediately. 
    // So we need to wait for the output to drain. 
    if (tcdrain(uartfd) < 0) fatal("tcdrain");

    // then we can sleep for the gap time. 
    usleep (gap);
  }
}
