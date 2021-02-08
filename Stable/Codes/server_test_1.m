clear all, close all, clc

wattmeter = tcpip('0.0.0.0', 11500, 'NetworkRole', 'server');
% Open a connection. This will not return until a connection is received.
fopen(wattmeter); %% REMEMBER TO CLOSE THIS CONNECTION LATER
format compact;

%%

limit = 100; %take reading of 100 values

while true
    
    voltage = zeros(limit,1); %initialize new buffer
    current = zeros(limit,1);
    power = zeros(limit,1);
    time = zeros(limit,1);
    
    current_time = uint32(clock()); %get the initial time
    time(1) = current_time(5)*60 + current_time(6); % minute and second to seconds
    for idx = 2:limit
        time(idx) = time(idx-1) + 1 ; %create a time axis of per second sampling
    end
    
    idx = 0;
    
    while true
        if (wattmeter.BytesAvailable)
            
            idx = idx + 1; %taking next reading
            incoming_data = fgets(wattmeter); %read one line of incoming data
            incoming_data = split(incoming_data,','); %split the line into the three fields

            voltage(idx) = str2num(char(incoming_data(1)));
            current(idx) = str2num(char(incoming_data(2)));
            power(idx) = str2num(char(incoming_data(3)));
            
            %plot(time,voltage,'r',time,current,'b',time,power);
            %drawnow;
            
            disp([voltage(idx),current(idx),power(idx)]);
            
        end
        
        if (idx == limit)
            break;
        end
    end
    
end

%%

fclose(wattmeter); %close the connection
clear wattmeter;