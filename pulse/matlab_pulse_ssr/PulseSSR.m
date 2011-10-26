classdef PulseSSR < handle
    
    properties
        ser = [];
        resetDelay = true;
    end
    
    properties (Constant)
        % Serial communications parameters
        baudrate = 9600;
        databits = 8;
        stopbits = 1;
        timeout = 0.5;
        % Delay for reserial reset
        resetDelaySec = 2.0;
        % Command Ids
        cmdStop = 0;
        cmdStart = 1;
        cmdStartAll = 2;
        cmdStopAll = 3;
        cmdSetPeriod = 4;
        cmdGetPeriod = 5;
        cmdSetNumPulse = 6;
        cmdGetNumPulse = 7;
        cmdGetRunning = 8;
    end
    
    properties (Dependent)
        isOpen;
    end
    
    methods
        
        function self = PulseSSR(port)
            % Creates a PulseSSR instance
            if (nargin ~=1)
                error('Usage: self = PulseSSR(port)');
            end
            self.ser = serial( ...
                port, ...
                'baudrate', self.baudrate, ...
                'databits', self.databits, ...
                'stopbits', self.stopbits, ...
                'timeout',  self.timeout ...
                );
        end
        
        function delete(self)
            % Object delete function.
            if self.isOpen
                self.close();
            end
            delete(self.ser);
        end
        
        function open(self)
            % Opens a serial connection to the gap crossing control
            % interface serice.
            fopen(self.ser);
            if self.resetDelay == true
                pause(self.resetDelaySec)
            end;
        end
        
        function close(self)
            % Closes the seraial connection to the gap crossing control
            % interface serice.
            fclose(self.ser);
        end
        
        function isOpen = get.isOpen(self)
            % Checks is serial port is open. Returs true (1) if it is and
            % false (0) if it is not.
            status = get(self.ser,'Status');
            if strcmpi(status,'open')
                isOpen = true;
            else
                isOpen = false;
            end
        end
        
        function sendCmd(self,cmd)
            % Send command to serial serice
            if self.isOpen
                fprintf(self.ser,'%s\n',cmd);
            else
                error('serice must be open to send message');
            end
        end
        
        function val = readNum(self)
            % Reads a single number from the serial port.
            outStr = fscanf(self.ser);
            val = str2num(outStr);
        end
        
        function start(self,n)
            % Start pulses on channel n
            checkDevNum(n)
            cmd = sprintf('[%d,%d]',self.cmdStart,n);
            self.sendCmd(cmd)
        end
        
        function stop(self,n)
            % Stop pulse and channel n
            checkDevNum(n)
            cmd = sprintf('[%d,%d]',self.cmdStop,n);
            self.sendCmd(cmd);
        end
        
        function startAll(self)
            % Start pulses on all device
            cmd = sprintf('[%d]',self.cmdStartAll);
            self.sendCmd(cmd);
        end
        
        function stopAll(self)
            % Stops pulses on all devices.
            cmd = sprintf('[%d]',self.cmdStopAll);
            self.sendCmd(cmd);
        end
        
        function setPeriod(self,n,period)
           % Sets the pulse period of channel n in milliseconds.
           checkDevNum(n);
           checkPeriod(period);
           cmd = sprintf('[%d,%d,%d]',self.cmdSetPeriod,n,period);
           self.sendCmd(cmd);
        end
       
        function period = getPeriod(self,n)
           % Returns the period of channel n in milliseconds
           checkDevNum(n);
           cmd = sprintf('[%d,%d]',self.cmdGetPeriod,n);
           self.sendCmd(cmd);
           period = self.readNum();
        end
        
        function setNumPulse(self,n,numPulse)
           % Sets the number of pulses (per start event) for channel n
           checkDevNum(n);
           checkNumPulse(numPulse);
           cmd = sprintf('[%d,%d,%d]',self.cmdSetNumPulse,n,numPulse);
           self.sendCmd(cmd);
        end
        
        function numPulse = getNumPulse(self,n)
            % Returns the number of pulses (per start event) for channel n
            checkDevNum(n);
            cmd = sprintf('[%d,%d]',self.cmdGetNumPulse,n);
            self.sendCmd(cmd);
            numPulse = self.readNum();
        end
        
        function running = getRunning(self,n)
           % Returns the running state of channel n (true or false)
           checkDevNum(n);
           cmd = sprintf('[%d,%d]',self.cmdGetRunning,n);
           self.sendCmd(cmd);
           running = self.readNum();
           if running ~= 0
               running = true;
           else
               running = false;
           end
        end
      
        
    end
end

function checkDevNum(n)
% Checks that the device number is an integer and >= 0
if rem(n,1) ~= 0
    error('device number must be an integer')
end
if n < 0
    error('device number must be >= 0')
end
end

function checkPeriod(value)
if rem(value,1) ~= 0
    error('period must be an integer');
end
if value < 0
    error('period must be >= ');
end
end

function checkNumPulse(value)
if rem(value,1) ~= 0
    error('number of pulses must be an integer');
end
if value < 0
    error('number of pulses must be >= ');
end
end