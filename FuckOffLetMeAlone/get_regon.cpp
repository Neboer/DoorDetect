#include <opencv2\opencv.hpp>
#include <opencv2/highgui.hpp>

void mouse_cb (int event, int x, int y, int flags, void* userdata) {
	int* data =(int*) userdata;// data: x1, x2, y1, y2
	if (event == cv::MouseEventTypes::EVENT_LBUTTONDOWN) {
			data[0] = x;
			data[2] = y;
	}
	else if (event == cv::MouseEventTypes::EVENT_RBUTTONDOWN) {
			data[1] = x;
			data[3] = y;
	}
}

cv::Rect get_regon_from_click(cv::VideoCapture& camera) {
	int regon[4] = {0,0,0,0};
	cv::namedWindow("rect");
	cv::setMouseCallback("rect", mouse_cb, (void*) regon);
	while (true)
	{
		cv::Mat frame;
		camera >> frame;
		cv::imshow("rect", frame);
		if (cv::waitKey(1) > 0) {
			break;
		}
	}
	cv::destroyWindow("rect");
	return cv::Rect(regon[0], regon[2], regon[1]-regon[0], regon[3]-regon[2]);
}

