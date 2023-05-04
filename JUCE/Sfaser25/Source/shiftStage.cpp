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

ShiftStage::ShiftStage() {

    Qv_T << 1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1,
        0, 0, 0, 1,
        0, 1, 0, 0,
        -1, 0, -1, -1,
        -1, -1, 0, -1;
    Qv = Qv_T.transpose();

    Qi_T << 1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1,
        -1, 0, -1, 0,
        0, 1, 0, 0,
        0, 0, 0, 0,
        -1, -1, 0, -1;

    Qi = Qi_T.transpose();

    I = Matrix8d::Identity(8, 8);

    Z.fill(0);

}

void ShiftStage::prepareShiftStage(float sampleRate)
{
    float Ts = 1/sampleRate;

    float Z4 = Ts / (2 * 47e-9);
    
    Matrix<double, 8, 1> z(Z1, Z2, Z3, Z4, Z5, Z6, Z7, Z8);
    Z = z.asDiagonal();
   
    
}

float ShiftStage::shiftStageSample(float inputSample, wavesSTAGE& waves, float LFO)
{
    Z(6,6) = (double) 1 / (k * (LFO - Vref - Vp));
    
    
    Matrix8d S1 = 2 * Qv_T * (Qi * Z.inverse() * Qv_T).inverse() * (Qi * Z.inverse()) - I;

    waves.a[0] = -inputSample;
    waves.a[3] = waves.b(3);
    waves.a[7] = 5.1;
    waves.b = S1 * waves.a;
    
    float outputSample = ((waves.a[6]+waves.b[6])/2);
    return outputSample;

}



