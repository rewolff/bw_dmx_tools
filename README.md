
## bw_dmx_tools

BitWizard DMX tools. 
existing DMX tools like OLA and QLC+ are way too complicated to 
work with easily. The idea is that it is simple and extensible. 

A driver for a piece of hardware should be less than an afternoon of
work.

## Advantages. 

OLA has a fancy web gui, but writing a driver or having several
different programs control several different sections of the DMX
universe is difficult. It shouldn't be. 

So for now there is no fancy web gui, but such a thing can be easily
made. 

So in BitWizard DMX drivers are  super simple. Three drivers are under
150 lines of code each. That's how it should be. The other two that
are currently present are longer because it is trickier to handle the 
Linux OS in those cases. 

QLC+ handles transitions from one scene to the next on its own. That's
nice if you're doing the lights for a theatre production, but maybe
not if you have a bunch of lights on one DMX universe, where the
lights might be in different rooms, so you might want different
programs controlling the lights in different ways.

## Output drivers

* bw_dmx . Should be called dmx_spi : Controls a BitWizard DMX module
over SPI. Not sure if this works yet. 

* bw_usb . Controls a BitWizard DMX module over USB. 

* bw_uart . outputs TTL DMX signals on the TX of an embedded CPU like
a raspberry pi. BitWizard has the DMX interface for raspberry pi. That
module isolates the DMX from the PI, does the level conversion and
provides proper XLR connectors.

* dmx2ola . This outputs a bitwizard DMX universe to OLA so that you can
use OLA output devices and features. 

* dmx_udp . This outputs an ARTNET like UDP stream to something that 
understands this. BitWizard sells the eth_dmx module that is an example that 
works.  

## testing and tools

* set_dmx The most practical tool: It sets a channel to a value from the 
commandline. This can be used to generate complex systems, for example a light
that indicates a certain status in a home automation setup. (e.g. red for 
"something wrong")

* mkdmx will create a universe file. 

* test_lamp should be able to test an RGB light by fading from red to green to blue. 

* walk moves a single light along a range of channels. 

* run_dmx will show a kitt effect: a light spot moves along the channels, with adjacent
channels also lighting up. 

* set_output allows you to sed a short or int in the DMX universe. I don't
  remember when this was useful. 










