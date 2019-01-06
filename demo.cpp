//
// Created by niracler on 18-12-31.
//

#include "include/LaneDetect.h"
#include "include/SignDetect.h"

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
        frame = imgLaneDetect(resize_frame, true);
        imshow("结果1", frame);
//        frame = imgSignDetect(resize_frame, true);
//        imshow("结果2", frame);


        if (waitKey(30) == 'q')
            break;
    }
    return 0;

}

