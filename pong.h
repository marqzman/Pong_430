#ifndef PONG_H
#define PONG_H


#define NONE		360
#define UP			0
#define RIGHT		90
#define DOWN		180
#define LEFT		270

#define HEIGHT	109
#define WIDTH	137

#define PI		3.14159265359

#define SPEED	1

#define BOUNCE(deg)		((deg < 180) ? (deg += 180) : (deg -= 180))
//#define BOUNCE(newDeg)		newDeg = 180 + newDeg
//#define BOUNCE(rad)	((rad < PI) ? (rad += PI) : (rad -= PI))

/*********STRUCTS*********/
typedef struct {
	int dir;
	//double radians;
	int x;
	int y;
	int radius;
} Ball;

/*********FUNCTION PROTOTYPES*********/
//	board.c
void drawBoard();
void play(int mode);
void startGame();
void makeBall(Ball* ball, int radius, int x, int y);

//	ball.c
void drawBall(Ball *myBall);
void moveBall(Ball *myBall);

//struct ball myBall;
//struct paddle myPaddle;

/*
struct paddle {
	int dir;		// Not really needed if the potentiometer determines position instead of acceleration
	int x;
}; */



#endif