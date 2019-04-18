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

#define MUTATIONTATIO 30
#define SIZEOFPOPULATION 120

int main()
{
	int generation=0;
	
	
	//initializing
	Brain population[SIZEOFPOPULATION];
	game populationgames[SIZEOFPOPULATION];
	
	
	
	while (true) {

		int tracked=0;
		
		int value=0;
		
		
		while(1)
		{
			if (!populationgames[tracked].GetRuning())
			{
				bool runningfound=0;
				for(int j = 0; j < SIZEOFPOPULATION; j++)
					if (populationgames[j].GetRuning())
					{
						tracked = j;
						runningfound = 1;
						break;
					}
				if (runningfound == 0)
					break;
			}
			for (int j = 0; j < SIZEOFPOPULATION; j++)
				if (populationgames[j].GetRuning())
					populationgames[j].Play(population[j].GetMove(populationgames[j].GetData()));
				else 
					Sleep(1);
				
			//populationgames[tracked].Play(population[0].GetMove(populationgames[tracked].GetData()));
			system("cls");
			std::cout << "=====" << generation << "======\nosobnik:"<<tracked<<"\n" << populationgames[tracked].Display()<<populationgames[tracked].GetMoves() ;
			Sleep(5);

		}

		generation++;
		
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
		std::cout << "test" << populationgames[0].GetPoints()<<"  "<< populationgames[SIZEOFPOPULATION-1].GetPoints();
		Sleep(2000);
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
	}

	return 0;
}

