#include "msp430x54x.h"
#include "hal_lcd.h"
#include "board_defs.h"
#include "pong.h"
#include <stdlib.h>
#include <math.h>

/* PROTOTYPES*/
char easy[5] = {"E" "A" "S" "Y" "\0"};
//void initADC(void);
void startADC(void);
void startSingleGame(void);
void startDoubleGame(void);
void startComputerGame(void);
int getX(void);
char med[7]	= {"M" "E" "D" "I" "U" "M" "\0"};

Ball theBall;
Paddle paddle1;
Paddle paddle2;

int pot1 = 0;
int pot2 = 0;

int xyz = 0;


int gameOver = 0;
int paddleLength = 0;

//float newX1 = 0.0;
//int newX2 = 0;
//int newX3 = 0;
//int newX2;

void makeBall(Ball* ball, int radius, int x, int y) {
	ball->radius	=	2;
	ball->x		=	x;
	ball->y		=	y;
	ball->dx	=	(rand() % 2);
	ball->dy	=	1;
}

void makePaddle(Paddle* paddle, int length, int x, int y) {
	paddle->length	=	length;
	paddle->x 		=	x;
	paddle->y		=	y;
	paddle->score	=	0;
}

void prepare() {
	char buff [6] = {" " " " " " " " " " "\0"};
	//char count [5] = {"3" "2" "1" "0" "\0"};
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
		/*
		int i, temp, avg;
		for(i = 0; i < 100; i ++) {
			startADC();
			temp = pot1*3;
			temp /= 2;
			avg += temp;
		}
		avg /= 100;
		*/
		pot1 /= 30;
		moveBall(&theBall, &paddle1);

		//paddleX = (paddleX + 1) % WIDTH;	// Testing
		//newX1 = (x_axis_sample/0XFFF)*WIDTH;
		//newX2 = (y_axis_sample/0XFFF)*WIDTH;
		//newX3 = (z_axis_sample/0XFFF)*WIDTH;
		//xyz = getX();
		//xyz *= WIDTH;
		//xyz /= 4095;
		//int temp = pot1*3;
		//temp /= 2;


		//movePaddle(&paddle1, xyz);	// Testing
		movePaddle(&paddle1, pot1);	// Testing
		//movePaddle(&paddle1, newX2);	// Testing
		//movePaddle(&paddle1, newX3);	// Testing

		__delay_cycles(100000);
	}

}

// Starts a Two Player Game
void startDoubleGame() {
	//int paddle1X = WIDTH/2;				// Testing; Move paddle automatically
	//int paddle2X = WIDTH/2;				// Testing; Move paddle automatically

	// Make and draw player 1's paddle
	makePaddle(&paddle1, paddleLength, WIDTH/2, HEIGHT - 14);
	drawPaddle(&paddle1);

	// Make and draw player 2's paddle
	makePaddle(&paddle2, paddleLength, WIDTH/2, 14);
	drawPaddle(&paddle2);

	// Make and draw the ball
	makeBall(&theBall, 2, WIDTH/2, HEIGHT/2);
	drawBall(&theBall);

	// Play forever
	while(gameOver == FALSE) {
		startADC();
		//int i, temp1, temp2, avg1, avg2;
		/*
		for(i = 0; i < 100; i ++) {
			startADC();
			temp1 = pot1*3;
			temp1 /= 2;
			avg1 += temp1;

			temp2 = pot2*3;
			temp2 /= 2;
			avg2 += temp2;
		}
		avg1 /= 100;
		avg2 /= 100;
		*/
		moveBall2(&theBall, &paddle1, &paddle2);

		//paddle1X = (paddle1X + 1) % WIDTH;	// Testing
		//paddle2X = (paddle2X - 1) % WIDTH;	// Testing
		pot1 /= 30;
		pot2 /= 30;
		movePaddle(&paddle1, pot1);				// Testing
		//if(paddle2X < paddle2.length) {
		//	paddle2X = WIDTH - paddle2.length;
		//}
		movePaddle(&paddle2, pot2);			// Testing

		if((paddle1.score == 15) || (paddle2.score == 15)) {
			endGame();
		}
		__delay_cycles(100000);
	}
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
	/* ACCELORAMETOR
	P6SEL |= BIT1 + BIT2;               		// Enable A/D channel inputs
	P6DIR &= ~(BIT1 + BIT2 + BIT3);             // P6.1, P6.2, and P6.3 (Vx, Vy, and Vz) are configured as input
	P6DIR |= BIT0;                      		// Enable ACC_POWER. Outputs from the MSP430 to the Peripheral module (ADXL322/330)
	P6OUT |= BIT0;                              // Turn on ACC_PWR

	// Configure ADC to sample 3 channels, we ignore z axis
	// Sequence of channels, once, using ACLK
	ADC12CTL0 = ADC12ON + ADC12SHT02 + ADC12MSC;
	ADC12CTL1 = ADC12SHP + ADC12CONSEQ_1 + ADC12SSEL_0;
	ADC12CTL2 = ADC12RES_2;
	ADC12MCTL0 = ADC12INCH_1;
	ADC12MCTL1 = ADC12INCH_2;
	ADC12MCTL2 = ADC12INCH_3 + ADC12EOS;
	*/

	P5SEL &= (BIT0 | BIT1);
	P5DIR |= (BIT0 | BIT1);
	P5OUT |= (BIT0 | BIT1);
	//P5SEL |= BIT0;						// Enable V+ ref
	//P5DIR |= BIT0;						// Set as output
	//P5OUT |= BIT0;						// Set output as high
	//P5SEL |= BIT1;						// Enable V+ ref
	//P5DIR |= BIT1;						// Set as output
	//P5OUT |= BIT1;						// Set output as high

	// Configure the POTENTIOMETER
	P7SEL |= BIT4 | BIT7;               // Enable A/D channel inputs P7.4 & P7.5
	P7DIR &= ~(BIT4 | BIT7);            // P7.4 is configured as input


	//P7DIR |= BIT0;                      // Enable ACC_POWER. Outputs from the MSP430 to the Peripheral module (ADXL322/330)
	//P7OUT |= BIT0;                      // Turn on ACC_PWR

	/*
	// Configure the ADC
	ADC12CTL0 = ADC12ON + ADC12SHT02 + ADC12MSC + ADC12REFON + ADC12REF2_5V;
	ADC12CTL1 = ADC12SHP + ADC12CONSEQ_1 + ADC12SSEL_0;
	ADC12CTL2 = ADC12REFOUT + ADC12RES_2;

	ADC12MCTL12 = ADC12SREF_5 + ADC12INCH_12;
	ADC12MCTL13 = ADC12SREF_5 + ADC12INCH_13 + ADC12EOS;
	*/

	ADC12CTL0 = ADC12ON + ADC12SHT02 + ADC12MSC;
	ADC12CTL1 = ADC12SHP + ADC12CONSEQ_1 + ADC12SSEL_0;
	ADC12CTL2 = ADC12RES_2;

	ADC12MCTL12 = ADC12SREF_0 + ADC12INCH_12;
	ADC12MCTL15 = ADC12SREF_0 + ADC12INCH_15 + ADC12EOS;

	__delay_cycles(200000);

	UCSCTL8 |= MODOSCREQEN;
}

int getX() {
	return pot1;
}

#pragma vector=ADC12_VECTOR
__interrupt void ADC12_ISR(void)
{
	//x_axis_sample = ADC12MEM0;
	pot1 = ADC12MEM12;
	pot2 = ADC12MEM15;
	//x_axis_sample /= 10;
	//y_axis_sample = ADC12MEM1;
	//z_axis_sample = ADC12MEM2;

	//char buffer[4];
	//unsigned int a = ADC12MEM0/42;
	//buffer[0] = '0' + (a/(1000)) % 10;
	//buffer[1] = '0' + (a/(100)) % 10;
	//buffer[0] = ' ';
	//buffer[1] = ' ';
	//buffer[2] = '0' + (a/(10)) % 10;
	//buffer[3] = '0' + (a) % 10;
	//newX1 = (a % 10) / 10;
	//buffer[1] = '0' + ADC12MEM1 % 10;
	//buffer[2] = '0' + ADC12MEM2 % 10;



	//newX1 = (ADC12MEM0/0XFFF)*WIDTH;
	//newX2 = (ADC12MEM1/0XFFF)*WIDTH;
	//newX3 = (ADC12MEM2/0XFFF)*WIDTH;
	//movePaddle(&paddle1, newX1);
	//char x[1] = {'0' + newX1};
	//halLcdPrintLine(buffer, 8, OVERWRITE_TEXT);
	//movePaddle(&paddle1, newX);
    ADC12IFG = 0;                                       // Clear the interrupt flags
    ADC12CTL0 &= ~( ADC12ENC | ADC12SC | ADC12REFON);   // (disable conversion | No sample-and-conversion-start | Reference off)
    __bic_SR_register_on_exit(LPM0_bits);
}

void endGame() {
	gameOver = TRUE;
}
