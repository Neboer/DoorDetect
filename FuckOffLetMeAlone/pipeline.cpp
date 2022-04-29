#include "pipeline.h"

cv::cuda::GpuMat canny_pipeline(cv::VideoCapture &camera, pipeline_setting &setting) {
	if (!setting.sobel_filter) {
		setting.sobel_filter = cv::cuda::createSobelFilter(CV_8UC3, CV_8UC1, 1, 0);
	}

	cv::Mat buffer1, buffer2;
	cv::cuda::GpuMat g_buffer1, g_buffer2;
	camera >> buffer1;
	buffer2 = buffer1(setting.area);
	g_buffer1.upload(buffer2);
	//cv::cuda::cvtColor(g_buffer1, g_buffer2, cv::COLOR_BGR2GRAY);
	//cv::cuda::fastNlMeansDenoising(g_buffer2, g_buffer1, setting.denoise_strenth, setting.denoise_window);
	setting.sobel_filter->apply(g_buffer1, g_buffer2);
	cv::cuda::cvtColor(g_buffer2, g_buffer1, cv::COLOR_BGR2GRAY);
	return g_buffer1;
}