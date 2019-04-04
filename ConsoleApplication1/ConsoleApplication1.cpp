// ConsoleApplication1.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//


#include "pch.h"
#include <iostream>
#include <string>
#include "game.h"
#include <cstdlib>
#include <ctime>
#include "Brain.h"
#include <Windows.h>
#include <algorithm>

#define MUTATIONTATIO 10
#define SIZEOFPOPULATION 100

int main()
{
	int generation=0;
	int numberofmoves;
	srand(time(NULL));
	//initializing
	Brain population[SIZEOFPOPULATION];
	game populationgames[SIZEOFPOPULATION];
	Brain LastBest;
	game gameofbest;
	//first play;
	numberofmoves = 20 + (generation % 5) * 10;
	for (int i = 0; i < numberofmoves; i++)
	{
		for (int j = 0; j < SIZEOFPOPULATION; j++)
			populationgames[j].Play(population[j].GetMove(populationgames[j].GetData()));
	}
	while (true) {
		int pos;
		int value=0;
		for (int i = 0; i < SIZEOFPOPULATION; i++)
		{
			if (populationgames[i].GetPoints() >= value)
			{
				value = populationgames[i].GetPoints();
				pos = i;
			}
		}
		LastBest = population[pos];
		gameofbest = game();
		for (int i = 0; i < SIZEOFPOPULATION; i++) {
			value = 0;
			for (int j = i; j < SIZEOFPOPULATION; j++)
			{
				if (populationgames[j].GetPoints() >= value)
				{
					value = populationgames[j].GetPoints();
					pos = i;
				}
			}
			std::swap(population[i], population[pos]);
			std::swap(populationgames[i], populationgames[pos]);
		}
		for (int i = 50; i < SIZEOFPOPULATION; i++)
		{
			population[i].evolve(MUTATIONTATIO);
		}
		for (int i = 0; i < SIZEOFPOPULATION; i++)
		{
			populationgames[i] = game();
		}
		numberofmoves = 30 + (++generation % 5) * 10;
		for (int i = 0; i < numberofmoves; i++)
		{
			for (int j = 0; j < SIZEOFPOPULATION; j++)
				populationgames[j].Play(population[j].GetMove(populationgames[j].GetData()));
			gameofbest.Play(LastBest.GetMove(gameofbest.GetData()));
			system("cls");
			std::cout << "=====" << generation << "======\n\n" << gameofbest.Display();
			Sleep(50);

		}


		Sleep (0);
	}

	return 0;
}

