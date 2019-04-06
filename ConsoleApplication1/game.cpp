#include "pch.h"
#include "game.h"
#include <string>
#include <iostream>
#include <cstdlib>

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
	Food.x= WIDTH / 2+4;
	Food.y = HEIGHT / 2-4;
	CzyOdpalone = 1;
	SnakeDirection = right;
	Points = 0;
	pointforlife = 00;
}


game::~game()
{
}

void game::Play(int input)
{
	if (!CzyOdpalone)
	{

		return;
	}
	int real;

	if ((input == 0 || input == 2) && (SnakeDirection == 0 || SnakeDirection == 2))
		real = static_cast<Direction>(SnakeDirection);
	else
		if ((input == 3 || input == 1) && (SnakeDirection == 1 || SnakeDirection == 3))
			real =static_cast<Direction>(SnakeDirection);
		else
			real = input;

	if (HeadPosition != Body.size() - 1)
		GhostTail = Body[HeadPosition + 1];
	else
		GhostTail = Body[0];
	switch (real) {
		//ghost tail setting


	case 1:
		SnakeDirection = right;
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
	case 3:
		SnakeDirection = left;
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
	case 2:
		SnakeDirection = down;
		if (HeadPosition != Body.size() - 1)
		{
			Body[HeadPosition + 1].y = Body[HeadPosition].y +1;
			Body[HeadPosition + 1].x = Body[HeadPosition].x;
			HeadPosition++;
		}
		else
		{
			Body[0].y = Body[HeadPosition].y +1;
			Body[0].x = Body[HeadPosition].x;
			HeadPosition = 0;
		}
		break;
	case 0:
		SnakeDirection = up;
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
	if (Body[HeadPosition].x < 0 || Body[HeadPosition].y < 0 || Body[HeadPosition].x > WIDTH-1 || Body[HeadPosition].y > HEIGHT-1)
		CzyOdpalone = 0;
	for (int i = 0; i < Body.size(); i++)
		if (Body[HeadPosition].x == Body[i].x&&Body[HeadPosition].y == Body[i].y&&i != HeadPosition)
			CzyOdpalone = 0;
		//food
	if (pointforlife > 0) {
		Points = Points + 5;
		pointforlife -= 5;
	}
	if (Body[HeadPosition] == Food)
	{
		 pointforlife+= 100;
		Body.insert(Body.begin() + HeadPosition + 1, GhostTail);//co jak na ostatniej
		SetFood();
	}


}

data game::GetData()
{
	data result;
	for (int i = 0; i < 8; i++)
	{
		result.food[i] = 0;
		result.body[i] = 0;
	}

	if(CzyOdpalone)
	{
		char screen[WIDTH][HEIGHT];
		for (int i = 0; i < HEIGHT; i++)
			for (int j = 0; j < WIDTH; j++)
				screen[i][j] = ' ';

		for (int i = 0; i < Body.size(); i++)
			screen[Body[i].x][Body[i].y] = 'X';

		screen[Food.y][Food.x] = '@';
		screen[Body[HeadPosition].y][Body[HeadPosition].x] = 'O';
		result.wall[0] = (float)Body[HeadPosition].y / HEIGHT;
		result.wall[1] = (float)Body[HeadPosition].x / WIDTH;
		result.wall[2] = (float)(HEIGHT - Body[HeadPosition].y) / HEIGHT;
		result.wall[3] = (float)(WIDTH - Body[HeadPosition].x) / WIDTH;
		//body
		for (int i = 1; i <= 10; i++)
		{
			if (Body[HeadPosition].y + i > HEIGHT - 1)
			{
				break;
			}
			if (screen[Body[HeadPosition].x][Body[HeadPosition].y+i]=='X')
			{
				result.body[0] = float(11 - i) / 10;
				break;
			}
		}
		for (int i = 1; i <= 10; i++)
		{
			if ((Body[HeadPosition].y + i > HEIGHT - 1)|| (Body[HeadPosition].x + i > WIDTH - 1))
			{
				break;
			}
			if (screen[Body[HeadPosition].x+i][Body[HeadPosition].y + i] == 'X')
			{
				result.body[1] = float(11 - i) / 10;
				break;
			}
		}
		for (int i = 1; i <= 10; i++)
		{
			if (Body[HeadPosition].x + i > WIDTH - 1)
			{
				break;
			}
			if (screen[Body[HeadPosition].x+i][Body[HeadPosition].y] == 'X')
			{
				result.body[2] = float(11 - i) / 10;
				break;
			}
		}
		for (int i = 1; i <= 10; i++)
		{
			if ((Body[HeadPosition].x + i > WIDTH - 1)|| (Body[HeadPosition].y - i < 0))
			{
				break;
			}
			if (screen[Body[HeadPosition].x + i][Body[HeadPosition].y-i] == 'X')
			{
				result.body[3] = float(11 - i) / 10;
				break;
			}
		}
		for (int i = 1; i <= 10; i++)
		{
			if (Body[HeadPosition].y - i < 0)
			{
				break;
			}
			if (screen[Body[HeadPosition].x][Body[HeadPosition].y - i] == 'X')
			{
				result.body[4] = float(11 - i) / 10;
				break;
			}
		}
		for (int i = 1; i <= 10; i++)
		{
			if ((Body[HeadPosition].y - i < 0)||(Body[HeadPosition].x - i < 0))
			{
				break;
			}
			if (screen[Body[HeadPosition].x-i][Body[HeadPosition].y - i] == 'X')
			{
				result.body[5] = float(11 - i) / 10;
				break;
			}
		}
		for (int i = 1; i <= 10; i++)
		{
			if (Body[HeadPosition].x - i < 0)
			{
				break;
			}
			if (screen[Body[HeadPosition].x-i][Body[HeadPosition].y] == 'X')
			{
				result.body[6] = float(11 - i) / 10;
				break;
			}
		}
		for (int i = 1; i <= 10; i++)
		{
			if ((Body[HeadPosition].y + i > HEIGHT - 1)||(Body[HeadPosition].x - i < 0))
			{
				break;
			}
			if (screen[Body[HeadPosition].x-1][Body[HeadPosition].y + i] == 'X')
			{
				result.body[7] = float(11 - i) / 10;
				break;
			}
		}
		
		//food
		for (int i = 1; i <= 15; i++)
		{
			if (Body[HeadPosition].y + i > HEIGHT - 1)
			{
				break;
			}
			if (screen[Body[HeadPosition].x][Body[HeadPosition].y + i] == '@')
			{
				result.food[0] = 1;// float(16 - i) / 15*2;
				break;
			}
		}
		for (int i = 1; i <= 15; i++)
		{
			if ((Body[HeadPosition].y + i > HEIGHT - 1) || (Body[HeadPosition].x + i > WIDTH - 1))
			{
				break;
			}
			if (screen[Body[HeadPosition].x + i][Body[HeadPosition].y + i] == '@')
			{
				result.food[1] = 1;// float(16 - i) / 15*2;
				break;
			}
		}
		for (int i = 1; i <= 15; i++)
		{
			if (Body[HeadPosition].x + i > WIDTH - 1)
			{
				break;
			}
			if (screen[Body[HeadPosition].x + i][Body[HeadPosition].y] == '@')
			{
				result.food[2] = 1;// float(16 - i) / 15*2;
				break;
			}
		}
		for (int i = 1; i <= 15; i++)
		{
			if ((Body[HeadPosition].x + i > WIDTH - 1) || (Body[HeadPosition].y - i < 0))
			{
				break;
			}
			if (screen[Body[HeadPosition].x + i][Body[HeadPosition].y - i] == '@')
			{
				result.food[3] = 1;// float(16 - i) / 15*2;
				break;
			}
		}
		for (int i = 1; i <= 15; i++)
		{
			if (Body[HeadPosition].y - i < 0)
			{
				break;
			}
			if (screen[Body[HeadPosition].x][Body[HeadPosition].y - i] == '@')
			{
				result.food[4] = 1;//float(16 - i) / 15*2;
				break;
			}
		}
		for (int i = 1; i <= 15; i++)
		{
			if ((Body[HeadPosition].y - i < 0) || (Body[HeadPosition].x - i < 0))
			{
				break;
			}
			if (screen[Body[HeadPosition].x - i][Body[HeadPosition].y - i] == '@')
			{
				result.food[5] = 1;// float(16 - i) / 16*2;
				break;
			}
		}
		for (int i = 1; i <= 15; i++)
		{
			if (Body[HeadPosition].x - i < 0)
			{
				break;
			}
			if (screen[Body[HeadPosition].x - i][Body[HeadPosition].y] == '@')
			{
				result.food[6] = 1;//float(16 - i) / 15*2;
				break;
			}
		}
		for (int i = 1; i <= 15; i++)
		{
			if ((Body[HeadPosition].y + i > HEIGHT - 1) || (Body[HeadPosition].x - i < 0))
			{
				break;
			}
			if (screen[Body[HeadPosition].x - 1][Body[HeadPosition].y + i] == '@')
			{
				result.food[7] = 1;//float(16 - i) / 15*2;
				break;
			}
		}


	}


	return result;
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

	if (Body[HeadPosition].x < 0 || Body[HeadPosition].y < 0 || Body[HeadPosition].x >= WIDTH || Body[HeadPosition].y > HEIGHT)
		CzyOdpalone = 0;
	for (int i = 0; i < Body.size(); i++)
		if (Body[HeadPosition].x == Body[i].x&&Body[HeadPosition].y == Body[i].y&&i != HeadPosition)
			CzyOdpalone = 0;
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
	{
		if(i!=HeadPosition)
		screen[Body[i].y][Body[i].x] = 'X';

	}
	screen[Food.y][Food.x] = '@';
	if(CzyOdpalone)
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




