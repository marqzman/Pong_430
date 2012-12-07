#ifndef PONG_H
#define PONG_H

#define TRUE		1
#define FALSE		0

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
#define STARTLENGTH	12

// Location in the Menu
#define MODESELECT	1
#define DIFFSELECT	2
#define INGAME		3

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
int getMode();

//	board.c
void makeBall(Ball* ball, int radius, int x, int y);
void makePaddle(Paddle* paddle, int length, int x, int y);
void play(int mode);
void endGame(void);
void initADC();

//	ball.c
void drawBall(Ball *myBall);
void moveBall(Ball *myBall, Paddle* myPaddle);
void moveBall2(Ball *myBall, Paddle* paddle1, Paddle* paddle2);

// paddle.c
void drawPaddle(Paddle* myPaddle);
void movePaddle(Paddle* myPaddle, int newX);

#endif
