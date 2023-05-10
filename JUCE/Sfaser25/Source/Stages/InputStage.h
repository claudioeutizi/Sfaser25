//
//  inputStage.h
//  Sfaser25
//
//  Created by Samuele Del Moro on 30/04/23.
//

#ifndef inputStage_h
#define inputStage_h
#endif

#include "../../eigen-3.4.0/Eigen/Dense"
#include <stdio.h>
#include <iostream>

using namespace Eigen;

struct wavesIN
{
    Vector4f a = { 0,0,0,0 };
    Vector4f b = { 0,-5.1,0,0 };
};

class InputStage {

public:

    InputStage();
    ~InputStage() {}
    Matrix4f prepareInputStage(float sampleRate);
    float inputStageSample(const float inputSample, Matrix4f S, wavesIN& waves);


private:
    float Z1 = 10e3;
    float Z3 = 1e9;
    float Z4 = 470e3;
    Matrix4f S;
    Matrix4f I;
    Matrix<float, 4, 2> Qi_T;
    Matrix<float, 4, 2> Qv_T;
    Matrix<float, 2, 4> Qv;
    Matrix<float, 2, 4> Qi;
};