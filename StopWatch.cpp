#include "StopWatch.hpp"
#include <fstream>
//set all the values to their initial values
StopWatch::StopWatch():isrunning(false),totaltime(0)
{
}
//call the start stop watch and make it start 
void StopWatch::StartStopWatch()
{
	//If its not running then run it 
	if (!isrunning)
	{
		isrunning = true;
		data = std::chrono::steady_clock::now();
		std::cout << "The clock is running " << std::endl;
	}
	//other wise there is nothign else to do
}

void StopWatch::StopStopWatch(std::ofstream&input)
{
	

	//If its running then get the total running time 
	if (isrunning)
	{
		
		isrunning = false;
		//Get the time 
		totaltime = GetTime();
		std::cout << "Total time:  " << totaltime << std::endl;
		input << "Total time: " << totaltime << "\n";
	}
	else
	{
		//If it is not not running it means the clock has been reset or already been stopped. So we just print the total time 
		std::cout << "Total time(Clock has already stopped): " << totaltime << std::endl;
		input << "Total time: " << totaltime << "\n";
	}
}

void StopWatch::Reset()
{
	//Steady clock has started from the moment of reset
	data = std::chrono::steady_clock::now();
	//Total time is resetted
	totaltime = 0;
	//If its not running dont do anything
	isrunning = false;
	
	
}

double StopWatch::GetTime() const
{
	//Get the time 
	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	std::chrono::duration<double>total_time = end - data;
	return total_time.count();
}
