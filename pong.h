#ifndef PONG_H
#define PONG_H

//#define RIGHT		0
//#define DOWNRIGHT	45
//#define DOWN		90
//#define DOWNLEFT	135
//#define LEFT		180
//#define UPLEFT		225
//#define UP			270
//#define UPRIGHT		315

#define HEIGHT		109
#define WIDTH		137

#define PI			3.14159265359

// Different play modes
#define SINGLE		1
#define DOUBLE		2
#define COMPUTER	3

// Difficulties
#define EASY		1
#define MEDIUM		2
#define	HARD		3

// Location in the Menu
#define MODESELECT	1
#define DIFFSELECT	2
#define INGAME		3

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

typedef struct {
	int x;
	int y;
	int length;
	int score;

} Paddle;

/*********FUNCTION AND GLOBAL VARIABLE PROTOTYPES*********/
// main.c
int getLevel();
void setMenuLoc(int menuLocation);

//	board.c
void makeBall(Ball* ball, int radius, int x, int y);
void makePaddle(Paddle* paddle, int length, int x, int y);
void play(int mode);

//	ball.c
void drawBall(Ball *myBall);
void moveBall(Ball *myBall, Paddle* myPaddle);
void moveBall2(Ball *myBall, Paddle* paddle1, Paddle* paddle2);

// paddle.c
void drawPaddle(Paddle* myPaddle);
void movePaddle(Paddle* myPaddle, int newX);

#endif
