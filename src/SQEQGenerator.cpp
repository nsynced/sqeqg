#include <iostream>
#include <fstream>
#include <ctime>
#include <cmath>
#include <sstream>

#include "SQEQGenerator.h"

#define CLEAR_SCREEN_COMMAND "clear"

#define A_MIN_VALUE 1
#define X1_MIN_VALUE 5
#define X2_MIN_VALUE X1_MIN_VALUE

SQEQGenerator::SQEQGenerator()
{
	srand((unsigned int)time(NULL));
	SetMode();
	SetMaxValues();

	if (CurrentMode == SQEQGenerator::Mode::OneByOne)
		OneByOneMode();
	else ListMode();
}

void SQEQGenerator::SetMode()
{
	int in;

	do {
		std::cout << "Choose mode(OneByOne = 0, List = 1): ";
		std::cin >> in;
	} while(in != 0 && in != 1);

	CurrentMode = SQEQGenerator::Mode(in);
}

void SQEQGenerator::SetMaxValues()
{
	do
	{
		std::cout << "Enter maximum value of x1(> " << X1_MIN_VALUE << "): ";
		std::cin >> MaxX1;
	} while(MaxX1 <= X1_MIN_VALUE);

	do
	{
		std::cout << "Enter maximum value of x2(> " << X2_MIN_VALUE << "): ";
		std::cin >> MaxX2;
	} while(MaxX2 <= X2_MIN_VALUE);

	do
	{
		std::cout << "Enter maximum value of a(> " << A_MIN_VALUE << "): ";
		std::cin >> MaxA;
	} while(MaxA <= A_MIN_VALUE);
}

/* Start a print task -> print the answer loop  */
void SQEQGenerator::OneByOneMode() const
{
	std::pair<std::string, std::string> task;

	while (true) {
		system(CLEAR_SCREEN_COMMAND);
		task = GetTask();
		std::cout << task.first << std::endl;
		getchar();
		std::cout << task.second << std::endl;
		getchar();
	}
}

void SQEQGenerator::ListMode() const
{
	unsigned int n, withAnswers;
	std::pair<std::string, std::string> task;
	std::string fname;

	std::cout << "Enter file name: ";
	std::cin >> fname;
	std::cout << "Enter n: ";
	std::cin >> n;

	do {
		std::cout << "With answers? Enter(0 - NO, 1 - YES) and press Enter: ";
		std::cin >> withAnswers;
	} while (withAnswers != 0 && withAnswers != 1);

	std::ofstream outf(fname);

	if(!outf.is_open()) {
		std::cout << "Can't open " << fname << " file" << std::endl;
		return;
	}

	while(n--) {
		task = GetTask();
		outf << task.first << std::endl;
		if(withAnswers)
			outf << task.second << std::endl;
		outf << std::endl;
	}

	std::cout << "Done." << std::endl;

	outf.flush();
	outf.close();
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

	x1 = GetRandomSignedNumInRange(X1_MIN_VALUE, MaxX1);
	x2 = GetRandomSignedNumInRange(X2_MIN_VALUE, MaxX2 - 1);
 	if(x2 == -x1) // Exclude incomplete equations
		x2 = MaxX2;
	a = GetRandomSignedNumInRange(A_MIN_VALUE, MaxA);
	b = -a*(x1 + x2);
	c = -a * x1 * x2;

	task << a << "x^2 ";
	task << GetSignOfNumber(b) << " " << abs(b) << "x ";
	task << GetSignOfNumber(c) << " " << abs(c) << " = 0";
	answer << "x1 = " << x1 << ", x2 = " << x2;

	return std::pair<std::string, std::string>(task.str(), answer.str());
}

// Generates a random signed number with a random sign in the given range
//                                           >=		<= 
int SQEQGenerator::GetRandomSignedNumInRange(int min, int max) const
{
	int x = min + (rand() % (max - min + 1));

	/* Get a random sign for x with probability 1/2 */
	if (rand() % 2)
		x = -x;

	return x;
}

inline std::string SQEQGenerator::GetSignOfNumber(int number) const
{
	return number < 0 ? "-" : "+";
}
