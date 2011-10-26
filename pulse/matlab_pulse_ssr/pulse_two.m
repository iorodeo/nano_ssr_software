function pulse_two(port)
% pulse_two.m - example of pulsing two solid state relays simultaneously

% Create an instnace and open the device
dev = PulseSSR(port);
dev.open();

% Set number of pulses and period for channels 0 and 1
for i = 0:1
    dev.setNumPulse(i,5);
    dev.setPeriod(i,1000);
end

% Set number of pulses for 2-7 to zero so they stay off when startAll is
% called. 
for i = 2:7
    dev.setNumPulse(i,0);
end

dev.startAll()
dev.close()
