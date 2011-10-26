"""
Provides a serial interface to Arduinos running the pulse_ssr_firmware 
for pulsing solid state relays.

Author: Will Dickson, IO Rodeo Inc.

Copyright 2010  IO Rodeo Inc.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
"""
import time
import serial

RESET_SLEEP_DT = 2.0

class PulseSSR(serial.Serial):

    def __init__(self,*arg,**kwargs):
        try:
            self.resetSleep = kwargs.pop('reset_sleep')
        except KeyError:
            self.resetSleep = True
        super(PulseSSR,self).__init__(*arg,**kwargs)

        self.cmdId = {
                'stop'        : 0, 
                'start'       : 1,
                'startAll'    : 2,
                'stopAll'     : 3,
                'setPeriod'   : 4, 
                'getPeriod'   : 5,
                'setNumPulse' : 6,
                'getNumPulse' : 7, 
                'getRunning'  : 8,
                }
        if self.resetSleep:
            time.sleep(RESET_SLEEP_DT)

    def sendCmd(self,cmd):
        self.write(cmd)

    def readValue(self):
        """
        Read a value from the device.
        """
        line = self.readline()
        line = line.strip()
        return line

    def readInt(self):
        """
        Read a single integer or list of integers separated by commas.
        """
        value = self.readValue()
        value = int(value)
        return value

    def setPeriod(self,n,period):
        """
        Set period of relay n to the value given by period in milliseconds. 
        """
        _n = int(n)
        assert _n >= 0, 'pin number must be >= 0'
        _period = int(period)
        assert _period > 0, 'period must be > 0' 
        cmd = '[%d,%d,%d]'%(self.cmdId['setPeriod'],_n,_period)
        self.sendCmd(cmd)

    def getPeriod(self,n):
        """
        Returns the curren period setting for relay n in milliseconds
        """
        _n = int(n)
        assert _n >=0, 'pin number must be >= 0'
        cmd = '[%d,%d]'%(self.cmdId['getPeriod'],_n)
        self.sendCmd(cmd)
        period = self.readInt()
        return period

    def setNumPulse(self,n,numPulse):
        """
        Set the number of pulses (per start event) for relay n. 
        """
        _n = int(n)
        assert _n >= 0, 'pin number must be >= 0'
        _numPulse = int(numPulse)
        assert _numPulse >= 0, 'number of pulses must be >= 0'
        cmd = '[%d,%d,%d]'%(self.cmdId['setNumPulse'],_n,_numPulse)
        self.sendCmd(cmd)

    def getNumPulse(self,n):
        """
        Returns the numbers of pulses (per start event) for relay n.
        """ 
        _n = int(n)
        assert _n >= 0, 'pin number must be >= 0'
        cmd = '[%d,%d]'%(self.cmdId['getNumPulse'],_n)
        self.sendCmd(cmd)
        numPulse = self.readInt()
        return numPulse

    def getRunning(self,n):
        """
        Returns true is the relay is running (sending out pulses) and false otherwise.
        """
        _n = int(n)
        assert n >= 0, 'pin number must be >= 0'
        cmd = '[%d,%d]'%(self.cmdId['getRunning'],_n)
        self.sendCmd(cmd)
        running = self.readInt()
        if running != 0:
            running = True
        else:
            running = False
        return running

    def start(self,n):
        """
        Start pulses on relay n
        """
        _n = int(n)
        assert _n >= 0, 'pin number must be >= 0'
        cmd = '[%d,%d]'%(self.cmdId['start'],_n)
        self.sendCmd(cmd)

    def stop(self,n):
        """
        Stop pulses on relay n
        """
        _n = int(n)
        assert _n >= 0, 'pin number must be >= 0'
        cmd = '[%d,%d]'%(self.cmdId['stop'],_n)
        self.sendCmd(cmd)

    def startAll(self):
        """
        Start all solid state relays pulsing.
        """
        cmd = '[%d]'%(self.cmdId['startAll'],)
        self.sendCmd(cmd)




