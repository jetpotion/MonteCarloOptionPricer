#include "SDE.hpp"
#include <cmath>
//Standard constructor for GBM
MonteCarloOptionApplication::ISde::GBM::GBM(double driftCoefficient, double diffusionCoefficient, double dividendYield,
                                            double initialCondition, double expiry) noexcept
	: SDE(), mu(driftCoefficient), vol(diffusionCoefficient), d(dividendYield), ic(initialCondition), exp(expiry)
{
}

//GBM copy constructor 
MonteCarloOptionApplication::ISde::GBM::GBM(const GBM& source)
	:
	SDE(source),
	mu{ source.mu },
	vol{ source.vol },
	d{ source.d },
	ic{ source.ic },
	exp{ source.exp }
{
	
}

MonteCarloOptionApplication::ISde::GBM& MonteCarloOptionApplication::ISde::GBM::operator=(const GBM& source)
{
	if (this == &source)
	{
		SDE::operator=(source);
		return *this;
	}
	mu = source.mu;
	vol = source.vol;
	d = source.d;
	ic = source.ic;
	exp = source.exp;
	SDE::operator=(source);
	return *this;
	// TODO: insert return statement here
}

//Drift 
double MonteCarloOptionApplication::ISde::GBM::Drift(double x, double t) const noexcept
{
	return (mu - d) * x;
}

//Dissuion
double MonteCarloOptionApplication::ISde::GBM::Diffusion(double x, double t) const noexcept
{
	return vol * x;
}

//dRIFT corrected
double MonteCarloOptionApplication::ISde::GBM::DriftedCorrected(double x, double t, double b) const noexcept
{
	return Drift(x, t) - b * Diffusion(x, t) * DiffusionDerivative(x, t);
}

//Difsuion deritivative 
double MonteCarloOptionApplication::ISde::GBM::DiffusionDerivative(double x, double t) const noexcept
{
	return vol;
}

//Expiry setter
void MonteCarloOptionApplication::ISde::GBM::Expiry(double expiry) noexcept
{
	exp = expiry;
}

//Expiry getter
double MonteCarloOptionApplication::ISde::GBM::Expiry() const noexcept
{
	return exp;
}

//IC setter
void MonteCarloOptionApplication::ISde::GBM::InitialCondition(double initial_price) noexcept
{
	ic = initial_price;
}

//IC getter 
double MonteCarloOptionApplication::ISde::GBM::InitialCondition() const noexcept
{
	return ic;
}

//SAME CLASS STRUCTURE AS GBM but ONLY DIFFERENCE IS THAT WE HAVE BETA 
MonteCarloOptionApplication::ISde::CEV::CEV(double driftCoefficient, double diffusionCoefficient, double dividendYield,
                                            double initialCondition, double expiry, double beta)  noexcept:
	SDE(), mu(driftCoefficient), d(dividendYield), ic(initialCondition), exp(expiry), beta(beta)
{
	vol = diffusionCoefficient * std::pow(ic, 1.0 - beta);
}

MonteCarloOptionApplication::ISde::CEV::CEV(const CEV& source) noexcept :
	SDE(source), mu(source.beta), vol(source.vol), d(source.d), ic(source.ic), exp(source.exp), beta(source.beta)
{
}

MonteCarloOptionApplication::ISde::CEV& MonteCarloOptionApplication::ISde::CEV::operator=(const CEV& source)
{
	if (this == &source)
	{
		SDE::operator=(source);
		return *this;
	}
	mu = source.mu;
	vol = source.vol;
	d = source.d;
	ic = source.ic;
	exp = source.exp;
	beta = source.beta;
	SDE::operator=(source);
	return *this;
	// TODO: insert return statement here
}

double MonteCarloOptionApplication::ISde::CEV::Drift(double x, double t) const noexcept
{
	return (mu - d) * x;
}

double MonteCarloOptionApplication::ISde::CEV::Diffusion(double x, double t) const noexcept
{
	return vol * std::pow(x, beta);
}

double MonteCarloOptionApplication::ISde::CEV::DriftedCorrected(double x, double t, double b) const noexcept
{
	return Drift(x, t) - b * Diffusion(x, t) * DiffusionDerivative(x, t);
}

double MonteCarloOptionApplication::ISde::CEV::DiffusionDerivative(double x, double t) const noexcept
{
	//If the beta is too high then subtract one 
	if (beta > 1.00f)
	{
		return vol * beta * std::pow(x, beta - 1.0);
	}
	//If its below 1.0 then subtract 
	return vol * beta / std::pow(x, 1.0 - beta);
}

void MonteCarloOptionApplication::ISde::CEV::Expiry(double expiry) noexcept
{
	exp = expiry;
}

double MonteCarloOptionApplication::ISde::CEV::Expiry() const noexcept
{
	return exp;
}

void MonteCarloOptionApplication::ISde::CEV::InitialCondition(double initial_price) noexcept
{
	ic = initial_price;
}

double MonteCarloOptionApplication::ISde::CEV::InitialCondition() const noexcept
{
	return ic;
}

MonteCarloOptionApplication::ISde::SDE& MonteCarloOptionApplication::ISde::SDE::operator=(const SDE& source) noexcept
{
	return *this;
	// TODO: insert return statement here
}
