//
// Created by niracler on 19-1-5.
//

#ifndef ROAD_DETECT_LANEDETECT_H
#define ROAD_DETECT_LANEDETECT_H


#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>


using namespace std;
using namespace cv;

Mat getWarpPerspective(const Mat &input);

Mat reverse(Mat &src);

Mat deNoise(const Mat &input);

Mat imgEnhancement(const Mat &input);

Mat imgMask(const Mat &input);

Mat edgeDetector(const Mat &input);

Mat imgMorphological(const Mat &input);


#endif //ROAD_DETECT_LANEDETECT_H
