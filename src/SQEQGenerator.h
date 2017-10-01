#ifndef SQEQGENERATOR_H_
#define SQEQGENERATOR_H_

#include <string>

class SQEQGenerator
{
public:
	SQEQGenerator();
	void Run(int argc, char *argv[]);

private:
	enum Mode { OneByOne = 0, List = 1 };

	int maxX, maxA;
	int argc;
	unsigned int number;
	char **argv;
	std::string outputFileName;
	SQEQGenerator::Mode mode;
	bool printSolutions;

	void OneByOneMode() const;
	void ListMode() const;
	bool HandleArgs();
	std::pair<std::string, std::string> GetTask() const;
	inline std::string GetSignOfNumber(int number) const;
	int GetRandomSignedNumInRange(int min, int max) const;
};

#endif /* SQEQGENERATOR_H_ */
