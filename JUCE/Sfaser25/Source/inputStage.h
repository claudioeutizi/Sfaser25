//
//  inputStage.h
//  Sfaser25
//
//  Created by Samuele Del Moro on 30/04/23.
//

#ifndef inputStage_h
#define inputStage_h


#endif /* inputStage_h */


#include "C:/Users/matti/Desktop/MAE/mxrPhase90/Face90/JUCE/eigen-3.4.0/Eigen/Dense"
#include <stdio.h>
#include <iostream>

using Eigen::MatrixXd;
using namespace Eigen;

struct Input_Data
{
    Matrix<float, 4, 1> a = {0,0,0,0};
    Matrix<float, 4, 1> b = {0,-5.1,0,0};
};

typedef Matrix<float,4,4> Mat_IN;
Mat_IN PrepareInputStage(float sampleRate);
float InputStageSample(const float inputBuffer, const Mat_IN& S, Input_Data& I_d);
