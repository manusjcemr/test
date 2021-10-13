/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.78.1
        Device            :  PIC18F26K22
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.10 and above
        MPLAB 	          :  MPLAB X 5.30	
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

/**
  Section: Included Files
*/

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set SW_SET aliases
#define SW_SET_TRIS                 TRISAbits.TRISA0
#define SW_SET_LAT                  LATAbits.LATA0
#define SW_SET_PORT                 PORTAbits.RA0
#define SW_SET_ANS                  ANSELAbits.ANSA0
#define SW_SET_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define SW_SET_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define SW_SET_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define SW_SET_GetValue()           PORTAbits.RA0
#define SW_SET_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define SW_SET_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define SW_SET_SetAnalogMode()      do { ANSELAbits.ANSA0 = 1; } while(0)
#define SW_SET_SetDigitalMode()     do { ANSELAbits.ANSA0 = 0; } while(0)

// get/set channel_AN1 aliases
#define channel_AN1_TRIS                 TRISAbits.TRISA1
#define channel_AN1_LAT                  LATAbits.LATA1
#define channel_AN1_PORT                 PORTAbits.RA1
#define channel_AN1_ANS                  ANSELAbits.ANSA1
#define channel_AN1_SetHigh()            do { LATAbits.LATA1 = 1; } while(0)
#define channel_AN1_SetLow()             do { LATAbits.LATA1 = 0; } while(0)
#define channel_AN1_Toggle()             do { LATAbits.LATA1 = ~LATAbits.LATA1; } while(0)
#define channel_AN1_GetValue()           PORTAbits.RA1
#define channel_AN1_SetDigitalInput()    do { TRISAbits.TRISA1 = 1; } while(0)
#define channel_AN1_SetDigitalOutput()   do { TRISAbits.TRISA1 = 0; } while(0)
#define channel_AN1_SetAnalogMode()      do { ANSELAbits.ANSA1 = 1; } while(0)
#define channel_AN1_SetDigitalMode()     do { ANSELAbits.ANSA1 = 0; } while(0)

// get/set channel_AN2 aliases
#define channel_AN2_TRIS                 TRISAbits.TRISA2
#define channel_AN2_LAT                  LATAbits.LATA2
#define channel_AN2_PORT                 PORTAbits.RA2
#define channel_AN2_ANS                  ANSELAbits.ANSA2
#define channel_AN2_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define channel_AN2_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define channel_AN2_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define channel_AN2_GetValue()           PORTAbits.RA2
#define channel_AN2_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define channel_AN2_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define channel_AN2_SetAnalogMode()      do { ANSELAbits.ANSA2 = 1; } while(0)
#define channel_AN2_SetDigitalMode()     do { ANSELAbits.ANSA2 = 0; } while(0)

// get/set RA3 procedures
#define RA3_SetHigh()            do { LATAbits.LATA3 = 1; } while(0)
#define RA3_SetLow()             do { LATAbits.LATA3 = 0; } while(0)
#define RA3_Toggle()             do { LATAbits.LATA3 = ~LATAbits.LATA3; } while(0)
#define RA3_GetValue()              PORTAbits.RA3
#define RA3_SetDigitalInput()    do { TRISAbits.TRISA3 = 1; } while(0)
#define RA3_SetDigitalOutput()   do { TRISAbits.TRISA3 = 0; } while(0)
#define RA3_SetAnalogMode()         do { ANSELAbits.ANSA3 = 1; } while(0)
#define RA3_SetDigitalMode()        do { ANSELAbits.ANSA3 = 0; } while(0)

// get/set SW_CFG aliases
#define SW_CFG_TRIS                 TRISAbits.TRISA4
#define SW_CFG_LAT                  LATAbits.LATA4
#define SW_CFG_PORT                 PORTAbits.RA4
#define SW_CFG_SetHigh()            do { LATAbits.LATA4 = 1; } while(0)
#define SW_CFG_SetLow()             do { LATAbits.LATA4 = 0; } while(0)
#define SW_CFG_Toggle()             do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
#define SW_CFG_GetValue()           PORTAbits.RA4
#define SW_CFG_SetDigitalInput()    do { TRISAbits.TRISA4 = 1; } while(0)
#define SW_CFG_SetDigitalOutput()   do { TRISAbits.TRISA4 = 0; } while(0)

// get/set SW_DOWN aliases
#define SW_DOWN_TRIS                 TRISAbits.TRISA5
#define SW_DOWN_LAT                  LATAbits.LATA5
#define SW_DOWN_PORT                 PORTAbits.RA5
#define SW_DOWN_ANS                  ANSELAbits.ANSA5
#define SW_DOWN_SetHigh()            do { LATAbits.LATA5 = 1; } while(0)
#define SW_DOWN_SetLow()             do { LATAbits.LATA5 = 0; } while(0)
#define SW_DOWN_Toggle()             do { LATAbits.LATA5 = ~LATAbits.LATA5; } while(0)
#define SW_DOWN_GetValue()           PORTAbits.RA5
#define SW_DOWN_SetDigitalInput()    do { TRISAbits.TRISA5 = 1; } while(0)
#define SW_DOWN_SetDigitalOutput()   do { TRISAbits.TRISA5 = 0; } while(0)
#define SW_DOWN_SetAnalogMode()      do { ANSELAbits.ANSA5 = 1; } while(0)
#define SW_DOWN_SetDigitalMode()     do { ANSELAbits.ANSA5 = 0; } while(0)

// get/set SW_UP aliases
#define SW_UP_TRIS                 TRISAbits.TRISA7
#define SW_UP_LAT                  LATAbits.LATA7
#define SW_UP_PORT                 PORTAbits.RA7
#define SW_UP_SetHigh()            do { LATAbits.LATA7 = 1; } while(0)
#define SW_UP_SetLow()             do { LATAbits.LATA7 = 0; } while(0)
#define SW_UP_Toggle()             do { LATAbits.LATA7 = ~LATAbits.LATA7; } while(0)
#define SW_UP_GetValue()           PORTAbits.RA7
#define SW_UP_SetDigitalInput()    do { TRISAbits.TRISA7 = 1; } while(0)
#define SW_UP_SetDigitalOutput()   do { TRISAbits.TRISA7 = 0; } while(0)

// get/set SW_MICRO aliases
#define SW_MICRO_TRIS                 TRISBbits.TRISB0
#define SW_MICRO_LAT                  LATBbits.LATB0
#define SW_MICRO_PORT                 PORTBbits.RB0
#define SW_MICRO_WPU                  WPUBbits.WPUB0
#define SW_MICRO_ANS                  ANSELBbits.ANSB0
#define SW_MICRO_SetHigh()            do { LATBbits.LATB0 = 1; } while(0)
#define SW_MICRO_SetLow()             do { LATBbits.LATB0 = 0; } while(0)
#define SW_MICRO_Toggle()             do { LATBbits.LATB0 = ~LATBbits.LATB0; } while(0)
#define SW_MICRO_GetValue()           PORTBbits.RB0
#define SW_MICRO_SetDigitalInput()    do { TRISBbits.TRISB0 = 1; } while(0)
#define SW_MICRO_SetDigitalOutput()   do { TRISBbits.TRISB0 = 0; } while(0)
#define SW_MICRO_SetPullup()          do { WPUBbits.WPUB0 = 1; } while(0)
#define SW_MICRO_ResetPullup()        do { WPUBbits.WPUB0 = 0; } while(0)
#define SW_MICRO_SetAnalogMode()      do { ANSELBbits.ANSB0 = 1; } while(0)
#define SW_MICRO_SetDigitalMode()     do { ANSELBbits.ANSB0 = 0; } while(0)

// get/set C_SEG aliases
#define C_SEG_TRIS                 TRISBbits.TRISB1
#define C_SEG_LAT                  LATBbits.LATB1
#define C_SEG_PORT                 PORTBbits.RB1
#define C_SEG_WPU                  WPUBbits.WPUB1
#define C_SEG_ANS                  ANSELBbits.ANSB1
#define C_SEG_SetHigh()            do { LATBbits.LATB1 = 1; } while(0)
#define C_SEG_SetLow()             do { LATBbits.LATB1 = 0; } while(0)
#define C_SEG_Toggle()             do { LATBbits.LATB1 = ~LATBbits.LATB1; } while(0)
#define C_SEG_GetValue()           PORTBbits.RB1
#define C_SEG_SetDigitalInput()    do { TRISBbits.TRISB1 = 1; } while(0)
#define C_SEG_SetDigitalOutput()   do { TRISBbits.TRISB1 = 0; } while(0)
#define C_SEG_SetPullup()          do { WPUBbits.WPUB1 = 1; } while(0)
#define C_SEG_ResetPullup()        do { WPUBbits.WPUB1 = 0; } while(0)
#define C_SEG_SetAnalogMode()      do { ANSELBbits.ANSB1 = 1; } while(0)
#define C_SEG_SetDigitalMode()     do { ANSELBbits.ANSB1 = 0; } while(0)

// get/set D_SEG aliases
#define D_SEG_TRIS                 TRISBbits.TRISB2
#define D_SEG_LAT                  LATBbits.LATB2
#define D_SEG_PORT                 PORTBbits.RB2
#define D_SEG_WPU                  WPUBbits.WPUB2
#define D_SEG_ANS                  ANSELBbits.ANSB2
#define D_SEG_SetHigh()            do { LATBbits.LATB2 = 1; } while(0)
#define D_SEG_SetLow()             do { LATBbits.LATB2 = 0; } while(0)
#define D_SEG_Toggle()             do { LATBbits.LATB2 = ~LATBbits.LATB2; } while(0)
#define D_SEG_GetValue()           PORTBbits.RB2
#define D_SEG_SetDigitalInput()    do { TRISBbits.TRISB2 = 1; } while(0)
#define D_SEG_SetDigitalOutput()   do { TRISBbits.TRISB2 = 0; } while(0)
#define D_SEG_SetPullup()          do { WPUBbits.WPUB2 = 1; } while(0)
#define D_SEG_ResetPullup()        do { WPUBbits.WPUB2 = 0; } while(0)
#define D_SEG_SetAnalogMode()      do { ANSELBbits.ANSB2 = 1; } while(0)
#define D_SEG_SetDigitalMode()     do { ANSELBbits.ANSB2 = 0; } while(0)

// get/set E_SEG aliases
#define E_SEG_TRIS                 TRISBbits.TRISB3
#define E_SEG_LAT                  LATBbits.LATB3
#define E_SEG_PORT                 PORTBbits.RB3
#define E_SEG_WPU                  WPUBbits.WPUB3
#define E_SEG_ANS                  ANSELBbits.ANSB3
#define E_SEG_SetHigh()            do { LATBbits.LATB3 = 1; } while(0)
#define E_SEG_SetLow()             do { LATBbits.LATB3 = 0; } while(0)
#define E_SEG_Toggle()             do { LATBbits.LATB3 = ~LATBbits.LATB3; } while(0)
#define E_SEG_GetValue()           PORTBbits.RB3
#define E_SEG_SetDigitalInput()    do { TRISBbits.TRISB3 = 1; } while(0)
#define E_SEG_SetDigitalOutput()   do { TRISBbits.TRISB3 = 0; } while(0)
#define E_SEG_SetPullup()          do { WPUBbits.WPUB3 = 1; } while(0)
#define E_SEG_ResetPullup()        do { WPUBbits.WPUB3 = 0; } while(0)
#define E_SEG_SetAnalogMode()      do { ANSELBbits.ANSB3 = 1; } while(0)
#define E_SEG_SetDigitalMode()     do { ANSELBbits.ANSB3 = 0; } while(0)

// get/set G_SEG aliases
#define G_SEG_TRIS                 TRISBbits.TRISB4
#define G_SEG_LAT                  LATBbits.LATB4
#define G_SEG_PORT                 PORTBbits.RB4
#define G_SEG_WPU                  WPUBbits.WPUB4
#define G_SEG_ANS                  ANSELBbits.ANSB4
#define G_SEG_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define G_SEG_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define G_SEG_Toggle()             do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
#define G_SEG_GetValue()           PORTBbits.RB4
#define G_SEG_SetDigitalInput()    do { TRISBbits.TRISB4 = 1; } while(0)
#define G_SEG_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)
#define G_SEG_SetPullup()          do { WPUBbits.WPUB4 = 1; } while(0)
#define G_SEG_ResetPullup()        do { WPUBbits.WPUB4 = 0; } while(0)
#define G_SEG_SetAnalogMode()      do { ANSELBbits.ANSB4 = 1; } while(0)
#define G_SEG_SetDigitalMode()     do { ANSELBbits.ANSB4 = 0; } while(0)

// get/set F_SEG aliases
#define F_SEG_TRIS                 TRISBbits.TRISB5
#define F_SEG_LAT                  LATBbits.LATB5
#define F_SEG_PORT                 PORTBbits.RB5
#define F_SEG_WPU                  WPUBbits.WPUB5
#define F_SEG_ANS                  ANSELBbits.ANSB5
#define F_SEG_SetHigh()            do { LATBbits.LATB5 = 1; } while(0)
#define F_SEG_SetLow()             do { LATBbits.LATB5 = 0; } while(0)
#define F_SEG_Toggle()             do { LATBbits.LATB5 = ~LATBbits.LATB5; } while(0)
#define F_SEG_GetValue()           PORTBbits.RB5
#define F_SEG_SetDigitalInput()    do { TRISBbits.TRISB5 = 1; } while(0)
#define F_SEG_SetDigitalOutput()   do { TRISBbits.TRISB5 = 0; } while(0)
#define F_SEG_SetPullup()          do { WPUBbits.WPUB5 = 1; } while(0)
#define F_SEG_ResetPullup()        do { WPUBbits.WPUB5 = 0; } while(0)
#define F_SEG_SetAnalogMode()      do { ANSELBbits.ANSB5 = 1; } while(0)
#define F_SEG_SetDigitalMode()     do { ANSELBbits.ANSB5 = 0; } while(0)

// get/set B_SEG aliases
#define B_SEG_TRIS                 TRISBbits.TRISB6
#define B_SEG_LAT                  LATBbits.LATB6
#define B_SEG_PORT                 PORTBbits.RB6
#define B_SEG_WPU                  WPUBbits.WPUB6
#define B_SEG_SetHigh()            do { LATBbits.LATB6 = 1; } while(0)
#define B_SEG_SetLow()             do { LATBbits.LATB6 = 0; } while(0)
#define B_SEG_Toggle()             do { LATBbits.LATB6 = ~LATBbits.LATB6; } while(0)
#define B_SEG_GetValue()           PORTBbits.RB6
#define B_SEG_SetDigitalInput()    do { TRISBbits.TRISB6 = 1; } while(0)
#define B_SEG_SetDigitalOutput()   do { TRISBbits.TRISB6 = 0; } while(0)
#define B_SEG_SetPullup()          do { WPUBbits.WPUB6 = 1; } while(0)
#define B_SEG_ResetPullup()        do { WPUBbits.WPUB6 = 0; } while(0)

// get/set A_SEG aliases
#define A_SEG_TRIS                 TRISBbits.TRISB7
#define A_SEG_LAT                  LATBbits.LATB7
#define A_SEG_PORT                 PORTBbits.RB7
#define A_SEG_WPU                  WPUBbits.WPUB7
#define A_SEG_SetHigh()            do { LATBbits.LATB7 = 1; } while(0)
#define A_SEG_SetLow()             do { LATBbits.LATB7 = 0; } while(0)
#define A_SEG_Toggle()             do { LATBbits.LATB7 = ~LATBbits.LATB7; } while(0)
#define A_SEG_GetValue()           PORTBbits.RB7
#define A_SEG_SetDigitalInput()    do { TRISBbits.TRISB7 = 1; } while(0)
#define A_SEG_SetDigitalOutput()   do { TRISBbits.TRISB7 = 0; } while(0)
#define A_SEG_SetPullup()          do { WPUBbits.WPUB7 = 1; } while(0)
#define A_SEG_ResetPullup()        do { WPUBbits.WPUB7 = 0; } while(0)

// get/set DB_SEG aliases
#define DB_SEG_TRIS                 TRISCbits.TRISC0
#define DB_SEG_LAT                  LATCbits.LATC0
#define DB_SEG_PORT                 PORTCbits.RC0
#define DB_SEG_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define DB_SEG_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define DB_SEG_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define DB_SEG_GetValue()           PORTCbits.RC0
#define DB_SEG_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define DB_SEG_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)

// get/set SSR1 aliases
#define SSR1_TRIS                 TRISCbits.TRISC1
#define SSR1_LAT                  LATCbits.LATC1
#define SSR1_PORT                 PORTCbits.RC1
#define SSR1_SetHigh()            do { LATCbits.LATC1 = 1; } while(0)
#define SSR1_SetLow()             do { LATCbits.LATC1 = 0; } while(0)
#define SSR1_Toggle()             do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define SSR1_GetValue()           PORTCbits.RC1
#define SSR1_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define SSR1_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)

// get/set SSR2 aliases
#define SSR2_TRIS                 TRISCbits.TRISC2
#define SSR2_LAT                  LATCbits.LATC2
#define SSR2_PORT                 PORTCbits.RC2
#define SSR2_ANS                  ANSELCbits.ANSC2
#define SSR2_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define SSR2_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define SSR2_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define SSR2_GetValue()           PORTCbits.RC2
#define SSR2_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define SSR2_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define SSR2_SetAnalogMode()      do { ANSELCbits.ANSC2 = 1; } while(0)
#define SSR2_SetDigitalMode()     do { ANSELCbits.ANSC2 = 0; } while(0)

// get/set DIGIT1 aliases
#define DIGIT1_TRIS                 TRISCbits.TRISC5
#define DIGIT1_LAT                  LATCbits.LATC5
#define DIGIT1_PORT                 PORTCbits.RC5
#define DIGIT1_ANS                  ANSELCbits.ANSC5
#define DIGIT1_SetHigh()            do { LATCbits.LATC5 = 1; } while(0)
#define DIGIT1_SetLow()             do { LATCbits.LATC5 = 0; } while(0)
#define DIGIT1_Toggle()             do { LATCbits.LATC5 = ~LATCbits.LATC5; } while(0)
#define DIGIT1_GetValue()           PORTCbits.RC5
#define DIGIT1_SetDigitalInput()    do { TRISCbits.TRISC5 = 1; } while(0)
#define DIGIT1_SetDigitalOutput()   do { TRISCbits.TRISC5 = 0; } while(0)
#define DIGIT1_SetAnalogMode()      do { ANSELCbits.ANSC5 = 1; } while(0)
#define DIGIT1_SetDigitalMode()     do { ANSELCbits.ANSC5 = 0; } while(0)

// get/set DIGIT2 aliases
#define DIGIT2_TRIS                 TRISCbits.TRISC6
#define DIGIT2_LAT                  LATCbits.LATC6
#define DIGIT2_PORT                 PORTCbits.RC6
#define DIGIT2_ANS                  ANSELCbits.ANSC6
#define DIGIT2_SetHigh()            do { LATCbits.LATC6 = 1; } while(0)
#define DIGIT2_SetLow()             do { LATCbits.LATC6 = 0; } while(0)
#define DIGIT2_Toggle()             do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define DIGIT2_GetValue()           PORTCbits.RC6
#define DIGIT2_SetDigitalInput()    do { TRISCbits.TRISC6 = 1; } while(0)
#define DIGIT2_SetDigitalOutput()   do { TRISCbits.TRISC6 = 0; } while(0)
#define DIGIT2_SetAnalogMode()      do { ANSELCbits.ANSC6 = 1; } while(0)
#define DIGIT2_SetDigitalMode()     do { ANSELCbits.ANSC6 = 0; } while(0)

// get/set DIGIT3 aliases
#define DIGIT3_TRIS                 TRISCbits.TRISC7
#define DIGIT3_LAT                  LATCbits.LATC7
#define DIGIT3_PORT                 PORTCbits.RC7
#define DIGIT3_ANS                  ANSELCbits.ANSC7
#define DIGIT3_SetHigh()            do { LATCbits.LATC7 = 1; } while(0)
#define DIGIT3_SetLow()             do { LATCbits.LATC7 = 0; } while(0)
#define DIGIT3_Toggle()             do { LATCbits.LATC7 = ~LATCbits.LATC7; } while(0)
#define DIGIT3_GetValue()           PORTCbits.RC7
#define DIGIT3_SetDigitalInput()    do { TRISCbits.TRISC7 = 1; } while(0)
#define DIGIT3_SetDigitalOutput()   do { TRISCbits.TRISC7 = 0; } while(0)
#define DIGIT3_SetAnalogMode()      do { ANSELCbits.ANSC7 = 1; } while(0)
#define DIGIT3_SetDigitalMode()     do { ANSELCbits.ANSC7 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/