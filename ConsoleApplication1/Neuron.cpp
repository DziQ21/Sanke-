


#include "pch.h"

#include "neuron.h"
#include <cstdlib>
#include <ctime>
#include <cmath>

//neuron::neuron()
//{
	

//}
float neuron::getvalue(std::vector<float> values)
{
	float argument=basevalue;
	for (int i = 0; i < this->ratio.size(); i++)
	{
		argument = argument + values[i] * this->ratio[i];
	}

	return  (argument*2/3)/(1+abs(argument*2/3));//fast sigmoid func *2/3 if to make it less acurate
}
neuron::neuron(int a)
{
	ratio.resize(a);
	basevalue = (float)(rand() % (20 * 10) /*RANGE*/) / 10-10;
	for (int i = 0; i < ratio.size(); i++)
	{
		ratio[i] = (float)(rand() % (20 * 10) /*RANGE*/) / 10 -10;
	}
}



void neuron::mutate(int procent)
{
	srand(time(NULL));
	if (rand() % 101 <= procent)
		basevalue += (float)(rand() %( 20 *10) /*RANGE*/)/10-10;
	for (int i = 0; i < ratio.size(); i++)
	{
		if (rand() % 101 <= procent)
			ratio[i] += (float)(rand() % (20 * 10) /*RANGE*/) / 10-10;
	}
}


neuron::~neuron()
{
}





