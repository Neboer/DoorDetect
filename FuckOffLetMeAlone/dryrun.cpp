#include <opencv2/opencv.hpp>
#include "stopwatch.h"

void dry_run(cv::VideoCapture &camera) {
	Watch watch {};
	watch.start();
	std::cout << "start!\n";
	for (int i = 0; i < 500; i++) {
		watch.increase();
		cv::Mat temp;
		camera >> temp;
	}
	watch.end();
	std::cout << watch.count << "\n";
	std::cout << watch.end_time - watch.start_time << "\n";
	std::cout << (float) watch.count / (float)(watch.end_time - watch.start_time);
}