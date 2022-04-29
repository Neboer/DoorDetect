#include "args.h"
#include <corecrt_wstring.h>
#include <corecrt_wstdio.h>

arguments parse_args(int argc, wchar_t* argv[]) {
	arguments result{};

	for (int i = 0; i < argc; i++) {
		if (wcscmp(argv[i], L"--debug") == 0) result.debug_mode = true;
		if (wcscmp(argv[i], L"--range") == 0) {
			for (int p = 0; p < 4; p++) {
				swscanf_s(argv[i + p + 1], L"%d", &(result.input_rect[p]));// 累了，如果出错就直接panic吧
			}
			result.input_rect_is_set = true;
			i += 4;
			continue;
		}
		if (wcscmp(argv[i], L"--good-point-rate") == 0) {
			swscanf_s(argv[i + 1], L"%f", &(result.good_point_rate));
			i += 1;
			continue;
		}
		if (wcscmp(argv[i], L"--frame") == 0) {
			swscanf_s(argv[i + 1], L"%d", &(result.frame_threshold));
			i += 1;
			continue;
		}
		if (wcscmp(argv[i], L"--sample") == 0) {
			swscanf_s(argv[i + 1], L"%d", &(result.sample));
			i += 1;
			continue;
		}
		if (wcscmp(argv[i], L"--window") == 0) {
			wcscpy_s(result.target_window_name, argv[i + 1]);
			i += 1;
			continue;
		}
	}
	return result;
}