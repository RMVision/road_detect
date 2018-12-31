//
// Created by niracler on 18-12-30.
//

#include <iostream>
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

using namespace std;
using namespace cv;

#define CLIP_RANGE(value, min, max)  ( (value) > (max) ? (max) : (((value) < (min)) ? (min) : (value)) )
#define COLOR_RANGE(value)  CLIP_RANGE(value, 0, 255)

/**
 *  \brief Automatic brightness and contrast optimization with optional histogram clipping
 *  \param [in]src Input image GRAY or BGR or BGRA
 *  \param [out]dst Destination image
 *  \param clipHistPercent cut wings of histogram at given percent tipical=>1, 0=>Disabled
 *  \note In case of BGRA image, we won't touch the transparency
*/
void BrightnessAndContrastAuto(const Mat &src, Mat &dst, float clipHistPercent=0)
{
    CV_Assert(clipHistPercent >= 0);
    CV_Assert((src.type() == CV_8UC1) || (src.type() == CV_8UC3) || (src.type() == CV_8UC4));

    int histSize = 256;
    float alpha, beta;
    double minGray = 0, maxGray = 0;

    //to calculate grayscale histogram
    Mat gray;
    if (src.type() == CV_8UC1) gray = src;
    else if (src.type() == CV_8UC3) cvtColor(src, gray, COLOR_BGR2GRAY);
    else if (src.type() == CV_8UC4) cvtColor(src, gray, COLOR_BGRA2GRAY);
    if (clipHistPercent == 0)
    {
        // keep full available range
        minMaxLoc(gray, &minGray, &maxGray);
    }
    else
    {
        Mat hist; //the grayscale histogram

        float range[] = { 0, 256 };
        const float* histRange = { range };
        bool uniform = true;
        bool accumulate = false;
        calcHist(&gray, 1, 0, Mat(), hist, 1, &histSize, &histRange, uniform, accumulate);

        // calculate cumulative distribution from the histogram
        vector<float> accumulator(histSize);
        accumulator[0] = hist.at<float>(0);
        for (int i = 1; i < histSize; i++)
        {
            accumulator[i] = accumulator[i - 1] + hist.at<float>(i);
        }

        // locate points that cuts at required value
        float max = accumulator.back();
        clipHistPercent *= (max / 100.0); //make percent as absolute
        clipHistPercent /= 2.0; // left and right wings
        // locate left cut
        minGray = 0;
        while (accumulator[minGray] < clipHistPercent)
            minGray++;

        // locate right cut
        maxGray = histSize - 1;
        while (accumulator[maxGray] >= (max - clipHistPercent))
            maxGray--;
    }

    // current range
    float inputRange = maxGray - minGray;

    alpha = (histSize - 1) / inputRange;   // alpha expands current range to histsize range
    beta = -minGray * alpha;             // beta shifts current range so that minGray will go to 0

    // Apply brightness and contrast normalization
    // convertTo operates with saurate_cast
    src.convertTo(dst, -1, alpha, beta);

    // restore alpha channel from source
    if (dst.type() == CV_8UC4)
    {
        int from_to[] = { 3, 3};
        mixChannels(&src, 4, &dst,1, from_to, 1);
    }
    return;
}

/**
 * Adjust Brightness and Contrast
 *
 * @param src [in] InputArray
 * @param dst [out] OutputArray
 * @param brightness [in] integer, value range [-255, 255]
 * @param contrast [in] integer, value range [-255, 255]
 *
 * @return 0 if success, else return error code
 */
int adjustBrightnessContrast(InputArray src, OutputArray dst, int brightness, int contrast)
{
    Mat input = src.getMat();
    if( input.empty() ) {
        return -1;
    }

    dst.create(src.size(), src.type());
    Mat output = dst.getMat();

    brightness = CLIP_RANGE(brightness, -255, 255);
    contrast = CLIP_RANGE(contrast, -255, 255);

    /**
    Algorithm of Brightness Contrast transformation
    The formula is:
        y = [x - 127.5 * (1 - B)] * k + 127.5 * (1 + B);

        x is the input pixel value
        y is the output pixel value
        B is brightness, value range is [-1,1]
        k is used to adjust contrast
            k = tan( (45 + 44 * c) / 180 * PI );
            c is contrast, value range is [-1,1]
    */

    double B = brightness / 255.;
    double c = contrast / 255. ;
    double k = tan( (45 + 44 * c) / 180 * M_PI );

    Mat lookupTable(1, 256, CV_8U);
    uchar *p = lookupTable.data;
    for (int i = 0; i < 256; i++)
        p[i] = COLOR_RANGE( (i - 127.5 * (1 - B)) * k + 127.5 * (1 + B) );

    LUT(input, lookupTable, output);

    return 0;
}


void waitESC(){
    while(int key=waitKey(0) != 27){};
}

static string window_name = "photo";
static Mat src,src1,dst1;
static int brightness = 255;
static int contrast = 255;

static void callbackAdjust(int , void *)
{
    Mat dst;
    adjustBrightnessContrast(src, dst, brightness - 255, contrast - 255);
    imshow(window_name, dst);
}


int main(){


    src1=imread(argv[1]);
    imshow("org",src1);
    BrightnessAndContrastAuto(src1,src,5);

    if ( !src.data ) {
        cout << "error read image" << endl;
        return -1;
    }

    namedWindow(window_name);
    createTrackbar("brightness", window_name, &brightness, 2*brightness, callbackAdjust);
    createTrackbar("contrast", window_name, &contrast, 2*contrast, callbackAdjust);
    callbackAdjust(0, 0);

    waitESC();

    VideoCapture capture("/home/zzh/1.mp4");
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

    return 0;

}