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

typedef Matrix<double, 8, 8> Matrix8d;

struct wavesSTAGE
{
    Matrix<double, 8, 1> a = { 0,0,0,0,0,0,0,0 };
    Matrix<double, 8, 1> b = { 0,0,0,0,0,0,0,0 };
};

class ShiftStage {

public:
    ShiftStage();
    ~ShiftStage() {};

    void prepareShiftStage(float sampleRate);
    float shiftStageSample(float inputSample, wavesSTAGE& waves, float LFO);
    void shiftMatrix(float Z4, float Z6);

private:
   
    //float Z1 = 1e-6;
    //float Z2 = 24e3;
    //float Z3 = 10e3;
    float Z4 = 0;
    //float Z5 = Z3;
    float Z6 = 700;
    //float Z7 = 1e9;
    //float Z8 = 1e-6;

    float Vref = 5.1;
    float Is = 5.185e-3;
    float Vp = -2.021;
    float k = 2 * Is / (pow(Vp, 2));

    //Matrix<double, 8, 4> Qv_T;
    //
    //Matrix<double, 4, 8> Qv;
    //
    //Matrix<double, 8, 4> Qi_T;
    //
    //Matrix<double, 4, 8> Qi;

    //Matrix8d Z;
 
    //Matrix8d I;

    //Matrix4d I4;

   Matrix8d S1;
};