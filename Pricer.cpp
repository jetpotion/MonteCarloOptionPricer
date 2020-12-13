#include "Pricer.hpp"
#include <iostream>
#include <numeric>
#include <omp.h>
//Constructor
WilliamZhang::IPricer::Pricer::Pricer(const std::function<double(double)>& payoff, const std::function<double()> discounter) : pay_off(payoff), m_discounter(discounter)
{
}
//Copy constructor
WilliamZhang::IPricer::Pricer::Pricer(const Pricer& source) : pay_off(source.pay_off), m_discounter(source.m_discounter)
{
}
//Assignment operaotr 
WilliamZhang::IPricer::Pricer& WilliamZhang::IPricer::Pricer::operator=(const Pricer& source)
{
	if (this == &source)
		return *this;
	pay_off = source.pay_off;
	m_discounter = source.m_discounter;
	return *this;
	// TODO: insert return statement here
}
//European pricer 
WilliamZhang::IPricer::EuropeanPricer::EuropeanPricer(const std::function<double(double)>& payoff, const std::function<double()> discounter) : Pricer(payoff, discounter), NSIM(0), sum(0.0), price(0.0)
{
}

WilliamZhang::IPricer::EuropeanPricer::EuropeanPricer(const EuropeanPricer& source) : Pricer(source), NSIM(source.NSIM), sum(source.sum), price(source.sum)
{
}
//Assignment operator 
WilliamZhang::IPricer::EuropeanPricer& WilliamZhang::IPricer::EuropeanPricer::operator=(const EuropeanPricer& source)
{
	if (this == &source)
	{
		Pricer::operator=(source);
		return *this;
	}
	NSIM = source.NSIM;
	sum = source.sum;
	price = source.price;
	Pricer::operator=(source);
	return *this;
	// TODO: insert return statement here
}
//
void WilliamZhang::IPricer::EuropeanPricer::ProcessPath(const std::vector<double>& arr)
{
	#pragma omp atomic
	sum += pay_off(arr[arr.size() - 1]);
	#pragma omp atomic
	NSIM++;
}
//Post the process of the price 
void WilliamZhang::IPricer::EuropeanPricer::PostProcess()
{
	price = EuropeanPricer::DiscountFactor() * sum / static_cast<double>(NSIM);
	std::cout << "\n";
	std::cout << "Price: " << price << " Iterations#: " << NSIM << "\n";
}
//Return the discount factor 
double WilliamZhang::IPricer::EuropeanPricer::DiscountFactor() const
{
	return m_discounter();
}
//Return the price 
double WilliamZhang::IPricer::EuropeanPricer::Price() const
{
	return price;
}

WilliamZhang::IPricer::AsianPricer::AsianPricer(const std::function<double(double)>& payoff, const std::function<double()> discounter) : Pricer(payoff, discounter), NSIM(0), sum(0.0), price(0.0)
{
}

WilliamZhang::IPricer::AsianPricer::AsianPricer(const AsianPricer& source) : Pricer(source), NSIM(source.NSIM), sum(source.sum), price(source.sum)
{
}

WilliamZhang::IPricer::AsianPricer& WilliamZhang::IPricer::AsianPricer::operator=(const AsianPricer& source)
{
	// TODO: insert return statement here
	if (this == &source)
	{
		Pricer::operator=(source);
		return *this;
	}
	NSIM = source.NSIM;
	sum = source.sum;
	price = source.price;
	Pricer::operator=(source);
	return *this;
}

void WilliamZhang::IPricer::AsianPricer::ProcessPath(const std::vector<double>& arr)
{
	//Increment
	   #pragma omp atomic
		NSIM++;

		double mean = 0;
		//Compute in parallel 
			#pragma omp parallel for reduction(+:mean)
			for (int i = 0; i < arr.size(); i++) {
				mean += arr[i];
			}
			#pragma omp atomic
			mean /= static_cast<double>(arr.size());
		
		#pragma omp atomic
		sum += pay_off(mean);
}
//Compute the price 
void WilliamZhang::IPricer::AsianPricer::PostProcess()
{
	//Compute the price 
	price = AsianPricer::DiscountFactor() * sum / static_cast<double>(NSIM);
	std::cout << "\n";
	std::cout << "Price: " << price << " Iterations#: " << NSIM << "\n";
}

double WilliamZhang::IPricer::AsianPricer::DiscountFactor() const
{
	return m_discounter();
}

double WilliamZhang::IPricer::AsianPricer::Price() const
{
	return price;
}

WilliamZhang::IPricer::BarrierPricer::BarrierPricer(const std::function<double(double)>& payoff, const std::function<double()> discounter, double l, double payback) : Pricer(payoff, discounter), NSIM(0), sum(0.0), price(0.0), barrier(l), rebate(payback)
{
}

WilliamZhang::IPricer::BarrierPricer::BarrierPricer(const BarrierPricer& source) : Pricer(source), NSIM(source.NSIM), sum(source.sum), price(source.sum), barrier(source.barrier)
{
}

WilliamZhang::IPricer::BarrierPricer& WilliamZhang::IPricer::BarrierPricer::operator=(const BarrierPricer& source)
{
	// TODO: insert return statement here
	if (this == &source)
	{
		Pricer::operator=(source);
		return *this;
	}
	NSIM = source.NSIM;
	sum = source.sum;
	price = source.price;
	barrier = source.barrier;
	Pricer::operator=(source);
	return *this;
}

void WilliamZhang::IPricer::BarrierPricer::ProcessPath(const std::vector<double>& arr)
{
	//Scan through the array
	bool crossed = false;
	for (int n = 0; n < arr.size(); n++)
	{
		//Check if it  been crossed 
		if (arr[n] >= barrier)
		{ 
			crossed = true;
			break;
		}
	}
	//Calculate the pay_off 
	if (crossed == false)
	{
		//If its not been crossed then add the pay 
		#pragma omp atomic
		sum += pay_off(arr[arr.size() - 1]);
		
	}
	else
	{
		//If it  cross add the rebate 
		#pragma omp atomic
		sum += rebate;
	}
	#pragma omp atomic
	NSIM++;
}

//Post the process 
void WilliamZhang::IPricer::BarrierPricer::PostProcess()
{
	price = BarrierPricer::DiscountFactor() * sum / static_cast<double>(NSIM);
	std::cout << "\n";
	std::cout << "Price: " << price << " Iterations#: " << NSIM << "\n";
}
//Discount facotrr 
double WilliamZhang::IPricer::BarrierPricer::DiscountFactor() const
{
	return m_discounter();
}
//Compute the price 
double WilliamZhang::IPricer::BarrierPricer::Price() const
{
	return price;
}