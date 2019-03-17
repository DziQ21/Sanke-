#ifndef GAME
#define GAME
#include <vector>
//
//		  @ @ @
//		   @@@
//	@@@@@@@@O@@@@@@@@@@@@@@		//@-eye trace	O-head X-Body
//		   @X@	
//		  @ X @

#pragma once
#define WIDTH 40
#define HEIGHT 20

enum Direction{up ,right ,down,left};//to make job easier
struct data {//type that represents what snake see
	float wall[8];
	float food[8];
	float body[8];
};

struct vector {
	int x;
	int y;
};

class game
{
private:
	vector Food;
	int Points;
	std::vector <vector> Body;
	int HeadPosition;
	vector GhostTail;
	Direction SnakeDirection;
	bool CzyOdpalone;//to fix ;

	//priv func
	void SetFood();
public:
	game();
	~game();
	data GetData();
	void Play(Direction input);
	std::string Display();
	//geting func
	int GetPoints() { return Points; }
};

#endif