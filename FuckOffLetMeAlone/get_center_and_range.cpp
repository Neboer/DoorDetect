// get the center of point with range.
#include "get_center_and_range.h"

pos_dis4 get_info_from_points(std::vector<p4Grp> sample_points) {
	p4Grp result_points;
	f4Grp result_distances;
	for (int i = 0; i < 4; i++) {
		std::vector<XYCord> points;
		for (auto& point : sample_points) {
			points.push_back(point[i]);
		}
		cv::Vec2d center_d;
		FindCG(points, center_d);
		int min_dis = INFINITY;
		for (auto& point : points) {
			int dis = distance(point, center_d);
			if (dis < min_dis) {
				min_dis = dis;
			}
		}
		result_points[i] = center_d;
		result_distances[i] = min_dis;
	}
	return {
		result_points,
		result_distances
	};
}

