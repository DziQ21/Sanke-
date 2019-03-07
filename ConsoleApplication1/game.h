#ifndef GAME
#define GAME

//
//		  @ @ @
//		   @@@
//	@@@@@@@@O@@@@@@@@@@@@@@		//@-eye trace	O-head X-Body
//		   @X@	
//		  @ X @

#pragma once
#define WIDTH 20
#define HIGHT 20

enum Direction{up ,right ,down,left};//to make job easier
struct data {//type that represents what snake see
	float wall[8];
	float food[8];
	float body[8];
};

class game
{
private:
	
	int points;


public:
	game();
	~game();
	data GetData();
	void Play(Direction);

};

#endif