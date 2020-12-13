// OptionData.hpp
//
// Encapsulate option data.
//
// (C) Datasim Education BV 2008-2016

#ifndef OptionData_HPP
#define OptionData_HPP
#include <iostream>
#include <algorithm> // for max()
#include <boost/parameter.hpp>

namespace OptionParams
{
	BOOST_PARAMETER_KEYWORD(Tag, strike)
		BOOST_PARAMETER_KEYWORD(Tag, expiration)
		BOOST_PARAMETER_KEYWORD(Tag, interestRate)
		BOOST_PARAMETER_KEYWORD(Tag, volatility)
		BOOST_PARAMETER_KEYWORD(Tag, dividend)
		BOOST_PARAMETER_KEYWORD(Tag, optionType)
		BOOST_PARAMETER_KEYWORD(Tag, Stockprice)
		BOOST_PARAMETER_KEYWORD(Tag, Beta)
		BOOST_PARAMETER_KEYWORD(Tag, Barrier)
		BOOST_PARAMETER_KEYWORD(Tag, Rebate)
}

// Encapsulate all data in one place
struct OptionData
{ // Option data + behaviour
	double S; //Stockprice
	double K;	//Strike price
	double T;	//Time to expiration 
	double r;	//interest rate 
	double sig;	//Volatility
	double l;	
	// Extra data
	double D;		// dividend
	double beta;	//Beta
	double rebate;	//Rebate 
	int type;		// 1 == call, -1 == put
	OptionData() : S(0.0), K(0.0), T(0.0), r(0.0), sig(0.0), D(0.0), beta(0.0), l(0.0), rebate(0.0), type(-1)
	{
	}
	explicit constexpr OptionData(double strike, double expiration, double interestRate,
		double volatility, double dividend, double b, double StockPrice, double barrier, double rebate, int PC)
		: K(strike), T(expiration), r(interestRate), sig(volatility), S(StockPrice), D(dividend), beta(b), l(barrier), rebate(rebate), type(PC)
	{}
	//The best way to instantiate the Optiondat class. Use Named parameter idiom to instantiate the optiondata
	template <typename ArgPack> OptionData(const ArgPack& args)
	{
		K = args[OptionParams::strike];
		T = args[OptionParams::expiration];
		r = args[OptionParams::interestRate];
		sig = args[OptionParams::volatility];
		D = args[OptionParams::dividend];
		type = args[OptionParams::optionType];
		beta = args[OptionParams::Beta];
		S = args[OptionParams::Stockprice];
		l = args[OptionParams::Barrier];
		rebate = args[OptionParams::Rebate];
	}
};

#endif