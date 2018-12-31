#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main() {
    VideoCapture capture("../video/1.mp4");
    Mat frame, HLS_frame;
    Mat resize_frame;
    Mat white_mask, yellow_mask;
    int width = (int)capture.get(3);
    int height = (int)capture.get(4);
    Size s(width/2, height/2);
    while (capture.read(frame)) {

        resize(frame, resize_frame, s);
        imshow("frame", resize_frame);
        cvtColor(resize_frame, HLS_frame, COLOR_BGR2HSV_FULL);
        // 设置阈值，挑出白色与黄色区域
        Vec3i white_low(0, 0, 221), yellow_low(26, 43, 46);
        Vec3i white_top(180, 30, 255), yellow_top(34, 255, 255);

        inRange(HLS_frame, white_low, white_top, white_mask);
        inRange(HLS_frame, yellow_low, yellow_top, yellow_mask);

        imshow("white_mask", white_mask);
        imshow("yellow_mask", yellow_mask);

        if (waitKey(20) == 'q')
            break;
    }
    return 0;
}