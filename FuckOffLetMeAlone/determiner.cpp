#include "determiner.h"

int distance(XYCord p1, XYCord p2) {
	return (p2[1] - p1[1]) * (p2[1] - p1[1]) + (p2[0] - p1[0]) * (p2[0] - p1[0]);
}


// �ڸ����ĵ㼯�У������ҵ�����target��ÿһ���������һ���㣬ͬʱ��������Ŀ��ľ��롣
// ��������ȿ������ڡ����Ľǡ��ϣ��ֿ������ڡ���֤ͼ���ϡ�
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