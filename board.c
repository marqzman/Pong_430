#include "msp430x54x.h"
#include "hal_lcd.h"
#include "board_defs.h"
#include "pong.h"
#include <stdlib.h>
#include <math.h>

Ball theBall;
Paddle paddle1;
Paddle paddle2;

void makeBall(Ball* ball, int radius, int x, int y) {
	ball->x		=	x;
	ball->y		=	y;
	ball->dx	=	1;
	ball->dy	=	1;
}

void makePaddle(Paddle* paddle, int length, int x, int y) {
	paddle->length	=	length;
	paddle->x 		=	x;
	paddle->y		=	y;
	paddle->score	=	0;
}

// mode = Single player; 2 Player; Agains MSP430
void play(int mode) {
	switch(mode) {
		case SINGLE:
			startSingleGame();
			break;
		case DOUBLE:
			startDoubleGame();
			break;
		case COMPUTER:
			break;
	}
}

// Starts a Single Player Game
void startSingleGame() {
	int paddleX = WIDTH/2;
	// Make and draw the paddle
	makePaddle(&paddle1, 6, WIDTH/2, HEIGHT - 12);
	drawPaddle(&paddle1);

	// Make and draw the ball
	makeBall(&theBall, 2, WIDTH/2, HEIGHT/2);
	drawBall(&theBall);

	// Play forever
	while(1) {
		moveBall(&theBall, &paddle1);

		paddleX = (paddleX + 1) % WIDTH;	// Testing

		movePaddle(&paddle1, paddleX);	// Testing

		__delay_cycles(100000);
	}
}

// Starts a Two Player Game
void startDoubleGame() {
	int paddle1X = WIDTH/2;
	int paddle2X = WIDTH/2;

	// Make and draw player 1's paddle
	makePaddle(&paddle1, 6, WIDTH/2, HEIGHT - 12);
	drawPaddle(&paddle1);

	// Make and draw player 2's paddle
	makePaddle(&paddle2, 6, WIDTH/2, 12);
	drawPaddle(&paddle2);

	// Make and draw the ball
	makeBall(&theBall, 2, WIDTH/2, HEIGHT/2);
	drawBall(&theBall);

	// Play forever
	while(1) {
		moveBall2(&theBall, &paddle1, &paddle2);

		paddle1X = (paddle1X + 1) % WIDTH;	// Testing
		paddle2X = (paddle2X - 1) % WIDTH;	// Testing

		movePaddle(&paddle1, paddle1X);				// Testing
		movePaddle(&paddle2, fabs(paddle2X));		// Testing

		__delay_cycles(100000);
	}
}
