#include "pch.h"
#include "neuron.h"
#include <cstdlib>
#include <ctime>
neuron::neuron()
{
}
neuron::neuron(int a)
{
	ratio.resize(a);

}

void neuron::mutate(int procent)
{
	srand(time(NULL));
	if (rand() % 101 <= procent)
		basevalue = (float)(rand() % 10 *20 /*RANGE*/)/10;
	for (int i = 0; i < ratio.size(); i++)
	{
		if (rand() % 101 <= procent)
			ratio[i] = (float)(rand() % 10 * 20 /*RANGE*/) / 10;
	}
}


neuron::~neuron()
{
}
