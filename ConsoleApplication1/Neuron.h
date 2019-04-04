#pragma once
#ifndef NEURON
#define NEURON

#include <vector>
class neuron
{
	std::vector <float> ratio;
	float basevalue;
public:
	float getvalue(std::vector <float> values);
	neuron(int a);
	void mutate(int procent);
	neuron();
	~neuron();
};

#endif // !NEURON
