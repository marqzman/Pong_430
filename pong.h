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

void startGame();

typedef struct {
	int dir;
	int x;
	int y;
} Ball;

//struct ball myBall;
//struct paddle myPaddle;

#endif
