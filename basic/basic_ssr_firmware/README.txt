basic_ssr_firmware.pde

Basic firmware for IO Rodeo's solid state relay exapansion board for the
Arduino Nano. Enables users to set the values of the relay uisng serial
communications.  

Requirements:  

IO Rodeo SerialReceiver library:  http://bitbucket.org/iorodeo/iorodeo_arduino_libs.
Streaming library: http://arduiniana.org/2009/04/new-streaming-library/ 

Build instructions:

1.) Place the SerialReceiver library directory in the users sketchbook/libraries folder.
2.) Launch the Arduino IDE and open  nano_ssr_firmware.ino
3.) Build the firmware and download to arduino.

Testing from the arduion IDE. 

The relay values can be set from the serial monitor by sending the following commands:

[n, val]  where n is a number in the  (0,..,8) and val = 0, 1 where 0 = off and 1 = on

If n is in the range (0,...,7) this command will set the corresponding relay to value. If
n=8 the all relay will be set to the value given by val. 

For example:
[0,1] will set relay #0 on. 
[5,0] will set relay #5 off.
[8,1] will set all relays on. 

