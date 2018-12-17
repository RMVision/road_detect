//
// Created by niracler on 18-12-17.
//

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;
int main(){
    VideoCapture capture(0);
    Mat frame;
    while(1) {
        capture >> frame;
        imshow("frame", frame);
        if (waitKey(1) == 'q')
            break;

    }
    destroyWindow("frame");
    return 0;
}