#include "msp430x54x.h"
#include "hal_lcd.h"
#include "pong.h"
//#include <stdio.h>

void erasePaddle(Paddle* myPaddle) {
	int paddleLength	=	myPaddle->length;
	int rightX			=	myPaddle->x + paddleLength/2;
	int leftX			=	myPaddle->x - paddleLength/2;

	halLcdLine(leftX, myPaddle->y, rightX, myPaddle->y, PIXEL_OFF);
}

/*
 * Draw the Paddle from it's center x and y coordinates
 */
void drawPaddle(Paddle* myPaddle) {
	int paddleLength	=	myPaddle->length;
	int rightX			=	myPaddle->x + paddleLength/2;
	int leftX			=	myPaddle->x - paddleLength/2;

	if (rightX > WIDTH) {
		myPaddle->x		=	WIDTH - paddleLength/2;
		rightX			=	myPaddle->x + paddleLength/2;
		leftX			=	myPaddle->x - paddleLength/2;
	}
	if (leftX < 0) {
		myPaddle->x		=	paddleLength/2;
		rightX			=	myPaddle->x + paddleLength/2;
		leftX			=	myPaddle->x - paddleLength/2;
	}

	halLcdLine(leftX, myPaddle->y, rightX, myPaddle->y, PIXEL_ON);
}


void movePaddle(Paddle* myPaddle, int newX ) {
	// Clear the paddle first
	erasePaddle(myPaddle);
	//printf("%d\n", newX);


	// Update the paddle's x coordinate;
	myPaddle->x = newX/30;

	// Draw the paddle
	drawPaddle(myPaddle);
}
