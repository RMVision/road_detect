//
// Created by niracler on 18-12-31.
//

#include "LaneDetect.h"


int main() {
    string path = "../video/challenge.mp4";
    VideoCapture capture(path);

    int width = (int) capture.get(3);
    int height = (int) capture.get(4);
    Size s(width / 2, height / 2);

    Mat frame, resize_frame;

    while (capture.read(frame)) {
        //修改图片大小
        resize(frame, resize_frame, s);
        imshow("原图", resize_frame);
        frame = imgLaneDetect(resize_frame, false);
        imshow("结果", frame);


        if (waitKey(0) == 'q')
            break;
    }
    return 0;

}

