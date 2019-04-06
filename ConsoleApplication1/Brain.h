#ifndef BRAIN
#define BRAIN
#include "game.h"
#include <vector>
#include "neuron.h"

#pragma once
class Brain
{
	std::vector <neuron> middle[2];
	std::vector <neuron> end;

public:
	int GetMove(data a);
	void evolve(int percent);
	Brain();
	~Brain();
};


#endif
