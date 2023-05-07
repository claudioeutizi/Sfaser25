close all;
clear;
clc;


sample_rate=96000;
speed=5;
lfoIndex=0:sample_rate/speed;
lfoValue = sin(2 * 3.14 * speed * lfoIndex / sample_rate) * 0.15 + 3.25;

plot(lfoIndex,lfoValue);