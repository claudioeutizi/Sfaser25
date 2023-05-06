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
    //Z1 = 150e3;
    //Z2 = Z1;
    //Z4 = 56e3;
    //Z5 = Z1;
    //Z6 = Z1;

    //Qv_T << 1, 0, 0,
    //    0, 1, 0,
    //    0, 0, 1,
    //    -1, -1, 0,
    //    1, 0, 0,
    //    -1, -1, -1;

    //Qi_T = Qv_T;
    //Qv = Qv_T.transpose();
    //Qi = Qv;

    //I = Matrix6f::Identity(6, 6);
    S.fill(0);
}

void OutputStage::prepareOutputStage(float sampleRate)
{
    float Ts = 1/sampleRate;
    float Z3 = Ts / (2 * 47e-9);
    
    /*Matrix<float, 6,1> z(Z1, Z2, Z3, Z4, Z5, Z6);
    Matrix6f Z = z.asDiagonal();*/
    outputScatteringMatrix(Z3);
    
    //Matrix6f S = 2 * Qv_T * (Qi * Z.inverse() * Qv_T).inverse() * (Qi * Z.inverse()) - I;
    //
    //return S;
    
}

float OutputStage::outputStageSample(float inputWet, float inputDry, wavesOUT& waves)
{
    waves.a[0] = -inputWet;
    waves.a[4] = -inputDry;
    waves.a[2] = waves.b(2);
    waves.b = S*waves.a;
    
    float outputSample = ((waves.a[5]+waves.b[5])/2);
    return outputSample;
}

void OutputStage::outputScatteringMatrix(float Z3)
{
    S(0, 0) = (2 * (103 * Z3 + 19650000)) / (281 * Z3 + 54750000) - 1;
    S(0, 1) = -(150 * (Z3 + 206000)) / (281 * Z3 + 54750000);
    S(0, 2) = -8400000 / (281 * Z3 + 54750000);
    S(0, 3) = -(150 * (Z3 + 150000)) / (281 * Z3 + 54750000);
    S(0, 4) = (2 * (103 * Z3 + 19650000)) / (281 * Z3 + 54750000);
    S(0, 5) = -8400000 / (281 * Z3 + 54750000);
    S(1, 0) = -(150 * (Z3 + 206000)) / (281 * Z3 + 54750000);
    S(1, 1) = (2 * (131 * Z3 + 23850000)) / (281 * Z3 + 54750000) - 1;
    S(1, 2) = -16800000 / (281 * Z3 + 54750000);
    S(1, 3) = -(300 * (Z3 + 150000)) / (281 * Z3 + 54750000);
    S(1, 4) = -(150 * (Z3 + 206000)) / (281 * Z3 + 54750000);
    S(1, 5) = -16800000 / (281 * Z3 + 54750000);
    S(2, 0) = -(56 * Z3) / (281 * Z3 + 54750000);
    S(2, 1) = -(112 * Z3) / (281 * Z3 + 54750000);
    S(2, 2) = 109500000 / (281 * Z3 + 54750000) - 1;
    S(2, 3) = (450 * Z3) / (281 * Z3 + 54750000);
    S(2, 4) = -(56 * Z3) / (281 * Z3 + 54750000);
    S(2, 5) = -(562 * Z3) / (281 * Z3 + 54750000);
    S(3, 0) = (150 * (Z3 + 206000)) / (281 * Z3 + 54750000) - (2 * (103 * Z3 + 19650000)) / (281 * Z3 + 54750000);
    S(3, 1) = (150 * (Z3 + 206000)) / (281 * Z3 + 54750000) - (2 * (131 * Z3 + 23850000)) / (281 * Z3 + 54750000);
    S(3, 2) = 25200000 / (281 * Z3 + 54750000);
    S(3, 3) = (450 * (Z3 + 150000)) / (281 * Z3 + 54750000) - 1;
    S(3, 4) = (150 * (Z3 + 206000)) / (281 * Z3 + 54750000) - (2 * (103 * Z3 + 19650000)) / (281 * Z3 + 54750000);
    S(3, 5) = 25200000 / (281 * Z3 + 54750000);
    S(4, 0) = (2 * (103 * Z3 + 19650000)) / (281 * Z3 + 54750000);
    S(4, 1) = -(150 * (Z3 + 206000)) / (281 * Z3 + 54750000);
    S(4, 2) = -8400000 / (281 * Z3 + 54750000);
    S(4, 3) = -(150 * (Z3 + 150000)) / (281 * Z3 + 54750000);
    S(4, 4) = (2 * (103 * Z3 + 19650000)) / (281 * Z3 + 54750000) - 1;
    S(4, 5) = -8400000 / (281 * Z3 + 54750000);
    S(5, 0) = (56 * Z3) / (281 * Z3 + 54750000) + (150 * (Z3 + 206000)) / (281 * Z3 + 54750000) - (2 * (103 * Z3 + 19650000)) / (281 * Z3 + 54750000);
    S(5, 1) = (112 * Z3) / (281 * Z3 + 54750000) + (150 * (Z3 + 206000)) / (281 * Z3 + 54750000) - (2 * (131 * Z3 + 23850000)) / (281 * Z3 + 54750000);
    S(5, 2) = -84300000 / (281 * Z3 + 54750000);
    S(5, 3) = (450 * (Z3 + 150000)) / (281 * Z3 + 54750000) - (450 * Z3) / (281 * Z3 + 54750000);
    S(5, 4) = (56 * Z3) / (281 * Z3 + 54750000) + (150 * (Z3 + 206000)) / (281 * Z3 + 54750000) - (2 * (103 * Z3 + 19650000)) / (281 * Z3 + 54750000);
    S(5, 5) = (562 * Z3) / (281 * Z3 + 54750000) + 25200000 / (281 * Z3 + 54750000) - 1;
}

