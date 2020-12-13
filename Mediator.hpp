#include "Builder.hpp"
#include "StopWatch.hpp"
#include <fstream>
#include <iostream>
#include <omp.h>

#ifndef  MEDIATOR_HPP
#define  MEDIATOR_HPP
//One FileOutput at a time throughout the p rogrma 
static std::ofstream filewriter = std::ofstream("Output.csv", std::ios::out);
struct Mediator
{
	//All the fields are public. I use a struct to easily modify the data fields of equation, It also not necessary to store Mediator as a class.Sine mediator in this case 
	//Will not be polymorphic 
	
	 StochasticEquation eq;	//EQ
	FiniteDifferenceMethod method; //Method 
	 RandomNumberGenerator rng; //Rng
	Pricers type; //Type of option 
	std::vector<double>resolution; //Resoluton operator 
	std::size_t NSIM;	//Number of file writer 
	int sample_num = 1;	//The current option data number 
	Mediator() = default;
	//Construct the parts from the builder methods 
	Mediator(const std::tuple<FiniteDifferenceMethod, RandomNumberGenerator, StochasticEquation, Pricers>& parts, std::size_t Nsim)
	{
		eq = std::get<2>(parts);
		method = std::get<0>(parts);
		rng = std::get<1>(parts);
		type = std::get<3>(parts);
		resolution = std::vector<double>(method->NT + 1);
		NSIM = Nsim;
		filewriter << "NSIM: " << NSIM << " NT:" << method->NT << "\n";
	}
	void start()
	{
		//start the watch 
		StopWatch watch;
		watch.StartStopWatch();
		//Parallelizd for loop with 2 threads. One thread for the outer loop and the collpase directive to specify that 2 threads are working in parallel in each loop
		
		resolution[0] = eq->InitialCondition();
		
		//Only parallaelize if its 2000000 ops , V0ld AND Vnew are instantiated constantly, The number of threads allocated will be 
		#pragma omp parallel  for if(NSIM*resolution.size()>= 1'000'000)
		for (int i = 1; i <= NSIM; ++i)
		{ // Calculate a path at each iteration. Make sure at most one thread is acess this  critical point 
			for (int n = 0; n < resolution.size()-1; n++)
			{
				//It is my job to reduce the requirement and necessity of inter loop dependcies. Intead of starting at 1 we start at zero and we will reduce the need for inter loop depeendcies
					resolution[n+1] = method->advance(resolution[n], method->RequestIncrement(n), method->k,rng ->generateRandomNumber());
			}
					//Store the result into the resolution array 
				//Process the path an calculate hay off at the end of each simulation 
		type->ProcessPath(resolution);
			
		}
		//Stop the stop watch
		watch.StopStopWatch(filewriter);
		//Print the process 
		type->PostProcess();
		}
			
	
		
	//Method to write it a file and increment the sample number 
	void WriteToFile()
	{

		
		filewriter << "Output # " << sample_num << " Price: " << type ->Price() << "\n";
		sample_num++;
	}
};


#endif // ! MEDIATOR