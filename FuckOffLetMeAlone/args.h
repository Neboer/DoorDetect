#pragma once

struct arguments {
	bool debug_mode = false;
	bool input_rect_is_set = false;
	float good_point_rate = 0.5;
	int input_rect[4] = { 0,0,0,0 }; // x, y, width, height
	int frame_threshold = 1;
	int sample = 100;
	wchar_t target_window_name[100];
};

arguments parse_args(int argc, wchar_t* argv[]);