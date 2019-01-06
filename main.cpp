//
// Created by niracler on 18-12-31.
//

#include "LaneDetect.h"
#include "SignDetect.h"

int main() {
    string path = "../video/vid2.mp4";
    VideoCapture capture(path);

    int width = (int) capture.get(3);
    int height = (int) capture.get(4);
    Size s(width / 2, height / 2);

    Mat frame, resize_frame;

    while (capture.read(frame)) {
        //修改图片大小
        resize(frame, resize_frame, s);
        imshow("原图", resize_frame);
//        frame = imgLaneDetect(resize_frame, false);
//        imshow("结果1", frame);
        frame = imgSignDetect(resize_frame, false);
        imshow("结果2", frame);


        if (waitKey(33) == 'q')
            break;
    }
    return 0;

}

