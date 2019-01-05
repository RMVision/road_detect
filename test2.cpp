//
// Created by zzh on 19-1-5.
//
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include "AutoAdjust.hpp" //亮度及对比度自适应方案

using namespace std;
using namespace cv;

Mat filterMat(Mat &input);

Mat imgMorphological(Mat &input);

Mat blurMat(Mat &input, int dSize);

Mat drawRect(Mat &input, Mat &frame);

int main() {
    VideoCapture capture("../video/challenge.mp4");
    Mat frame;


    int width = (int) capture.get(3);
    int height = (int) capture.get(4);
    Size s(width / 2, height / 2);
    Mat resize_frame;
    while (capture.read(frame)) {
        resize(frame, resize_frame, s);
        Mat temp = Mat::zeros(resize_frame.size(), CV_8UC1);

        // 转换HSV颜色空间
        Mat HSV_frame;
        cvtColor(resize_frame, HSV_frame, COLOR_BGR2HSV);

        // 提取区域
        Mat filter_mat = filterMat(HSV_frame);

        // 模糊处理
        Mat blur_mat = blurMat(filter_mat, 3);

        // 形态学变换
        Mat morph_mat = imgMorphological(blur_mat);

        //绘制矩形
        Mat result = drawRect(morph_mat, resize_frame);

        imshow("morph_mat", result);
//        imshow("frame", resize_frame);
        if (waitKey(10) == 'q')
            break;
    }
    return 0;
}

Mat filterMat(Mat &input) {
    Mat output;
    Mat blue_mask, red_mask, yellow_mask;
    Vec3i blue_low(100, 50, 50), blue_high(124, 255, 255);
//    Vec3i red_low(0, 50, 50), red_high(10, 255, 255);
//    Vec3i yellow_low(25, 50, 50), yellow_high(35, 255, 255);
    inRange(input, blue_low, blue_high, blue_mask);
//    inRange(input, red_low, red_high, red_mask);
//    inRange(input, yellow_low, yellow_high, yellow_mask);
//    Mat temp;
//    imshow("blue_mask", blue_mask);
//    imshow("red_mask", red_mask);
//    bitwise_or(blue_mask, red_mask, output);
    return blue_mask;
}

Mat blurMat(Mat &input, int dSize) {
    Mat output;
//    blur(input, output, Size(dSize, dSize));
    GaussianBlur(input, output, Size(dSize, dSize), 0);
    return output;
}

Mat imgMorphological(Mat &input) {
    Mat output;
    Mat kernel = getStructuringElement(MORPH_RECT, Size(21, 7));
    morphologyEx(input, output, MORPH_CLOSE, kernel);
    return output;
}

Mat drawRect(Mat &input, Mat &frame) {
    //  查找轮廓
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    Mat output = frame.clone();
    findContours(input, contours, hierarchy, RETR_LIST, CHAIN_APPROX_SIMPLE);
    for (const auto &contour : contours) {
        Rect rect = boundingRect(contour);
        rectangle(output, rect, Scalar(0,0,255),2);
    }
    return output;
}