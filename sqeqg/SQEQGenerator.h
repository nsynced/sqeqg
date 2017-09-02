#include <string>

class SQEQGenerator
{
public:
	SQEQGenerator();

private:
	enum Mode { OneByOne = 0, List = 1 };

	int MaxX1, MaxX2, MaxA;
	SQEQGenerator::Mode mode;

	void setMode();
	void oneByOneMode() const;
	void listMode() const;
	std::pair<std::string, std::string> getTask() const;
	inline std::string getSignOfNumber(int number) const;
	int getRandomSignedNumInRange(int min, int max) const;
};