#include <iostream>
#include <opencv2/opencv.hpp>
#include <tkInt.h>

using namespace std;
using namespace cv;

int main() {

    Mat image = imread("../img/road.jpg");

    if (!image.data) {
        cout << "读取图片失败" << endl;
        return 0;
    }

    imshow("道路图片", image);

    //使用Canny算子进行边缘检测
    Mat contours;
    Canny(image, contours, 50, 350);
    //imshow("使用Canny算子进行边缘检测", contours);
    Mat contoursInv;
    threshold(contours, contoursInv, 128, 255, THRESH_BINARY_INV);
    imshow("使用Canny算子进行边缘检测", contoursInv);

    vector<Vec2f> lines;
    int houghVote = 0;
    if (houghVote < 1 or lines.size() > 2) {
        houghVote = 200;
    } else {
        houghVote += 25;
    }

    while (lines.size() < 5 && houghVote > 0) {
        HoughLines(contours, lines, 1, PI / 180, houghVote);
        houghVote -= 5;
    }

    cout << houghVote << endl;
    Mat result(contours.rows, contours.cols, CV_8U, Scalar(255));
    image.copyTo(result);


    // Draw the limes
    std::vector<Vec2f>::const_iterator it= lines.begin();
    Mat hough(image.size(),CV_8U,Scalar(0));
    while (it!=lines.end()) {
        float rho= (*it)[0];   // first element is distance rho
        float theta= (*it)[1]; // second element is angle theta
        Point pt1(rho/cos(theta),0);
        Point pt2((rho-result.rows*sin(theta))/cos(theta),result.rows);
        line( result, pt1, pt2, Scalar(255), 8);
        line( hough, pt1, pt2, Scalar(255), 8);
        ++it;
    }

    imshow("结果", result);

    waitKey(0);

    return 0;
}
