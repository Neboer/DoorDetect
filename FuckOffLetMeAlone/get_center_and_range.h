#pragma once
#include <opencv2/opencv.hpp>
#include "determiner.h"

// 输入一些四点集合。返回其中每个点的几何中心和最大偏离值。
pos_dis4 get_info_from_points(std::vector<p4Grp> sample_points);