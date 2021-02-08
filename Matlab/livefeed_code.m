clear all, close all, clc
wattmeter = tcpip('0.0.0.0', 11500, 'NetworkRole', 'server');
% Open a connection. This will not return until a connection is received.
fopen(wattmeter); %% REMEMBER TO CLOSE THIS CONNECTION LATER
format compact;
%%%take reading of 100 values
h=figure(1);
current_time = uint32(clock()); %get the initial time
time(1) = current_time(5)*60 + current_time(6); % minute and second to seconds
idx = 0;
%load('d:\history_info','consume');
while ishandle(h)
    title('Server on');
    if  (wattmeter.BytesAvailable)
        idx = idx + 1; %taking next reading
        incoming_data = fgets(wattmeter); %read one line of incoming data
        incoming_data = split(incoming_data,','); %split the line into the three fields
        voltage(idx) = str2num(char(incoming_data(1)));
        current(idx) = str2num(char(incoming_data(2)));
        power(idx) = str2num(char(incoming_data(3)));
%         if power(idx)==NaN
%         else
%         consume(current_time(3))=consume(current_time(3))+power(idx);
%         end
        %plot(time,voltage,'r',time,current,'b',time,power);
        %drawnow;
        
        disp([idx,voltage(idx),current(idx),power(idx)]);
        time(idx+1)=time(idx)+1;
    end
    pause(0.001);
end
%%
%save('d:\history_info','consume');
fclose(wattmeter); %close the connection
clear wattmeter;
% clc;clear all;close all;
% consume=zeros(1,30);
% save('d:\history_info','consume');