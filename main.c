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
	//halLcdBackLightInit();
	//halLcdSetBackLight(lcdBackLightLevelSettingLOCAL-5);
	halLcdSetContrast(lcdContrastSettingLOCAL+20);
	//halLcdSetContrast(0);
	halLcdClearScreen();

	//__delay_cycles(200000);
	
	//UCSCTL8 |= MODOSCREQEN;
}

int main() {
	WDTCTL = WDTPW + WDTHOLD;           // Stop WDT
	P1DIR |= BIT0 + BIT1;               // P1.0 and P1.1 LEDs configured as output
	initCP();

	__delay_cycles(200000);

	play(DOUBLE);
	//start1PlayerGame();
	
	//halLcdPrintLine("PONG", 2, OVERWRITE_TEXT);

	//halLcdCircle(myBall->x, myBall->y, 1, PIXEL_ON);
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
