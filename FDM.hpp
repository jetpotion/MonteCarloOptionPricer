#include "SDE.hpp"
#include <memory>
#include <vector>
#include <cmath>
//FDM METHODS
#ifndef FDM_HPP
#define FDM_HPP
namespace WilliamZhang
{
	namespace IFdm
	{
		class  FDM
		{
		protected:
			std::shared_ptr<WilliamZhang::ISde::SDE>eq; //equation itself
		public:
			std::size_t NT; //Number of trials(which is a unisnged interger)
			double k; //Mesh size
		public:
			//Constructor
			FDM(std::shared_ptr<WilliamZhang::ISde::SDE> sde, std::size_t sub_divisions);
			virtual ~FDM() = default;
			//Copy construcotr
			FDM(const FDM& source);
			//Assignment operator
			FDM& operator=(const FDM& source);
			//equation  getter
			std::shared_ptr<WilliamZhang::ISde::SDE> equation() const;
			//Equatioon setter
			void equation(std::shared_ptr<WilliamZhang::ISde::SDE> sde);
			//Virtual Method to find the next solution to the finite difference methid 
			virtual double advance(double x_n, double t_n, double d_t, double WeinerIncrement) const = 0;
			double RequestIncrement(unsigned int n) const;	//Takes an unsigned int and be multiply it by the mesh size
		};
		//The Following classes are so short we decided to put them in the header files instead of source
		//This is the euler FDM
		class EulerFDM : public FDM
		{
		public:
			//Constructor
			EulerFDM(std::shared_ptr<WilliamZhang::ISde::SDE> sde, std::size_t sub_divisions) : FDM(sde, sub_divisions)
			{
			}
			//Copy constructor 
			EulerFDM(const EulerFDM& source) : FDM(source)
			{
			}
			//Assignment operator 
			EulerFDM& operator=(const EulerFDM& source)
			{
				FDM::operator=(source);
				return *this;
			}
			//Destructor 
			virtual ~EulerFDM() override = default;
			//Result in default inline  equation for the explicit euler equatioj
			virtual double  advance(double x_n, double t_n, double d_t, double NormalVar) const override {
				return x_n + d_t * eq->Drift(x_n, t_n) + eq->Diffusion(x_n, t_n) * std::sqrt(d_t) * NormalVar;
			}
		};
		class MilsteinFDM :public FDM
		{
		public:
			//constructor
			MilsteinFDM(std::shared_ptr<WilliamZhang::ISde::SDE> sde, std::size_t sub_divisions) : FDM(sde, sub_divisions)
			{
			}
			//copy constructor
			MilsteinFDM(const MilsteinFDM& source) : FDM(source)
			{
			}
			//assignemnt operator 
			MilsteinFDM& operator=(const MilsteinFDM& source)
			{
				FDM::operator=(source);
				return *this;
			}
			//destructor 
			virtual ~MilsteinFDM() override = default;
			//Result in  milstein fdm differnece method 
			virtual double  advance(double x_n, double t_n, double d_t, double NormalVar) const override {
				return x_n + eq->Drift(x_n, t_n) * d_t + eq->Diffusion(x_n, t_n) * std::sqrt(d_t) * NormalVar
					+ 0.5 * d_t * eq->Diffusion(x_n, t_n) * eq->DiffusionDerivative(x_n, t_n) * (NormalVar * NormalVar - 1.0);
			}
		};
		//The following is for the class with the adjusted mid point method 
		class PredictedMidPointFDM :public FDM
		{
		private:

			double a;
			double b;
		public:
			//Constructor
			PredictedMidPointFDM(std::shared_ptr<WilliamZhang::ISde::SDE> sde, std::size_t sub_divisions, double a, double b) : FDM(sde, sub_divisions), a(a), b(b)
			{
			}
			//Copy constructor
			PredictedMidPointFDM(const PredictedMidPointFDM& source) : FDM(source), a(source.a), b(source.b)
			{
			}
			//Assignment  constructor 
			PredictedMidPointFDM& operator=(const PredictedMidPointFDM& source)
			{
				FDM::operator=(source);
				return *this;
			}
			virtual ~PredictedMidPointFDM() override = default;
			//Result in default inline  equation for the explicit euler equatioj
			virtual double  advance(double x_n, double t_n, double d_t, double NormalVar) const override {
				// Euler for predictor
				double vmid = x_n + eq->Drift(x_n, t_n) * d_t + eq->Diffusion(x_n, t_n) * std::sqrt(d_t) * NormalVar;

				// Modified double rapezoidal rule
				double driftdoubleTerm = (a * eq->Drift(vmid, t_n + d_t) + ((1.0 - a) * eq->Drift(x_n, t_n))) * d_t;
				double diffusiondoubleTerm = (b * eq->Diffusion(vmid, t_n + d_t) + ((1.0 - b) * eq->Diffusion(x_n, t_n))) * std::sqrt(d_t) * NormalVar;
				//Then the next X(n+1) = drift term and diffusion term 
				return x_n + driftdoubleTerm + diffusiondoubleTerm;
			}
		};
	}
};
#endif