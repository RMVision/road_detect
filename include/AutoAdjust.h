//
// Created by niracler on 19-1-6.
//


#ifndef ROAD_DETECT_AUTOADJUST_H
#define ROAD_DETECT_AUTOADJUST_H

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

void BrightnessAndContrastAuto(const Mat &src, Mat &dst, float clipHistPercent = 0);
int adjustBrightnessContrast(InputArray src, OutputArray dst, int brightness, int contrast);

#endif //ROAD_DETECT_AUTOADJUST_H
