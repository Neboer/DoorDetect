#pragma once
#include <chrono>
#include <string>
#include <ctime>

uint64_t get_current_time();
std::string get_current_local_time_string(); // public

struct Watch {
	uint16_t start_time = 0;
	uint16_t end_time = 0;
	bool working = false;
	int count = 0;

	void start();
	void end();
	void increase();
};