#include "msp430x54x.h"
#include "hal_lcd.h"
#include "board_defs.h"
#include "pong.h"
#include <stdlib.h>
#include <math.h>

/* PROTOTYPES*/
void initADC(void);
void startADC1(void);
void startSingleGame(void);
void startDoubleGame(void);
int getX(void);

Ball theBall;
Paddle paddle1;
Paddle paddle2;

int x_axis_sample = 0;
int y_axis_sample = 0;
int z_axis_sample = 0;
int xyz = 0;


float newX1 = 0.0;
int newX2 = 0;
int newX3 = 0;
//int newX2;

void makeBall(Ball* ball, int radius, int x, int y) {
	ball->x		=	x;
	ball->y		=	y;
	ball->dx	=	1;
	ball->dy	=	1;
}

void makePaddle(Paddle* paddle, int length, int x, int y) {
	paddle->length	=	length;
	paddle->x 		=	x;
	paddle->y		=	y;
	paddle->score	=	0;
}

// mode = Single player; 2 Player; Agains MSP430
void play(int mode) {
	initADC();
	switch(mode) {
		case SINGLE:
			startSingleGame();
			break;
		case DOUBLE:
			startDoubleGame();
			break;
		case COMPUTER:
			break;
	}
}

// Starts a Single Player Game
void startSingleGame() {
	//int paddleX = WIDTH/2;
	// Make and draw the paddle
	makePaddle(&paddle1, 6, WIDTH/2, HEIGHT - 12);
	drawPaddle(&paddle1);

	// Make and draw the ball
	makeBall(&theBall, 2, WIDTH/2, HEIGHT/2);
	drawBall(&theBall);

	// Play forever
	while(1) {
		startADC1();

		moveBall(&theBall, &paddle1);

		//paddleX = (paddleX + 1) % WIDTH;	// Testing
		//newX1 = (x_axis_sample/0XFFF)*WIDTH;
		//newX2 = (y_axis_sample/0XFFF)*WIDTH;
		//newX3 = (z_axis_sample/0XFFF)*WIDTH;
		//xyz = getX();
		//xyz *= WIDTH;
		//xyz /= 4095;

		movePaddle(&paddle1, xyz);	// Testing
		//movePaddle(&paddle1, newX2);	// Testing
		//movePaddle(&paddle1, newX3);	// Testing

		__delay_cycles(100000);
	}
}

// Starts a Two Player Game
void startDoubleGame() {
	int paddle1X = WIDTH/2;
	int paddle2X = WIDTH/2;

	// Make and draw player 1's paddle
	makePaddle(&paddle1, 6, WIDTH/2, HEIGHT - 12);
	drawPaddle(&paddle1);

	// Make and draw player 2's paddle
	makePaddle(&paddle2, 6, WIDTH/2, 12);
	drawPaddle(&paddle2);

	// Make and draw the ball
	makeBall(&theBall, 2, WIDTH/2, HEIGHT/2);
	drawBall(&theBall);

	// Play forever
	while(1) {
		moveBall2(&theBall, &paddle1, &paddle2);

		paddle1X = (paddle1X + 1) % WIDTH;	// Testing
		paddle2X = (paddle2X - 1) % WIDTH;	// Testing

		movePaddle(&paddle1, paddle1X);				// Testing
		movePaddle(&paddle2, fabs(paddle2X));		// Testing

		__delay_cycles(100000);
	}
}

// Start ADC Conversion Process
void startADC1() {
	ADC12IFG &= ~(BIT0);                 // Clear any pending flags
	ADC12CTL0 |=  ADC12ENC | ADC12SC;
	ADC12IE |= BIT0;

	__bis_SR_register(LPM0_bits + GIE);
}

void initADC() {
	P6SEL |= BIT1 + BIT2;               // Enable A/D channel inputs
	P6DIR &= ~(BIT1 + BIT2 + BIT3);             // P6.1, P6.2, and P6.3 (Vx, Vy, and Vz) are configured as input
	P6DIR |= BIT0;                      // Enable ACC_POWER. Outputs from the MSP430 to the Peripheral module (ADXL322/330)
	P6OUT |= BIT0;                                              // Turn on ACC_PWR

	// Configure ADC to sample 3 channels, we ignore z axis
	// Sequence of channels, once, using ACLK
	ADC12CTL0 = ADC12ON + ADC12SHT02 + ADC12MSC;
	ADC12CTL1 = ADC12SHP + ADC12CONSEQ_1 + ADC12SSEL_0;
	ADC12CTL2 = ADC12RES_2;
	ADC12MCTL0 = ADC12INCH_1;
	ADC12MCTL1 = ADC12INCH_2;
	ADC12MCTL2 = ADC12INCH_3 + ADC12EOS;
}

int getX() {
	return x_axis_sample;
}

#pragma vector=ADC12_VECTOR
__interrupt void ADC12_ISR(void)
{
	//x_axis_sample = ADC12MEM0;
	xyz = ADC12MEM0;
	y_axis_sample = ADC12MEM1;
	z_axis_sample = ADC12MEM2;

	char buffer[4];
	unsigned int a = ADC12MEM0/42;
	//buffer[0] = '0' + (a/(1000)) % 10;
	//buffer[1] = '0' + (a/(100)) % 10;
	buffer[0] = ' ';
	buffer[1] = ' ';
	buffer[2] = '0' + (a/(10)) % 10;
	buffer[3] = '0' + (a) % 10;
	newX1 = (a % 10) / 10;
	//buffer[1] = '0' + ADC12MEM1 % 10;
	//buffer[2] = '0' + ADC12MEM2 % 10;



	//newX1 = (ADC12MEM0/0XFFF)*WIDTH;
	//newX2 = (ADC12MEM1/0XFFF)*WIDTH;
	//newX3 = (ADC12MEM2/0XFFF)*WIDTH;
	//movePaddle(&paddle1, newX1);
	//char x[1] = {'0' + newX1};
	halLcdPrintLine(buffer, 8, OVERWRITE_TEXT);
	//movePaddle(&paddle1, newX);
    ADC12IFG = 0;                                       // Clear the interrupt flags
    ADC12CTL0 &= ~( ADC12ENC | ADC12SC | ADC12REFON);   // (disable conversion | No sample-and-conversion-start | Reference off)
    __bic_SR_register_on_exit(LPM0_bits);
}
