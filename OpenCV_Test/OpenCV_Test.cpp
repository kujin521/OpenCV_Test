// OpenCV_Test.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<openCV2/core/core.hpp>
#include<openCV2/highgui/highgui.hpp>
using namespace cv;

int main()
{
    Mat srcImage = imread("E:\\a.jpg");
    //Mat srcImage = imread("ab.jpg",0);
    namedWindow("show");
    imshow("show",srcImage);
    waitKey(0);
    return 0;
}