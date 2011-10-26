from pulse_ssr import PulseSSR

dev = PulseSSR(port='/dev/ttyUSB0', baudrate=9600,timeout=1)
dev.setPeriod(0,2000) # Set period of channel 0, to 2000ms (2s)
dev.setNumPulse(0,10) # Set number of pulses for channel 0, to 10
dev.start(0)


#dev.setPeriod(0,500)
#dev.setPeriod(1,1000)
#dev.setNumPulse(0,10)
#dev.setNumPulse(1,5)
#
#for i in range(2,8):
#    print i
#    dev.setNumPulse(i,0)
#
#for i in range(8):
#    print 'chan=%d, period=%d'%(i,dev.getPeriod(i))
#
#for i in range(8):
#    print 'chan=%d, num pulse=%d'%(i,dev.getNumPulse(i))
#
#for i in range(8):
#    print 'chan=%d, running=%s'%(i,dev.getRunning(i))
#
##dev.start(0)
##dev.start(1)
#dev.startAll()
#
#for i in range(8):
#    print 'chan=%d, running=%s'%(i,dev.getRunning(i))
