// canny.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"



Mat src, src_gray;
Mat dst, detected_edges;

int edgeThresh = 1;
int lowThreshold;
int const max_lowThreshold = 100;
int ratio = 3;
int kernel_size = 3;
const char* window_name = "Edge Map";

static void CannyThreshold(int, void*)
{
	//物体边缘检测器，虽然效果卓越，但是速度非常慢
	blur(src_gray, detected_edges, Size(3, 3));
	//大约到100的阈值的时候识别大件物体边缘的效果比较好
	Canny(detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size);

	dst = Scalar::all(0);
	//将处理过的图片送回dst，虽然dst不会再进行一次灰度化
	src.copyTo(dst, detected_edges);

	imshow(window_name, dst);
}


int main(int argc, char** argv)
{
	CommandLineParser parser(argc, argv, "{@input |C:\\Users\\11235\\Pictures\\Camera Roll\\IMG_20170915_171544.jpg | input image}");
	src = imread(parser.get<String>("@input"), IMREAD_COLOR); // Load an image

	if (src.empty())
	{
		std::cout << "Could not open or find the image!\n" << std::endl;
		std::cout << "Usage: " << argv[0] << " <Input image>" << std::endl;
		return -1;
	}

	dst.create(src.size(), src.type());

	cvtColor(src, src_gray, COLOR_BGR2GRAY);

	namedWindow(window_name, WINDOW_NORMAL);
	cvResizeWindow(window_name, 500, 500);

	createTrackbar("Min Threshold:", window_name, &lowThreshold, max_lowThreshold, CannyThreshold);

	CannyThreshold(0, 0);

	waitKey(0);

	return 0;
}