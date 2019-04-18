#include "pch.h"
#include "Brain.h"
#include "neuron.h"


std::vector <float> getvalues(std::vector <neuron> data, std::vector <float> beforevalues)
{
	std::vector <float> result;
	for (int i = 0; i < data.size(); i++)
	{
		result.push_back(data[i].getvalue(beforevalues));
	}
	return result;
}

int Brain::GetMove(data a)
{
	std::vector <float> prepareddata;
	for (int i = 0; i < 8; i++)
	{
		prepareddata.push_back(a.wall[i]);
	}
	for (int i = 0; i < 8; i++)
	{
		prepareddata.push_back(a.food[i]);
	}
	for (int i = 0; i < 8; i++)
	{
		prepareddata.push_back(a.body[i]);
	}
	std::vector <float> bufer;
	bufer = getvalues(middle[0],prepareddata);
	bufer = getvalues(middle[0], bufer);
	bufer = getvalues(end, bufer);
	int pos1;
	int pos2;
	if (bufer[0] >= bufer[1])
		pos1 = 0;
	else
		pos1 = 1;

	if (bufer[2] >= bufer[3])
		pos2 = 2;
	else
		pos2 = 3;

	if (bufer[pos1] >= bufer[pos2])
		return pos1;
		return pos2;



}

void Brain::evolve(int percent)
{
	for (int i = 0; i < 50; i++)
		middle[0][i].mutate(percent);
	for (int i = 0; i < 50; i++)
		middle[1][i].mutate(percent);
	for (int i = 0; i < 4; i++)
		end[i].mutate(percent);
}

Brain::Brain()
{

	for (int i = 0; i < 50; i++)
		middle[0].push_back(neuron(24));
	for (int i = 0; i < 50; i++)
		middle[1].push_back(neuron(50));
	for (int i = 0; i < 4; i++)
		end.push_back(neuron(50));
}


Brain::~Brain()
{
}
