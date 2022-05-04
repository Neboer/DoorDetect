#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

struct cbinfo
{
	int base_pos[2] = { 0,0 };// x y
	int curr_pos[2] = { 0,0 };
	bool is_mouse_down = false;
	bool is_drawable = false;
};

void mouse_cb(int event, int x, int y, int flags, void* userdata_p) {
	cbinfo* userdata = (cbinfo*)userdata_p;
	if (event == cv::MouseEventTypes::EVENT_LBUTTONDOWN) {
		// 左键按下，初始化选区
		userdata->is_drawable = false;
		userdata->base_pos[0] = x;
		userdata->base_pos[1] = y;
		userdata->curr_pos[0] = x;
		userdata->curr_pos[1] = y;
		userdata->is_mouse_down = true;
	}
	else if (event == cv::MouseEventTypes::EVENT_MOUSEMOVE) {
		if (userdata->is_mouse_down) {
			userdata->curr_pos[0] = x;
			userdata->curr_pos[1] = y;
			userdata->is_drawable = true;
		}
	}
	else if (event == cv::MouseEventTypes::EVENT_LBUTTONUP) {
		// 左键抬起，停止选择。
		userdata->is_mouse_down = false;
	}
}

cv::Rect get_regon_from_click(cv::VideoCapture& camera) {
	cbinfo info;
	cv::namedWindow("rect");
	cv::setMouseCallback("rect", mouse_cb, (void*)&info);
	while (true)
	{
		cv::Mat frame;
		camera >> frame;
		if (info.is_drawable) {
			cv::rectangle(frame, { info.base_pos[0], info.base_pos[1] }, { info.curr_pos[0], info.curr_pos[1] }, { 100,100,100 });
		}
		cv::imshow("rect", frame);
		if (cv::waitKey(1) > 0) {
			break;
		}
	}
	cv::destroyWindow("rect");
	return cv::Rect(info.base_pos[0], info.base_pos[1], info.curr_pos[0] - info.base_pos[0], info.curr_pos[1] - info.base_pos[1]);
}
