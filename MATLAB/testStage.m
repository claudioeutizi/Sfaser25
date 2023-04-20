clear;
close all;
clc;

fs=44100;
Ts=1/fs;

Qv=[1 0 1 1 1 1;
    0 1 0 0 0 1];

Qi=[1 0 0 1 1 0;
    0 1 1 0 0 0];

Z=diag([15000 10000 10000 24000 10*10^9 5000]);

S=2 * Qv.' * inv(Qi * inv(Z) * Qv.') * Qi * inv(Z) - eye(6);

%%qui iniziano i problemi


