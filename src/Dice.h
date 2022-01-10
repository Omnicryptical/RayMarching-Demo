#pragma once

#include <random>

class Die {

public:

	static int seed;

	static std::mt19937 rng;

	static int rollInt(int low, int high);

	static int rollTrueInt(int low, int high);

	static float rollFloat(float low, float high);

};