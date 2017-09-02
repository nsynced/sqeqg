#include <iostream>
#include <ctime>
#include <cmath>
#include <sstream>

#include "SQEQGenerator.h"

#define WINDOWS_CLEAR_SCREEN_COMMAND "CLS"
#define WINDOWS_PAUSE_COMMAND "pause >nul"
#define ENTER_MAX_VALUE(name, value) std::cout << "Enter maximum value of " name ": "; std::cin >> value

#define A_MIN_VALUE 2
#define X1_MIN_VALUE 5
#define X2_MIN_VALUE X1_MIN_VALUE

SQEQGenerator::SQEQGenerator()
{
	srand((unsigned int)time(NULL));
	ENTER_MAX_VALUE("x1", MaxX1);
	ENTER_MAX_VALUE("x2", MaxX2);
	ENTER_MAX_VALUE("a", MaxA);
}

/* Start a print task -> print the answer loop  */
void SQEQGenerator::StartLoop() const
{
	std::pair<std::string, std::string> task;

	while (true) {
		system(WINDOWS_CLEAR_SCREEN_COMMAND);
		task = getTask();
		std::cout << task.first << std::endl;
		system(WINDOWS_PAUSE_COMMAND);
		std::cout << task.second << std::endl;
		system(WINDOWS_PAUSE_COMMAND);
	}
}

/* It generates a full quadratic equation + the answer
	a*x^2 + b*x + c = 0 <=> a(x - x1)(x - x2) = 0
	b = -a(x1 + x2)
	c = -a(x1 * x2)
	{ x1 + x2 = -b
	{ x1 * x2 = c
*/
std::pair<std::string, std::string> SQEQGenerator::getTask() const
{
	int x1, x2, a, b, c;
	std::stringstream task, answer;

	x1 = getRandomSignedNumInRange(X1_MIN_VALUE, MaxX1);
	x2 = getRandomSignedNumInRange(X2_MIN_VALUE, MaxX2);
	a = getRandomSignedNumInRange(A_MIN_VALUE, MaxA);
	b = -a*(x1 + x2);
	c = -a * x1 * x2;

	task << a << "x^2 ";
	task << getSignOfNumber(b) << " " << abs(b) << "x ";
	task << getSignOfNumber(c) << " " << abs(c) << " = 0";
	answer << "x1 = " << x1 << ", x2 = " << x2;

	return std::pair<std::string, std::string>(task.str(), answer.str());
}

// Generates a random signed number with a random sign in the given range
//                                           >=		<= 
int SQEQGenerator::getRandomSignedNumInRange(int min, int max) const
{
	int x = (min - 1) + (rand() % (max - min + 1));

	/* Get a random sign for x with probability 1/2 */
	if (rand() % 2)
		x = -x;

	return x;
}

inline std::string SQEQGenerator::getSignOfNumber(int number) const
{
	return number < 0 ? "-" : "+";
}
