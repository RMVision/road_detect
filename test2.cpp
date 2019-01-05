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
bool isRed(float b_data, float g_data, float r_data);
bool isBlue(float b_data, float g_data, float r_data);
bool isYellow(float b_data, float g_data, float r_data);
int main() {
    VideoCapture capture("/home/zzh/2.mp4");
    Mat frame;
    int sum = 0;
    int b, g, r;
    float b_data, g_data, r_data;

    int width = (int) capture.get(3);
    int height = (int) capture.get(4);
    Size s(width / 2, height / 2);
    Mat resize_frame;
    while (capture.read(frame)) {
        resize(frame, resize_frame, s);
        Mat temp = Mat::zeros(resize_frame.size(), CV_8UC1);
        for (int i = 0; i < resize_frame.rows; i++) {
            for (int j = 0; j < resize_frame.cols; j++) {
                b = resize_frame.at<Vec3i>(i, j)[0];
                g = resize_frame.at<Vec3i>(i, j)[1];
                r = resize_frame.at<Vec3i>(i, j)[2];
                sum = b + g + r;

                b_data = (float) b / sum;
                g_data = (float) g / sum;
                r_data = (float) r / sum;

                if(isRed(b_data,g_data,r_data) || isBlue(b_data,g_data,r_data) || isYellow(b_data,g_data,r_data)) {
                    temp.at<uchar>(i, j) = 255;
                }
            }
        }
        imshow("temp", temp);
        imshow("frame", resize_frame);
        if( waitKey(10) == 'q')
            break;
    }
    return 0;
}

bool isRed(float b_data, float g_data, float r_data) {
    return (r_data >= 0.4) && (g_data <= 0.3);
}

bool isBlue(float b_data, float g_data, float r_data) {
    return b_data >= 0.4;
}

bool isYellow(float b_data, float g_data, float r_data) {
    return r_data + g_data >= 0.85;
}