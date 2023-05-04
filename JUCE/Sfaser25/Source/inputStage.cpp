//
//  inputStage.cpp
//  Sfaser25 - VST3
//
//  Created by Samuele Del Moro on 30/04/23.
//

#include "InputStage.h"

InputStage::InputStage()
{
    Z1 = 10e3;
    Z3 = 1e9;
    Z4 = 470e3;

    Qv_T << 1, 0,
        0, 1,
        -1, -1,
        -1, -1;
    Qv = Qv_T.transpose();

    Qi_T << 1, 0,
        0, 1,
        0, 0,
        -1, -1;
    Qi = Qi_T.transpose();
    I = Matrix4f::Identity(4, 4);
}

Matrix4f InputStage::prepareInputStage(float sampleRate)
{      
    float Ts = 1/sampleRate; 
    float Z2 = Ts / (2 * 0.01e-6);
    Vector4f z(Z1, Z2, Z3, Z4);
    Matrix4f Z = z.asDiagonal();

    Matrix4f S = 2 * Qv_T * (Qi * Z.inverse() * Qv_T).inverse() * (Qi * Z.inverse()) - I;
    return S;
    
}

float InputStage::inputStageSample(const float inputSample, const Matrix4f& S, wavesIN& waves)
{
    //mettere qui il for per riempire il buffer?
    waves.a[0] = -inputSample;
    waves.a[1] = waves.b(1);
    waves.a[3] = 5.1;
    waves.b = S*waves.a;
    
    float outputSample = ((waves.a[2]+waves.b[2])/2);
    return outputSample;

}

