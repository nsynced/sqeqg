#include <iostream>
#include <fstream>
#include <ctime>
#include <cmath>
#include <sstream>
#include <cxxopts.hpp>

#include "SQEQGenerator.h"

#if (defined __MINGW32__ || defined __MINGW64__)
#define CLEAR_SCREEN_COMMAND "cls"
#elif __GNUC__
#define CLEAR_SCREEN_COMMAND "clear"
#else
#define CLEAR_SCREEN_COMMAND ""
#endif

SQEQGenerator::SQEQGenerator()
{
	srand((unsigned int)time(NULL));
	outputFileName = "";
	number = 1;
	printSolutions = false;
	maxA = 5;
	maxX = 15;
}

void SQEQGenerator::Run(int argc, char *argv[]) {
	this->argc = argc;
	this->argv = argv;

	if(!HandleArgs())
		exit(1);

	if (mode == SQEQGenerator::Mode::List)
		ListMode();
	else OneByOneMode();
}

/* Handles command line arguments and returns true if
 * successful but false otherwise */
bool SQEQGenerator::HandleArgs() {
	try {
		cxxopts::Options options(argv[0], "Simple Quadratic Equation Generator");
		options.add_options()
			("l,list", "Enables list mode")
			("h,help", "Shows this page")
			("x,max-x", "Sets the maximum value of X1,X2", cxxopts::value<int>(maxX))
			("a,max-a", "Sets the maximum value of the A coefficient", cxxopts::value<int>(maxA))
			("f,file", "Sets output file name", cxxopts::value<std::string>(outputFileName))
			;
		options.add_options("List mode only")
			("s,print-solutions", "Prints tasks with solutions", cxxopts::value<bool>(printSolutions))
			("n,number", "Sets the number of tasks to be written", cxxopts::value<unsigned int>(number))
			;
		options.parse(argc, argv);

		if (options.count("help")) {
			std::cout << options.help({ "", "List mode only" }) << std::endl;
			exit(0);
		}

		if (options.count("list"))
			mode = SQEQGenerator::Mode::List;
		else mode = SQEQGenerator::Mode::OneByOne;

	}
	catch (const cxxopts::OptionException& e) {
		std::cout << "Error parsing options: " << e.what() << std::endl;
		return false;
	}

	return true;
}

/* Start a print task -> print the answer loop  */
void SQEQGenerator::OneByOneMode() const
{
	std::pair<std::string, std::string> task;

	while (true) {
		system(CLEAR_SCREEN_COMMAND);
		task = GetTask();
		std::cout << task.first;
		getchar();
		std::cout << task.second << std::endl;
		getchar();
	}
}

void SQEQGenerator::ListMode() const
{
	unsigned int n = number;
	std::pair<std::string, std::string> task;
	std::ofstream outf(outputFileName);

	if (!outf.is_open()) {
		std::cout << "Can't open " << outputFileName << " file" << std::endl;
		exit(1);
	}

	while (n--) {
		task = GetTask();
		outf << task.first << std::endl;
		if (printSolutions)
			outf << task.second << std::endl;
	}

	outf.flush();
	outf.close();

	std::cout << "Done!" << std::endl;
	exit(0);
}

/* It generates a full quadratic equation + the answer
a*x^2 + b*x + c = 0 <=> a(x - x1)(x - x2) = 0
b = -a(x1 + x2)
c = -a(x1 * x2)
{ x1 + x2 = -b
{ x1 * x2 = c
*/
std::pair<std::string, std::string> SQEQGenerator::GetTask() const
{
	int x1, x2, a, b, c;
	std::stringstream task, answer;

	x1 = GetRandomSignedNumInRange(-maxX, maxX);
	x2 = GetRandomSignedNumInRange(-maxX, maxX - 1);
	if (x2 == -x1) // Exclude incomplete equations
		x2 = maxX;
	a = GetRandomSignedNumInRange(-maxA, maxA);
	b = -a*(x1 + x2);
	c = a * x1 * x2;

	task << GetSignOfNumber(a) << abs(a) << "x^2 ";
	task << GetSignOfNumber(b) << " " << abs(b) << "x ";
	task << GetSignOfNumber(c) << " " << abs(c) << " = 0";
	answer << "x1 = " << x1 << ", x2 = " << x2;

	return std::pair<std::string, std::string>(task.str(), answer.str());
}

// Generates a random signed number with a random sign in the given range
//                                           >=         <=
int SQEQGenerator::GetRandomSignedNumInRange(int min, int max) const
{
	unsigned range = (max + 1) - min;
re:
	int x = min + rand() % range;

	if(!x)
		goto re;

	return x;
}

inline std::string SQEQGenerator::GetSignOfNumber(int number) const
{
	return number < 0 ? "-" : "+";
}
