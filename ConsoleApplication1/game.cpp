#include "pch.h"
#include "game.h"
#include <string>
#include <iostream>


game::game()
{
}


game::~game()
{
}

data game::GetData()
{



	return data();
}

void game::Play(Direction)
{


}

void game::Display()
{
	char screen[HEIGHT][WIDTH];
	for (int i = 0; i < HEIGHT; i++)
		for (int j = 0; j < WIDTH; j++)
			screen[i][j] = ' ';

	//for (int i = 0; i < Body.size(); i++)
	//	screen[Body[i].y][Body[i].x]='X';

	//screen[Food.y][Food.x] = '@';
	//screen[Body[HeadPosition].y][Body[HeadPosition].x] = 'O';

	std::string bufer;
	for (int i = 0; i < WIDTH + 2; i++)
		bufer += '#';
	bufer += '\n';

	for (int i = 0; i < HEIGHT; i++)
	{
		bufer += '#';
		for (int j = 0; j < WIDTH; j++)
			bufer += screen[i][j];
		bufer += "#\n";
	}

	for (int i = 0; i < WIDTH + 2; i++)
		bufer += '#';

	std::cout << bufer;

}





