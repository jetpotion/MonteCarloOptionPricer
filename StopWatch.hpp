

#ifndef STOPWATCH_HPP 
#define STOPWATCH_HPP
#include <chrono>
#include <exception>
#include <iostream>
class StopWatch {
public:
	  explicit StopWatch();
	  void StartStopWatch();
	  void StopStopWatch(std::ofstream& os); 
	  void Reset();
	  double GetTime() const;
private: 
	std::chrono::steady_clock::time_point data;
	bool isrunning;
	double totaltime;
	//These are going to be deleted
	StopWatch(const StopWatch&) = delete;
	StopWatch& operator=(const StopWatch&) = delete;
};
#endif // !STOPWATCH_HPP 
