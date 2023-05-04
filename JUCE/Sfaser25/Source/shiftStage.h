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

using namespace Eigen;
//da definire globale?
typedef Matrix<double, 8, 8> Matrix8d;

class ShiftingStage {

public:
    ShiftingStage();
    ~ShiftingStage();

<<<<<<< Updated upstream
    struct wavesSTAGE
    {
        Matrix<double, 8, 1> a = {0,0,0,0,0,0,0,0};
        Matrix<double, 8, 1> b = {0,0,0,0,0,0,0,0};
    };
=======
    Matrix8d prepareShiftStage(float sampleRate);
    float shiftStageSample(float inputSample, Matrix8d S, wavesSTAGE& waves, float LFO);
>>>>>>> Stashed changes

private:
   
    float Z1 = 1e-6;
    float Z2 = 24e3;
    float Z3 = 10e3;
    float Z4;
    float Z5 = Z3;
    float Z6 = 700;
    float Z7 = 1e9;
    float Z8 = 1e-6;
    
    
    Matrix<double, 8, 4> Qv_T;
    
    Matrix<double, 4, 8> Qv;
    
    Matrix<double, 8, 4> Qi_T;
    
    Matrix<double, 4, 8> Qi;
    
    Matrix8d Z;
    Matrix8d I;
    
    Matrix8d S1;
    Matrix8d prepareShiftStage(float sampleRate);
    float shiftStageSample(float inputSample, const Matrix8d& S, wavesSTAGE& waves, float LFO);
};