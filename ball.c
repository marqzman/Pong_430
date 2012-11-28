#include "msp430x54x.h"
#include "hal_lcd.h"
#include "board_defs.h"
//#include <stdlib.h>
#include <math.h>

#include "pong.h"
//#include "hal_lcd_fonts.h"

//struct ball* myBall;

// Whatever.....

/*ERASE THE CIRCLE*/
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
	//halLcdClearScreen();

	/* Draw a solid circle in a while loop by drawing a circle of
	 * Radius 0, then radius 1, ..., until we reach the radius
	 */
	//int i;
	//for(i = 0; i <= myBall->radius; i++) {
	//	halLcdCircle(myBall->x, myBall->y, i, PIXEL_ON);
	//}



	//myBall = newBall;
	//halLcdPrintLine("PONG", 1, OVERWRITE_TEXT);

	/*DRAW THE CIRCLE*/
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

void updateBall(Ball *myBall) {	/*double myDir = (myBall->dir)*(PI/180);*/}

void moveBall(Ball *myBall){
	eraseBall(myBall);
	int myRadius = myBall->radius;
	/*
	int oldY = myBall->y;
	int oldX = myBall->x;

	// Calculate the change in x and change in y for the ball's direction
	//double currentDir = (myBall->dir)(PI/180);
	double currentDir = myBall->radians;
	double dx = SPEED*cos(currentDir);
	double dy = SPEED*sin(currentDir);

	// Check to see if the ball is hitting a boundary
	//  If it is, flip the appropriate change in axis
	if(oldY <= myRadius) {				// Check for Top boundary
		dy *= -1;
	}
	if(oldX >= (WIDTH - myRadius)) {	// Check for Right or Left boundary
		dx *= -1;
	}
	if(oldY >= (HEIGHT - myRadius)) {	// Check for Bottom boundary
		dy *= -1;
	}
	if(oldX <= myRadius) {				// Check for Left boundary
		dx *= -1;
	}

	// Update the x and y coordinate of the ball
	myBall->y = oldY + dy;
	myBall->x = oldX + dy;

	// Calculate the new direction (Old if there was no bounce)
	double newAngle = atan(dy/dx);
	if(dx > 0) {
		myBall->radians = ((2*PI) + newAngle);
	} else if(dx < 0) {
		myBall->radians = PI + newAngle;
	} else {
		myBall->radians = ((2*PI) + newAngle);
	}
	*/



	switch(myBall->dir) {
		case UP:
			if(myBall->y > myRadius) {
				myBall->y -= 1;
			} else {
				myBall->dir = BOUNCE(myBall->dir);
				moveBall(myBall);
			}
			break;
		case RIGHT:
			if(myBall->x < (WIDTH - myRadius)) {
				myBall->x += 1;
			} else {
				myBall->dir = BOUNCE(myBall->dir);
				moveBall(myBall);
			}
			break;
		case DOWN:
			if(myBall->y < (HEIGHT - myRadius)) {
				myBall->y += 1;
			} else {
				myBall->dir = BOUNCE(myBall->dir);
				moveBall(myBall);
			}
			break;
		case LEFT:
			if(myBall->x > myRadius) {
				myBall->x -= 1;
			} else {
				myBall->dir = BOUNCE(myBall->dir);
				moveBall(myBall);
			}
			break;
		case NONE:							// Random Direction
			//myBall->dir = rand() % 360;
			moveBall(myBall);				// TESTING!!!
			break;
	}

	drawBall(myBall);
}

//void bounce(int currentDir) {
//	moveBall(
//}
