//
//  inputStage.h
//  Sfaser25
//
//  Created by Samuele Del Moro on 30/04/23.
//

#ifndef inputStage_h
#define inputStage_h


#endif /* inputStage_h */


#include "../../eigen-3.4.0/Eigen/Dense"
#include <stdio.h>
#include <iostream>

using Eigen::MatrixXd;
using namespace Eigen;


struct wavesIN
{
    Vector4f a = {0,0,0,0};
    Vector4f b = {0,-5.1,0,0};
};


Matrix4f prepareInputStage(float sampleRate);
float inputStageSample(const float inputSample, const Matrix4f& S, wavesIN& waves);
