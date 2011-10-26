function test_pulse(port, test_name)
% test_pulse.m  provides number of simple test using the PulseSSR class.
%
% Usage: test_pulse(port, test_names)
%
% Allowed test names: 'start', 'start-loop', 'start-stop', 'start-all', 
% 'start-stop-all', 'set-get-period', 'set-get-num-pulse', 'get-running'
%

dev = PulseSSR(port);
dev.open();

switch test_name
    
    case 'start'
        dev.start(0);
        
    case 'start-loop'
        for i = 0:7
            dev.start(i);
            pause(0.5);
        end
        
    case 'start-stop'
        dev.start(1);
        pause(2.0);
        dev.stop(1);
        
    case 'start-all'
        dev.startAll();
        
    case 'start-stop-all'
        dev.startAll();
        pause(2.0);
        dev.stopAll();
        
    case 'set-get-period'
        dev.setPeriod(0,500);
        period = dev.getPeriod(0);
        fprintf('period: %f\n',period);
        dev.start(0);
        
    case 'set-get-num-pulse'
        dev.setNumPulse(0,10);
        numPulse = dev.getNumPulse(0);
        fprintf('numPulse: %f\n',numPulse);
        dev.start(0);
        
    case 'get-running'
        running = dev.getRunning(0);
        fprintf('running: %d\n', running);
        dev.start(0);
        running = dev.getRunning(0);
        fprintf('running: %d\n', running)
        
end

dev.close();
