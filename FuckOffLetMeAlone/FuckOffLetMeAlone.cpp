#include <stdio.h>
#include <opencv2\core\core.hpp>
#include <opencv2\core\cuda.hpp>
#include <opencv2\imgproc.hpp>
#include <opencv2\opencv.hpp>
#include <opencv2/photo/cuda.hpp>
#include <opencv2/cudaimgproc.hpp>
#include "CoincidenceDetector.h"
#include "stopwatch.h"
#include "pipeline.h"
#include "args.h"
#include <format>
#include <iostream>
#include <windows.h> 

extern cv::Rect get_regon_from_click(cv::VideoCapture& camera);
extern void ShowDesktop();
using namespace cv;

uint64_t timeSinceEpochMillisec() {
	using namespace std::chrono;
	return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

int wmain(int argc, wchar_t* argv[], wchar_t* envp[]) {
	// parse arguments
	arguments Arg = parse_args(argc, argv);
	// get hwnd
	//HWND hide_target = FindWindow(NULL, Arg.target_window_name);
	//if (hide_target == NULL) {
	//	std::wcerr << L"no such process!" << Arg.target_window_name << std::endl;
	//	return -1;
	//}
	//else
	//{
	//	std::cout << hide_target << std::endl;
	//}


	cv::VideoCapture camera(0);
	if (!camera.isOpened()) {
		std::wcerr << L"ERROR: Could not open camera" << std::endl;
		return 1;
	}

	cv::Rect crop_region;
	if (Arg.input_rect_is_set) {
		crop_region = cv::Rect(Arg.input_rect[0], Arg.input_rect[1], Arg.input_rect[2], Arg.input_rect[3]);
		for (int c = 0; c < 100; c++) { // burn camera
			cv::Mat test_frame;
			camera >> test_frame;
		}
	}
	else
	{
		crop_region = get_regon_from_click(camera);
	}
	std::cout << crop_region.x << " " << crop_region.y << " " << crop_region.width << " " << crop_region.height << std::endl;
	pipeline_setting setting{
		crop_region,
		1,100,
		30, 10
	};

	CoincidenceDetector detector(Arg.sample, Arg.good_point_rate);
	if (Arg.debug_mode) {
		cv::namedWindow("points");
	}
	int invalid_frame_count = 0;

	Watch stopwatch;
	stopwatch.start();
	while (1) {
		stopwatch.increase();

		cv::cuda::GpuMat outline = canny_pipeline(camera, setting);
		if (Arg.debug_mode) {
			cv::imshow("points", cv::Mat(outline));
			waitKey(1);
		}
		DetectResult analyze_result = detector.data(outline);
		if (analyze_result == FEEDEND) {
			stopwatch.end();
			float fps = (float)stopwatch.count / ((float)(stopwatch.end_time - stopwatch.start_time) / 1000.0);
			printf_s("feed end with fps: %.2f, nonzero: %d\n", fps, detector.core_nonzero);
		}
		else if (analyze_result == INVALID) {
			invalid_frame_count++;
			if (invalid_frame_count > Arg.frame_threshold) {
				ShowDesktop();
				// warning! the door is open!
				//ShowWindow(hide_target, SW_MINIMIZE);
				//ShowWindow(hide_target, SW_SHOWMAXIMIZED);
				std::cout << get_current_local_time_string() << std::endl;
				getchar();// 在切换桌面之后，程序不会立即退出，他会留在原地待命。
				invalid_frame_count = 0;
				detector.reset();
				stopwatch.start();
			}
		}
		else if (analyze_result == VALID) {
			invalid_frame_count = 0;
		}
	}
}