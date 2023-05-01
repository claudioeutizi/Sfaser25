//
//  inputStage.cpp
//  Sfaser25 - VST3
//
//  Created by Samuele Del Moro on 30/04/23.
//

#include "inputStage.h"

Mat_IN PrepareInputStage(float sampleRate)
{
    //parameters of circuit
    //double V_gnd = -4.5; non useful here
            //float R_gnd = 1e-3;
            
            float Ts = 1/sampleRate;
            //WDF analysis
            float Z1 = 10e3;
            float Z2 = Ts/(2*0.01e-6);
            float Z3 = 5e3;
            float Z4 = 470e3;
    
    Matrix<float, 4, 2> Qv;
    Qv <<   1, 0,
            0, 1,
            -1, 1,
            -1, -1;
    Matrix<float, 2, 4> Qv_T = Qv.transpose();
    
    Matrix<float, 4, 2> Qi;
    Qi <<   1, 0,
            0, 1,
            0, 0,
            -1,-1;
    Matrix<float, 2, 4> Qi_T = Qi.transpose();
    
    Matrix<float, 4,1> vector1;
    vector1 << Z1, Z2, Z3, Z4;
    
    MatrixXf Z;
    Z = vector1.asDiagonal();
    
    int rowNumber = 4;
    int columnNumber = 4;
    
    MatrixXf I;
    I = MatrixXf::Identity(rowNumber,columnNumber);
    
    Mat_IN S;
    S << 2 * Qv * (Qi_T * Z.inverse() * Qv).inverse() * (Qi_T * Z.inverse()) - I;
    
    return S;
    
}

float InputStageSample(const float inputSample, const Mat_IN& S, Input_Data& I_d)
{
    

    //outputBuffer[i] = inputBuffer[i] * 0.1;
    I_d.a[0] = -inputSample;
    I_d.a[1] = I_d.b[1];
    I_d.a[3] = 5.1; //V_gnd
    I_d.b = S*I_d.a;
    double outputSample = ((I_d.a[2]+I_d.b[2])/2);
    return outputSample;

}

