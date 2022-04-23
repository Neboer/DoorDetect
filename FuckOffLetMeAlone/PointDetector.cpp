#include "PointDetector.h"


PointDetector::PointDetector(int count, cv::Size2f size):vertex_data(), edge_points(), best_points(), allow_distances() {
	max_sample_count = count;
	width = size.width;
	height = size.height;
	edge_points = { XYCord {0,0}, XYCord {size.width, 0}, XYCord {0,size.height}, XYCord {size.width,size.height} };
	captureing = true; // start capture immediately.
}

void PointDetector::calculate() {
	float sumX[4] = { 0,0,0,0 }, sumY[4] = { 0,0,0,0 };

	for (int index = 0; index < 4; index++) {
		for (auto& vertex : vertex_data) {
			sumX[index] += vertex[index][0];
			sumY[index] += vertex[index][1];
		}
	}
	for (int i = 0; i < 4; i++) {
		best_points[i] = { sumX[i] / max_sample_count, sumY[i] / max_sample_count };
	}
	
	float max_distance[4] = { 0,0,0,0 };
	for (int index = 0; index < 4; index++) {
		for (p4Grp& vertex : vertex_data) {
			float dis = distance(vertex[index], best_points[index]);
			if (dis > max_distance[index]) {
				max_distance[index] = dis;
			}
		}
	}

	for (int i = 0; i < 4; i++) {
		allow_distances[i] = max_distance[i];
	}
}

PointResult PointDetector::find_vertex_and_add(std::vector<XYCord>& points_list) {
	pos_dis4 current_vertex = get_closest_points_distances(points_list, edge_points);
	// 找到顶点四点
	vertex_data.push_back(current_vertex.points);
	if (vertex_data.size() == max_sample_count) {
		// 已经找到了足够的点
		calculate();
		captureing = false;
		return FEEDEND;
	}
	else
	{
		return FEED;
	}
}

// 已经准备完成了，检查点是否合法。
std::array<PointResult, 4> PointDetector::get_cords_is_valid(std::vector<XYCord>& points_list) {
	pos_dis4 current_points_dis = get_closest_points_distances(points_list, best_points);
	if (debug_image) {
		for (int i = 0; i < 4; i++) {
			auto& point = current_points_dis.points[i];
			circle(*debug_image, cv::Point(point), 1, cv::Scalar(255, 255, 255));
		}
	}
	std::array<PointResult, 4> result = { INVALID, INVALID, INVALID, INVALID };
	for (int i = 0; i < 4; i++) {
		if (current_points_dis.distances[i] <= allow_distances[i]) {
			result[i] = VALID;
		}
	}
	return result;
}

std::array<PointResult, 4> PointDetector::point_data(std::vector<XYCord> points_list) {
	if (captureing) {
		return { find_vertex_and_add(points_list) };
	}
	else
	{
		if (debug_image) {
			for (int i = 0; i < 4; i++) {
				circle(*debug_image, cv::Point(best_points[i]), sqrt(allow_distances[i]), cv::Scalar(255, 255, 255));
			}
		}
		return get_cords_is_valid(points_list);
	}
}
