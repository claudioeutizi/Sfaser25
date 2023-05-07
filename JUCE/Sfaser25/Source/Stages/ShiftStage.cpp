/*
  ==============================================================================

    shiftStage.cpp
    Created: 1 May 2023 6:03:45pm
    Author:  Samuele Del Moro

  ==============================================================================
*/
#pragma once

#include "ShiftStage.h"
#include <cmath>
#include <stdio.h>

ShiftStage::ShiftStage() {

    //Qv_T << 1, 0, 0, 0,
    //    0, 1, 0, 0,
    //    0, 0, 1, 0,
    //    0, 0, 0, 1,
    //    0, 0, 0, 1,
    //    0, 1, 0, 0,
    //    -1, 0, -1, -1,
    //    -1, -1, 0, -1;
    //Qv = Qv_T.transpose();

    //Qi_T << 1, 0, 0, 0,
    //    0, 1, 0, 0,
    //    0, 0, 1, 0,
    //    0, 0, 0, 1,
    //    -1, 0, -1, 0,
    //    0, 1, 0, 0,
    //    0, 0, 0, 0,
    //    -1, -1, 0, -1;

    //Qi = Qi_T.transpose();

    //I = Matrix8d::Identity(8, 8);
    //I4 = Matrix4d::Identity(4, 4);
    //Z.fill(0);
    S.fill(0);
}

void ShiftStage::prepareShiftStage(float sampleRate)
{
    float Ts = 1/sampleRate;

    Z4 = Ts / (2 * 47e-9);
    //Matrix<double, 8, 1> z(Z1, Z2, Z3, Z4, Z5, Z6, Z7, Z8);
    //Z = z.asDiagonal();
    ///*Matrix8d S = 2 * Qv_T * (Qi * Z.inverse() * Qv_T).inverse() * (Qi * Z.inverse()) - I;*/
    ////Matrix8d S;
}

float ShiftStage::shiftStageSample(float inputSample, wavesSTAGE& waves, float LFO)
{
    Z6 = 1 / (k * (LFO - Vref - Vp));
 
    shiftScatteringMatrix(Z4, Z6);
 
    
    waves.a[0] = -inputSample;
    waves.a[3] = waves.b(3);
    waves.a[7] = 5.1;
    waves.b = S * waves.a;
    
    float outputSample = ((waves.a[6] + waves.b[6]) / 2);
    LFOprev = LFO;
    return outputSample;

}

void ShiftStage::shiftScatteringMatrix(float Z4, float Z6)
{
    S(0, 0) = (20000 * (24000000000 * Z4 + 24000000001 * Z6 + 1000000 * Z4 * Z6 + 24000)) / (240000000024000 * Z4 + 240000000020000 * Z6 + 10000000001 * Z4 * Z6 + 480000000) - 1;
    S(0, 1) = -(2 * (10000 * Z6 + Z4 * Z6)) / (240000000024000 * Z4 + 240000000020000 * Z6 + 10000000001 * Z4 * Z6 + 480000000);
    S(0, 2) = 0;
    S(0, 3) = (3 * (4666666667 * Z6 - 79999999992000)) / (500000 * (240000000024000 * Z4 + 240000000020000 * Z6 + 10000000001 * Z4 * Z6 + 480000000));
    S(0, 4) = -(24000000000 * Z4 + 24000000001 * Z6 + 1000000 * Z4 * Z6 + 24000) / (500000 * (240000000024000 * Z4 + 240000000020000 * Z6 + 10000000001 * Z4 * Z6 + 480000000));
    S(0, 5) = -(48000 * (Z4 + 10000)) / (240000000024000 * Z4 + 240000000020000 * Z6 + 10000000001 * Z4 * Z6 + 480000000);
    S(0, 6) = 0;
    S(0, 7) = -(2 * (24000 * Z4 + 10000 * Z6 + Z4 * Z6 + 240000000)) / (240000000024000 * Z4 + 240000000020000 * Z6 + 10000000001 * Z4 * Z6 + 480000000);
    S(1, 0) = -(480000000000000 * Z6) / (240000000024000 * Z4 + 240000000020000 * Z6 + 10000000001 * Z4 * Z6 + 480000000);
    S(1, 1) = (2 * Z6 * (10000000001 * Z4 + 20000)) / (240000000024000 * Z4 + 240000000020000 * Z6 + 10000000001 * Z4 * Z6 + 480000000) - 1;
    S(1, 2) = 0;
    S(1, 3) = -(480000000048000 * Z6) / (240000000024000 * Z4 + 240000000020000 * Z6 + 10000000001 * Z4 * Z6 + 480000000);
    S(1, 4) = (48000 * Z6) / (240000000024000 * Z4 + 240000000020000 * Z6 + 10000000001 * Z4 * Z6 + 480000000);
    S(1, 5) = (48000 * (10000000001 * Z4 + 20000)) / (240000000024000 * Z4 + 240000000020000 * Z6 + 10000000001 * Z4 * Z6 + 480000000);
    S(1, 6) = 0;
    S(1, 7) = -(480000000000000 * Z6) / (240000000024000 * Z4 + 240000000020000 * Z6 + 10000000001 * Z4 * Z6 + 480000000);
    S(2, 0) = -(20000000000 * (24000 * Z4 + Z4 * Z6)) / (240000000024000 * Z4 + 240000000020000 * Z6 + 10000000001 * Z4 * Z6 + 480000000);
    S(2, 1) = -(20000000000 * Z4 * Z6) / (240000000024000 * Z4 + 240000000020000 * Z6 + 10000000001 * Z4 * Z6 + 480000000);
    S(2, 2) = 1;
    S(2, 3) = (40000 * (12000000001 * Z6 + 24000)) / (240000000024000 * Z4 + 240000000020000 * Z6 + 10000000001 * Z4 * Z6 + 480000000);
    S(2, 4) = -(40000 * (12000000000 * Z4 + 12000000001 * Z6 + 500000 * Z4 * Z6 + 24000)) / (240000000024000 * Z4 + 240000000020000 * Z6 + 10000000001 * Z4 * Z6 + 480000000);
    S(2, 5) = -(480000000000000 * Z4) / (240000000024000 * Z4 + 240000000020000 * Z6 + 10000000001 * Z4 * Z6 + 480000000);
    S(2, 6) = 0;
    S(2, 7) = -(20000000000 * (24000 * Z4 + Z4 * Z6)) / (240000000024000 * Z4 + 240000000020000 * Z6 + 10000000001 * Z4 * Z6 + 480000000);
    S(3, 0) = -(20000000000 * (24000 * Z4 + Z4 * Z6)) / (240000000024000 * Z4 + 240000000020000 * Z6 + 10000000001 * Z4 * Z6 + 480000000);
    S(3, 1) = -(20000000000 * Z4 * Z6) / (240000000024000 * Z4 + 240000000020000 * Z6 + 10000000001 * Z4 * Z6 + 480000000);
    S(3, 2) = 0;
    S(3, 3) = (40000 * (12000000001 * Z6 + 24000)) / (240000000024000 * Z4 + 240000000020000 * Z6 + 10000000001 * Z4 * Z6 + 480000000) - 1;
    S(3, 4) = (2 * (24000 * Z4 + Z4 * Z6)) / (240000000024000 * Z4 + 240000000020000 * Z6 + 10000000001 * Z4 * Z6 + 480000000);
    S(3, 5) = -(480000000000000 * Z4) / (240000000024000 * Z4 + 240000000020000 * Z6 + 10000000001 * Z4 * Z6 + 480000000);
    S(3, 6) = 0;
    S(3, 7) = -(20000000000 * (24000 * Z4 + Z4 * Z6)) / (240000000024000 * Z4 + 240000000020000 * Z6 + 10000000001 * Z4 * Z6 + 480000000);
    S(4, 0) = -(20000000000 * (24000 * Z4 + Z4 * Z6)) / (240000000024000 * Z4 + 240000000020000 * Z6 + 10000000001 * Z4 * Z6 + 480000000);
    S(4, 1) = -(20000000000 * Z4 * Z6) / (240000000024000 * Z4 + 240000000020000 * Z6 + 10000000001 * Z4 * Z6 + 480000000);
    S(4, 2) = 0;
    S(4, 3) = (40000 * (12000000001 * Z6 + 24000)) / (240000000024000 * Z4 + 240000000020000 * Z6 + 10000000001 * Z4 * Z6 + 480000000);
    S(4, 4) = (2 * (24000 * Z4 + Z4 * Z6)) / (240000000024000 * Z4 + 240000000020000 * Z6 + 10000000001 * Z4 * Z6 + 480000000) - 1;
    S(4, 5) = -(480000000000000 * Z4) / (240000000024000 * Z4 + 240000000020000 * Z6 + 10000000001 * Z4 * Z6 + 480000000);
    S(4, 6) = 0;
    S(4, 7) = -(20000000000 * (24000 * Z4 + Z4 * Z6)) / (240000000024000 * Z4 + 240000000020000 * Z6 + 10000000001 * Z4 * Z6 + 480000000);
    S(5, 0) = -(480000000000000 * Z6) / (240000000024000 * Z4 + 240000000020000 * Z6 + 10000000001 * Z4 * Z6 + 480000000);
    S(5, 1) = (2 * Z6 * (10000000001 * Z4 + 20000)) / (240000000024000 * Z4 + 240000000020000 * Z6 + 10000000001 * Z4 * Z6 + 480000000);
    S(5, 2) = 0;
    S(5, 3) = -(480000000048000 * Z6) / (240000000024000 * Z4 + 240000000020000 * Z6 + 10000000001 * Z4 * Z6 + 480000000);
    S(5, 4) = (48000 * Z6) / (240000000024000 * Z4 + 240000000020000 * Z6 + 10000000001 * Z4 * Z6 + 480000000);
    S(5, 5) = (48000 * (10000000001 * Z4 + 20000)) / (240000000024000 * Z4 + 240000000020000 * Z6 + 10000000001 * Z4 * Z6 + 480000000) - 1;
    S(5, 6) = 0;
    S(5, 7) = -(480000000000000 * Z6) / (240000000024000 * Z4 + 240000000020000 * Z6 + 10000000001 * Z4 * Z6 + 480000000);
    S(6, 0) = (40000000000 * (24000 * Z4 + Z4 * Z6)) / (240000000024000 * Z4 + 240000000020000 * Z6 + 10000000001 * Z4 * Z6 + 480000000) - (20000 * (24000000000 * Z4 + 24000000001 * Z6 + 1000000 * Z4 * Z6 + 24000)) / (240000000024000 * Z4 + 240000000020000 * Z6 + 10000000001 * Z4 * Z6 + 480000000);
    S(6, 1) = (2 * (10000 * Z6 + Z4 * Z6)) / (240000000024000 * Z4 + 240000000020000 * Z6 + 10000000001 * Z4 * Z6 + 480000000) + (40000000000 * Z4 * Z6) / (240000000024000 * Z4 + 240000000020000 * Z6 + 10000000001 * Z4 * Z6 + 480000000);
    S(6, 2) = -2;
    S(6, 3) = -(3 * (4666666667 * Z6 - 79999999992000)) / (500000 * (240000000024000 * Z4 + 240000000020000 * Z6 + 10000000001 * Z4 * Z6 + 480000000)) - (80000 * (12000000001 * Z6 + 24000)) / (240000000024000 * Z4 + 240000000020000 * Z6 + 10000000001 * Z4 * Z6 + 480000000);
    S(6, 4) = (40000 * (12000000000 * Z4 + 12000000001 * Z6 + 500000 * Z4 * Z6 + 24000)) / (240000000024000 * Z4 + 240000000020000 * Z6 + 10000000001 * Z4 * Z6 + 480000000) + (24000000000 * Z4 + 24000000001 * Z6 + 1000000 * Z4 * Z6 + 24000) / (500000 * (240000000024000 * Z4 + 240000000020000 * Z6 + 10000000001 * Z4 * Z6 + 480000000)) - (2 * (24000 * Z4 + Z4 * Z6)) / (240000000024000 * Z4 + 240000000020000 * Z6 + 10000000001 * Z4 * Z6 + 480000000);
    S(6, 5) = (960000000000000 * Z4) / (240000000024000 * Z4 + 240000000020000 * Z6 + 10000000001 * Z4 * Z6 + 480000000) + (48000 * (Z4 + 10000)) / (240000000024000 * Z4 + 240000000020000 * Z6 + 10000000001 * Z4 * Z6 + 480000000);
    S(6, 6) = -1;
    S(6, 7) = (2 * (24000 * Z4 + 10000 * Z6 + Z4 * Z6 + 240000000)) / (240000000024000 * Z4 + 240000000020000 * Z6 + 10000000001 * Z4 * Z6 + 480000000) + (40000000000 * (24000 * Z4 + Z4 * Z6)) / (240000000024000 * Z4 + 240000000020000 * Z6 + 10000000001 * Z4 * Z6 + 480000000);
    S(7, 0) = (480000000000000 * Z6) / (240000000024000 * Z4 + 240000000020000 * Z6 + 10000000001 * Z4 * Z6 + 480000000) - (20000 * (24000000000 * Z4 + 24000000001 * Z6 + 1000000 * Z4 * Z6 + 24000)) / (240000000024000 * Z4 + 240000000020000 * Z6 + 10000000001 * Z4 * Z6 + 480000000) + (20000000000 * (24000 * Z4 + Z4 * Z6)) / (240000000024000 * Z4 + 240000000020000 * Z6 + 10000000001 * Z4 * Z6 + 480000000);
    S(7, 1) = (2 * (10000 * Z6 + Z4 * Z6)) / (240000000024000 * Z4 + 240000000020000 * Z6 + 10000000001 * Z4 * Z6 + 480000000) + (20000000000 * Z4 * Z6) / (240000000024000 * Z4 + 240000000020000 * Z6 + 10000000001 * Z4 * Z6 + 480000000) - (2 * Z6 * (10000000001 * Z4 + 20000)) / (240000000024000 * Z4 + 240000000020000 * Z6 + 10000000001 * Z4 * Z6 + 480000000);
    S(7, 2) = 0;
    S(7, 3) = (480000000048000 * Z6) / (240000000024000 * Z4 + 240000000020000 * Z6 + 10000000001 * Z4 * Z6 + 480000000) - (3 * (4666666667 * Z6 - 79999999992000)) / (500000 * (240000000024000 * Z4 + 240000000020000 * Z6 + 10000000001 * Z4 * Z6 + 480000000)) - (40000 * (12000000001 * Z6 + 24000)) / (240000000024000 * Z4 + 240000000020000 * Z6 + 10000000001 * Z4 * Z6 + 480000000);
    S(7, 4) = (24000000000 * Z4 + 24000000001 * Z6 + 1000000 * Z4 * Z6 + 24000) / (500000 * (240000000024000 * Z4 + 240000000020000 * Z6 + 10000000001 * Z4 * Z6 + 480000000)) - (48000 * Z6) / (240000000024000 * Z4 + 240000000020000 * Z6 + 10000000001 * Z4 * Z6 + 480000000) - (2 * (24000 * Z4 + Z4 * Z6)) / (240000000024000 * Z4 + 240000000020000 * Z6 + 10000000001 * Z4 * Z6 + 480000000);
    S(7, 5) = (480000000000000 * Z4) / (240000000024000 * Z4 + 240000000020000 * Z6 + 10000000001 * Z4 * Z6 + 480000000) - (48000 * (10000000001 * Z4 + 20000)) / (240000000024000 * Z4 + 240000000020000 * Z6 + 10000000001 * Z4 * Z6 + 480000000) + (48000 * (Z4 + 10000)) / (240000000024000 * Z4 + 240000000020000 * Z6 + 10000000001 * Z4 * Z6 + 480000000);
    S(7, 6) = 0;
    S(7, 7) = (480000000000000 * Z6) / (240000000024000 * Z4 + 240000000020000 * Z6 + 10000000001 * Z4 * Z6 + 480000000) + (2 * (24000 * Z4 + 10000 * Z6 + Z4 * Z6 + 240000000)) / (240000000024000 * Z4 + 240000000020000 * Z6 + 10000000001 * Z4 * Z6 + 480000000) + (20000000000 * (24000 * Z4 + Z4 * Z6)) / (240000000024000 * Z4 + 240000000020000 * Z6 + 10000000001 * Z4 * Z6 + 480000000) - 1;
}


