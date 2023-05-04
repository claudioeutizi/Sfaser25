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

    this->Qv_T << 1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1,
        0, 0, 0, 1,
        0, 1, 0, 0,
        -1, 0, -1, -1,
        -1, -1, 0, -1;
    this->Qv = Qv_T.transpose();

    this->Qi_T << 1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1,
        -1, 0, -1, 0,
        0, 1, 0, 0,
        0, 0, 0, 0,
        -1, -1, 0, -1;

    this->Qi = Qi_T.transpose();

    this->I = Matrix8d::Identity(8, 8);

}

Matrix8d ShiftStage::prepareShiftStage(float sampleRate)
{
    float Ts = 1/sampleRate;

    float Z4 = Ts / (2 * 47e-9);
    
    /*Matrix<double, 8,1> z(Z1, Z2, Z3, Z4, Z5, 0, Z7, Z8);*/
    Matrix<double, 8, 1> z(Z1, Z2, Z3, Z4, Z5, 0, Z7, Z8);
    this->Z = z.asDiagonal();
    
    Matrix8d S = 2 * this->Qv_T * (this->Qi * Z.inverse() * this->Qv_T).inverse() * (this->Qi * Z.inverse()) - this->I;
    
    return S;
    
}

float ShiftStage::shiftStageSample(float inputSample, const Matrix8d& S, wavesSTAGE& waves, float LFO)
{
    Z(6,6) = 1 / (k * (LFO - Vref - Vp));
    
    this->S1 = 2 * this->Qv_T * (this->Qi * Z.inverse() * this->Qv_T).inverse() * (this->Qi * Z.inverse()) - this->I;

    waves.a[0] = -inputSample;
    waves.a[3] = waves.b(3);
    waves.a[7] = 5.1;
    waves.b = S1 * waves.a;
    
    float outputSample = ((waves.a[6]+waves.b[6])/2);
    return outputSample;

}



