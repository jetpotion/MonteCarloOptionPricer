#include "RNG.hpp"
#include <cmath>
#include <numbers>
//Generate the engine with a random device and with a distribution with mean 0 and sd = 1
//Make sure that MT19937_64 engine is thread safe by declaring it thread local 
thread_local std::mt19937_64 WilliamZhang::IRng::RNG::engine(std::random_device{}());

WilliamZhang::IRng::MyMersenneTwister::MyMersenneTwister() : gaussian(0.0f, 1.0f)
{
}
//Copy constructor
WilliamZhang::IRng::MyMersenneTwister::MyMersenneTwister(const MyMersenneTwister& source) : gaussian(source.gaussian)
{
}
//Assignment operator
WilliamZhang::IRng::MyMersenneTwister& WilliamZhang::IRng::MyMersenneTwister::operator=(const MyMersenneTwister& source)
{
	if (this == &source)
	{
		RNG::operator=(source);
		return *this;
	}
	engine = source.engine;
	gaussian = source.gaussian;
	RNG::operator=(source);
	return *this;
	// TODO: insert return statement here
}
//Generate the mersenee twister rnadom number generation from the from the guassian
double WilliamZhang::IRng::MyMersenneTwister::generateRandomNumber()
{
	return gaussian(engine);
}
//The following are constructgors/copy and assignment operator

WilliamZhang::IRng::PolarMasglia::PolarMasglia() : distribution(0.0, 1.0)
{
}

WilliamZhang::IRng::PolarMasglia::PolarMasglia(const PolarMasglia& source) : RNG(source), distribution(source.distribution)
{
}

WilliamZhang::IRng::PolarMasglia& WilliamZhang::IRng::PolarMasglia::operator=(const PolarMasglia& source)
{
	if (this == &source)
		return *this;
	distribution = source.distribution;
	engine = source.engine;
	RNG::operator=(source);
	return *this;
}
//The method to generate the random numbers 
double WilliamZhang::IRng::PolarMasglia::generateRandomNumber()
{
	double u, v, S;

	do
	{   //First select a number 0<= x <= 1.0 for both U,V
		u = 2.0 * distribution(engine) - 1.0;
		v = 2.0 * distribution(engine) - 1.0;
		//Checks if its within the circle 
		S = u * u + v * v;
	} while (S > 1.0 || S <= 0.0);
	//Since mean is zero and standard deviation is one the following generates a random number in polar form with normal distribution
	//fac = mean  + std_dev * std::sqrt(-2.0 * std::log(S)/S):
	double fac = std::sqrt(-2.0 * std::log(S) / S);
	return u * fac;
}
//Standard constructors destruction 
WilliamZhang::IRng::BoxMuller::BoxMuller() : distribution(0.0, 1.0)
{
}

WilliamZhang::IRng::BoxMuller::BoxMuller(const BoxMuller& source) : RNG(source), distribution(source.distribution)
{
}

WilliamZhang::IRng::BoxMuller& WilliamZhang::IRng::BoxMuller::operator=(const BoxMuller& source)
{
	if (this == &source)
		return *this;
	distribution = source.distribution;
	engine = source.engine;
	RNG::operator=(source);
	return *this;
}

double WilliamZhang::IRng::BoxMuller::generateRandomNumber()
{
	//Since sigma = 1 and mu = 0. The addtional terms dont apply
	double u1;
	double u2;
	do
	{
		//Choose random bumbers from zero to one that are uniform distributed
		u1 = distribution(engine);
		u2 = distribution(engine);

		//Perform operations while its smaller than the epsilon.If its not then perform the transformatio
	} while (u1 <= std::numeric_limits<double>::epsilon());
	//Return the real part of box mueller 
	return std::sqrt(-2.0 * std::log(u1)) * std::cos(2 * std::numbers::pi * u2);
}