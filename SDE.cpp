#include "SDE.hpp"
#include <cmath>
//Standard constructor for GBM
WilliamZhang::ISde::GBM::GBM(double driftCoefficient, double diffusionCoefficient, double dividendYield, double initialCondition, double expiry)
	:SDE(), mu(driftCoefficient), vol(diffusionCoefficient), d(dividendYield), ic(initialCondition), exp(expiry)
{
}
//GBM copy constructor 
WilliamZhang::ISde::GBM::GBM(const GBM& source)
	: SDE(source), mu(source.mu), vol(source.vol), d(source.d), ic(source.ic), exp(source.exp)
{
}

WilliamZhang::ISde::GBM& WilliamZhang::ISde::GBM::operator=(const GBM& source)
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
double WilliamZhang::ISde::GBM::Drift(double x, double t) const
{
	return (mu - d) * x;
}
//Dissuion
double WilliamZhang::ISde::GBM::Diffusion(double x, double t) const
{
	return  vol * x;
}
//dRIFT corrected
double WilliamZhang::ISde::GBM::DriftedCorrected(double x, double t, double b) const
{
	return Drift(x, t) - b * Diffusion(x, t) * DiffusionDerivative(x, t);
}
//Difsuion deritivative 
double WilliamZhang::ISde::GBM::DiffusionDerivative(double x, double t) const
{
	return vol;
}
//Expiry setter
void WilliamZhang::ISde::GBM::Expiry(double expiry)
{
	exp = expiry;
}
//Expiry getter
double WilliamZhang::ISde::GBM::Expiry() const
{
	return exp;
}
//IC setter
void WilliamZhang::ISde::GBM::InitialCondition(double initial_price)
{
	ic = initial_price;
}
//IC getter 
double WilliamZhang::ISde::GBM::InitialCondition() const
{
	return ic;
}
//SAME CLASS STRUCTURE AS GBM but ONLY DIFFERENCE IS THAT WE HAVE BETA 
WilliamZhang::ISde::CEV::CEV(double driftCoefficient, double diffusionCoefficient, double dividendYield, double initialCondition, double expiry, double beta) :
	SDE(), mu(driftCoefficient), d(dividendYield), ic(initialCondition), exp(expiry), beta(beta)
{
	vol = diffusionCoefficient * std::pow(ic, 1.0 - beta);
}

WilliamZhang::ISde::CEV::CEV(const CEV& source) :
	SDE(source), mu(source.beta), vol(source.vol), d(source.d), ic(source.ic), exp(source.exp), beta(source.beta)
{
}

WilliamZhang::ISde::CEV& WilliamZhang::ISde::CEV::operator=(const CEV& source)
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

double WilliamZhang::ISde::CEV::Drift(double x, double t) const
{
	return (mu - d) * x;
}

double WilliamZhang::ISde::CEV::Diffusion(double x, double t) const
{
	return vol * std::pow(x, beta);
}

double WilliamZhang::ISde::CEV::DriftedCorrected(double x, double t, double b) const
{
	return Drift(x, t) - b * Diffusion(x, t) * DiffusionDerivative(x, t);
}

double WilliamZhang::ISde::CEV::DiffusionDerivative(double x, double t) const
{
	//If the beta is too high then subtract one 
	if (beta > 1.00f)
	{
		return vol * beta * std::pow(x, beta - 1.0);
	}
	//If its below 1.0 then subtract 
	else
	{
		return vol * beta / std::pow(x, 1.0 - beta);
	}
}

void WilliamZhang::ISde::CEV::Expiry(double expiry)
{
	exp = expiry;
}

double WilliamZhang::ISde::CEV::Expiry() const
{
	return exp;
}

void WilliamZhang::ISde::CEV::InitialCondition(double initial_price)
{
	ic = initial_price;
}

double WilliamZhang::ISde::CEV::InitialCondition() const
{
	return ic;
}

WilliamZhang::ISde::SDE& WilliamZhang::ISde::SDE::operator=(const SDE& source)
{

	return *this;
	// TODO: insert return statement here
}
