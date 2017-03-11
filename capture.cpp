/*
*
* @ C++ PROGRAM TO SHOW CAPTURING OF AN IMAGE
* @ AUTHOR BRAHMOS TEAM
*/

#include<iostream>
#include <stdlib.h>
#include <stdio.h>
//LIBRARIES OF OPEN CV
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace cv;

using namespace std;

int main(int argc, char* argv[])
{
	cout << "\n";
	cout << "\t\t\t\t TEAM BRAHMOS" << endl;
	cout << "\n";
	cout << "\n";
	cout << "\t*************************************************************" << endl;
	cout << "\t*                                                           *" << endl;
	cout << "\t*  Welcome to image capturing and edge detection program    *" << endl;
	cout << "\t*  We will first capture the image.                         *" << endl;
	cout << "\t*  From this we are going to detect the edge and            *" << endl;
	cout << "\t*  give the real time length.                               *" << endl;
	cout << "\t*                                                           *" << endl;
	cout << "\t*************************************************************" << endl;
	cout << "\n";
	cout << "\n";
	cout << "enter the command" << endl;
	int m;
	cin >> m;
	if (m != 1)
		return 0;
	//0 is the id of video device.0 if you have only one camera.
	VideoCapture stream1(0);

	if (!stream1.isOpened())
	{
		//check if video device has been initialised
		cout << "cannot open camera";
	}

	//unconditional loop
	while (true)
	{
		Mat cameraFrame;
		stream1.read(cameraFrame);
		imshow("cam", cameraFrame);
		if (waitKey(30) >= 0)
			break;
	}

	// open the video camera no. 0
	VideoCapture cap(0);

	// if not success, exit program
	if (!cap.isOpened())
	{
		cout << "Cannot open the video cam" << endl;
		return -1;
	}

	//get the width of frames of the video
	double dWidth = cap.get(CV_CAP_PROP_FRAME_WIDTH);

	//get the height of frames of the video
	double dHeight = cap.get(CV_CAP_PROP_FRAME_HEIGHT);

	cout << "Frame size : " << endl;
	cout << dWidth << " x " << dHeight << endl;

	//create a window called "MyVideo"
	namedWindow("MyVideo", CV_WINDOW_AUTOSIZE);

	Mat frame;

	// read a new frame from video
	bool bSuccess = cap.read(frame);

	//if not success, break loop
	if (!bSuccess)
	{
		cout << "Cannot read a frame from video stream" << endl;

	}
	imwrite("C:/Dhruv/Manu Uncle Assignments/opeeencv/opeeencv/4.jpg", frame);

	//show the frame in "MyVideo" window
	imshow("MyVideo", frame);

	//wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
	if (waitKey(30) == 27)
	{
		cout << "esc key is pressed by user" << endl;

	}

	system("pause");

	return 0;
}

