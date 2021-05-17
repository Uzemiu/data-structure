#pragma once

#include <time.h>
#include <iostream>

using namespace std;

class Random {
public:
	Random(bool pseudo = false) {
		if (pseudo) seed = 1;
		else seed = time(NULL) % INT_MAX;
		multiplier = 2743;
		add_on = 5923;
	}
	double random_real() {
		double max = (double)INT_MAX + 1;
		double temp = reseed();
		if (temp < 0) temp += max;
		return temp / max;
	}

	int random_integer(int low, int high) {
		if (low > high) return random_integer(high, low);
		return (int)((high - low) * random_real()) + low;
	}

	int poisson(double mean) {
		double limit = exp(-mean);
		double product = random_real();
		int count = 0;
		while (product > limit) {
			count++;
			product *= random_real();
		}
		return count;
	}
private:
	int seed, multiplier, add_on;
	int reseed() {
		seed = seed * multiplier + add_on;
		return seed;
	}
};

void randomNumber(double d, int n) {
	Random random(false);
	int sum = 0;
	cout << "产生随机序列：" << endl;
	for (int i = 1; i <= n; i++) {
		int r = random.poisson(d);
		sum += r;
		cout << r << " ";
	}
	cout << "随机数平均值：" << (sum / (double)n) << endl;
}

