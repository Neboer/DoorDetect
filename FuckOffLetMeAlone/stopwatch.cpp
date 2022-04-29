// a stopwatch which can count framerate.
#include "stopwatch.h"
#include <winsock.h>
typedef std::chrono::system_clock Clock;

uint64_t get_current_time() {
	using namespace std::chrono;
	return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

int gettimeofday(struct timeval* tp, struct timezone* tzp)
{
	// Note: some broken versions only have 8 trailing zero's, the correct epoch has 9 trailing zero's
	// This magic number is the number of 100 nanosecond intervals since January 1, 1601 (UTC)
	// until 00:00:00 January 1, 1970 
	static const uint64_t EPOCH = ((uint64_t)116444736000000000ULL);

	SYSTEMTIME  system_time;
	FILETIME    file_time;
	uint64_t    time;

	GetSystemTime(&system_time);
	SystemTimeToFileTime(&system_time, &file_time);
	time = ((uint64_t)file_time.dwLowDateTime);
	time += ((uint64_t)file_time.dwHighDateTime) << 32;

	tp->tv_sec = (long)((time - EPOCH) / 10000000L);
	tp->tv_usec = (long)(system_time.wMilliseconds * 1000);
	return 0;
}


std::string get_current_local_time_string() {
	timeval tv;
	gettimeofday(&tv, NULL);
	time_t currentTime;
	struct tm localTime;

	time(&currentTime);                   // Get the current time
	localtime_s(&(localTime), &currentTime);  // Convert the current time to the local time

	int Hour = localTime.tm_hour;
	int Min = localTime.tm_min;
	int Sec = localTime.tm_sec;


	char result_str[13];
	sprintf_s(result_str, "%02d:%02d:%02d.%03ld", Hour, Min, Sec, tv.tv_usec/1000);
	return { result_str };
}

void Watch::start() {
	start_time = get_current_time();
	working = true;
}

void Watch::increase() {
	if (working) {
		count++;
	}
}

void Watch::end() {
	end_time = get_current_time();
	working = false;
}