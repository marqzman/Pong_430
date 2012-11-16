#include "pong.h"
#include "ball.h"
#include "board.h"

Ball theBall;

void drawBoard() {
	// Clear the LCD
	// Draw each component
	// drawBall();
	// drawPaddle();
}

// mode = Single player; 2 Player; Agains MSP430
void play(int mode) {
	while(1) {
		
	}
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
