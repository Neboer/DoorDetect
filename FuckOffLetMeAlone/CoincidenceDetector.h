#pragma once
#include <opencv2/opencv.hpp>

enum DetectResult
{
	VALID, INVALID, FEED, FEEDEND
};

class CoincidenceDetector {
private:
	int max_sample, current_sample;
	bool capturing;
	float threshold;
public:
	cv::cuda::GpuMat image_core; // the same point of image.
	int core_nonzero;
	CoincidenceDetector(int count, float threshold);
	DetectResult data(cv::cuda::GpuMat &input_map);
	void reset();
};
