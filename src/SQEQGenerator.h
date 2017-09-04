#include <string>

class SQEQGenerator
{
public:
	SQEQGenerator();

private:
	enum Mode { OneByOne = 0, List = 1 };

	int MaxX1, MaxX2, MaxA;
	SQEQGenerator::Mode CurrentMode;

	void SetMaxValues();
	void SetMode();
	void OneByOneMode() const;
	void ListMode() const;
	std::pair<std::string, std::string> GetTask() const;
	inline std::string GetSignOfNumber(int number) const;
	int GetRandomSignedNumInRange(int min, int max) const;
};
