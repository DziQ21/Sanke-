#include "pch.h"
#include "game.h"
#include <string>
#include <iostream>

bool operator==(vector a,vector b)
{
	if (a.x == b.x&&a.y == b.y)
		return 1;
	return 0;
}

void game::SetFood()
{
	while (true)
	{
		bool isGood=1;
		Food.x = rand() % WIDTH;
		Food.y = rand() % HEIGHT;
		for(int i=0;i<Body.size();i++)
			if (Food == Body[i])
			{
				isGood = 0;
				break;
			}
		if (isGood)
			break;

	}
}

game::game()
{
	vector bufor;
	bufor.x = WIDTH/2;
	bufor.y = HEIGHT/2;
	Body.push_back(bufor);
	bufor.x = bufor.x - 3;
	Body.push_back(bufor);
	bufor.x++;
	Body.push_back(bufor);
	bufor.x++;
	Body.push_back(bufor);
	HeadPosition = 0;
	SetFood();
}


game::~game()
{
}

data game::GetData()
{



	return data();
}

void game::Play(Direction input)
{
	//game have to run
	if (!CzyOdpalone)
		return;

	int real;

	if ((input == up || input == down) && (SnakeDirection == up || SnakeDirection == down))
		real = SnakeDirection;
	else
		if ((input == left || input == right) && (SnakeDirection == left || SnakeDirection == right))
			real = SnakeDirection;
		else
			real = input;
	real++;//conversion

	switch (real) {
		//ghost tail setting 
		if (HeadPosition != Body.size() - 1)
			GhostTail = Body[HeadPosition + 1];
		else
			GhostTail = Body[0];


	case 2:
		if (HeadPosition != Body.size() - 1)
		{
			Body[HeadPosition + 1].x = Body[HeadPosition].x + 1;
			Body[HeadPosition + 1].y = Body[HeadPosition].y;
			HeadPosition++;
		}
		else
		{
			Body[0].x = Body[HeadPosition].x + 1;
			Body[0].y = Body[HeadPosition].y;
			HeadPosition = 0;
		}
		break;
	case 4:
		if (HeadPosition != Body.size() - 1)
		{
			Body[HeadPosition + 1].x = Body[HeadPosition].x - 1;
			Body[HeadPosition + 1].y = Body[HeadPosition].y;
			HeadPosition++;
		}
		else
		{
			Body[0].x = Body[HeadPosition].x - 1;
			Body[0].y = Body[HeadPosition].y;
			HeadPosition = 0;
		}
		break;
	case 3:
		if (HeadPosition != Body.size() - 1)
		{
			Body[HeadPosition + 1].y = Body[HeadPosition].y + 1;
			Body[HeadPosition + 1].x = Body[HeadPosition].x;
			HeadPosition++;
		}
		else
		{
			Body[0].y = Body[HeadPosition].y + 1;
			Body[0].x = Body[HeadPosition].x;
			HeadPosition = 0;
		}
		break;
	case 1:
		if (HeadPosition != Body.size() - 1)
		{
			Body[HeadPosition + 1].y = Body[HeadPosition].y - 1;
			Body[HeadPosition + 1].x = Body[HeadPosition].x;
			HeadPosition++;
		}
		else
		{
			Body[0].y = Body[HeadPosition].y - 1;
			Body[0].x = Body[HeadPosition].x;
			HeadPosition = 0;
		}
		break;

	};
	//colision
	//food
	if (Body[HeadPosition] == Food)
	{
		Body.insert(Body.begin() + HeadPosition + 1, GhostTail);//co jak na ostatniej
		SetFood();
	}

}

std::string game::Display()
{

	char screen[HEIGHT][WIDTH];
	for (int i = 0; i < HEIGHT; i++)
		for (int j = 0; j < WIDTH; j++)
			screen[i][j] = ' ';

	for (int i = 0; i < Body.size(); i++)
		screen[Body[i].y][Body[i].x]='X';

	screen[Food.y][Food.x] = '@';
	screen[Body[HeadPosition].y][Body[HeadPosition].x] = 'O';

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

	return  bufer;

}




