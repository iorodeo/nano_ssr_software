from pulse_ssr import PulseSSR

dev = PulseSSR(port='/dev/ttyUSB0', baudrate=9600,timeout=1)

for i in range(8):
    dev.setPeriod(i,(i+1)*200)
    dev.setNumPulse(i,i+2)

# Print periods
for i in range(8):
    print 'chan=%d, period=%d'%(i,dev.getPeriod(i))
print

# Print number pulses
for i in range(8):
    print 'chan=%d, num pulse=%d'%(i,dev.getNumPulse(i))
print

# Print running 
for i in range(8):
    print 'chan=%d, running=%s'%(i,dev.getRunning(i))
print

dev.startAll()

# Print running
for i in range(8):
    print 'chan=%d, running=%s'%(i,dev.getRunning(i))
print
