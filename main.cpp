//
// Created by niracler on 18-12-31.
//

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include "AutoAdjust.hpp" //亮度及对比度自适应方案

using namespace std;
using namespace cv;

static string path = "../video/challenge.mp4";
static int brightness = 255;
static int contrast = 255;



// 设置trackbar滑动块
int max_thres = 255;
int val = 1;
Mat canny_white;

void cannyCallBack(int, void *);
Mat getWarpPerspective(const Mat &input);
Mat reverse(Mat &src);

Mat deNoise(const Mat &input);

Mat imgEnhancement(const Mat &input);

Mat imgMask(const Mat &input);

Mat edgeDetector(const Mat &input);

Mat imgMorphological(const Mat &input);

int main() {

    VideoCapture capture(path);
    Mat frame;
    Mat resize_frame, auto_frame, adjust_frame, denoise_frame;
    Mat enhancement_frame, morphological_frame;
    Mat warp, edges_frame;
    Mat mask_frame;

    int width = (int) capture.get(3);
    int height = (int) capture.get(4);
    Size s(width / 2, height / 2);

    // 设置ROI
    Rect roi(0, (s.height * 2 / 3), s.width / 2, s.height / 3);
    Mat roi_mat;
    vector<Vec4i> lines;

    while (capture.read(frame)) {
        //修改图片大小
        resize(frame, resize_frame, s);


        //亮度及对比度自适应
        BrightnessAndContrastAuto(resize_frame, auto_frame, 5);
        adjustBrightnessContrast(auto_frame, adjust_frame, brightness - 255, contrast - 255);
//        imshow("亮度及对比度自适应结果", adjust_frame);

        //图像增强
        enhancement_frame = imgEnhancement(adjust_frame);

        //进行模糊化处理
        denoise_frame = deNoise(enhancement_frame);

        //形态学变换
        morphological_frame = imgMorphological(denoise_frame);

        //透视变换
        warp = getWarpPerspective(morphological_frame);
//        imshow("经过透视变换的道路图", warp);

        //标记黄色与白色
        mask_frame = imgMask(warp);
        imshow("标记黄色与白色", mask_frame);

        //边缘检测
        edges_frame = edgeDetector(mask_frame);
        imshow("进行边缘检测", edges_frame);

        // roi Hough直线检测
 //       roi_mat = canny_white(roi);
        HoughLinesP(mask_frame, lines, 1, CV_PI / 180, 30, 30);
        Mat copy_mask = Mat::zeros(warp.size(), warp.type());
        for (auto &i : lines) {
            line(copy_mask, Point(i[0], i[1]), Point(i[2], i[3]), Scalar(255,255,0),2);
        }

        Mat re_warp = reverse(copy_mask);
        for (int i = 0; i < resize_frame.rows; ++i) {
            for (int j = 0; j < resize_frame.cols ; ++j) {
                if (!(!re_warp.at<Vec3b>(i,j)[0] && !re_warp.at<Vec3b>(i,j)[1] &&!re_warp.at<Vec3b>(i,j)[2] )) {
                    resize_frame.at<Vec3b>(i,j)[0] = 0;
                    resize_frame.at<Vec3b>(i,j)[1] = 0;
                    resize_frame.at<Vec3b>(i,j)[2] = 255;
                }
            }
        }
        imshow("原图", resize_frame);

        imshow("copy_mask", re_warp);

        if (waitKey(20) == 'q')
            break;
    }
    return 0;

}

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
/*    Mat M2 = getPerspectiveTransform(pts_src, pts_dst);
    Mat warp2;
    warpPerspective(warp, warp2, M2, src.size(), INTER_LINEAR);*/
    return warp;
    //  imshow("warp", warp);
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
/*    Mat M2 = getPerspectiveTransform(pts_src, pts_dst);
    Mat warp2;
    warpPerspective(warp, warp2, M2, src.size(), INTER_LINEAR);*/
    return warp;
    //  imshow("warp", warp);
}