#pragma once
class Random {
public:
	Random(bool pseudo = true);
	double random_real();
	int random_integer(int low, int high);
	int poisson(double mean);
private:
	int reseed();
	int seed, multiplier, add_on;
};

