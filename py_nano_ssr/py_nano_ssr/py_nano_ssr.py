"""
Python serial interface to the IO Rodeo solid state relay expansion board for 
the Arduino Nano. 

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
import serial

class pyNanoSSR(serial.Serial):

    def __init__(self,**kwargs):
        super(pyNanoSSR,self).__init__(**kwargs)

    def setSSR(self, ssrNum, ssrVal):
        """
        Set value of individual solid state relay
        """
        if not ssrNum in range(0,8):
            raise ValueError, 'ssrNum must be between 0 and 8'
        if not type(ssrVal) == bool:
            raise ValueError, 'ssrVal must be boolean'
        if ssrVal == True:
            self.write('[%d, 1]\n'%(ssrNum,))
        else:
            self.write('[%d, 0]\n'%(ssrNum))

    def setAllSSR(self,ssrVal):
        if not type(ssrVal) == bool:
            raise ValueError, 'ssrVal must be boolean'
        if ssrVal == True:
            self.write('[8, 1]\n')
        else:
            self.write('[8, 0]\n')


