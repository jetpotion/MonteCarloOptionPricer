#ifndef SDE_HPP
#define SDE_HPP
//THE VARIOUS TYPES OF SDE 
namespace WilliamZhang
{
	namespace ISde
	{
		class SDE
		{
		public:
			SDE() = default;
			SDE(const SDE& source) = default;
			SDE& operator=(const SDE& source);
			virtual ~SDE() = default;			//Destructor
			virtual double Drift(double x, double  t) const = 0;	//Drift
			virtual double Diffusion(double x, double t) const = 0; //Diffusion term
			virtual double DriftedCorrected(double x, double t, double b) const = 0;	//Drif correcte
			virtual double DiffusionDerivative(double x, double t) const = 0; //Diffusion Derivative
			virtual void  Expiry(double exp) = 0; //Expiry  setter
			virtual double Expiry() const = 0;  //Expiry  getter ;
			virtual void InitialCondition(double initial_price) = 0; //Initial condition SETTER
			virtual double InitialCondition() const = 0;  //Returns the initial stock price

			
		};
		//Classical GBM SDE
		class GBM :public SDE
		{
		private:
			double mu;		//The Drift
			double vol;		//The volatility
			double d;		//The dividend yield
			double ic;		//StockPrice
			double exp;		//Expiry
		public:
			GBM(double driftCoefficient, double diffusionCoefficient, double dividendYield, double initialCondition, double expiry);	//Overloaded constructor
			GBM(const GBM& source);
			GBM& operator=(const GBM& source);
			virtual ~GBM() override = default;	//Overrided destructor
			virtual double Drift(double x, double  t) const override;	//Drift
			virtual double Diffusion(double x, double t) const override; //Diffusion term
			virtual double DriftedCorrected(double x, double t, double b) const override;	//Drif correcte
			virtual double DiffusionDerivative(double x, double t) const override; //Diffusion Derivative
			virtual void  Expiry(double exp) override; //Expiry  setter
			virtual double Expiry() const override;  //Expiry  getter ;
			virtual void InitialCondition(double initial_price) override; //Initial condition SETTER
			virtual double InitialCondition() const  override;  //Returns the initial stock price
			
		};
		//The elastacity variance model of the SDE
		class CEV : public SDE
		{
		private:
			double mu;		//The Drift
			double vol;		//The volatility
			double d;		//The dividend yield
			double ic;		//StockPrice
			double exp;		//Expiry
			double beta;
		public:
			CEV(double driftCoefficient, double diffusionCoefficient, double dividendYield, double initialCondition, double expiry, double beta);	//Overloaded constructor
			CEV(const CEV& source);
			CEV& operator=(const CEV& source);
			virtual ~CEV() override = default;	//Overrided destructor
			virtual double Drift(double x, double  t) const override;	//Drift
			virtual double Diffusion(double x, double t) const override; //Diffusion term
			virtual double DriftedCorrected(double x, double t, double b) const override;	//Drif correcte
			virtual double DiffusionDerivative(double x, double t) const override; //Diffusion Derivative
			virtual void  Expiry(double exp) override; //Expiry  setter
			virtual double Expiry() const override;  //Expiry  getter ;
			virtual void InitialCondition(double initial_price) override; //Initial condition SETTER
			virtual double InitialCondition() const  override;  //Returns the initial stock price
			
		};
	}
}
#endif