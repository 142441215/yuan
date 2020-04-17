#include <opencv.hpp>
#include <math.h>

using namespace cv;
using namespace std;

int main()
{
	Mat srcMat = imread("c://project//rim.png", 0), dspMat = imread("c://project//rim.png");
	Mat binaryMat;
	//Binarization and  Connected Component -getting
	Mat inversedMat = 255 - srcMat;
	threshold(inversedMat, binaryMat, 150, 255, THRESH_OTSU);

	Mat element = getStructuringElement(MORPH_RECT, Size(13, 13));
	morphologyEx(binaryMat, binaryMat, MORPH_OPEN, element);

	vector<vector<Point>> contours;
	findContours(binaryMat, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE, Point());
	cout << "num=" << contours.size() << endl;

	float rate[100];

	for (int i = 0; i < contours.size(); i++)
	{
		RotatedRect rect = minAreaRect(contours[i]);
		Point2f P[4];
		rect.points(P);
		// rate of rect 
		float Y = sqrt((P[0].y - P[1].y) * (P[0].y - P[1].y) + (P[0].x - P[1].x) * (P[0].x - P[1].x));
		float X = sqrt((P[1].y - P[2].y) * (P[1].y - P[2].y) + (P[1].x - P[2].x) * (P[1].x - P[2].x));
		rate[i] = X / Y;
		cout << "num=" << i << "rate of rect =" << rate[i] << endl;
		if ((rate[i] >= 0.95) and (rate[i] <= 1.1))
		{
			for (int j = 0; j <= 3; j++)
			{
				line(dspMat, P[j], P[(j + 1) % 4], Scalar(0,0,255), 1);
			}
		}
	}
	imshow("dspMat", dspMat);
	waitKey(0);
	return 0;
}