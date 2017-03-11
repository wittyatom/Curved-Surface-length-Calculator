#include<iostream>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>
using namespace cv;
using namespace std;

Mat src; Mat src_gray;
int thresh = 100;
int max_thresh = 255;
RNG rng(12345);

void thresh_callback(int, void*);


int main(int argc, char** argv)
{
	Mat bgr_image = imread("4.jpg", CV_LOAD_IMAGE_UNCHANGED);

	// Check if the image can be loaded
	Mat orig_image = bgr_image.clone();
	medianBlur(bgr_image, bgr_image, 3);

	// Coverting input image to HSV
	Mat hsv_image;
	cvtColor(bgr_image, hsv_image, COLOR_BGR2HSV);
	Mat lower_red_hue_range;
	Mat upper_red_hue_range;
	inRange(hsv_image, Scalar(0, 100, 100), Scalar(10, 255, 255), lower_red_hue_range);
	inRange(hsv_image, Scalar(160, 100, 100), Scalar(179, 255, 255), upper_red_hue_range);
	Mat red_hue_image;
	addWeighted(lower_red_hue_range, 1.0, upper_red_hue_range, 1.0, 0.0, red_hue_image);
	GaussianBlur(red_hue_image, red_hue_image, cv::Size(9, 9), 2, 2);

	// Use of the Hough transform to detect circles in the combined threshold image
	std::vector<cv::Vec3f> circles;
	HoughCircles(red_hue_image, circles, CV_HOUGH_GRADIENT, 1, red_hue_image.rows / 8, 100, 20, 0, 0);

	// Looping over all detected circles and outling them on the original image
	if (circles.size() == 0) std::exit(-1);
	for (size_t current_circle = 0; current_circle < circles.size(); ++current_circle) {
		Point center(std::round(circles[current_circle][0]), std::round(circles[current_circle][1]));
		int radius = std::round(circles[current_circle][2]);
		circle(orig_image, center, radius, cv::Scalar(0, 255, 0), 5);
	}
	imwrite("4.jpg", red_hue_image);
	namedWindow("Combined threshold images", cv::WINDOW_AUTOSIZE);
	imshow("Combined threshold images", red_hue_image);
	src = imread("4.jpg", 1);
	cvtColor(src, src_gray, CV_BGR2GRAY);
	blur(src_gray, src_gray, Size(3, 3));
	char* source_window = "Source";
	namedWindow(source_window, CV_WINDOW_AUTOSIZE);
	imshow(source_window, src);
	createTrackbar(" Canny thresh:", "Source", &thresh, max_thresh, thresh_callback);
	thresh_callback(0, 0);
	waitKey(0);
	return(0);
}

void thresh_callback(int, void*)
{
	Mat canny_output;
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	Canny(src_gray, canny_output, thresh, thresh * 2, 3);
	findContours(canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
	vector<Moments> mu(contours.size());
	for (int i = 0; i < contours.size(); i++)
	{
		mu[i] = moments(contours[i], false);
	}
	vector<Point2f> mc(contours.size());
	for (int i = 0; i < contours.size(); i++)
	{
		mc[i] = Point2f(mu[i].m10 / mu[i].m00, mu[i].m01 / mu[i].m00);
		cout << mc[i];
	}
}