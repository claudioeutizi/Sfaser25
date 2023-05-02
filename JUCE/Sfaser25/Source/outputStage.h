/*
  ==============================================================================

    outputStage.h
    Created: 1 May 2023 2:37:54pm
    Author:  Samuele Del Moro

  ==============================================================================
*/
#include "C:\Users\matti\Desktop\MAE\mxrPhase90\Face90\JUCE\eigen-3.4.0\Eigen\Dense"
#include <stdio.h>
#include <iostream>

#pragma once

using Eigen::MatrixXd;
using namespace Eigen;


struct wavesOUT
{
    Matrix<float, 6, 1> a = {0,0,0,0,0,0};
    Matrix<float, 6, 1> b = {0,0,1.01637,0,0,0};
};

typedef Matrix<float,6,6> Matrix6f;
Matrix6f PrepareOutputStage(float sampleRate);
float OutputStageSample(float inputWet, float inputDry, const Matrix6f& S, wavesOUT& waves);
