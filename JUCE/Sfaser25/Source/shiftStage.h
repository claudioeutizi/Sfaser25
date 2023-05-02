/*
  ==============================================================================

    shiftStage.h
    Created: 1 May 2023 6:03:45pm
    Author:  Samuele Del Moro

  ==============================================================================
*/


#include "../../eigen-3.4.0/Eigen/Dense"
#include <stdio.h>
#include <iostream>

#pragma once

using Eigen::MatrixXd;
using namespace Eigen;



struct wavesSTAGE
{
    Matrix<double, 8, 1> a = {0,0,0,0,0,0,0,0};
    Matrix<double, 8, 1> b = {0,0,0,0,0,0,0,0};
};
//da definire globale?
typedef Matrix<double, 8, 8> Matrix8d;

Matrix8d PrepareShiftStage(float sampleRate);
float ShiftStageSample(float inputSample, const Matrix8d& S, wavesSTAGE& waves);
