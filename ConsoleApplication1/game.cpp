#include "pch.h"
#include "game.h"
#include <string>
#include <iostream>
#include <cstdlib>

vector operator+(vector a, vector b)
{
	vector result;
	result.x = a.x + b.x;
	result.y = a.y + b.y;
	return result;
}

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
		Food.x = rand() % (WIDTH-4)+2;
		Food.y = rand() % (HEIGHT-4)+2;
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
	moves = 100;
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
	CzyOdpalone = 1;
	SnakeDirection = right;
	Points = 0;
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
	if(moves<0)
		CzyOdpalone = 0;
		//food
	
	if (Body[HeadPosition] == Food)
	{
		 Points+= 100;
		 moves += 50;
		Body.insert(Body.begin() + HeadPosition + 1, GhostTail);//co jak na ostatniej
		SetFood();
	}
	moves--;
	

}

data game::GetData()
{
	data result;
	for (int i = 0; i < 8; i++)
	{
		result.food[i] = 0;
		result.body[i] = 0;
	}
	
	if (CzyOdpalone)
	{
		char screen[WIDTH][HEIGHT];
		for (int i = 0; i < HEIGHT; i++)
			for (int j = 0; j < WIDTH; j++)
				screen[i][j] = ' ';

		for (int i = 0; i < Body.size(); i++)
			screen[Body[i].x][Body[i].y] = 'X';

		screen[Food.y][Food.x] = '@';
		screen[Body[HeadPosition].y][Body[HeadPosition].x] = 'O';
		int i=0;
		{
			vector direction = { 0,1 };
			vector position = vector{ Body[HeadPosition].x, Body[HeadPosition].y };//the position where we are currently looking for food or tail or wall
			bool foodIsFound = false;//true if the food has been located in the direction looked
			bool tailIsFound = false;//true if the tail has been located in the direction looked 
			float distance = 0;
			//move once in the desired direction before starting 
			position = position + direction;
			distance += 1;

			//look in the direction until you reach a wall
			while (!(position.x < 0 || position.y < 0 || position.x > WIDTH || position.y > HEIGHT)) {

				//check for food at the position
				if (!foodIsFound && position.x == Food.x && position.y == Food.y) {
					result.food[i] = 1;
					foodIsFound = true; // dont check if food is already found
				}

				//check for tail at the position
				if (!tailIsFound && screen[position.x][position.y] == 'X') {
					result.body[i] / distance;
					tailIsFound = true; // dont check if tail is already found
				}

				//look further in the direction
				position = position + direction;
				distance += 1;
			}
			//set the distance to the wall
			result.wall[i] = 1 / distance;
			i++;

		}
		{
			vector direction = { 1,1 };
			vector position = vector{ Body[HeadPosition].x, Body[HeadPosition].y };//the position where we are currently looking for food or tail or wall
			bool foodIsFound = false;//true if the food has been located in the direction looked
			bool tailIsFound = false;//true if the tail has been located in the direction looked 
			float distance = 0;
			//move once in the desired direction before starting 
			position = position + direction;
			distance += 1;

			//look in the direction until you reach a wall
			while (!(position.x < 0 || position.y < 0 || position.x > WIDTH || position.y > HEIGHT)) {

				//check for food at the position
				if (!foodIsFound && position.x == Food.x && position.y == Food.y) {
					result.food[i] = 1;
					foodIsFound = true; // dont check if food is already found
				}

				//check for tail at the position
				if (!tailIsFound && screen[position.x][position.y] == 'X') {
					result.body[i] / distance;
					tailIsFound = true; // dont check if tail is already found
				}

				//look further in the direction
				position = position + direction;
				distance += 1;
			}

			//set the distance to the wall
			result.wall[i] = 1 / distance;

			i++;

		}

		{
			vector direction = { 1,0 };
			vector position = vector{ Body[HeadPosition].x, Body[HeadPosition].y };//the position where we are currently looking for food or tail or wall
			bool foodIsFound = false;//true if the food has been located in the direction looked
			bool tailIsFound = false;//true if the tail has been located in the direction looked 
			float distance = 0;
			//move once in the desired direction before starting 
			position = position + direction;
			distance += 1;

			//look in the direction until you reach a wall
			while (!(position.x < 0 || position.y < 0 || position.x > WIDTH || position.y > HEIGHT)) {

				//check for food at the position
				if (!foodIsFound && position.x == Food.x && position.y == Food.y) {
					result.food[i] = 1;
					foodIsFound = true; // dont check if food is already found
				}

				//check for tail at the position
				if (!tailIsFound && screen[position.x][position.y] == 'X') {
					result.body[i] / distance;
					tailIsFound = true; // dont check if tail is already found
				}

				//look further in the direction
				position = position + direction;
				distance += 1;
			}

			//set the distance to the wall
			result.wall[i] = 1 / distance;
			i++;
		}
		{
			vector direction = { 1,-1 };
			vector position = vector{ Body[HeadPosition].x, Body[HeadPosition].y };//the position where we are currently looking for food or tail or wall
			bool foodIsFound = false;//true if the food has been located in the direction looked
			bool tailIsFound = false;//true if the tail has been located in the direction looked 
			float distance = 0;
			//move once in the desired direction before starting 
			position = position + direction;
			distance += 1;

			//look in the direction until you reach a wall
			while (!(position.x < 0 || position.y < 0 || position.x > WIDTH || position.y > HEIGHT)) {

				//check for food at the position
				if (!foodIsFound && position.x == Food.x && position.y == Food.y) {
					result.food[i] = 1;
					foodIsFound = true; // dont check if food is already found
				}

				//check for tail at the position
				if (!tailIsFound && screen[position.x][position.y] == 'X') {
					result.body[i] / distance;
					tailIsFound = true; // dont check if tail is already found
				}

				//look further in the direction
				position = position + direction;
				distance += 1;
			}

			//set the distance to the wall
			result.wall[i] = 1 / distance;
			i++;
		}
		{
			vector direction = { 0,-1 };
			vector position = vector{ Body[HeadPosition].x, Body[HeadPosition].y };//the position where we are currently looking for food or tail or wall
			bool foodIsFound = false;//true if the food has been located in the direction looked
			bool tailIsFound = false;//true if the tail has been located in the direction looked 
			float distance = 0;
			//move once in the desired direction before starting 
			position = position + direction;
			distance += 1;

			//look in the direction until you reach a wall
			while (!(position.x < 0 || position.y < 0 || position.x > WIDTH || position.y > HEIGHT)) {

				//check for food at the position
				if (!foodIsFound && position.x == Food.x && position.y == Food.y) {
					result.food[i] = 1;
					foodIsFound = true; // dont check if food is already found
				}

				//check for tail at the position
				if (!tailIsFound && screen[position.x][position.y] == 'X') {
					result.body[i] / distance;
					tailIsFound = true; // dont check if tail is already found
				}

				//look further in the direction
				position = position + direction;
				distance += 1;
			}

			//set the distance to the wall
			result.wall[i] = 1 / distance;
			i++;
		}
		{
			vector direction = { -1,-1 };
			vector position = vector{ Body[HeadPosition].x, Body[HeadPosition].y };//the position where we are currently looking for food or tail or wall
			bool foodIsFound = false;//true if the food has been located in the direction looked
			bool tailIsFound = false;//true if the tail has been located in the direction looked 
			float distance = 0;
			//move once in the desired direction before starting 
			position = position + direction;
			distance += 1;

			//look in the direction until you reach a wall
			while (!(position.x < 0 || position.y < 0 || position.x > WIDTH || position.y > HEIGHT)) {

				//check for food at the position
				if (!foodIsFound && position.x == Food.x && position.y == Food.y) {
					result.food[i] = 1;
					foodIsFound = true; // dont check if food is already found
				}

				//check for tail at the position
				if (!tailIsFound && screen[position.x][position.y] == 'X') {
					result.body[i] / distance;
					tailIsFound = true; // dont check if tail is already found
				}

				//look further in the direction
				position = position + direction;
				distance += 1;
			}

			//set the distance to the wall
			result.wall[i] = 1 / distance;
			i++;
		}
		{
			vector direction = { -1,0 };
			vector position = vector{ Body[HeadPosition].x, Body[HeadPosition].y };//the position where we are currently looking for food or tail or wall
			bool foodIsFound = false;//true if the food has been located in the direction looked
			bool tailIsFound = false;//true if the tail has been located in the direction looked 
			float distance = 0;
			//move once in the desired direction before starting 
			position = position + direction;
			distance += 1;

			//look in the direction until you reach a wall
			while (!(position.x < 0 || position.y < 0 || position.x > WIDTH || position.y > HEIGHT)) {

				//check for food at the position
				if (!foodIsFound && position.x == Food.x && position.y == Food.y) {
					result.food[i] = 1;
					foodIsFound = true; // dont check if food is already found
				}

				//check for tail at the position
				if (!tailIsFound && screen[position.x][position.y] == 'X') {
					result.body[i] / distance;
					tailIsFound = true; // dont check if tail is already found
				}

				//look further in the direction
				position = position + direction;
				distance += 1;
			}

			//set the distance to the wall
			result.wall[i] = 1 / distance;
			i++;
		}
		{
			vector direction = { -1,1 };
			vector position = vector{ Body[HeadPosition].x, Body[HeadPosition].y };//the position where we are currently looking for food or tail or wall
			bool foodIsFound = false;//true if the food has been located in the direction looked
			bool tailIsFound = false;//true if the tail has been located in the direction looked 
			float distance = 0;
			//move once in the desired direction before starting 
			position = position + direction;
			distance += 1;

			//look in the direction until you reach a wall
			while (!(position.x < 0 || position.y < 0 || position.x > WIDTH || position.y > HEIGHT)) {

				//check for food at the position
				if (!foodIsFound && position.x == Food.x && position.y == Food.y) {
					result.food[i] = 1;
					foodIsFound = true; // dont check if food is already found
				}

				//check for tail at the position
				if (!tailIsFound && screen[position.x][position.y] == 'X') {
					result.body[i] / distance;
					tailIsFound = true; // dont check if tail is already found
				}

				//look further in the direction
				position = position + direction;
				distance += 1;
			}

			//set the distance to the wall
			result.wall[i] = 1 / distance;
			i++; 
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




