function pulse_ssr_example(port)
% pulse_ssr_example.m - A simple example demonstrating the use of the 
% PusleSSR class which provides a serial interface an Arduino running the 
% pulse_ssr_firmware.
%
% Usage:  pulse_ssr_example('com5')
% 

% Create an instnace and open the device
dev = PulseSSR(port);
dev.open();

% Set the period (in ms) and the number of pulses for channel 0
dev.setPeriod(0,1500);
dev.setNumPulse(0,8);

% Start the pulses on channel 0
dev.start(0);

% Close the device
dev.close();


