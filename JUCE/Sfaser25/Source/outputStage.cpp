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
    this->Z1 = 150e3;
    this->Z2 = Z1;
    this->Z3 = 0;
    this->Z4 = 56e3;
    this->Z5 = Z1;
    this->Z6 = Z1;

    this->Qv_T << 1, 0, 0,
        0, 1, 0,
        0, 0, 1,
        -1, -1, 0,
        1, 0, 0,
        -1, -1, -1;

    this->Qi_T = Qv_T;
    this->Qv = this->Qv_T.transpose();
    this->Qi = Qv;

    this->I = Matrix6f::Identity(6, 6);
}

Matrix6f OutputStage::prepareOutputStage(float sampleRate)
{
    float Ts = 1/sampleRate;
    this->Z3 = Ts / (2 * 47e-9);
    
    Matrix<float, 6,1> z(Z1, Z2, Z3, Z4, Z5, Z6);
    Matrix6f Z = z.asDiagonal();
    
    Matrix6f S = 2 * Qv_T * (Qi * Z.inverse() * Qv_T).inverse() * (Qi * Z.inverse()) - I;
    
    return S;
    
}

float OutputStage::outputStageSample(float inputWet, float inputDry, const Matrix6f& S, wavesOUT& waves)
{
    waves.a[0] = -inputWet;
    waves.a[4] = -inputDry;
    waves.a[2] = waves.b(2);
    waves.b = S*waves.a;
    
    double outputSample = ((waves.a[5]+waves.b[5])/2);
    return outputSample;

}

