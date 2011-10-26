function test_pulse
    dev = PulseSSR('com55');
    dev.open()
    
%     dev.start(0)
%     pause(2.0)
%     dev.stop(0)
%     dev.close()

%     dev.startAll()
%     pause(2.0)
%     dev.stopAll()

    dev.setPeriod(0,500);
    dev.setNumPulse(0,10);
    
    period = dev.getPeriod(0);
    fprintf('period: %f\n',period);
    
    numPulse = dev.getNumPulse(0);
    fprintf('numPulse: %f\n',numPulse);
    
    running = dev.getRunning(0);
    fprintf('running: %d\n', running);
    
    dev.start(0);
    
    running = dev.getRunning(0);
    fprintf('running: %d\n', running);
end