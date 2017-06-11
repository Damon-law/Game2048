#pragma once
#ifndef RANDOM_H_
#define RANDOM_H_
#include <iostream>
#include <ctime>
class Random
{
public:
	Random();
	double GetRandom(double start,double end);
};
Random::Random()
{
	srand(unsigned int(time(0)));
}
double Random::GetRandom(double start,double end)
{
	return start + (end - start)*rand() / (RAND_MAX + 1.0);
}
#endif // !RANDOM_H_
