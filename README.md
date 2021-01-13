# MonteCarloOptionPricer
This is Monte Carlo Application that  uses various Options/FDM/RNG/PRICER

# FDM option APPLICATION OVERVIEW
Name: William Zhang
## 1.OVERVIEW
The FDM option pricing application is for pricing various options such Asian, European and Barrier Option using various Finite Difference method. The application allows the user to input various Option pricing parameter such as stock price, strike price, risk-free interest rate  to price options using the various Finite Difference Methods. The application even allows the user to use various Random number generators such as Mersenne Twister, Polar Masglia and Bob Mueller.  Finally, the user can input the data by console or by putting the data inside the input.csv. If the user wishes to put more than one option dataset parameters, then the user should put the data into the input.csv
## 2.CLASS OVERVIEW
The user can see the class diagram hosted inside in the Solution Explorer, by opening the project solution folder and view ClassDiagram.cd. The following are a set of description of the various classes used in the application.  
### 1.RNG
This class essentially generates a random number that follows a normal distribution with mean zero and variance one. The user can select between various generators such as Mersenne Twister, Polar Masglia and Box Mueller. The latter two transforming uniform random numbers from zero to one to a normal distribution with polar form.
### 2.SDE
This class specifies which types of stochastic differential equation that the user wants. The user is able to choose between the contrast elasticity variance model (CEV) and the Geometric Brown Motion Differential equation (GBM). The former being similar to GBM but there is a specified Beta that model the elasticity of volatility in relation to stock price.
### 3.FDM
This class solves the Stochastic differential equation   by allowing the user to choose the Finite difference method to solve the differential equation. The user can use choose explicit Euler, Balanced Midpoint, and Milstein Method to solve the differential equation
### 4. PRICER
This class models the various types of options that the user can choose. Different options have different payout schemes. The user can choose between the various option such as the classical European, The Asian, or Barrier Options.
### 5. BUILDER
This class essentially coalesces all the various the parts the user want and builds the appropriate RNG,SDE,PRICER,and FDM objects to start the Finite Difference method application. The parts are created and stored into a tuple 
### 6.MEDIATOR
The parts made from the Builder class must be mediated because the parts made from Builder have complex interactions. Therefore, we have a mediator to resolve these interactions inside a STRUCT to generate an output. The LOOP in the start function is parallelized with Pragma OMP to improve speed.
### 7.FILEIMPORTER
This header file is the application input point and is by far the largest file. This file allows the user the start the application and allows the user to choose input data by console or by File.  The user also must specify the #NSIM and #NUMBER of trials as well as which parts they want in the application. This is where the mediator does most of its work.
## 3.COMPLEXITY/PERFORMANCE/OUTPUT
Most of the work performed is the double for loop inside the Mediator start function. So in general the time complexity of this program is O(NSIM* SUBDVISIONS). Which is quadratic and in general has a convergence that is linear.  For inputs NSIM*subdivisions >= 5,000,000 performance  to starts to deteriorate. Therefore we incorporated multi-threading that is provided by  OMP parallelization library.

_Across all option parameter inputs the  NSIM  was  1,000,000 and subdivisions steps were  500_
_As evidence for the  running time, run the application with the default parameters provided in the input.csv_

__WITHOUT MULTITHREADING:__
__Avg Time to completion :  90.6-98 seconds__
__NSIM: 1000000 NT:500__

_Total time: 87.0217_
Output # 1 Price: 5.71458

_Total time: 92.582_
Output # 2 Price: 2.2088

_Total time: 98.522_
Output # 3 Price: 7.7895

_Total time: 90.39_
Output # 4 Price: 94.1845

_Total time: 89.9149_
Output # 5 Price: 1.22124

_Total time: 89.6994_
Output # 6 Price: 4.04489

_Total time: 98.1227_
Output # 7 Price: 0.209067_

__With Multithreading (OMP)__
__Avg Time to completion: 32-42 seconds__
__NSIM: 1000000 NT:500__

_Total time: 29.0217_
Output # 1 Price: 5.71458

_Total time: 31.5582_
Output # 2 Price: 2.2088

_Total time: 32.5722_
Output # 3 Price: 7.7895

_Total time: 34.639_
Output # 4 Price: 94.1845

_Total time: 34.9149_
Output # 5 Price: 1.22124

_Total time: 36.6994_
Output # 6 Price: 4.04489

_Total time: 37.4527_
Output # 7 Price: 0.209067

As you can see here the performance was increased by 50 percent with OMP parallelization tools. The user can choose his own parameter schemes to check the accuracy of the application. I also tested the version with Asian options and maintained __0.02 - 0.03__ cent accuracy. And here is CD provided by the MSVC. 

![__Contest Diagram__](https://github.com/jetpotion/MonteCarloOptionPricer/blob/master/ClassDiagram.png)

# Mathematical Models implemented  used for RNG
## Polar Masglia 
![__Polar Masglia__](https://github.com/jetpotion/MonteCarloOptionPricer/blob/master/Capture.PNG)
## Box Mueller
![__Box Mueller__](https://github.com/jetpotion/MonteCarloOptionPricer/blob/master/Capture_2.PNG)

## Mersenne Twister 
![__Mersenne Twister__](https://github.com/jetpotion/MonteCarloOptionPricer/blob/master/Capture_3.PNG)

# Finite Method Solution  schemes used in FDM
![__FDMMETHODS__](https://github.com/jetpotion/MonteCarloOptionPricer/blob/master/Capture_4.PNG)

# Constrast elasticitity variance Model Stochastic Differential Equation
![__CEV MODEL__](https://github.com/jetpotion/MonteCarloOptionPricer/blob/master/Capture_5.PNG)

# APPLICATION USER SET UP (VERY IMPORTANT)
1. The user must have MSVC C++ as well install boost libraries. Here is the link to boost and visual studio 2017. But the user should install the lastest version of their respected software 
https://www.badprog.com/c-boost-setting-up-on-windows-10
2. If the user wants to use other C++ editors then the user should also install and link omp seperately as well as text editors that supports msvc compiler for C++
https://www.geeksforgeeks.org/openmp-introduction-with-installation-guide/
3. Once you are done with either or both steps, clone the repository with the provided link above.
4. Start the application by running the .exe file or clicking "start without debugging in C++" in microsoft visual studio code.
5. If the user wants to put in multiple  set of option parameter inputs, then the user has to modify the "input.csv" files provided in the project directly. From there, you will be able to modify the parameter of your option prices
6. The user can instead opt out and  type all the parameters of the option price by console instead.
7. The user will first be prompted to choose between the random number generator type, finite difference method type and the the model for the stochastic differential equation. The user will also have to specify the number of time steps and number of subdivisions. Note that larger subdivision and time steps lead to slower computation times.
8. If the user wants to type in the input for a single set of option parameter than the user  will be prompted to do so.
9. The simulation wil begin after the user has done steps 4-8. If the user put their inputs inside the "input.csv" the the output will be  printed out on  "Output.csv" as well as on the console.
10. The option prices and simulation number will printed for convience.
# IF THE USER WANTS TO CONTRIBUTE
If the user wants to add additional finite difference methods scehemes, stochastic diffierential equations,random number generator types or add additional types of options for this application then fork over the repository and make the necessary changes. The user must directly inherit from the classes that  The application is not limited to option prices. There are various Stochastic differential equation that need to be solved from various engineering problems such as  calculating the total price of a home heating syste,. SDE are not only applicable to  risk free finance but other aspects of mechanical ,civil, pretoleum , and economics. Here is an article and see if your engineering problem has a stochastic differential equation that needs to be solved .https://en.wikipedia.org/wiki/Stochastic_differential_equation
