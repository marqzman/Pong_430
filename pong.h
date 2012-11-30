#ifndef PONG_H
#define PONG_H

#define RIGHT		0
//#define DOWNRIGHT	45
#define DOWN		90
//#define DOWNLEFT	135
#define LEFT		180
//#define UPLEFT		225
#define UP			270
//#define UPRIGHT		315

#define HEIGHT	109
#define WIDTH	137

#define PI		3.14159265359

#define SPEED	1

//#define BOUNCE(deg)		((deg < 180) ? (deg += 180) : (deg -= 180))
//#define BOUNCE(newDeg)		newDeg = 180 + newDeg
//#define BOUNCE(rad)	((rad < PI) ? (rad += PI) : (rad -= PI))

/*********STRUCTS*********/
typedef struct {
	//int dir;
	//double radians;
	int x;
	int y;
	int dx;
	int dy;
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
