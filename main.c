#include "msp430x54x.h"
#include "hal_lcd.h"
#include "board_defs.h"
#include "pong.h"


/* From LAB 3*/
	void halBoardStartXT1(void);
	void halBoardSetSystemClock(unsigned char systemClockSpeed);
	static void halBoardGetSystemClockSettings(unsigned char systemClockSpeed,
                                           unsigned char *setDcoRange,
                                           unsigned char *setVCore,
                                           unsigned int  *setMultiplier);

	//__no_init unsigned char lcdBackLightLevelSetting @ 0x1908;
	unsigned char lcdBackLightLevelSetting;
	unsigned char lcdContrastSetting;
	unsigned char lcdBackLightLevelSettingLOCAL;
	unsigned char lcdContrastSettingLOCAL;
/*End From LAB 3*/

// Initialize Clock and peripherals
void initCP() {
	halBoardStartXT1();
	halBoardSetSystemClock(SYSCLK_16MHZ);

	lcdBackLightLevelSettingLOCAL = lcdBackLightLevelSetting;
	lcdContrastSettingLOCAL = lcdContrastSetting;
	if ( lcdContrastSettingLOCAL < 60 || lcdContrastSettingLOCAL > 128)
		lcdContrastSettingLOCAL = 100;
	if ( lcdBackLightLevelSettingLOCAL > 15)
		lcdBackLightLevelSettingLOCAL = 16;

	// Initialize LCD and backlight
	halLcdInit();
	halLcdBackLightInit();
	halLcdSetBackLight(lcdBackLightLevelSettingLOCAL-5);
	halLcdSetContrast(lcdContrastSettingLOCAL+15);
	halLcdClearScreen();
}

initJoyStick() {
	// Configure button on P2.4 (UP) to cause an interrupt
	P2OUT |= BIT4;  // Configure output as High
	P2DIR &= ~BIT4; // Configure pin direction as input - overrides setting to high
	P2REN |= BIT4;  // Enable Pull-up resistor
	P2SEL &= ~BIT4; // Configure P2.4 as GPIO and not as some auxilary function

	// Enable interrupts for button on P2.4 (UP)
	P2IES &= ~BIT4;  // flag generated by low-to-high transition
	P2IFG &= ~BIT4;  // Clear Interrupt Flag for P2.4
	P2IE  |=  BIT4;  // enable Interrupt for P2.4

	// Configure button on P2.2 (RIGHT) to cause an interrupt
	P2OUT |= BIT2;  // Configure output as High
	P2DIR &= ~BIT2; // Configure pin direction as input - overrides setting to high
	P2REN |= BIT2;  // Enable Pull-up resistor
	P2SEL &= ~BIT2; // Configure P2.2 as GPIO and not as some auxilary function

	// Enable interrupts for button on P2.2 (RIGHT)
	P2IES &= ~BIT2;  // flag generated by low-to-high transition
	P2IFG &= ~BIT2;  // Clear Interrupt Flag for P2.2
	P2IE  |=  BIT2;  // enable Interrupt for P2.2

	// Configure button on P2.5 (DOWN) to cause an interrupt
	P2OUT |= BIT5;  // Configure output as High
	P2DIR &= ~BIT5; // Configure pin direction as input - overrides setting to high
	P2REN |= BIT5;  // Enable Pull-up resistor
	P2SEL &= ~BIT5; // Configure P2.5 as GPIO and not as some auxilary function

	// Enable interrupts for button on P2.5 (DOWN)
	P2IES &= ~BIT5;  // flag generated by low-to-high transition
	P2IFG &= ~BIT5;  // Clear Interrupt Flag for P2.5
	P2IE  |=  BIT5;  // enable Interrupt for P2.5

	// Configure button on P2.3 (SELECT) to cause an interrupt
	P2OUT |= BIT3;  // Configure output as High
	P2DIR &= ~BIT3; // Configure pin direction as input - overrides setting to high
	P2REN |= BIT3;  // Enable Pull-up resistor
	P2SEL &= ~BIT3; // Configure P2.3 as GPIO and not as some auxilary function

	// Enable interrupts for button on P2.3 (SELECT)
	P2IES &= ~BIT3;  // flag generated by low-to-high transition
	P2IFG &= ~BIT3;  // Clear Interrupt Flag for P2.3
	P2IE  |=  BIT3;  // enable Interrupt for P2.3

	// Configure button on P2.6 to cause an interrupt
	P2OUT |= BIT6;  // Configure output as High
	P2DIR &= ~BIT6; // Configure pin direction as input - overrides setting to high
	P2REN |= BIT6;  // Enable Pull-up resistor
	P2SEL &= ~BIT6; // Configure P2.6 as GPIO and not as some auxilary function

	// Enable interrupts for button on P2.6
	P2IES &= ~BIT6;  // flag generated by low-to-high transition
	P2IFG &= ~BIT6;  // Clear Interrupt Flag for P2.6
	P2IE  |=  BIT6;  // enable Interrupt for P2.6


	// Configure button on P2.7
	// Flag is used but no interrupt is generated

	P2OUT |= BIT7;  // Configure output as High
	P2DIR &= ~BIT7; // Configure pin direction as input - overrides setting to high
	P2REN |= BIT7;  // Enable Pull-up resistor
	P2SEL &= ~BIT7; // Configure P2.7 as GPIO and not as some auxilary function

	// Enable interrupts for button on P2.7
	P2IES &= ~BIT7; // flag generated by low-to-high transition
	P2IFG &= ~BIT7;	// Clear Interrupt Flag for P2.6
	P2IE |= BIT7;  	// enable Interrupt for P2.6
}

int level = EASY;
int menuLoc;
int mode;
int main() {
	WDTCTL = WDTPW + WDTHOLD;           // Stop WDT
	P1DIR |= BIT0 + BIT1;               // P1.0 and P1.1 LEDs configured as output
	initJoyStick();
	initCP();
	__bis_SR_register(GIE);
	mode = SINGLE;
	menuLoc = MODESELECT;


	// Go to low power mode to wait for the user input
	//__bis_SR_register(LPM0_bits + GIE);

	/* TESTING LOOP
	while(1) {
		halLcdPrintLine("Hello World", 5, OVERWRITE_TEXT);
	} */

	//play(SINGLE);
	//setMenuLoc(MODESELECT);
	while(1) {
		if(menuLoc != INGAME) {
			while(menuLoc == MODESELECT) {
				halLcdPrintLine("UP - 1 player", 1, OVERWRITE_TEXT);
				halLcdPrintLine("Right - 2 player", 4, OVERWRITE_TEXT);
				halLcdPrintLine("Down - vs. MSP430", 7, OVERWRITE_TEXT);
			}
			halLcdClearScreen();

			//setMenuLoc(DIFFSELECT);
			menuLoc = DIFFSELECT;
			while(menuLoc == DIFFSELECT) {
				halLcdPrintLine("Easy       Medium", 8, OVERWRITE_TEXT);
			}
			//setMenuLoc(INGAME);
			menuLoc = INGAME;
		}
		play(mode);
	}
}

// Port 2 interrupt service routine for button
#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void) {
    if(P2IFG & BIT4) {		// Up is pressed
    	//halLcdPrintLine("UP    ", 0, OVERWRITE_TEXT );
        P2IFG &= ~BIT4;
        if(menuLoc == MODESELECT) {
        	mode = SINGLE;
        	menuLoc = DIFFSELECT;
        	P2IE &= ~(BIT4 + BIT2 + BIT5);
        }
        __delay_cycles(20000);
    }
    else if(P2IFG & BIT2) {		// Right is pressed
    	//halLcdPrintLine("RIGHT ", 0, OVERWRITE_TEXT );
        P2IFG &= ~BIT2;
        if(menuLoc == MODESELECT) {
        	mode = DOUBLE;
        	menuLoc = DIFFSELECT;
        	P2IE &= ~(BIT4 + BIT2 + BIT5);
        }
        __delay_cycles(20000);
        }
    else if(P2IFG & BIT5) {		// Down is Pressed
    	//halLcdPrintLine("DOWN  ", 0, OVERWRITE_TEXT );
        P2IFG &= ~BIT5;
        if(menuLoc == MODESELECT) {
        	mode = SINGLE;
        	menuLoc = DIFFSELECT;
        	P2IE &= ~(BIT4 + BIT2 + BIT5);
        }
        __delay_cycles(20000);
    }
    else if(P2IFG & BIT6) {		// Left BUTTON is pressed
    	//halLcdPrintLine("EASY  ", 0, OVERWRITE_TEXT );
        P2IFG &= ~BIT6;  // Clear Interrupt Flag for P2.6
        if(menuLoc == DIFFSELECT) {
        	level = EASY;
        	menuLoc = INGAME;
        	P2IE &= ~(BIT6 + BIT7);
        }
        __delay_cycles(20000);
    }
    else if(P2IFG & BIT7) {		// Right BUTTON is pressed
    	//halLcdPrintLine("MEDIUM ", 0, OVERWRITE_TEXT );
        P2IFG &= ~BIT7;                          // P1.7 IFG cleared
        if(menuLoc == DIFFSELECT) {
        	level = MEDIUM;
        	menuLoc = INGAME;
        	P2IE &= ~(BIT6 + BIT7);
        }
        __delay_cycles(20000);
	} else if(P2IFG & BIT3) {		// MIDDLE is pressed
		// Clear the flag
		P2IFG &= ~BIT3;
		endGame();
		menuLoc = MODESELECT;

		//halLcdClearScreen();
		//halLcdPrintLine("OVER   ", 0, OVERWRITE_TEXT );
		__delay_cycles(1000000);
        P2IE |= (BIT2 + BIT4 + BIT5 + BIT6 + BIT7);
        __bis_SR_register(GIE);
        __delay_cycles(20000);
    }
    //__bic_SR_register_on_exit(LPM0_bits);

    //P1IFG &= ~0x010;                          // P1.4 IFG cleared
}

int getLevel() {
	return level;
}

int getMode() {
	return mode;
}

/*Functions from LAB 3*/
	void halBoardStartXT1(void) {
	    // Set up XT1 Pins to analog function, and to lowest drive
	    P7SEL |= 0x03;
	    UCSCTL6 |= XCAP_3 ;                       // Set internal cap values

	    while(SFRIFG1 & OFIFG) {                  // Check OFIFG fault flag
	        while ( (SFRIFG1 & OFIFG))              // Check OFIFG fault flag
	        {
	            // Clear OSC fault flags
	            UCSCTL7 &= ~(DCOFFG + XT1LFOFFG + XT1HFOFFG + XT2OFFG);
	            SFRIFG1 &= ~OFIFG;                    // Clear OFIFG fault flag
	        }
	        UCSCTL6 &= ~(XT1DRIVE1_L+XT1DRIVE0);    // Reduce the drive strength
	    }
	}

	void halBoardSetSystemClock(unsigned char systemClockSpeed) {
	    unsigned char setDcoRange, setVCore;
	    unsigned int  setMultiplier;

	    halBoardGetSystemClockSettings( systemClockSpeed, &setDcoRange,  \
	        &setVCore, &setMultiplier);

	    //halBoardSetVCore( setVCore );

	    __bis_SR_register(SCG0);                  // Disable the FLL control loop
	    UCSCTL0 = 0x00;                           // Set lowest possible DCOx, MODx
	    UCSCTL1 = setDcoRange;                    // Select suitable range

	    UCSCTL2 = setMultiplier + FLLD_1;         // Set DCO Multiplier
	    UCSCTL4 = SELA__XT1CLK | SELS__DCOCLKDIV  |  SELM__DCOCLKDIV ;
	    __bic_SR_register(SCG0);                  // Enable the FLL control loop

	    // Loop until XT1,XT2 & DCO fault flag is cleared
	    do
	    {
	        UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + XT1HFOFFG + DCOFFG);
	        // Clear XT2,XT1,DCO fault flags
	        SFRIFG1 &= ~OFIFG;                      // Clear fault flags
	    }while (SFRIFG1&OFIFG);                   // Test oscillator fault flag

	    // Worst-case settling time for the DCO when the DCO range bits have been
	    // changed is n x 32 x 32 x f_FLL_reference. See UCS chapter in 5xx UG
	    // for optimization.
	    // 32 x 32 x / f_FLL_reference (32,768 Hz) = .03125 = t_DCO_settle
	    // t_DCO_settle / (1 / 25 MHz) = 781250 = counts_DCO_settle
	    __delay_cycles(781250);
	}

	static void halBoardGetSystemClockSettings(unsigned char systemClockSpeed,
	                                           unsigned char *setDcoRange,
	                                           unsigned char *setVCore,
	                                           unsigned int  *setMultiplier) {
	    switch (systemClockSpeed)
	    {
	    case SYSCLK_1MHZ:
	        *setDcoRange = DCORSEL_1MHZ;
	        *setVCore = VCORE_1MHZ;
	        *setMultiplier = DCO_MULT_1MHZ;
	        break;
	    case SYSCLK_4MHZ:
	        *setDcoRange = DCORSEL_4MHZ;
	        *setVCore = VCORE_4MHZ;
	        *setMultiplier = DCO_MULT_4MHZ;
	        break;
	    case SYSCLK_8MHZ:
	        *setDcoRange = DCORSEL_8MHZ;
	        *setVCore = VCORE_8MHZ;
	        *setMultiplier = DCO_MULT_8MHZ;
	        break;
	    case SYSCLK_12MHZ:
	        *setDcoRange = DCORSEL_12MHZ;
	        *setVCore = VCORE_12MHZ;
	        *setMultiplier = DCO_MULT_12MHZ;
	        break;
	    case SYSCLK_16MHZ:
	        *setDcoRange = DCORSEL_16MHZ;
	        *setVCore = VCORE_16MHZ;
	        *setMultiplier = DCO_MULT_16MHZ;
	        break;
	    case SYSCLK_20MHZ:
	        *setDcoRange = DCORSEL_20MHZ;
	        *setVCore = VCORE_20MHZ;
	        *setMultiplier = DCO_MULT_20MHZ;
	        break;
	    case SYSCLK_25MHZ:
	        *setDcoRange = DCORSEL_25MHZ;
	        *setVCore = VCORE_25MHZ;
	        *setMultiplier = DCO_MULT_25MHZ;
	        break;
	    }
	}
/*End Functions from LAB 3*/
