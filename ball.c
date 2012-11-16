#include "hal_lcd.h"
#include "pong.h"
//#include "hal_lcd_fonts.h"

//struct ball* myBall;

// Call the LCD functins to draw a ball
// at it's current location
void drawBall(Ball *myBall) {
	//myBall = newBall;
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

void moveBall(Ball *myBall, int direction){
	switch(direction) {
		case UP:
			if(myBall->y > 2) {
				myBall->y -= 1;
				myBall->dir = UP;
			} else {
				moveBall(myBall, DOWN);
			}
			break;
		case UPRIGHT:
			break;
		case RIGHT:
			break;
		case DOWN:
			if(myBall->y < (HEIGHT - 2)) {
				myBall->y += 1;
				myBall->dir = DOWN;
			} else {
				moveBall(myBall, UP);
			}
			break;
		case LEFT:
			break;
		case 0:							// Random Direction
			moveBall(myBall, UP);		// TESTING!!!
			break;
	}
}

//void bounce(int currentDir) {
//	moveBall(
//}
