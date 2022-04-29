#pragma once
#include <opencv2/opencv.hpp>
#include <opencv2/cudaimgproc.hpp>
#include <opencv2/photo/cuda.hpp>
#include <opencv2/cudafilters.hpp>

struct pipeline_setting {
	cv::Rect area;
	double canny_low; // compulsory
	double canny_high; // compulsory
	float denoise_strenth; // compulsory
	int denoise_window  = 21;// ÆæÊý£¡default 21
	int sliding_buffer_max_len = 10;

	// cv::Ptr<cv::cuda::CannyEdgeDetector> CannyDetector = NULL;
	cv::Ptr<cv::cuda::Filter> sobel_filter = NULL;
};

cv::cuda::GpuMat canny_pipeline(cv::VideoCapture& camera, pipeline_setting& setting);