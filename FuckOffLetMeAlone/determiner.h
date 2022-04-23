#pragma once;
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/core/matx.hpp>

typedef cv::Vec2f XYCord;

typedef std::array<XYCord, 4> p4Grp;
typedef std::array<float, 4> f4Grp;
typedef std::array<int, 4> i4Grp;
struct pos_dis4 {
	p4Grp points; // 表示存储了4个点的坐标
	f4Grp distances;
};

pos_dis4 get_closest_points_distances(std::vector<XYCord> points, p4Grp target_points);
int distance(XYCord p1, XYCord p2);

template <class T>
std::vector<XYCord> convert(std::vector<cv::Vec<T, 2>> src);