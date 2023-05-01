/*
  ==============================================================================

    shiftStage.h
    Created: 1 May 2023 6:03:45pm
    Author:  Samuele Del Moro

  ==============================================================================
*/


#include "/Users/djsamu.el/Documents/eigen-3.4.0/Eigen/Dense"
#include <stdio.h>
#include <iostream>

#pragma once

using Eigen::MatrixXd;
using namespace Eigen;

//float sampleRate = 192000;

//float Z6 = 0;

struct Shift_Data
{
    Matrix<float, 8, 1> a = {0,0,0,0,0,0,0,0};
    Matrix<float, 8, 1> b = {0,0,0,0,0,0,0,0};
};

typedef Matrix<float,8,8> Mat_SH;
Mat_SH PrepareShiftStage(float sampleRate);
float ShiftStageSample(float inputBuffer, const Mat_SH& S, Shift_Data& Sh_d);
