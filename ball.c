#include "msp430x54x.h"
#include "hal_lcd.h"
#include "board_defs.h"

#include "pong.h"
//#include "hal_lcd_fonts.h"

//struct ball* myBall;

// Whatever.....

// Call the LCD functins to draw a ball
// at it's current location
void drawBall(Ball *myBall) {
	halLcdClearScreen();

	/* Draw a solid circle in a while loop by drawing a circle of
	 * Radius 0, then radius 1, ..., until we reach the radius
	 */
	//int i;
	//for(i = 0; i <= myBall->radius; i++) {
	//	halLcdCircle(myBall->x, myBall->y, i, PIXEL_ON);
	//}



	//myBall = newBall;
	//halLcdPrintLine("PONG", 1, OVERWRITE_TEXT);
	/*ERASE THE CIRCLE*/ /*
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
	*/


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

void updateBall(Ball *myBall) {
	//double myDir = (myBall->dir)*(PI/180);

}

void moveBall(Ball *myBall){
	int myRadius = myBall->radius;

	switch(myBall->dir) {
		case UP:
			if(myBall->y > myRadius) {
				myBall->y -= 1;
			} else {
				myBall->dir = BOUNCE(myBall->dir);
				//myBall->dir = DOWN;
				moveBall(myBall);
			}
			break;
		case RIGHT:
			if(myBall->x < (WIDTH - myRadius)) {
				myBall->x += 1;
			} else {
				myBall->dir = BOUNCE(myBall->dir);
				//myBall->dir = LEFT;
				moveBall(myBall);
			}
			break;
		case DOWN:
			if(myBall->y < (HEIGHT - myRadius)) {
				myBall->y += 1;
			} else {
				//myBall->dir = BOUNCE(myBall->dir);
				myBall->dir = 360 - (myBall->dir);
				//myBall->dir = UP;
				moveBall(myBall);
			}
			break;
		case LEFT:
			if(myBall->x > myRadius) {
				myBall->x -= 1;
			} else {
				myBall->dir = BOUNCE(myBall->dir);
				//myBall->dir = RIGHT;
				moveBall(myBall);
			}
			break;
		case NONE:							// Random Direction
			moveBall(myBall);				// TESTING!!!
			break;
	}

	drawBall(myBall);
}

//void bounce(int currentDir) {
//	moveBall(
//}
