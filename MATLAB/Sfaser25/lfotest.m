close all;
clear;
clc;


sample_rate = 44100;
speed = 10;
dutyCycle = 0.65;
%lfoIndex = 0:sample_rate/speed;
% lfoValue = sin(2 * 3.14 * speed * lfoIndex / sample_rate) * 0.15 + 3.25;
% lfoValue = 2 * 0.3 * abs(speed*lfoIndex/sample_rate - floor(speed*lfoIndex/sample_rate + 0.5))+3.25-0.15;

lfoValue=zeros(1,sample_rate/speed);

for lfoIndex=1:(sample_rate+1)/speed
    index=lfoIndex*speed/sample_rate;
    if (index < dutyCycle) 
        lfoValue(lfoIndex)= (index*0.3) / dutyCycle+3.1;
    
    else 
        lfoValue(lfoIndex)=  0.3 / (1 - dutyCycle)*(-index + 1)+3.1;
   
    end
end
lfoIndex=1:sample_rate/speed;
plot(lfoIndex,lfoValue, 'b', 'LineWidth', 2);