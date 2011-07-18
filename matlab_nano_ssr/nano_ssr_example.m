function nano_ssr_example(port)
% nano_ssr_example - a simple examples demonstrating the use of the nano
% ssr matlab library. 
%
% Usage: 
% dev = nano_ssr_example(port) where port = com1, or com14, etc. 
%

    dev = NanoSSR(port);
    
    dev.open();
    
    for i = 0:7
        % Set SSR i on 
        dev.setSSR(i,1);
        pause(0.5);
        
        % Set SSR i off
        dev.setSSR(i,0);
        pause(0.5);
    end
    
    % Set all SSRs on
    dev.setAllSSR(1);
    pause(0.5);
    
    % Set allSSRs off
    dev.setAllSSR(0);
    
    dev.close();
