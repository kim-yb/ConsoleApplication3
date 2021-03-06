// ConsoleApplication3.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include <iostream>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <Windows.h>
using namespace std;
using namespace cv;
int DELAY_CAPTION = 1500;
int DELAY_BLUR = 100;
int MAX_KERNEL_LENGTH = 31;
Mat src; Mat dst;
char window_name[] = "Smoothing Demo";
int display_caption(const char* caption);
int display_dst(int delay);
int main(int argc, char ** argv)
{
	namedWindow(window_name, WINDOW_AUTOSIZE);
	const char* filename = argc >= 2 ? argv[1] : "c:/busan.jpg";
	src = imread(filename, IMREAD_COLOR);
	if (src.empty()) {
		printf(" Error opening image\n");
		printf(" Usage: ./Smoothing [image_name -- default ../data/lena.jpg] \n");
		return -1;
	}
	double t = (double)getTickCount();
	double f = (double)getTickFrequency();
	Sleep(1234);
	double e = t - (double)getTickCount();
	e = e / f;
	// do something ...

	if (display_caption("Original Image") != 0) { return 0; }
	dst = src.clone();
	if (display_dst(DELAY_CAPTION) != 0) { return 0; }
	if (display_caption("Homogeneous Blur") != 0) { return 0; }
	for (int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2)
	{
		blur(src, dst, Size(i, i), Point(-1, -1));
		if (display_dst(DELAY_BLUR) != 0) { return 0; }
	}
	
	t = ((double)getTickCount() - t) /f;
	cout << " Homogeneous Blure " << t << " \n";
	if (display_caption("Gaussian Blur") != 0) { return 0; }
	t = (double)getTickCount();
	for (int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2)
	{
		GaussianBlur(src, dst, Size(i, i), 0, 0);
		if (display_dst(DELAY_BLUR) != 0) { return 0; }
	}
	t = ((double)getTickCount() - t) / f;
	cout << " Gaussian Blure " << t << " \n";

	if (display_caption("Median Blur") != 0) { return 0; }
	t = (double)getTickCount();
	for (int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2)
	{
		medianBlur(src, dst, i);
		if (display_dst(DELAY_BLUR) != 0) { return 0; }
	}
	t = ((double)getTickCount() - t) / f;
	cout << " Median Blure " << t << " \n";
	if (display_caption("Bilateral Blur") != 0) { return 0; }
	t = (double)getTickCount();
	for (int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2)
	{
		bilateralFilter(src, dst, i, i * 2, i / 2);
		if (display_dst(DELAY_BLUR) != 0) { return 0; }
	}
	display_caption("Done!");
	waitKey();
	return 0;
}
int display_caption(const char* caption)
{
	dst = Mat::zeros(src.size(), src.type());
	putText(dst, caption,
		Point(src.cols / 4, src.rows / 2),
		FONT_HERSHEY_COMPLEX, 1, Scalar(255, 255, 255));
	return display_dst(DELAY_CAPTION);
}
int display_dst(int delay)
{
	imshow(window_name, dst);
	int c = waitKey(delay);
	if (c >= 0) { return -1; }
	return 0;
}