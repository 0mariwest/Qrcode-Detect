#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv; 
int main()
{
    Mat img = imread("/root/computer-vision/test-opencv/pictures/1.png");
    imshow("test", img);
    waitKey(0);
    return 0;
}