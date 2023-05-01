/*
  ==============================================================================

    outputStage.cpp
    Created: 1 May 2023 2:37:54pm
    Author:  Samuele Del Moro

  ==============================================================================
*/

#include "outputStage.h"

Mat_OUT PrepareOutputStage(float sampleRate)
{
    //parameters of circuit
    //double V_gnd = -4.5; non useful here
            //float R_gnd = 1e-3;
            
    float Ts = 1/sampleRate;
            //WDF analysis
    float Z1 = 150e3;
    float Z2 = Z1;
    float Z3 = Ts/(2*47e-9);
    float Z4 = 56e3;
    float Z5 = Z1;
    float Z6 = Z1;
    
    Matrix<float, 6, 3> Qv;
    Qv <<   1, 0, 0,
            0, 1, 0,
            0, 0, 1,
            -1, -1, 0,
            1, 0, 0,
            -1, -1, -1;
    Matrix<float, 3, 6> Qv_T = Qv.transpose();
    
    Matrix<float, 6, 3> Qi;
    Qi = Qv;
    Matrix<float, 3, 6> Qi_T = Qi.transpose();
    
    Matrix<float, 6,1> vector1;
    vector1 << Z1, Z2, Z3, Z4, Z5, Z6;
    
    MatrixXf Z;
    Z = vector1.asDiagonal();
    
    int rowNumber = 6;
    int columnNumber = 6;
    
    MatrixXf I;
    I = MatrixXf::Identity(rowNumber,columnNumber);
    
    Mat_OUT S;
    S << 2 * Qv * (Qi_T * Z.inverse() * Qv).inverse() * (Qi_T * Z.inverse()) - I;
    
    return S;
    
}

float OutputStageSample( float inputSample, float inputDry, const Mat_OUT& S, Output_Data& V_d)
{
    //outputBuffer[i] = inputBuffer[i] * 0.1;
    V_d.a[0] = -inputSample;
    V_d.a[4] = -inputDry;
    V_d.a[2] = V_d.b(2); //V_gnd
    V_d.b = S*V_d.a;
    //B_old_out=V_d.b(2);
    
    double outputSample = ((V_d.a[5]+V_d.b[5])/2);
    return outputSample;

}

