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

Mat getRoi(Mat &input);

Mat imgEnhancement(const Mat &input);

Mat filterMat(Mat &input);

Mat imgMorphological(Mat &input);

Mat blurMat(Mat &input, int dSize);

Mat cannyMat(Mat &input);

Mat drawRect(Mat &input, Mat &frame);


void callback(int, void *);

int main() {
    VideoCapture capture("../video/vid2.mp4");
    Mat frame;


    int width = (int) capture.get(3);
    int height = (int) capture.get(4);
    Size s(width / 2, height / 2);
    Mat resize_frame;

    while (capture.read(frame)) {
        resize(frame, resize_frame, s);
        Mat temp = Mat::zeros(resize_frame.size(), CV_8UC1);

//        Mat roi = getRoi(resize_frame);
        // 转换HSV颜色空间
        Mat HSV_frame;
        cvtColor(resize_frame, HSV_frame, COLOR_BGR2HSV);

        // 图像增强
        Mat enhance_mat = imgEnhancement(HSV_frame);

        // 提取区域
        Mat filter_mat = filterMat(enhance_mat);

        // 模糊处理
        Mat blur_mat = blurMat(filter_mat, 3);


        // 形态学变换
        Mat morph_mat = imgMorphological(blur_mat);

        // canny边缘处理
//        Mat canny_mat = cannyMat(morph_mat);

        //绘制矩形
        Mat result = drawRect(morph_mat, resize_frame);

        imshow("result", result);
        imshow("morph_mat", morph_mat);
//        imshow("frame", resize_frame);
        if (waitKey(10) == 'q')
            break;
    }
    return 0;
}

Mat getRoi(Mat &input) {
    Rect rect(0, static_cast<int>(input.rows * 0.2), input.cols, static_cast<int>(input.rows * 0.8));
    return input(rect);
}

Mat imgEnhancement(const Mat &input) {
    Mat output;
    Mat kernel = (Mat_<int>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
    filter2D(input, output, input.depth(), kernel);

    return output;
}

Mat filterMat(Mat &input) {
    Mat output;
    Mat blue_mask, red_mask, yellow_mask;
    Vec3i blue_low(100, 100, 70), blue_high(124, 255, 255);
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

Mat cannyMat(Mat &input) {
    Mat output;
    Canny(input, output, 100, 200);
    return output;
}

Mat imgMorphological(Mat &input) {
    Mat output;
    Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5));
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
        double k = (double) (rect.width) / rect.height;
        double area = rect.width * rect.height;
        if (k >= 0.95 && area > 1000)
            rectangle(output, rect, Scalar(0, 0, 255), 2);
    }
    return output;
}