/*
*
* @ C++ PROGRAM TO SHOW CAPTURING OF AN IMAGE
* @ AUTHOR BRAHMOS TEAM
*/
#include<iostream>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace cv;

using namespace std;

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
	/// Reduce noise with a kernel 3x3
	blur(src_gray, detected_edges, Size(3, 3));

	/// Canny detector
	Canny(detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size);

	/// Using Canny's output as a mask, we display our result
	dst = Scalar::all(0);

	src.copyTo(dst, detected_edges);
	imshow(window_name, dst);

}
int main(int, char** argv)

{
	char i[20];
	int j;
	/// Load an image
	cout << "Enter the image name and file value";
	cin >> i;
	cout << "Enter the value of the image corresponding to the image from the list below \n 1.Cap \n 2.Igloo \n 3.a complex picture";
	cin >> j;
	if (j == 1)
		src = imread("4.JPG", CV_LOAD_IMAGE_UNCHANGED);
	else if (j == 2)
		src = imread("2.JPG", CV_LOAD_IMAGE_UNCHANGED);
	else
		src = imread("3.JPG", CV_LOAD_IMAGE_UNCHANGED);
	/// Create a matrix of the same type and size as src (for dst)
	dst.create(src.size(), src.type());

	/// Convert the image to grayscale
	cvtColor(src, src_gray, COLOR_BGR2GRAY);

	/// Create a window
	namedWindow(window_name, WINDOW_AUTOSIZE);

	/// Create a Trackbar for user to enter threshold
	createTrackbar("Min Threshold:", window_name, &lowThreshold, max_lowThreshold, CannyThreshold);

	/// Show the image
	CannyThreshold(0, 0);
	int x, y;
	Mat a;
	Mat b;
	Mat M(1, 1, CV_8UC3, Scalar(0, 0, 255));

	//Copying image from dst to (a)
	dst.copyTo(a);

	//Vector Datatype to check  for colour in 2d array (image)
	Vec3b vec;

	int count = 0;
	vec = Vec3b(0, 0, 0);
	int *x1, *y1, s = 0;
	int q = 100; int r = 100;
	int ya, yb;
	cout << "Enter centre of mass x1 of 1st circle" << endl;
	cin >> ya;
	cout << "Enter centre of mass x1 of 2nd circle" << endl;
	cin >> yb;

	for (x = ya; x < 381; x++)
	for (y = 1; y < a.rows; y++)
	{

		if (vec == a.at<Vec3b>(y, x))
		{
			int d1;
			d1 =   (q - x)*(q - x) + (r - y)*(r - y);
			d1 = sqrt(d1);
			s = s + d1;
			
			cout <<"Detected x cor=ordinate"<< x << "Detected y cordinate  " << y << endl;
			cout << count << endl;
			q = x;
			r = y;
			count++;

			break;
		}

	}
	cout << "The pixelated lenght is" << s <<endl;
	cout << "Ente the real time lenght" << endl;
	int xa;
	cin >> xa;
	s = s*xa;
	s = s / 640;
	cout << "The Real lenght is" << s;



	/// Wait until user exit program by pressing a key
	waitKey(0);

	cout << "Thank you";
	system("pause");
	return 0;
}