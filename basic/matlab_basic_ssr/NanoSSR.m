% NanoSSR - provides a simple serial interface to IO Rodeo's solid state
% relay expansion board for the Arduino Nano. 
%
%
% Usage:
%
% dev = NanoSSR(port)  % where port = com1, or com15, etc.
% dev.setSSR(0, 1)     % Turns on SSR #0 
% dev.setSSR(5, 0)     % Turns off SSR #5
% dev.setAllSSR(1)     % Turns on all SSRs
% -------------------------------------------------------------------------
classdef NanoSSR < handle
    
    properties
       dev = [];
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
        
    end
    
    properties (Dependent)
       isOpen; 
    end
    
    methods
       
        function self = NanoSSR(port)
            % Creates a NanoSSR instance
            if (nargin ~=1)
                error('Usage: self = NanoSSR(port)');
            end
            self.dev = serial( ...
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
            delete(self.dev);
        end
        
        function open(self)
            % Opens a serial connection to the gap crossing control
            % interface device.
            fopen(self.dev);
            if self.resetDelay == true
                pause(self.resetDelaySec)
            end;
        end
        
        function close(self)
            % Closes the seraial connection to the gap crossing control
            % interface device.
            fclose(self.dev);
        end
        
         function isOpen = get.isOpen(self)
            % Checks is serial port is open. Returs true (1) if it is and
            % false (0) if it is not.
            status = get(self.dev,'Status');
            if strcmpi(status,'open')
                isOpen = true;
            else
                isOpen = false;
            end
         end
        
         function setSSR(self, num, value)
             % Sets the value of relay num to value where num can be in the
             % range 0, .. 7 and value 0 (off) or 1 (on). 
             if (num < 0 || num > 7)
                 error('relay number must be between 0 and 7'); 
             end
             if ~((value==0) || (value==1))
                 error('value must be either 0 or 1');
             end
             numInt = floor(num);
             valueInt = floor(value);
             cmd = sprintf('[%d, %d]\n', numInt, valueInt);
             fwrite(self.dev, cmd);
         end
         
         function setAllSSR(self, value)
             % Sets the value of all relays where value = 0 (on) an value =
             % 1 (off). 
             if ~((value==0) || (value==1)) 
                 error('value must be either 0 or 1');
             end
             valueInt = floor(value);
             cmd = sprintf('[8, %d]\n', valueInt);
             fwrite(self.dev, cmd);
         end
        
    end
end