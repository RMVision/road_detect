//
// Created by niracler on 19-1-6.
//

#ifndef ROAD_DETECT_SIGNDETECT_H
#define ROAD_DETECT_SIGNDETECT_H

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>


using namespace std;
using namespace cv;

Mat getRoi(Mat &input);

Mat imgEnhancement2(const Mat &input);

Mat filterMat(Mat &input);

Mat imgMorphological(Mat &input);

Mat blurMat(Mat &input, int dSize);

Mat cannyMat(Mat &input);

Mat drawRect(Mat &input, Mat &frame);

void callback(int, void *);

Mat imgSignDetect(const Mat &input, bool flag);

#endif //ROAD_DETECT_SIGNDETECT_H
