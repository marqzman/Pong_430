#include "pong.h"

Ball *theBall;

Ball *makeBall(int x, int y) {
	Ball *temp;
	temp.dir = UP;
	temp.x = x;
	temp.y = y;

	return temp;
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

// Brings up the main menue
void startGame() {
	theBall = makeBall(WIDTH/2, HEIGHT/2);
	drawBall(theBall);
	while(1) {
		moveBall(theBall, theBall.dir);
	}
	// Print a message...
	// halLcdPrintLine(buffer, 3, OVERWRITE_TEXT );
}

