#include <stdio.h>
#include <opencv2\core\core.hpp>
#include <opencv2\core\cuda.hpp>
#include <opencv2\imgproc.hpp>
#include <opencv2\opencv.hpp>
#include <opencv2/photo/cuda.hpp>
#include <opencv2/cudaimgproc.hpp>
#include "determiner.h"
#include "PointDetector.h"

extern cv::Rect get_regon_from_click(cv::VideoCapture& camera);

using namespace cv;

int main(int argc, char** argv) {
	cv::VideoCapture camera(0);
	if (!camera.isOpened()) {
		std::cerr << "ERROR: Could not open camera" << std::endl;
		return 1;
	}

	cv::Rect crop_region = get_regon_from_click(camera);
	PointDetector detector(100, crop_region.size());
	cv::namedWindow("points");
	cv::namedWindow("Webcam");
	cv::Mat frame;
	// prepare cuda utils
	auto canny_edg = cv::cuda::createCannyEdgeDetector(1, 100.0, 3, false);
	// auto hough_lne = cv::cuda::createHoughSegmentDetector(1.0f, (int)(CV_PI / 180.0f), 21, 20);
	auto corrner_detector = cv::cuda::createGoodFeaturesToTrackDetector(CV_8UC1, 8, 0.2, 15.0);

	bool need_collect_data = true;
	
	while (1) {
		cv::Mat debug_frame = cv::Mat::zeros(crop_region.size(), CV_8UC3);
		detector.debug_image = &debug_frame;

		camera >> frame;
		cv::Mat croped_frame = frame(crop_region);

		cv::cuda::GpuMat src(croped_frame), grey_frame, denoised_grey_frame, canny_result, corner_mat;
		cv::cuda::cvtColor(src, grey_frame, cv::COLOR_BGR2GRAY);
		cv::cuda::fastNlMeansDenoising(grey_frame, denoised_grey_frame, 5.0);
		canny_edg->detect(denoised_grey_frame, canny_result);
		corrner_detector->detect(canny_result, corner_mat);
		std::vector<Vec2f> corner_f;

		
		if (!corner_mat.empty() && corner_mat.size().width >= 4) {
			corner_mat.download(corner_f);
			
			auto point_data_result = detector.point_data(corner_f);
			if (point_data_result[0] == FEEDEND) {
				// start timer here.
				std::cout << "feed end" << std::endl;

			}
			else if (point_data_result[0] != FEED) {
				int invalid_count = 0;
				for (int status : point_data_result) {
					if (status == INVALID) invalid_count++;
				}
				if (invalid_count > 1) {
					std::cerr << "open!!!";
				}
			}
		}
		else {
			std::cerr << "lack of data" << std::endl;
		}

		cv::imshow("points", debug_frame);
		cv::imshow("Webcam", croped_frame);
		if (cv::waitKey(1) >= 0)
			break;
	}
	return 0;
}