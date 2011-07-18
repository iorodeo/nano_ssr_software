import time
from py_nano_ssr import pyNanoSSR

dev = pyNanoSSR(port='/dev/ttyUSB0',timeout=1)
time.sleep(2.0)  # Sleep for serial reset of arduino

for i in range(0,8):
    dev.setSSR(i,True)
    time.sleep(0.25)
    dev.setSSR(i,False)
    time.sleep(0.25)

dev.setAllSSR(True)
time.sleep(0.25)
dev.setAllSSR(False)

