/*
  ==============================================================================

    shiftStage.cpp
    Created: 1 May 2023 6:03:45pm
    Author:  Samuele Del Moro

  ==============================================================================
*/

#include "shiftStage.h"
#include <cmath>

Mat_SH PrepareShiftStage(float sampleRate)
{
    //parameters of circuit
    //double V_gnd = -4.5; non useful here
            //float R_gnd = 1e-3;
    float Ts = 1/sampleRate;
    
    
            //WDF analysis
    float Z1 = 1e-6;
    float Z2 = 24e3;
    float Z3 = 10e3;
    float Z4 = Ts/(2*47e-9);
    float Z5 = Z3;
    //float Z6 = 1/(k*(Vg - Vref - Vp));
    float Z6 = 10e3;
    float Z7 = 5e3;
    float Z8 = 1e-6;
            
    
    Matrix<float, 8, 4> Qv;
    Qv <<   1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1,
            0, 0, 0, 1,
            0, 1, 0, 0,
            -1, 0, -1, -1,
            -1, -1, 0,-1;
    
    Matrix<float, 4, 8> Qv_T = Qv.transpose();
    
    Matrix<float, 8, 4> Qi;
    Qi <<   1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1,
            -1, 0, -1, 0,
            0, 1, 0, 0,
            0, 0, 0, 0,
            -1, -1, 0, -1;
    
    Matrix<float, 4, 8> Qi_T = Qi.transpose();
    
    Matrix<float, 8,1> vector1;
    vector1 << Z1, Z2, Z3, Z4, Z5, Z6, Z7, Z8;
    
    MatrixXf Z;
    Z = vector1.asDiagonal();
    
    int rowNumber = 8;
    int columnNumber = 8;
    
    MatrixXf I;
    I = MatrixXf::Identity(rowNumber,columnNumber);
    
    Mat_SH S;
    S << 2 * Qv * (Qi_T * Z.inverse() * Qv).inverse() * (Qi_T * Z.inverse()) - I;
    
    return S;
    
}

float ShiftStageSample(const float inputSample, const Mat_SH& S, Shift_Data& Sh_d)
{
    //outputBuffer[i] = inputBuffer[i] * 0.1;
    
    
    Sh_d.a[0] = -inputSample;
    Sh_d.a[3] = Sh_d.b(3);
    Sh_d.a[7] = 5.1; //V_gnd
    Sh_d.b = S*Sh_d.a;
    //B_old_in=I_d.b(1);
    
    float outputSample = ((Sh_d.a[6]+Sh_d.b[6])/2);
    return outputSample;

}



