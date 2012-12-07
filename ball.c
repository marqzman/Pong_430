#include "msp430x54x.h"
#include "hal_lcd.h"
#include "board_defs.h"
//#include <stdlib.h>
//#include <math.h>

#include "pong.h"

char SCORE[9] = {"S" "C" "O" "R" "E" " " " " " " "\0"};

/* Erase the ball at it's current location
 * MUST BE CALLED BEFORE THE BALL IS DRAWN */
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

/* Draw the ball at it's current location*/
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

/* Single Player Mode
 * Bounces off all 4 Walls*/
void checkWalls(Ball *myBall){
	int myRadius = myBall->radius;
	if((myBall->x <= myRadius) || (myBall->x >= (WIDTH - myRadius))) {	// Check the Left and Right walls
		myBall->dx = -1*(myBall->dx);
	}

	if((myBall->y <= myRadius) || (myBall->y >= (HEIGHT - myRadius))) {	// Check the Top and Bottom walls
		myBall->dy = -1*(myBall->dy);
	}
}

/* Multi-player Mode
 * Bounces off the Left and Right Walls
 * Increments the score of the player that successfully made it past the other player
 * Bounces off the Top and Bottom Walls*/
void checkWalls2(Ball *myBall, Paddle* top, Paddle* bottom){
	int myRadius = myBall->radius;
	if((myBall->x <= myRadius) || (myBall->x >= (WIDTH - myRadius))) {	// Check the Left and Right walls
		myBall->dx = -1*(myBall->dx);
	}

	if((myBall->y <= myRadius)) { 	// Check the Top wall
		bottom->score++;
		myBall->dy = -1*(myBall->dy);
	} else if(myBall->y >= (HEIGHT - myRadius)) { // Check the Bottom wall
		top->score++;
		myBall->dy = -1*(myBall->dy);
	}
}

/* Single Player mode
 * Checks to see of the player missed the ball
 * If the player missed the ball, the game is over*/
void checkMiss(Ball* myBall, Paddle* myPaddle) {
	if(myBall->y >= (HEIGHT - myBall->radius)) {
		myPaddle->score = 0;
		endGame();
	}
}
void checkPaddle(Ball* myBall, Paddle* myPaddle) {
	//char buffer[7] = {"S" "C" "O" "R" "E" " "};
	int leftX	= myPaddle->x - (myPaddle->length)/2;
	int rightX	= myPaddle->x + (myPaddle->length)/2;
	if(((myBall->y + (myBall->radius)*myBall->dy) == myPaddle->y) && (myBall->x + myBall->radius >= leftX) && (myBall->x - myBall->radius <= rightX)) {
		myBall->dy *= -1;
		if(getMode() == SINGLE) {
			myPaddle->score += 1;
		}
	} else if(getMode() == SINGLE){
		checkMiss(myBall, myPaddle);
	}
}

/* For Single Player mode
 * Changes the ball's position and re-draws it
 * Checks the walls for a bounce
 * */
void updateBall(Ball* myBall){
	// Erase the current location of the ball
	eraseBall(myBall);

	// Check for a bounce
	checkWalls(myBall);

	// Update the ball's position
	myBall->x += myBall->dx;
	myBall->y += myBall->dy;

	// Draw the ball in it's new location
	drawBall(myBall);
}

/* For Double Player or Computer Mode*/
void updateBall2(Ball* myBall, Paddle* top, Paddle* bottom){
	// Erase the current location of the ball
	eraseBall(myBall);

	// Check for a bounce
	checkWalls2(myBall, top, bottom);

	// Update the ball's position
	myBall->x += myBall->dx;
	myBall->y += myBall->dy;

	// Draw the ball in it's new location
	drawBall(myBall);
}

/* For Single Player Mode */
void moveBall(Ball* myBall, Paddle* myPaddle) {
	checkPaddle(myBall, myPaddle);
	SCORE[6] = '0' + (myPaddle->score)/10;
	SCORE[7] = '0' + (myPaddle->score)%10;
	halLcdPrintLine(SCORE, 0, OVERWRITE_TEXT);

	updateBall(myBall);
}

/* For Double Player or Computer Mode */
void moveBall2(Ball* myBall, Paddle* paddle1, Paddle* paddle2) {
	checkPaddle(myBall, paddle1);
	SCORE[6] = '0' + (paddle1->score)/10;
	SCORE[7] = '0' + (paddle1->score)%10;
	halLcdPrintLine(SCORE, 8, OVERWRITE_TEXT);

	checkPaddle(myBall, paddle2);
	SCORE[6] = '0' + (paddle2->score)/10;
	SCORE[7] = '0' + (paddle2->score)%10;
	halLcdPrintLine(SCORE, 0, OVERWRITE_TEXT);

	updateBall2(myBall, paddle2, paddle1);
}
