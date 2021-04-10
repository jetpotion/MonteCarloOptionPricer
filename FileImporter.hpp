#include "Mediator.hpp"
#include <cctype>

#include <string>
#include <boost/algorithm/string.hpp>

#ifndef  FILEIMPORTER_HPP
#define  FILEIMPORTER_HPP
//Only one mediator at a time. That has on

namespace MonteCarloOptionApplication
{
	namespace FileImporter
	{
		
		static Mediator medium;
		//designed to ask for the creation of parts. Note that we will only have at most one mediator
		//The following parts are singular and constant throughout the program, No matter the parameters. Regardless of parameters . SDE type/Rng_type/FDM_type,the simulations and the mesh array size
		static std::tuple<int, int, int, int, int>inmutableparts() {



			//The following ask for the imuttable parts of the mediator. We will ask the user what RNG/FDM/SDE type/Subdivisions
			unsigned int sde_type = 1;
			std::cout << "What is the SDE you want\n1.GBM 2.CEV" << "\n";

			std::cin >> sde_type;
			if (std::cin.fail())
			{
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				sde_type = 1;
				std::cout << "Defaulting to GBM\n";
			}
			unsigned int rng_type = 1;
			std::cout << "What is the RNG type \n1.MerseneeTwister 2.PolarMasglia 3.BoxMueller\n";
			std::cin >> rng_type;
			if (std::cin.fail())
			{
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				rng_type = 1;
				std::cout << "Defaulting to MerseneeTwister\n";
			}

			unsigned int  fdm_type = 1;
			std::cout << "What is FDM method type \n 1.EulerFDM 2. MilsteinFDM 3.MidPointer\n";
			std::cin >> fdm_type;
			if (std::cin.fail())
			{
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				fdm_type = 1;
				std::cout << "Defaulting to EulerFDM\n";
			}
			unsigned int subdivsion = 100;
			std::cout << "How many subdivisions\n";
			std::cin >> subdivsion;
			if (std::cin.fail() || subdivsion <= 0)
			{
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				subdivsion = 100;
				std::cout << "Defaulting to 100 subdivisions\n";
			}
			unsigned int simulations = 50000;
			std::cout << "How many simulations\n";
			std::cin >> simulations;
			if (std::cin.fail() || simulations <= 0)
			{
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				simulations = 50000;
				std::cout << "Defaulting to 50k simulations\n";
			}
			return std::make_tuple(sde_type, rng_type, fdm_type, subdivsion, simulations);
		}
		//Starts a console process 
		static void createConsoleProcess()
		{
		
			double k = 65.0;
			double exp = 0.25;
			double vol = 0.3;
			double dividend = 0.0;
			int  optiontype = -1;
			double ir = 0.08;
			double stockprice = 60.0;
			double beta = 1.0;
			double barrier = 0.0;
			double rebate = 0.0;
			std::tuple<int, int, int, int, int>type = inmutableparts();
			int sde_type = std::get<0>(type);
			int rng_type = std::get<1>(type);
			int fdm_type = std::get<2>(type);
			int subdivision = std::get<3>(type);
			int simulations = std::get<4>(type);

			//Parts necessary for the sde,rng,fdm,subdivision,simulations
			std::cout << "Now asking for option data by console\n";
			std::cout << "What is the option type\n 1. EuropeanOption 2.AsianOption 3.BarrierOption\n";
			int type_of_option;
			std::cin >> type_of_option;
			switch (type_of_option)
			{
				//The case when we have european,AsianOption
			default:
			case 1:
			case 2:
			{
				//check if the inputs are correct. If they are not then just flush the buffer and reinitialize 
				std::cout << "What is the strike price\n";
				std::cin >> k;
				if (k < 0.00f || std::cin.fail())
				{
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					k = 65.0;
					std::cout << "Defaulting to stockprice of 65.00\n";
				}
				std::cout << "What is the time of expiration\n";
				std::cin >> exp;
				if (exp < 0.00f || std::cin.fail())
				{
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					exp = 0.25;
					std::cout << "Defaulting to expiration date of 0.25\n";
				}
				std::cout << "What is the volatility\n";
				std::cin >> vol;
				if (vol < 0.00f || std::cin.fail())
				{
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					vol = 0.3;
					std::cout << "Defaulting to a volailty of 0.3\n";
				}
				std::cout << "What is the dividend\n";
				std::cin >> dividend;
				if (dividend < 0.00f || std::cin.fail())
				{
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					dividend = 0.00;
					std::cout << "Defaulting to zero dividend\n";
				}
				std::cout << "What is the Option type(-1:put, 1:call)\n";
				std::cin >> optiontype;
				if (optiontype != -1 && optiontype != 1 || std::cin.fail())
				{
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					optiontype = -1;
					std::cout << "Defaulting to put option\n";
				}
				std::cout << "What is the interest rate\n";
				std::cin >> ir;
				if (ir > 10.0 || ir < 0.00f || std::cin.fail())
				{
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					ir = 0.08;
					std::cout << "Defaulting to interest rate of 0.08\n";
				}

				std::cout << "What is the initial stockprice\n";
				std::cin >> stockprice;

				if (stockprice < 0.00 || std::cin.fail())
				{
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					stockprice = 60.0;
					std::cout << "Defaulting to stockprice of 60.0\n";
				}

				//Ask for barrier
				if (sde_type == 2)
				{
					std::cout << "What is the beta " << std::endl;
					std::cin >> beta;
					if (std::cin.fail() || beta > 10.0)
					{
						std::cin.clear();
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						beta = 1.0;
						std::cout << "Defaulting to beta of 1.0f\n";
					}
				}
				OptionData myOption((OptionParams::strike = k, OptionParams::expiration = exp,
					OptionParams::volatility = vol, OptionParams::dividend = dividend,
					OptionParams::optionType = optiontype, OptionParams::interestRate = ir,
					OptionParams::Stockprice = stockprice, OptionParams::Beta = beta,
					OptionParams::Barrier = barrier, OptionParams::Rebate = rebate));
				McBuilder build(myOption);
				//Create parts and build parts
				auto parts = build.BuildParts(sde_type, rng_type, fdm_type, type_of_option, subdivision);
				medium = Mediator(parts, simulations);
				medium.start();

				break;
			}
			case 3:
				//check if the inputs are correct
				std::cout << "What is the strike price\n";
				std::cin >> k;
				if (k < 0.00f || std::cin.fail())
				{
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					k = 65.0;
					std::cout << "Defaulting to stockprice of 65.00\n";
				}
				std::cout << "What is the time of expiration\n";
				std::cin >> exp;
				if (exp < 0.00f || std::cin.fail())
				{
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					exp = 0.25;
					std::cout << "Defaulting to expiration date of 0.25\n";
				}
				std::cout << "What is the volatility\n";
				std::cin >> vol;
				if (vol < 0.00f || std::cin.fail())
				{
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					vol = 0.3;
					std::cout << "Defaulting to volatility of 0.3\n";
				}
				std::cout << "What is the dividend\n";
				std::cin >> dividend;
				if (dividend < 0.00f || std::cin.fail())
				{
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					dividend = 0.00;
					std::cout << "Defaulting to zero dividend\n";
				}
				std::cout << "What is the Option type(-1:put, 1:call)\n";
				std::cin >> optiontype;
				if (optiontype != -1 && optiontype != 1 || std::cin.fail())
				{
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					optiontype = -1;
					std::cout << "Defaulting to put option\n";
				}
				std::cout << "What is the interest rate\n";
				std::cin >> ir;
				if (ir > 10.0 || ir < 0.00f || std::cin.fail())
				{
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					ir = 0.08;
					std::cout << "Defaulting to interest rate of 0.08\n";
				}

				std::cout << "What is the initial stockprice\n";
				std::cin >> stockprice;

				if (stockprice < 0.00 || std::cin.fail())
				{
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					stockprice = 60.0;
					std::cout << "Defaulting to stockprice of 60.0\n";
				}

				//Ask for barrier
				if (sde_type == 2)
				{
					std::cout << "What is the beta " << std::endl;
					std::cin >> beta;
					if (std::cin.fail() || beta > 10.0 || beta < 0.0)
					{
						std::cin.clear();
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						beta = 1.0;
						std::cout << "Defaulting to beta of 1.0f\n";
					}
				}
				//What is the barrier and what is the rebate
				std::cout << "What is the barrier\n";
				std::cin >> barrier;
				if (barrier <= 0.00f || barrier <= k|| std::cin.fail())
				{
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

					barrier = 170.0;
					std::cout << "Defaulting to barrier of 170.0\n";
				}
				std::cout << "What is the rebate\n";
				if (rebate < 0.00f || std::cin.fail())
				{
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					rebate = 0.00f;
					std::cout << "Defaulting to rebate of 0.00\n";
					
				}
				std::cin >> rebate;
				OptionData myOption(
					(OptionParams::strike = k, OptionParams::expiration = exp,
						OptionParams::volatility = vol, OptionParams::dividend = dividend,
						OptionParams::optionType = optiontype, OptionParams::interestRate = ir,
						OptionParams::Stockprice = stockprice, OptionParams::Beta = beta,
						OptionParams::Barrier = barrier, OptionParams::Rebate = rebate)
				);
				McBuilder build(myOption);
				//Create parts and build parts
				auto parts = build.BuildParts(sde_type, rng_type, fdm_type, type_of_option, subdivision);
				medium = Mediator(parts, simulations);
				medium.start();

				break;
			}
		}
		static  void CreateFileProces()
		{
			//First ask for the inmutable parts
			double k = 65.0;
			double expiration = 0.25;
			double vol = 0.3;
			double dividend = 0.0;
			int type_of_option = 1;
			int  optiontype = -1;
			double ir = 0.08;
			double stockprice = 60.0;
			double beta = 1.0;
			double barrier = 0.0;
			double rebate = 0.0;
			//Ask for the user what is the SDE we want,RNG you want/FDM you want
			std::tuple<int, int, int, int, int>type = inmutableparts();
			int sde_type = std::get<0>(type);
			int rng_type = std::get<1>(type);
			int fdm_type = std::get<2>(type);
			int subdivision = std::get<3>(type);
			int simulations = std::get<4>(type);
			//Make sure file stream is open for input
			std::ifstream fileinput("Input.csv", std::ios::in);
			std::string line;
			std::vector<std::string>line_data;
			//Specifies line count
			bool first_line = true;
			//forget the first line
			std::getline(fileinput, line);
			while (std::getline(fileinput, line))
			{
				//Split in commas for each line.Store the result into line data of the vector
				boost::algorithm::split(line_data, line, boost::algorithm::is_any_of(","));
				//This is the necessary data regardless optiontype of stochastic differnatial equation

				//Try catch any possible arguments that might lead to  exception. We have to change if the arguments provided by the user is incorrect 
				try {
					k = std::stod(line_data[0]);
					if (k <= 0.00)
						throw std::invalid_argument("Invalid strike,Defaulting to regular\n");
				}
				catch (const std::invalid_argument& arg)
				{
					std::cout << arg.what();
					k = 65.0;
				}
				try
				{
					expiration = std::stod(line_data[1]);
					if (expiration <= 0.00)
						throw std::invalid_argument("Invalid expiration date,Defaulting to regular\n");
				}
				catch (const std::invalid_argument& arg)
				{
					expiration = 0.25;
					std::cout << arg.what();
				}
				try
				{
					vol = std::stod(line_data[2]);
					if (vol < 0.00)
						throw std::invalid_argument("Invalid volatility,Defaulting to regular\n");
				}
				catch (const std::invalid_argument& arg)
				{
					std::cout << arg.what();
					vol = 0.3;
				}
				try
				{
					dividend = std::stod(line_data[3]);
					if (dividend < 0)
						throw std::invalid_argument("Invalid dividend,Defaulting to regular\n");
				}
				catch (const std::invalid_argument& arg)
				{
					std::cout << arg.what();
					dividend = 0.00;
				}
				try {
					ir = std::stod(line_data[4]);
					if (ir < 0 || ir > 10.0)
						throw std::invalid_argument("Invalid interest rate,Defaulting to regular\n");
				}
				catch (const std::invalid_argument& arg)
				{
					std::cout << arg.what();
					ir = 0.08;
				}
				try
				{
					stockprice = std::stod(line_data[5]);
					if (stockprice < 0.00)
						throw std::invalid_argument("Invalid stock price,defaulting to regular\n");
				}
				catch (const std::invalid_argument& arg)
				{
					std::cout << arg.what();
					stockprice = 60.0;
				}
				try
				{
					optiontype = std::stoi(line_data[6]);
					if (optiontype != -1 && optiontype != 1)
						throw std::invalid_argument("Invalid option type,defaulting to regular\n");
				}
				catch (const std::invalid_argument& arg)
				{

					std::cout << arg.what();
					optiontype = -1;
				}
						

				//If we have  CEV MODEL then we have to ask for the beta as well
				if (sde_type == 2)
				{
					try {
						beta = std::stod(line_data[7]);
						if (beta < 0.00 || beta > 10.0)
							throw std::invalid_argument("Invalid beta,Defaulting to regular\n");
					}
					catch (const std::invalid_argument& arg)
					{
						std::cout << arg.what();
						beta = 1.0;
					}
				}

				//Get the type of option
				try {
					type_of_option = std::stoi(line_data[8]);
				}
				catch (const std::invalid_argument& arg)
				{
					std::cout << arg.what();
					type_of_option = 1;
				}
				
				if ( type_of_option == 3)
				{
					//If we have the type_of_option is a barrier then we have we ask for rebate and barrier
					try
					{
						barrier = std::stod(line_data[9]);
						if (barrier <= 0.00 || barrier <= k)
							throw std::invalid_argument("Not a valid barrier\n");
					}
					catch (const std::invalid_argument& arg)
					{
						std::cout << arg.what();
						barrier = 170.0;
					}
					try
					{
						rebate = std::stod(line_data[10]);
						if (rebate < 0)
							throw std::invalid_argument("Not a valid rebate\n");
					}
					catch(const std::invalid_argument&arg)
					{
						std::cout << arg.what();
						barrier = 0;
					}
					
				}
				//If we have that this the first line. We need to to build the parts
					//Place the data into my option
				OptionData myOption(
					(OptionParams::strike = k, OptionParams::expiration = expiration,
						OptionParams::volatility = vol, OptionParams::dividend = dividend,
						OptionParams::optionType = optiontype, OptionParams::interestRate = ir,
						OptionParams::Stockprice = stockprice, OptionParams::Beta = beta,
						OptionParams::Barrier = barrier, OptionParams::Rebate = rebate)
				);
				McBuilder build(myOption);

				//If its the first time build parts  and store them nto medator 
				if (first_line)
				{
					
					//Create parts and build parts
					auto parts = build.BuildParts(sde_type, rng_type, fdm_type, type_of_option, subdivision);
					medium = Mediator(parts, simulations);
					medium.start();
					//Write to file of the simulation number and then the price
					medium.WriteToFile();
					first_line = false;
				}
				else
				{
					//Buil  the parts aside from the RNG. RNG is a very expensive resource to be constantly reinstaniating 
					auto sde = build.BuildSde(sde_type);
					auto fdm = build.BuildFdm(sde, subdivision, fdm_type);
					auto pricer = build.BuildPricer(type_of_option);
					//Change EQ/Method/PRICER
					medium.eq = sde;
					medium.method = fdm;
					medium.type = pricer;
					//start the process 
					medium.start();
					medium.WriteToFile();

				}
			}
		}
		//the starting process of the 
		void StartProcess()
		{
			std::cout << "********************FDM PRICING APPLICATION********************\n";
			std::cout << "Welcome to the Option pricing application\n";
			std::cout << "If your data needs more than 1 input.Please put the data into the Input.csv.\n";
			std::cout << "INSTRUCTIONS(FOR FILE IMPORT): In each row specify the proper data as specified by the column\n";
			std::cout << "INSTRUCTIONS(FOR CONSOLE IMPORT/INPUTS): TYPE IN THE INTEGER VALUES OF PARTS YOU WANT\n";
			std::cout << "NO matter which data input the user will always be asked by console input sde/Rng/Fdm/#numbersubdivisions/#simulations\n";
			std::cout << "********************FDM PRICING APPLICATION ********************\n";
		
			std::cout << "Will the data be imported through  a CSV file (y/n)\n";
			char test = 'N';
			std::cin >> test;
	
			//Swtich between if 
			
			switch (std::toupper(test))
			{
			default:
			case 'N':
			{  createConsoleProcess();
			   break;
			}
			case 'Y':
			{	CreateFileProces();
				break;
			}
			}
		}
	}
}
#endif // ! FILEIMPORTER_HPP