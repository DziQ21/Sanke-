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

#define MUTATIONTATIO 90
#define SIZEOFPOPULATION 200

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
	numberofmoves = 40 + (generation / 10) * 3;
	for (int i = 0; i < numberofmoves; i++)
	{
		for (int j = 0; j < SIZEOFPOPULATION; j++)
			populationgames[j].Play(population[j].GetMove(populationgames[j].GetData()));
	}
	while (true) {
		int pos;
		int value=0;
		
		for (int i = 0; i < SIZEOFPOPULATION; i++) {
			value = 0;
			for (int j = 0; j < SIZEOFPOPULATION-i-1; j++)
			{
				if (populationgames[j].GetPoints()< populationgames[j+1].GetPoints())
				{
					std::swap(population[j], population[j+1]);
					std::swap(populationgames[j], populationgames[j+1]);
				}
			}
		}
		LastBest = population[0];
		gameofbest = game();
		
		for (int i = SIZEOFPOPULATION/2; i < SIZEOFPOPULATION; i++)
		{
			population[i] = population[SIZEOFPOPULATION-1 - i];
			population[i].evolve(MUTATIONTATIO);
		}
		for (int i = SIZEOFPOPULATION/4 ; i < SIZEOFPOPULATION/2; i++)
		{
			
			population[i].evolve(MUTATIONTATIO/10);
		}
		for (int i = 0; i < SIZEOFPOPULATION; i++)
		{
			populationgames[i] = game();
		}
		numberofmoves = 40 + (++generation / 20) * 3;
		for (int i = 0; i < numberofmoves; i++)
		{
			for (int j = 0; j < SIZEOFPOPULATION; j++)
				if (populationgames[j].GetRuning())
					populationgames[j].Play(population[j].GetMove(populationgames[j].GetData()));
				else
					Sleep(1);
				
			gameofbest.Play(LastBest.GetMove(gameofbest.GetData()));
			system("cls");
			std::cout << "=====" << generation << "======\n\n" << gameofbest.Display();
			Sleep(5);

		}


		
	}

	return 0;
}

