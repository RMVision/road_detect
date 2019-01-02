//
// Created by niracler on 18-12-31.
//

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include "AutoAdjust.hpp" //亮度及对比度自适应方案

using namespace std;
using namespace cv;

static string path = "/home/zzh/1.mp4";
static int brightness = 255;
static int contrast = 255;

// 设置阈值，挑出白色与黄色区域
static Vec3i white_low(0, 200, 0), yellow_low(26, 43, 46);
static Vec3i white_top(255, 255, 255), yellow_top(34, 255, 255);

// 设置trackbar滑动块
int max_thres = 255;
int val = 80;
Mat canny_white;
Mat white_mask, yellow_mask;

void canny_call_back(int, void *);


int main() {

    VideoCapture capture(path);
    Mat frame, HLS_frame;
    Mat resize_frame, auto_frame, adjust_frame;
    Mat laplace_frame;

    int width = (int) capture.get(3);
    int height = (int) capture.get(4);
    Size s(width / 2, height / 2);

    // 设置ROI
    Rect roi(0, (s.height * 2 / 3), s.width / 2, s.height / 3);
    Mat roi_mat;
    vector<Vec4i> lines;

    namedWindow("white", WINDOW_AUTOSIZE);
    while (capture.read(frame)) {
        //修改图片大小
        resize(frame, resize_frame, s);


//        //亮度及对比度自适应
//        BrightnessAndContrastAuto(resize_frame, auto_frame, 5);
//        if (!auto_frame.data) {
//            cout << "自适应失败" << endl;
//            return -1;
//        }
//        adjustBrightnessContrast(auto_frame, adjust_frame, brightness - 255, contrast - 255);
//        imshow("亮度及对比度自适应结果", adjust_frame);

        //Laplace图像增强
        Mat kernel = (Mat_<int>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
        filter2D(resize_frame, laplace_frame, resize_frame.depth(), kernel);

        //转换为HLS颜色空间
        cvtColor(laplace_frame, HLS_frame, COLOR_BGR2HSV_FULL);
        inRange(HLS_frame, white_low, white_top, white_mask);
        inRange(HLS_frame, yellow_low, yellow_top, yellow_mask);

//        imshow("白色1", white_mask);
        //canny边缘检测
        blur(white_mask, white_mask, Size(5, 5));
/*        createTrackbar("canny", "white", &val, max_thres, canny_call_back);
        canny_call_back(0, 0);*/
        Canny(white_mask, canny_white, val, val * 2);

        // roi Hough直线检测
        roi_mat = canny_white(roi);
        HoughLinesP(roi_mat, lines, 1, CV_PI / 180, 10, 10);
        double k_queue[lines.size()];
        int p1_ys[lines.size()];
        int p2_xs[lines.size()];
        for (int i = 0; i < lines.size(); i++) {
            double k = (static_cast<double >(lines[i][3] - lines[i][1]) /
                        static_cast<double >(lines[i][2] - lines[i][0]));
            k_queue[i] = k;
            p1_ys[i] = abs(static_cast<int>(-1 * k * lines[i][0] + lines[i][1]));
            p2_xs[i] = abs(static_cast<int>(lines[i][1] / k * (-1) + lines[i][0]));
        }
        double k = 0;
        double p1_y = 0, p2_x = 0;
        for (int i = 0; i < lines.size(); i++) {
            k += k_queue[i];
            p1_y += p1_ys[i];
            p2_x += p2_xs[i];
        }
        k /= lines.size();
        p1_y /= lines.size();
        p2_x /= lines.size();
        // x = 0时
        Point p1(0, static_cast<int>(p1_y));
        // y = 0时
        Point p2(static_cast<int>(p2_x), 0);

        line(resize_frame(roi), p1, p2, Scalar(0, 0, 255), 5);
        imshow("frame", resize_frame);
//        imshow("roi_mat", roi_mat);
//        imshow("white", canny_white);
//        imshow("白色", white_mask);
//        imshow("黄色", yellow_mask);

        if (waitKey(20) == 'q')
            break;
    }
    return 0;

}

void canny_call_back(int, void *) {
    Canny(white_mask, canny_white, val, val * 2);

    imshow("white", canny_white);
}