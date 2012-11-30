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
		myBall->dy = -1*(myBall->dy);
	}
}

void checkPaddle(Ball* myBall) {

}

void moveBall(Ball *myBall){
	// Erase the current location of the ball
	eraseBall(myBall);
	// Check for a bounce
	checkWalls(myBall);
	// Update the ball's position
	myBall->x += SPEED*myBall->dx;
	myBall->y += SPEED*myBall->dy;
	// Draw the ball in it's new location
	drawBall(myBall);
}
