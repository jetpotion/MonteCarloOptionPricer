#include "Builder.hpp"
//Constructor
McBuilder::McBuilder(const struct OptionData& data) :m_data(data)
{
}
//Copy constructor
McBuilder::McBuilder(const McBuilder& source) : m_data(source.m_data)
{
}
//Assignment operator 
McBuilder& McBuilder::operator=(const McBuilder& source)
{
	if (this == &source)
	{
		return *this;
	}

	// TODO: insert return statement here
}
//The tuple to store the parts of the equation,Rng,FDM,Pricer
std::tuple<FiniteDifferenceMethod, RandomNumberGenerator, StochasticEquation, Pricers> McBuilder::BuildParts
(std::size_t equationchoice, std::size_t RngChoice, std::size_t FDMChoice, std::size_t PricerChoice, std::size_t subdivision)
{
	//Now using the parameter to choose from each part 
	StochasticEquation  eq = BuildSde(equationchoice);
	RandomNumberGenerator rng = BuildRng(RngChoice);
	FiniteDifferenceMethod fdm = BuildFdm(eq, subdivision, FDMChoice);
	Pricers price = BuildPricer(PricerChoice);
	return  std::make_tuple(fdm, rng, eq, price);
}
//Method to allow the user to choose the SDE 
StochasticEquation McBuilder::BuildSde(std::size_t choice) const
{
	//Switch through the choices  and return the correct SDE

	switch (choice)
	{
	default:
	case 1: return std::make_shared<WilliamZhang::ISde::GBM>(m_data.r, m_data.sig, m_data.D, m_data.S, m_data.T);
	case 2: return std::make_shared<WilliamZhang::ISde::CEV>(m_data.r, m_data.sig, m_data.D, m_data.S, m_data.T, m_data.beta);
	}
	return std::make_shared<WilliamZhang::ISde::GBM>(m_data.r, m_data.sig, m_data.D, m_data.S, m_data.T);
}
//Build the RNG
RandomNumberGenerator McBuilder::BuildRng(std::size_t choice) const
{
	//Switch through the choices  and return the correct RNG
	switch (choice)
	{
	default:
	case 1: return std::make_shared<WilliamZhang::IRng::MyMersenneTwister>();
	case 2: return std::make_shared<WilliamZhang::IRng::PolarMasglia>();
	case 3: return std::make_shared<WilliamZhang::IRng::BoxMuller>();
	}
	return std::make_shared<WilliamZhang::IRng::MyMersenneTwister>();
}
//Build the fdm facotry method 
FiniteDifferenceMethod McBuilder::BuildFdm(StochasticEquation eq, std::size_t sub_division, std::size_t choice) const
{
	//Switch through the choices  and return the correct FDM
	switch (choice)
	{
	default:
	case 1: return std::make_shared<WilliamZhang::IFdm::EulerFDM>(eq, sub_division);
	case 2: return std::make_shared<WilliamZhang::IFdm::MilsteinFDM>(eq, sub_division);
		//In this case with the fully symtettric since we already have FDM schemes for the Euler and the Milstein method s
	case 3: return std::make_shared<WilliamZhang::IFdm::PredictedMidPointFDM>(eq, sub_division, 0.5, 0.5);
	}
	return std::make_shared<WilliamZhang::IFdm::EulerFDM>(eq, sub_division);
}
//Build the pricer
Pricers McBuilder::BuildPricer(std::size_t choice) const
{
	//Discounter operation 
	std::function<double()>discounter = [&]() -> double
	{
		return std::exp(-m_data.r * m_data.T);
	};
	std::function<double(double)>payoff = [&](double s) -> double
	{
		//Payyoff function depending on call and put 
		if (m_data.type == 1)
			return std::max(s - m_data.K, 0.00);
		else
			return std::max(m_data.K - s, 0.00);
	};
	//Switch through the choices 
	switch (choice)
	{
	default:
	case 1: return std::make_shared<WilliamZhang::IPricer::EuropeanPricer>(payoff, discounter);
	case 2: return std::make_shared<WilliamZhang::IPricer::AsianPricer>(payoff, discounter);
	case 3: return std::make_shared<WilliamZhang::IPricer::BarrierPricer>(payoff, discounter, m_data.l, m_data.rebate);
	}
	//In case if some exception occured then return Eurooean
	return std::make_shared<WilliamZhang::IPricer::EuropeanPricer>(payoff, discounter);
}