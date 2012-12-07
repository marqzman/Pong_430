#include "msp430x54x.h"
#include "hal_lcd.h"
#include "board_defs.h"
#include "pong.h"
#include <stdlib.h>
#include <math.h>

/* PROTOTYPES*/
void startADC(void);
void startSingleGame(void);
void startDoubleGame(void);
void startComputerGame(void);

Ball theBall;
Paddle paddle1;
Paddle paddle2;

int pot1 = 0;
int pot2 = 0;


int gameOver = 0;
int paddleLength = STARTLENGTH;

void makeBall(Ball* ball, int radius, int x, int y) {
	ball->radius	=	2;
	ball->x		=	x;
	ball->y		=	y;
	ball->dx	=	(rand() % 2) ? -1 : 1;
	ball->dy	=	(rand() % 2) ? -1 : 1;
}

void makePaddle(Paddle* paddle, int length, int x, int y) {
	paddle->length	=	length;
	paddle->x 		=	x;
	paddle->y		=	y;
	paddle->score	=	0;
}

void checkWinner(Paddle* top, Paddle* bottom) {
	if(top->score > bottom->score) {
		P1OUT = BIT0;
	} else if(top->score < bottom->score) {
		P1OUT = BIT1;
	} else {
		P1OUT = BIT0 + BIT1;
	}
}

void prepare() {
	char buff [6] = {" " " " " " " " " " "\0"};
	int j;
	for(j = 3; j >= 0; j--) {
		buff[4] = '0' + j;
		halLcdPrintLine(buff, 4, OVERWRITE_TEXT);
		unsigned long i;
		for(i = 0; i < 500000; i++);
		for(i = 0; i < 500000; i++);
		for(i = 0; i < 500000; i++);
		for(i = 0; i < 500000; i++);
		for(i = 0; i < 500000; i++);
		for(i = 0; i < 500000; i++);
	}
	halLcdClearScreen();
}

// mode = Single player; 2 Player; Agains MSP430
void play(int mode) {
	initADC();
	gameOver = FALSE;
	halLcdClearScreen();
	prepare();
	paddleLength = STARTLENGTH/getLevel();
	switch(mode) {
		case SINGLE:
			startSingleGame();
			break;
		case DOUBLE:
			startDoubleGame();
			break;
		case COMPUTER:
			startComputerGame();
			break;
	}
	halLcdClearScreen();
}

// Starts a Single Player Game
void startSingleGame() {
	//int paddleX = WIDTH/2;
	// Make and draw the paddle
	makePaddle(&paddle1, paddleLength, WIDTH/2, HEIGHT - 14);
	drawPaddle(&paddle1);

	// Make and draw the ball
	makeBall(&theBall, 2, WIDTH/2, HEIGHT/2);
	drawBall(&theBall);

	// Play till there is a loser
	while(gameOver == FALSE) {
		startADC();
		pot1 /= 30;

		moveBall(&theBall, &paddle1);
		movePaddle(&paddle1, pot1);	// Testing
		__delay_cycles(100000);
	}

}

// Starts a Two Player Game
void startDoubleGame() {
	// Make and draw player 1's paddle
	makePaddle(&paddle1, paddleLength, WIDTH/2, HEIGHT - 14);
	drawPaddle(&paddle1);

	// Make and draw player 2's paddle
	makePaddle(&paddle2, paddleLength, WIDTH/2, 14);
	drawPaddle(&paddle2);

	// Make and draw the ball
	makeBall(&theBall, 2, WIDTH/2, HEIGHT/2);
	drawBall(&theBall);

	// Play until the game is over
	while(gameOver == FALSE) {
		startADC();
		moveBall2(&theBall, &paddle1, &paddle2);

		pot1 /= 30;
		pot2 /= 30;
		movePaddle(&paddle1, pot1);
		movePaddle(&paddle2, pot2);

		if((paddle1.score == 15) || (paddle2.score == 15)) {
			endGame();
		}
	}
	checkWinner(&paddle1, &paddle2);
}

void startComputerGame() {
	int compCounter = 0;
	// Make and draw player 1's paddle
	makePaddle(&paddle1, paddleLength, WIDTH/2, HEIGHT - 14);
	drawPaddle(&paddle1);

	// Make and draw the computer's paddle
	makePaddle(&paddle2, paddleLength, WIDTH/2, 14);
	drawPaddle(&paddle2);

	// Make and draw the ball
	makeBall(&theBall, 2, WIDTH/2, HEIGHT/2);
	drawBall(&theBall);

	while(gameOver == FALSE) {
		compCounter++;
		startADC();
		moveBall2(&theBall, &paddle1, &paddle2);
		pot1 /= 30;
		movePaddle(&paddle1, pot1);
		int temp = fabs(getLevel() - 4)/1;
		int turn = compCounter%temp;
		if(turn == 0) {
			// Move the AI
			if(theBall.x < paddle2.x) {
				movePaddle(&paddle2, paddle2.x - 1);
			} else if(theBall.x > paddle2.x) {
				movePaddle(&paddle2, paddle2.x + 1);
			}
		}

		if((paddle1.score == 15) || (paddle2.score == 15)) {
			endGame();
		}
	}
	checkWinner(&paddle1, &paddle2);
}

// Start ADC Conversion Process
void startADC() {
	ADC12IFG &= 0X0000;
	//ADC12IFG &= ~(ADC12IFG12 + ADC12IFG15);                 // Clear any pending flags
	ADC12CTL0 |=  ADC12ENC | ADC12SC;
	ADC12IE |= ADC12IE15;

	__bis_SR_register(LPM0_bits + GIE);
}

void initADC() {
	P5SEL &= (BIT0 | BIT1);
	P5DIR |= (BIT0 | BIT1);
	P5OUT |= (BIT0 | BIT1);

	// Configure the POTENTIOMETER
	P7SEL |= BIT4 | BIT7;               // Enable A/D channel inputs P7.4 & P7.5
	P7DIR &= ~(BIT4 | BIT7);            // P7.4 is configured as input

	ADC12CTL0 = ADC12ON + ADC12SHT02 + ADC12MSC;
	ADC12CTL1 = ADC12SHP + ADC12CONSEQ_1 + ADC12SSEL_0;
	ADC12CTL2 = ADC12RES_2;

	ADC12MCTL12 = ADC12SREF_0 + ADC12INCH_12;
	ADC12MCTL15 = ADC12SREF_0 + ADC12INCH_15 + ADC12EOS;

	__delay_cycles(200000);

	UCSCTL8 |= MODOSCREQEN;
}

#pragma vector=ADC12_VECTOR
__interrupt void ADC12_ISR(void)
{
	pot1 = ADC12MEM12;
	pot2 = ADC12MEM15;

    ADC12IFG = 0;                                       // Clear the interrupt flags
    ADC12CTL0 &= ~( ADC12ENC | ADC12SC | ADC12REFON);   // (disable conversion | No sample-and-conversion-start | Reference off)
    __bic_SR_register_on_exit(LPM0_bits);
}

void endGame() {
	gameOver = TRUE;
}
