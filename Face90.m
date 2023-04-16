clear all
close all
clc
%% Face90 WDF MXR Phase90

%% Import Input Audio Signal
[Vin, ~] = audioread('jumpMono.wav');

%% LTSpice Files for Ground-Truth
[outputLTSpice, FSOutputLTSpice] = audioread('jump_face90.wav');

%% Qui iniziano i problemi