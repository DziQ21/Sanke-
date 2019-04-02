#pragma once
#ifndef NEURON
#define NEURON
#define RANGE 20;

#include <vector>
class neuron
{
	std::vector <float> ratio;
	float basevalue;
	float value;
public:
	neuron(int a);
	void mutate(int procent);
	neuron();
	~neuron();
};

#endif // !NEURON
