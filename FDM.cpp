#include "FDM.hpp"
//FDM constructor  
WilliamZhang::IFdm::FDM::FDM(std::shared_ptr<WilliamZhang::ISde::SDE> sde, std::size_t subdivision) :eq(sde), NT(subdivision)
{
	//Initialize the mesh size
	k = sde->Expiry() / static_cast<double>(NT);
}
//Copy constructor
WilliamZhang::IFdm::FDM::FDM(const FDM& source) :eq(source.eq), NT(source.NT), k(source.k)
{
}
//Assignment operator 
WilliamZhang::IFdm::FDM& WilliamZhang::IFdm::FDM::operator=(const FDM& source)
{
	if (this == &source)
		return *this;
	eq = source.eq;
	NT = source.NT;
	k = source.k;

	return *this;
	// TODO: insert return statement here
}
//The equation itself 
std::shared_ptr<WilliamZhang::ISde::SDE> WilliamZhang::IFdm::FDM::equation() const
{
	return  eq;
}
//Setting the equaiton 
void WilliamZhang::IFdm::FDM::equation(std::shared_ptr<WilliamZhang::ISde::SDE> sde)
{
	sde = eq;
}
//Request the  proper increment 
double WilliamZhang::IFdm::FDM::RequestIncrement(unsigned int n) const
{
	return n * k;
}