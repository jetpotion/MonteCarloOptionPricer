#ifndef SDE_HPP
#define SDE_HPP

//THE VARIOUS TYPES OF SDE 
namespace MonteCarloOptionApplication
{
	namespace ISde
	{
		class SDE
		{
		public:
			SDE() = default;
			SDE(const SDE& source) = default;
			SDE& operator=(const SDE& source);
			virtual ~SDE() = default; //Destructor
			[[nodiscard]] virtual double Drift(double x, double t) const noexcept = 0; //Drift
			[[nodiscard]] virtual double Diffusion(double x, double t) const noexcept = 0; //Diffusion term
			[[nodiscard]] virtual double DriftedCorrected(double x, double t, double b) const noexcept = 0; //Drif correcte
			[[nodiscard]] virtual double DiffusionDerivative(double x, double t) const  noexcept= 0; //Diffusion Derivative
			[[nodiscard]] virtual void Expiry(double exp)  noexcept= 0; //Expiry  setter
			[[nodiscard]] virtual double Expiry() const  noexcept= 0; //Expiry  getter ;
			[[nodiscard]] virtual void InitialCondition(double initial_price) noexcept = 0; //Initial condition SETTER
			[[nodiscard]] virtual double InitialCondition() const noexcept = 0; //Returns the initial stock price
		};

		//Classical GBM SDE
		class GBM : public SDE
		{
		private:
			double mu; //The Drift
			double vol; //The volatility
			double d; //The dividend yield
			double ic; //StockPrice
			double exp; //Expiry
		public:
			constexpr GBM(double driftCoefficient, double diffusionCoefficient, double dividendYield, double initialCondition,
			    double expiry) noexcept; //Overloaded constructor
			constexpr GBM(const GBM& source);
			GBM& operator=(const GBM& source);
			~GBM() override = default ; //Overrided destructor
			[[nodiscard]] constexpr double Drift(double x, double t) const noexcept override; //Drift
			[[nodiscard]] constexpr double Diffusion(double x, double t) const noexcept override; //Diffusion term
			[[nodiscard]] constexpr double DriftedCorrected(double x, double t, double b) const noexcept override; //Drif correcte
			[[nodiscard]] constexpr double DiffusionDerivative(double x, double t) const noexcept override; //Diffusion Derivative
			[[nodiscard]] constexpr void Expiry(double exp)  noexcept override; //Expiry  setter
			[[nodiscard]] constexpr double Expiry() const  noexcept override; //Expiry  getter ;
			[[nodiscard]] constexpr void InitialCondition(double initial_price)  noexcept override; //Initial condition SETTER
			[[nodiscard]] constexpr double InitialCondition() const noexcept override; //Returns the initial stock price
		};

		//The elastacity variance model of the SDE
		class CEV : public SDE
		{
		private:
			double mu; //The Drift
			double vol; //The volatility
			double d; //The dividend yield
			double ic; //StockPrice
			double exp; //Expiry
			double beta;
		public:
			constexpr CEV(double driftCoefficient, double diffusionCoefficient, double dividendYield, double initialCondition,
			    double expiry, double beta) noexcept; //Overloaded constructor
			constexpr CEV(const CEV& source) noexcept;
			CEV& operator=(const CEV& source);
			~CEV() override = default; //Overrided destructor
			[[nodiscard]] double Drift(double x, double t) const noexcept override; //Drift
			[[nodiscard]] double Diffusion(double x, double t) const  noexcept override; //Diffusion term
			[[nodiscard]] double DriftedCorrected(double x, double t, double b) const noexcept override; //Drif correcte
			[[nodiscard]] double DiffusionDerivative(double x, double t) const noexcept override; //Diffusion Derivative
			[[nodiscard]] void Expiry(double exp)  noexcept override; //Expiry  setter
			[[nodiscard]] double Expiry() const override; //Expiry  getter ;
			[[nodiscard]] void InitialCondition(double initial_price) noexcept  override; //Initial condition SETTER
			[[nodiscard]] double InitialCondition() const noexcept  override; //Returns the initial stock price
		};
	}
}
#endif
