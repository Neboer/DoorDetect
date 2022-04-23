#pragma once
#include "determiner.h"

enum PointResult
{
	VALID, INVALID, FEED, FEEDEND
};


class PointDetector
{
private:
	std::vector<p4Grp> vertex_data;
	PointResult find_vertex_and_add(std::vector<XYCord>& points_list);
	std::array<PointResult, 4> get_cords_is_valid(std::vector<XYCord>& points_list);
	void calculate();
public:
	int max_sample_count;
	int width, height;
	p4Grp edge_points;// points for four covex
	p4Grp best_points;// empty first, after average the value is updated to average point cords.
	f4Grp allow_distances;// empty first, ...
	bool captureing;

	PointDetector(int count, cv::Size2f size);

	std::array<PointResult, 4> point_data(std::vector<XYCord> points_list);
	cv::Mat* debug_image = NULL;
};

