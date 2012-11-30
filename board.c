#include "msp430x54x.h"
#include "hal_lcd.h"
#include "board_defs.h"
#include "pong.h"
#include <stdlib.h>

Ball theBall;
Paddle paddle1;

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
			break;
		case COMPUTER:
			break;
	}
}

// Brings up the main menu
void startSingleGame() {
//	halLcdPrintLine("PONG", 4, OVERWRITE_TEXT);

	int paddleX = WIDTH/2;

	//Paddle thePaddle;
	makePaddle(&paddle1, 6, WIDTH/2, HEIGHT - 10);
	drawPaddle(&paddle1);

	//Ball theBall;
	makeBall(&theBall, 2, WIDTH/2, HEIGHT/2);
	drawBall(&theBall);

	while(1) {
		moveBall(&theBall, &paddle1);

		paddleX = (paddleX + 1) % WIDTH;	// Testing

		movePaddle(&paddle1, paddleX);	// Testing

		__delay_cycles(100000);
	}
	// Print a message...
	// halLcdPrintLine(buffer, 3, OVERWRITE_TEXT );

}

