#include <functional>
#ifndef PRICER_HPP
#define PRICER_HPP
//PRICER FOR EUROPEAN/ASIAN/BARRIER
namespace WilliamZhang
{
	namespace IPricer
	{
		class Pricer
		{
		public:
			std::function<double(double)>pay_off; //Payoff function 
		protected:
			std::function <double()>m_discounter;	//Discounter
		public:
			//Standard constructors destructrs and  assignment operator 
			Pricer() = default;
			Pricer(const std::function<double(double)>& payoff, const std::function <double()> discounter);
			Pricer(const Pricer& source);
			Pricer& operator=(const Pricer& source);
			virtual ~Pricer() = default;
			//Compute the price at TIME= t
			virtual void ProcessPath(const std::vector<double>& arr) = 0;
			//Post process
			virtual void PostProcess() = 0;
			//Discountfactor orand sum 
			virtual double DiscountFactor() const = 0;
			virtual double Price() const = 0;
		};
		//Class for the European Option pricing model
		class EuropeanPricer :public Pricer {
		private:
			double sum;	//The sum 
			int NSIM; //Nsim
			double price;	//The price 
		public:
			//Standard consturctor,destructor/copy and assignment 
			EuropeanPricer(const std::function<double(double)>& payoff, const std::function <double()> discounter);
			virtual ~EuropeanPricer()  override = default;
			EuropeanPricer(const EuropeanPricer& source);
			EuropeanPricer& operator=(const EuropeanPricer& source);
			//Process path  to compute the price 
			virtual void ProcessPath(const std::vector<double>& arr) override;
			//Post the price 
			virtual void PostProcess() override;

			//Discountfactor and price 
			virtual double DiscountFactor() const override;
			virtual double Price() const  override;
		};
		//class for the asian option price and the same scheme with european but the prices is computed among the average 
		class AsianPricer :public Pricer {
		private:
			double sum;
			int NSIM;
			double price;
		public:
			AsianPricer(const std::function<double(double)>& payoff, const std::function <double()> discounter);
			virtual ~AsianPricer()  override = default;
			AsianPricer(const AsianPricer& source);
			AsianPricer& operator=(const AsianPricer& source);
			//Compute the average price at time T
			virtual void ProcessPath(const std::vector<double>& arr) override;
			virtual void PostProcess() override;
			virtual double DiscountFactor() const override;
			virtual double Price() const  override;
		};
		class BarrierPricer :public Pricer {
		private:
			double sum;	//Sum
			int NSIM;	//NSIM
			double price; //Price
			double barrier;//Barrier 
			double rebate;//Rebate 
		public:
			BarrierPricer(const std::function<double(double)>& payoff, const std::function <double()> discounter, double L, double payback); //constructor
			virtual ~BarrierPricer()  override = default;						//Destrucotr
			BarrierPricer(const BarrierPricer& source);							//Copy and assignment 
			BarrierPricer& operator=(const BarrierPricer& source);
			//Compute the barrier at time T
			virtual void ProcessPath(const std::vector<double>& arr) override;
			virtual void PostProcess() override;		//Method to post the process at time = T
			virtual double DiscountFactor() const override;	//Discount facotr
			virtual double Price() const  override;			//Price function 
		};
	}
};
#endif // !PRICER_HPP