/*******************************************************************************
  MPLAB Harmony Application Header File

  Company:
    Microchip Technology Inc.

  File Name:
    myapp.h

  Summary:
    This header file provides prototypes and definitions for the application.

  Description:
    This header file provides function prototypes and data type definitions for
    the application.  Some of these are required by the system (such as the
    "APP1_Initialize" and "APP1_Tasks" prototypes) and some of them are only used
    internally by the application (such as the "APP1_STATES" definition).  Both
    are defined here for convenience.
*******************************************************************************/

#ifndef _MYAPP_H
#define _MYAPP_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "configuration.h"
#include "driver/usart/drv_usart.h"
#include "peripheral/port/plib_port.h"
#include "peripheral/systick/plib_systick.h"
// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

extern "C" {

#endif
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Type Definitions
// *****************************************************************************
// *****************************************************************************
//#define APP1_DATA_SIZE   1
// *****************************************************************************
/* Application states

  Summary:
    Application states enumeration

  Description:
    This enumeration defines the valid application states.  These states
    determine the behavior of the application at various times.
*/

typedef enum
{
    /* Application's state machine's initial state. */
    MYAPP_STATE_INIT,
    MYAPP_STATE_LEDTOGGLE, 
	MYAPP_STATE_GSM_INITI,
    MYAPP_STATE_GSM_IDEL,        
	MYAPP_STATE_REC_SMS,
	MYAPP_STATE_SEND_SMS,
    MYAPP_STATE_SEND_SERVER        
       
//    APP1_STATE_TRANSMIT_MESSAGE,
//    APP1_STATE_WAIT_MESSAGE_TRANSFER_COMPLETE,
//    APP1_STATE_RECEIVE_DATA,
//    APP1_STATE_WAIT_RECEIVE_COMPLETE,
//    APP1_STATE_TRANSMIT_DATA,
//    APP1_STATE_WAIT_TRANSMIT_COMPLETE,
//    APP1_STATE_ERROR
} MYAPP_STATES;


// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    Application strings and buffers are be defined outside this structure.
 */

typedef struct
{
    MYAPP_STATES             state;
//    DRV_HANDLE              usartHandle;
//    DRV_USART_BUFFER_HANDLE bufferHandle;
//    char                    readBuffer[APP1_DATA_SIZE];
    volatile bool           transferStatus;
} MYAPP_DATA;

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Routines
// *****************************************************************************
// *****************************************************************************
/* These routines are called by drivers when certain events occur.
*/

// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP1_Initialize ( void )

  Summary:
     MPLAB Harmony application initialization routine.

  Description:
    This function initializes the Harmony application.  It places the
    application in its initial state and prepares it to run so that its
    APP1_Tasks function can be called.

  Precondition:
    All other system initialization routines should be called before calling
    this routine (in "SYS_Initialize").

  Parameters:
    None.

  Returns:
    None.

  Example:
    <code>
    APP1_Initialize();
    </code>

  Remarks:
    This routine must be called from the SYS_Initialize function.
*/

void MYAPP_Initialize ( void );


/*******************************************************************************
  Function:
    void APP1_Tasks ( void )

  Summary:
    MPLAB Harmony Demo application tasks function

  Description:
    This routine is the Harmony Demo application's tasks function.  It
    defines the application's state machine and core logic.

  Precondition:
    The system and application initialization ("SYS_Initialize") should be
    called before calling this.

  Parameters:
    None.

  Returns:
    None.

  Example:
    <code>
    APP1_Tasks();
    </code>

  Remarks:
    This routine must be called from SYS_Tasks() routine.
 */

void MYAPP_Tasks( void );

void ftoa(float n, char* res, int afterpoint);
void reverse(char* str, int len);
int intToStr(int x, char str[], int d);

#endif /* _APP1_H */

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

/*******************************************************************************
 End of File
 */

