//
// Created by zzh on 19-1-5.
//
#include "SignDetect.h"

Mat imgSignDetect(const Mat &input, bool flag) {
    Mat output;
    input.copyTo(output);

    Mat temp = Mat::zeros(input.size(), CV_8UC1);

//  Mat roi = getRoi(resize_frame);
    // 转换HSV颜色空间
    Mat HSV_frame;
    cvtColor(input, HSV_frame, COLOR_BGR2HSV);
    if(flag) imshow("转换HSV颜色空间", HSV_frame);

    // 图像增强
    Mat enhance_mat = imgEnhancement2(HSV_frame);
    if(flag) imshow("图像增强", enhance_mat);

    // 提取区域
    Mat filter_mat = filterMat(enhance_mat);
    if(flag) imshow("提取区域", filter_mat);

    // 模糊处理
    Mat blur_mat = blurMat(filter_mat, 3);
    if(flag) imshow("模糊处理", blur_mat);

    // 形态学变换
    Mat morph_mat = imgMorphological(blur_mat);
    if(flag) imshow("形态学变换", morph_mat);

    // canny边缘处理
//        Mat canny_mat = cannyMat(morph_mat);

    //绘制矩形
    Mat result = drawRect(morph_mat, output);
    if(flag) imshow("绘制矩形", result);
    if(flag) imshow("morph_mat", morph_mat);
    return result;
}

Mat getRoi(Mat &input) {
    Rect rect(0, static_cast<int>(input.rows * 0.2), input.cols, static_cast<int>(input.rows * 0.8));
    return input(rect);
}

Mat imgEnhancement2(const Mat &input) {
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