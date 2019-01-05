//
// Created by niracler on 19-1-5.
//

#include "LaneDetect.h"

Mat imgMorphological(const Mat &input) {
    Mat output;
    Mat kernel1 = getStructuringElement(MORPH_RECT, Size(3,3));
    Mat kernel2 = getStructuringElement(MORPH_RECT, Size(5,5));
    dilate(input, output, kernel2);
    erode(output, output, kernel1);

    return output;
}

Mat edgeDetector(const Mat &input) {
    Mat output;

    // 设置trackbar滑动块
    int val = 1;

    //canny
    blur(input, input, Size(5, 5));
    Canny(input, output, val, val * 2);

    return output;
}

Mat imgMask(const Mat &input) {

    // 设置阈值，挑出白色与黄色区域
    static Mat white_mask, yellow_mask;
    static Vec3i white_low(0, 250, 0), yellow_low(26, 35, 46);
    static Vec3i white_top(255, 255, 255), yellow_top(34, 255, 255);
    Mat output;
    Mat HLS_frame;

    //转换为HLS颜色空间
    cvtColor(input, HLS_frame, COLOR_BGR2HLS);
    inRange(HLS_frame, white_low, white_top, white_mask);
    inRange(HLS_frame, yellow_low, yellow_top, yellow_mask);
    bitwise_or(white_mask, yellow_mask, output);

    return output;
}

Mat imgEnhancement(const Mat &input) {
    Mat output;
    Mat kernel = (Mat_<int>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
    filter2D(input, output, input.depth(), kernel);

    return output;
}

Mat deNoise(const Mat &input) {
    Mat output;
    GaussianBlur(input, output, cv::Size(3, 3), 0, 0);

    return output;
}

Mat getWarpPerspective(const Mat &input) {
    Point2f pts_src[] = {
            Point2d(input.cols * 0.2, input.rows * 0.95),
            Point2d(input.cols * 0.9, input.rows * 0.95),
            Point2d(input.cols * 0.7, input.rows * 0.7),
            Point2d(input.cols * 0.3, input.rows * 0.7),
    };
    Point2f pts_dst[] = {
            Point2d(0, input.rows * 0.9),
            Point2d(input.cols-1, input.rows * 0.9),
            Point2d(input.cols-1, 0),
            Point2d(0, 0),
    };

    Mat M = getPerspectiveTransform(pts_src, pts_dst);
    Mat warp;
    warpPerspective(input, warp, M, input.size(), INTER_LINEAR);
    return warp;
}

Mat reverse(Mat &src) {
    Point2f pts_src[] = {
            Point2d(src.cols * 0.2, src.rows * 0.95),
            Point2d(src.cols * 0.9, src.rows * 0.95),
            Point2d(src.cols * 0.7, src.rows * 0.7),
            Point2d(src.cols * 0.3, src.rows * 0.7),
    };
    Point2f pts_dst[] = {
            Point2d(0, src.rows * 0.9),
            Point2d(src.cols-1, src.rows * 0.9),
            Point2d(src.cols-1, 0),
            Point2d(0, 0),
    };

    Mat M = getPerspectiveTransform(pts_dst, pts_src);
    Mat warp;
    warpPerspective(src, warp, M, src.size(), INTER_LINEAR);

    return warp;
}