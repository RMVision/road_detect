//
// Created by niracler on 18-12-31.
//

#include "LaneDetect.h"
#include "AutoAdjust.hpp" //亮度及对比度自适应方案

int main() {
    string path = "../video/challenge.mp4";
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
    Mat roi_mat;
    vector<Vec4i> lines;

    while (capture.read(frame)) {
        //修改图片大小
        resize(frame, resize_frame, s);
        imshow("原图", resize_frame);

        //亮度及对比度自适应
        int brightness = 255;
        int contrast = 255;
        BrightnessAndContrastAuto(resize_frame, auto_frame, 5);
        adjustBrightnessContrast(auto_frame, adjust_frame, brightness - 255, contrast - 255);
        imshow("亮度及对比度自适应结果", adjust_frame);

        //图像增强
        enhancement_frame = imgEnhancement(adjust_frame);

        //进行模糊化处理
        denoise_frame = deNoise(enhancement_frame);

        //形态学变换
        morphological_frame = imgMorphological(denoise_frame);
        imshow("经过形态学变换的道路图", morphological_frame);

        //透视变换
        warp = getWarpPerspective(morphological_frame);
        imshow("经过透视变换的道路图", warp);

        //标记黄色与白色
        mask_frame = imgMask(warp);
        imshow("标记黄色与白色", mask_frame);

        //边缘检测
        edges_frame = edgeDetector(mask_frame);
        imshow("进行边缘检测", edges_frame);

        // roi Hough直线检测
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
        imshow("标出车道线的原图", resize_frame);
        imshow("copy_mask", re_warp);

        if (waitKey(40) == 'q')
            break;
    }
    return 0;

}

