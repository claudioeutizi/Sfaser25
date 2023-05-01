/*
  ==============================================================================

    outputStage.h
    Created: 1 May 2023 2:37:54pm
    Author:  Samuele Del Moro

  ==============================================================================
*/
#include "/Users/djsamu.el/Documents/eigen-3.4.0/Eigen/Dense"
#include <stdio.h>
#include <iostream>

#pragma once

using Eigen::MatrixXd;
using namespace Eigen;

//float B_old_out=1.01637;

struct Output_Data
{
    Matrix<float, 6, 1> a = {0,0,0,0,0,0};
    Matrix<float, 6, 1> b = {0,0,1.01637,0,0,0};
};

typedef Matrix<float,6,6> Mat_OUT;
Mat_OUT PrepareOutputStage(float sampleRate);
float OutputStageSample(float inputBuffer, float inputDry, const Mat_OUT& S, Output_Data& V_d);
