close all;
clear;
clc;


sample_rate=44100;
speed=10;
lfoIndex=0:sample_rate/speed;
% lfoValue = sin(2 * 3.14 * speed * lfoIndex / sample_rate) * 0.15 + 3.25;
lfoValue = 2 * 0.3 * abs(speed*lfoIndex/sample_rate - floor(speed*lfoIndex/sample_rate + 0.5))+3.25-0.15;


plot(lfoIndex,lfoValue);