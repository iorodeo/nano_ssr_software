matlab_nano_ssr - a simple library for serial communications with IO Rodeo's
solid state relay expansion board for the Arduino Nano. 

Installation:

1. Add the matlab_nano_ssr directory to your matlab path. 


Usage:

dev = NanoSSR(port)  % where port = com1, or com15, etc.
dev.setSSR(0, 1)     % Turns on SSR #0 
dev.setSSR(5, 0)     % Turns off SSR #5
dev.setAllSSR(1)     % Turns on all SSRs

Examples

nano_ssr_example.m  - turns relay on and then off in sequece with a 0.5 sec
delay. Then turns on all relays and turns them off again. 

Example usage:  nano_ssr_example('com15') 


