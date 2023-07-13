/*
  ==============================================================================

    outputStage.h
    Created: 1 May 2023 2:37:54pm
    Author:  Samuele Del Moro

  ==============================================================================
*/
#include "../../eigen-3.4.0/Eigen/Dense"
#include <stdio.h>
#include <iostream>

#pragma once

using namespace Eigen;


struct wavesOUT
{
    Matrix<float, 6, 1> a = {0,0,0,0,0,0};
    Matrix<float, 6, 1> b = {0,0,1.01637,0,0,0};
};

typedef Matrix<float,6,6> Matrix6f;

class OutputStage {
public:
    OutputStage();
    ~OutputStage() {};
    Matrix6f prepareOutputStage(float sampleRate);
    float outputStageSample(float inputWet, float inputDry, Matrix6f S, wavesOUT& waves);

private:
    Matrix<float, 6, 3> Qv_T;
    Matrix<float, 3, 6> Qv;

    Matrix<float, 6, 3> Qi_T = Qv_T;
    Matrix<float, 3, 6> Qi = Qv;

    Matrix6f I=Matrix6f::Identity(6,6);

    //port impedances
    float Z1 = 150e3;
    float Z2 = Z1;
    float Z4 = 56e3;
    float Z5 = Z1;
    float Z6 = Z1;
    Matrix6f S;
};
