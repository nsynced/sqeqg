#include <string>

class SQEQGenerator
{
public:

	void StartLoop() const;
	SQEQGenerator();

private:
	int MaxX1, MaxX2, MaxA;

	std::pair<std::string, std::string> getTask() const;
	inline std::string getSignOfNumber(int number) const;
	int getRandomSignedNumInRange(int min, int max) const;
};