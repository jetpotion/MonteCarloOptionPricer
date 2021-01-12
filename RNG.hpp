#include <random>
#include <omp.h>
#ifndef RNG_HPP
#define RNG_HPP
//RNG  generator to create GAUSSIAN distributed numbers with mean zero sd = 1

namespace MonteCarloOptionApplication
{
	namespace IRng
	{
		//The following classes generate random numbers from a number distribution
		class RNG
		{
		
			
		public:
			//RNG base class 
			static thread_local std::mt19937_64 engine;
			
			virtual ~RNG() = default;
			//Generate random number 
			virtual double generateRandomNumber() = 0;
		};
		//The polarMasglia distriubtion 
		class PolarMasglia :public RNG
		{
		private:
			//Default random engine 
			
			//Distribution 
			std::uniform_real_distribution<double> distribution;

		public:
			//Default constructor
			PolarMasglia();
			//Virtual distructor/Copy constructor 
			virtual ~PolarMasglia() override = default;
			PolarMasglia(const  PolarMasglia& source);
			PolarMasglia& operator=(const PolarMasglia& source);
			//Generate a randomnumber from RNG
			virtual double generateRandomNumber()  override;
		};
		class MyMersenneTwister :public RNG
		{
		private:
			
			//Distribution
			std::normal_distribution<double>gaussian;
		public:
			//Standard constructors,destructors,assignment operators
			MyMersenneTwister();
			virtual ~MyMersenneTwister() override = default;
			MyMersenneTwister(const  MyMersenneTwister& source);
			MyMersenneTwister& operator=(const MyMersenneTwister& source);
			//Overriden  virtual method 
			virtual double generateRandomNumber()  override;
		};
		//Generate random numbers from box mueller 
		class BoxMuller : public RNG
		{
		
			std::uniform_real_distribution<double> distribution; //The uniform distribution 

		public:

			//Standard constructors,destructors,assignment operators
			BoxMuller();
			virtual ~BoxMuller() override = default;
			BoxMuller(const  BoxMuller& source);
			BoxMuller& operator=(const BoxMuller& source);
			//Overriden generateRandomNumber 
			virtual double generateRandomNumber()  override;
		};
	}
}

#endif //