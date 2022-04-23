#include "determiner.h"

int distance(XYCord p1, XYCord p2) {
	return (p2[1] - p1[1]) * (p2[1] - p1[1]) + (p2[0] - p1[0]) * (p2[0] - p1[0]);
}


// 在给定的点集中，依次找到距离target中每一个点最近的一个点，同时返回它与目标的距离。
// 这个方法既可以用在“找四角”上，又可以用在“验证图像”上。
pos_dis4 get_closest_points_distances(std::vector<XYCord> points, p4Grp target_points) {
	// lu ru ld rd
	// XYCord edge_points[4] = {XYCord {0,0}, XYCord {size.width, 0}, XYCord {0,size.height}, XYCord {size.width,size.height}};

	f4Grp minimum_distance = {INFINITY, INFINITY ,INFINITY ,INFINITY };

	p4Grp best_points = { points[0] };
	for (auto& point : points) {
		for (int index = 0; index < 4; index++) {
			int dis = distance(point, target_points[index]);
			if (dis < minimum_distance[index]) {
				minimum_distance[index] = dis;
				best_points[index] = point;
			}
		}
	}

	return {
		best_points,
		minimum_distance
	};
}

template <class T>
std::vector<XYCord> convert(std::vector<cv::Vec<T, 2>> src) {
	std::vector<XYCord> result(src.size(), {});
	for (int i = 0; i < src.size(); i++) {
		result[i] = src[i];
	}
	return result;
}