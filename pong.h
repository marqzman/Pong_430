#ifndef PONG_H
#define PONG_H

#define NONE	0
#define UP		1
#define RIGHT	2
#define DOWN	3
#define LEFT	4
#define UPRIGHT	5

#define HEIGHT	109
#define WIDTH	137

/*********FUNCTION PROTOTYPES*********/
//	board.c
void drawBoard();
void play(int mode);
void startGame();
Ball *makeBall(int x, int y);

//	ball.c
void drawBall(Ball *myBall);
void moveBall(Ball *myBall, int direction);

/*********STRUCTS*********/
typedef struct {
	int dir;
	int x;
	int y;
} Ball;


//struct ball myBall;
//struct paddle myPaddle;

/*
struct paddle {
	int dir;		// Not really needed if the potentiometer determines position instead of acceleration
	int x;
}; */



#endif
