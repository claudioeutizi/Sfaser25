/*
  ==============================================================================

    outputStage.cpp
    Created: 1 May 2023 2:37:54pm
    Author:  Samuele Del Moro

  ==============================================================================
*/

#include "outputStage.h"

Matrix6f prepareOutputStage(float sampleRate)
{
    float Ts = 1/sampleRate;
        
    float Z1 = 150e3;
    float Z2 = Z1;
    float Z3 = Ts/(2*47e-9);
    float Z4 = 56e3;
    float Z5 = Z1;
    float Z6 = Z1;
    
    Matrix<float, 6, 3> Qv_T;
    Qv_T << 1, 0, 0,
            0, 1, 0,
            0, 0, 1,
           -1, -1, 0,
            1, 0, 0,
           -1, -1, -1;
    Matrix<float, 3, 6> Qv = Qv_T.transpose();
    
    Matrix<float, 6, 3> Qi_T = Qv_T;
    Matrix<float, 3, 6> Qi = Qv;
    
    Matrix<float, 6,1> z(Z1, Z2, Z3, Z4, Z5, Z6);
    Matrix6f Z = z.asDiagonal();

    
    Matrix6f I = Matrix6f::Identity(6, 6);
    
    Matrix6f S = 2 * Qv_T * (Qi * Z.inverse() * Qv_T).inverse() * (Qi * Z.inverse()) - I;
    
    return S;
    
}

float outputStageSample(float inputWet, float inputDry, const Matrix6f& S, wavesOUT& waves)
{
    waves.a[0] = -inputWet;
    waves.a[4] = -inputDry;
    waves.a[2] = waves.b(2);
    waves.b = S*waves.a;
    
    double outputSample = ((waves.a[5]+waves.b[5])/2);
    return outputSample;

}

