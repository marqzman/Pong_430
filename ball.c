#include "msp430x54x.h"
#include "hal_lcd.h"
#include "board_defs.h"
//#include <stdlib.h>
//#include <math.h>

#include "pong.h"
//#include "hal_lcd_fonts.h"

//struct ball* myBall;

// Whatever.....

/* ERASE THE CIRCLE */
void eraseBall(Ball *myBall) {
	halLcdPixel(myBall->x-1, myBall->y+2, PIXEL_OFF);
	halLcdPixel(myBall->x-0, myBall->y+2, PIXEL_OFF);
	halLcdPixel(myBall->x+1, myBall->y+2, PIXEL_OFF);

	halLcdPixel(myBall->x-2, myBall->y+1, PIXEL_OFF);
	halLcdPixel(myBall->x-1, myBall->y+1, PIXEL_OFF);
	halLcdPixel(myBall->x+0, myBall->y+1, PIXEL_OFF);
	halLcdPixel(myBall->x+1, myBall->y+1, PIXEL_OFF);
	halLcdPixel(myBall->x+2, myBall->y+1, PIXEL_OFF);

	halLcdPixel(myBall->x-2, myBall->y+0, PIXEL_OFF);
	halLcdPixel(myBall->x-1, myBall->y+0, PIXEL_OFF);
	halLcdPixel(myBall->x+0, myBall->y+0, PIXEL_OFF);
	halLcdPixel(myBall->x+1, myBall->y+0, PIXEL_OFF);
	halLcdPixel(myBall->x+2, myBall->y+0, PIXEL_OFF);

	halLcdPixel(myBall->x-2, myBall->y-1, PIXEL_OFF);
	halLcdPixel(myBall->x-1, myBall->y-1, PIXEL_OFF);
	halLcdPixel(myBall->x+0, myBall->y-1, PIXEL_OFF);
	halLcdPixel(myBall->x+1, myBall->y-1, PIXEL_OFF);
	halLcdPixel(myBall->x+2, myBall->y-1, PIXEL_OFF);

	halLcdPixel(myBall->x-1, myBall->y-2, PIXEL_OFF);
	halLcdPixel(myBall->x-0, myBall->y-2, PIXEL_OFF);
	halLcdPixel(myBall->x+1, myBall->y-2, PIXEL_OFF);
}

// Call the LCD functins to draw a ball
// at it's current location
void drawBall(Ball *myBall) {
	halLcdPixel(myBall->x-1, myBall->y+2, PIXEL_ON);
	halLcdPixel(myBall->x-0, myBall->y+2, PIXEL_ON);
	halLcdPixel(myBall->x+1, myBall->y+2, PIXEL_ON);

	halLcdPixel(myBall->x-2, myBall->y+1, PIXEL_ON);
	halLcdPixel(myBall->x-1, myBall->y+1, PIXEL_ON);
	halLcdPixel(myBall->x+0, myBall->y+1, PIXEL_ON);
	halLcdPixel(myBall->x+1, myBall->y+1, PIXEL_ON);
	halLcdPixel(myBall->x+2, myBall->y+1, PIXEL_ON);

	halLcdPixel(myBall->x-2, myBall->y+0, PIXEL_ON);
	halLcdPixel(myBall->x-1, myBall->y+0, PIXEL_ON);
	halLcdPixel(myBall->x+0, myBall->y+0, PIXEL_ON);
	halLcdPixel(myBall->x+1, myBall->y+0, PIXEL_ON);
	halLcdPixel(myBall->x+2, myBall->y+0, PIXEL_ON);

	halLcdPixel(myBall->x-2, myBall->y-1, PIXEL_ON);
	halLcdPixel(myBall->x-1, myBall->y-1, PIXEL_ON);
	halLcdPixel(myBall->x+0, myBall->y-1, PIXEL_ON);
	halLcdPixel(myBall->x+1, myBall->y-1, PIXEL_ON);
	halLcdPixel(myBall->x+2, myBall->y-1, PIXEL_ON);

	halLcdPixel(myBall->x-1, myBall->y-2, PIXEL_ON);
	halLcdPixel(myBall->x-0, myBall->y-2, PIXEL_ON);
	halLcdPixel(myBall->x+1, myBall->y-2, PIXEL_ON);

}

void checkWalls(Ball *myBall){
	int myRadius = myBall->radius;
	if((myBall->x <= myRadius) || (myBall->x >= (WIDTH - myRadius))) {	// Check the Left and Right walls
		myBall->dx = -1*(myBall->dx);
	}

	if((myBall->y <= myRadius) || (myBall->y >= (HEIGHT - myRadius))) {	// Check the Top and Bottom walls
		//gameOver++;
		myBall->dy = -1*(myBall->dy);
	}
}

void checkPaddle(Ball* myBall, Paddle* myPaddle) {
	//char buffer[7] = {"S" "C" "O" "R" "E" " "};
	int leftX	= myPaddle->x - (myPaddle->length)/2;
	int rightX	= myPaddle->x + (myPaddle->length)/2;
	if(((myBall->y + (myBall->radius)*myBall->dy) == myPaddle->y) && (myBall->x + myBall->radius >= leftX) && (myBall->x - myBall->radius <= rightX)) {
		myBall->dy *= -1;
		myPaddle->score += 1;
	}
	// If player 1 scored
		// P1OUT ^= BIT1;              // toggle P1.1
	// else
		// P2OUT ^= BIT1;              // toggle P1.1

	//buffer[6] = '0' + myPaddle->score;
	//halLcdPrintLine(buffer, 1, OVERWRITE_TEXT);
}

void updateBall(Ball *myBall){
	// Erase the current location of the ball
	eraseBall(myBall);
	// Check for a bounce
	checkWalls(myBall);
	// Update the ball's position
	myBall->x += getLevel()*myBall->dx;
	myBall->y += getLevel()*myBall->dy;
	// Draw the ball in it's new location
	drawBall(myBall);
}

/* For Single Player Mode */
void moveBall(Ball* myBall, Paddle* myPaddle) {
	char SCORE[7] = {"S" "C" "O" "R" "E" " "};

	checkPaddle(myBall, myPaddle);
	SCORE[6] = '0' + myPaddle->score;
	halLcdPrintLine(SCORE, 0, OVERWRITE_TEXT);

	updateBall(myBall);
}

/* For Double Player or Computer Mode */
void moveBall2(Ball* myBall, Paddle* paddle1, Paddle* paddle2) {
	char SCORE[7] = {"S" "C" "O" "R" "E" " "};

	checkPaddle(myBall, paddle1);
	SCORE[6] = '0' + paddle1->score;
	halLcdPrintLine(SCORE, 0, OVERWRITE_TEXT);

	checkPaddle(myBall, paddle2);
	SCORE[6] = '0' + paddle2->score;
	halLcdPrintLine(SCORE, 8, OVERWRITE_TEXT);

	updateBall(myBall);
}
