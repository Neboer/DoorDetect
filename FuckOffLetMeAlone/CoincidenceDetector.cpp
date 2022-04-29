#include "CoincidenceDetector.h"
#include <opencv2/cudaarithm.hpp>

CoincidenceDetector::CoincidenceDetector(int count, float threshold):image_core() {
	max_sample = count;
	current_sample = 0;
	this->threshold = threshold;
	capturing = true;
	core_nonzero = 0;
}

DetectResult CoincidenceDetector::data(cv::cuda::GpuMat& input_map) {
	if (capturing) {// first, if the map is not ready
		if (image_core.empty()) {
			image_core = input_map;
		}
		else
		{
			// reshape image core to fit
			cv::cuda::GpuMat cache;
			cv::cuda::bitwise_and(input_map, image_core, cache);
			image_core = cache; // reshape the core, get same part.
		}
		current_sample++;
		if (current_sample == max_sample) {
			// calculate the 
			core_nonzero = cv::cuda::countNonZero(image_core);
			capturing = false;
			return FEEDEND;
		}
		else
		{
			return FEED;
		}
	}
	else
	{
		// check similarity.
		cv::cuda::GpuMat coincidence;
		cv::cuda::bitwise_and(input_map, image_core, coincidence);
		int coincidence_threshould = core_nonzero * threshold;
		int coincidence_real = cv::cuda::countNonZero(coincidence);
		if (coincidence_real >= coincidence_threshould) return VALID;
		else return INVALID;
	}
}

void CoincidenceDetector::reset() {
	current_sample = 0;
	capturing = true;
}