clear all
close all
clc
%% Face90 WDF MXR Phase90

%% Import Input Audio Signal
[Vin,~] = audioread('jump.wav');

%% LTSpice Files for Ground-Truth
[outputSpice,FSOutputSpice]=audioread('jump_face90.wav');
[OutHighSpice,FsLTSpice]=audioread('jump_face90.wav');
TsLTSpice=1/FsLTSpice;

%% Qui iniziano i problemi