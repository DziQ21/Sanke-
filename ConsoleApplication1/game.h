#ifndef GAME
#define GAME
#include <vector>
#include <string>
//
//		  @ @ @
//		   @@@
//	@@@@@@@@O@@@@@@@@@@@@@@		//@-eye trace	O-head X-Body
//		   @X@
//		  @ X @

#pragma once
#define WIDTH 30
#define HEIGHT 15

enum Direction{up=0 ,right ,down,left};//to make job easier
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
	int moves;
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
	void Play(int input);
	data GetData();
	void Play(Direction input);
	std::string Display();
	//geting func
	int GetMoves() { return moves; }
	int GetPoints() { return Points; }
	bool GetRuning() { return CzyOdpalone; }
};

#endif
