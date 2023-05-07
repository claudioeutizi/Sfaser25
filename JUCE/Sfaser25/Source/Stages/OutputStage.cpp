/*
  ==============================================================================

    outputStage.cpp
    Created: 1 May 2023 2:37:54pm
    Author:  Samuele Del Moro

  ==============================================================================
*/

#include "OutputStage.h"

OutputStage::OutputStage()
{

    Qv_T << 1, 0, 0,
        0, 1, 0,
        0, 0, 1,
        -1, -1, 0,
        1, 0, 0,
        -1, -1, -1;

    Qi_T = Qv_T;
    Qv = Qv_T.transpose();
    Qi = Qv;

    S.fill(0);
}

Matrix6f OutputStage::prepareOutputStage(float sampleRate)
{
    float Ts = 1/sampleRate;
    float Z3 = Ts / (2 * 47e-9);
    
    Matrix<float, 6,1> z(Z1, Z2, Z3, Z4, Z5, Z6);
    Matrix6f Z = z.asDiagonal();
    
    S = 2 * Qv_T * (Qi * Z.inverse() * Qv_T).inverse() * (Qi * Z.inverse()) - I;
    
    return S;
    
}

float OutputStage::outputStageSample(float inputWet, float inputDry, Matrix6f S, wavesOUT& waves)
{
    waves.a[0] = -inputWet;
    waves.a[4] = -inputDry;
    waves.a[2] = waves.b(2);
    waves.b = S*waves.a;
    
    float outputSample = ((waves.a[5]+waves.b[5])/2);
    return outputSample;
}


