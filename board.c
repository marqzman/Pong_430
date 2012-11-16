#include "msp430x54x.h"
#include "hal_lcd.h"
#include "board_defs.h"

#include "pong.h"



void makeBall(Ball* ball, int radius, int x, int y) {
	//Ball temp;
	//Ball *tempptr;
	//tempptr = &temp;

	ball->dir = UP;
	ball->radius = radius;
	ball->x = x;
	ball->y = y;


	//return tempptr;
}

/*
struct paddle makePaddle(int x) {
	struct paddle temp;
	temp.x = x;

	return temp;
}*/

void drawBoard() {
	// Clear the LCD
	// Draw each component
	// drawBall();
	// drawPaddle();
}

// mode = Single player; 2 Player; Agains MSP430
void play(int mode) {
	//while(1) {	
	//}
}

// Brings up the main menu
void startGame() {
//	halLcdPrintLine("PONG", 4, OVERWRITE_TEXT);
	Ball theBall;
	makeBall(&theBall, 2, WIDTH/2, HEIGHT/2);
	drawBall(&theBall);
	while(1) {
		moveBall(&theBall);
		//__delay_cycles(5000);
	}
	// Print a message...
	// halLcdPrintLine(buffer, 3, OVERWRITE_TEXT );

}

