/*
  ==============================================================================

    shiftStage.cpp
    Created: 1 May 2023 6:03:45pm
    Author:  Samuele Del Moro

  ==============================================================================
*/

#include "shiftStage.h"
#include <cmath>

Matrix8d prepareShiftStage(float sampleRate)
{
    float Ts = 1/sampleRate;
    
   
    float Z1 = 1e-6;
    float Z2 = 24e3;
    float Z3 = 10e3;
    float Z4 = Ts/(2*47e-9);
    float Z5 = Z3;
    //float Z6 = 1/(k*(Vg - Vref - Vp));
    float Z6 = 1e3;
    float Z7 = 1e9;
    float Z8 = 1e-6;
            
    
    Matrix<double, 8, 4> Qv_T;
    Qv_T << 1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1,
            0, 0, 0, 1,
            0, 1, 0, 0,
           -1, 0, -1, -1,
           -1, -1, 0,-1;
    
    Matrix<double, 4, 8> Qv = Qv_T.transpose();
    
    Matrix<double, 8, 4> Qi_T;
    Qi_T << 1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1,
           -1, 0, -1, 0,
            0, 1, 0, 0,
            0, 0, 0, 0,
           -1, -1, 0, -1;
    
    Matrix<double, 4, 8> Qi = Qi_T.transpose();
    
    Matrix<double, 8,1> z(Z1, Z2, Z3, Z4, Z5, Z6, Z7, Z8);
    MatrixXd Z = z.asDiagonal();
    
    MatrixXd I = MatrixXd::Identity(8,8);
    
    Matrix8d S = 2 * Qv_T * (Qi * Z.inverse() * Qv_T).inverse() * (Qi * Z.inverse()) - I;
    
    return S;
    
}

float shiftStageSample(float inputSample, const Matrix8d& S, wavesSTAGE& waves)
{
    waves.a[0] = -inputSample;
    waves.a[3] = waves.b(3);
    waves.a[7] = 5.1;
    waves.b = S*waves.a;
    
    float outputSample = ((waves.a[6]+waves.b[6])/2);
    return outputSample;

}



