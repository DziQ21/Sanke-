#ifndef NEURON
#define NEURON
#include <vector>

struct Valued_Neuron
{
	float value;
	Neuron orginal;
};

class Neuron
{
public:
	Neuron();
	~Neuron();
	std::vector <Valued_Neuron*> Before;
	int num_of_before_neurons;

private:

};
#endif // !NEURON
