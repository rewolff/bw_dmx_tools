
CFLAGS=-Wall -O2
CC=gcc 

MYBIN=bw_dmx mon_dmx dmx2ola dmx_uart makechar set_output \
	dmx_udp set_dmx dmx_random mkdmx run_dmx dmx_usb \
	bw_osc 

LIBDMX=libdmx.o

all: $(MYBIN)

install: $(MYBIN)
	cp $(MYBIN) /usr/bin

clean:
	rm -f *~ *.o $(MYBIN)


$(MYBIN): %: %.c $(LIBDMX)
	$(CC) $(CFLAGS) -o $@ $< $(LIBDMX)

