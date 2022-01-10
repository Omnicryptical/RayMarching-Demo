#include "Dice.h"

int Die::seed = Die::rollTrueInt(0, (int)pow(2, sizeof(int)*8));

//For Debugging
//int Die::seed = ;


std::mt19937 Die::rng = std::mt19937(seed);

int Die::rollInt(int low, int high)
{
	int offset = 0;

	if (low < 0) {
		offset = low;
		high -= low;
		low = 0;
	}

	std::uniform_int_distribution<std::mt19937::result_type> dist(low, high);

	int result = dist(rng);
	result += offset;

	return result;
}

float Die::rollFloat(float low = 0, float high = 1) {

	std::random_device dev;
	std::uniform_real_distribution<> dist(low, high);

	return (float) dist(rng);

}

int Die::rollTrueInt(int low, int high) {

	std::random_device dev;
	std::mt19937 rn(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist(low, high);

	return dist(rn);

}