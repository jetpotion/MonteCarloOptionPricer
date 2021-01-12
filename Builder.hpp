#include "FDM.hpp"
#include "RNG.hpp"
#include "OptionData.hpp"
#include "Pricer.hpp"
#include  <algorithm>
#include <tuple>
#ifndef BUILDER_HPP
#define BUILDER_HPP
//Appropate alias for the shared pt
using FiniteDifferenceMethod = std::shared_ptr<MonteCarloOptionApplication::IFdm::FDM>;
using RandomNumberGenerator = std::shared_ptr<MonteCarloOptionApplication::IRng::RNG>;
using StochasticEquation = std::shared_ptr<MonteCarloOptionApplication::ISde::SDE>;
using Pricers = std::shared_ptr<MonteCarloOptionApplication::IPricer::Pricer>;
class McBuilder {
private:
	//The data itself 
	OptionData m_data;
	//Randomber generator factory build method 
	RandomNumberGenerator BuildRng(std::size_t  choice) const;

public:
	//McBuilder constructor
	McBuilder(const  struct OptionData& data);
	//Copy constructor 
	McBuilder(const McBuilder& source);
	//Assignment operator 
	McBuilder& operator=(const McBuilder& source);
	//Build the individual parts from the selection of equation,RNG,FDM and pricer as well as subdivison
	std::tuple<FiniteDifferenceMethod, RandomNumberGenerator, StochasticEquation, Pricers> BuildParts(
		std::size_t equationchoice, std::size_t RngChoice, std::size_t FDMChoice, std::size_t PricerChoice, std::size_t subdivision);
	//SDE factory method 
	StochasticEquation BuildSde(std::size_t  choice) const;
	//FDM factory method 
	FiniteDifferenceMethod BuildFdm(StochasticEquation eq, std::size_t subdivision, std::size_t choice) const;
	//The pricers 
	Pricers BuildPricer(std::size_t choice) const;
};

#endif // !BUILDER_HPP