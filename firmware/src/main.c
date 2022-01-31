/*******************************************************************************
  Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This file contains the "main" function for a project.

  Description:
    This file contains the "main" function for a project.  The
    "main" function calls the "SYS_Initialize" function to initialize the state
    machines of all modules in the system
 *******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include "definitions.h"                // SYS function prototypes
#include "app.h"
#include <math.h>
#include <stdio.h>

// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
//MHC : package virsion 3.90
// *****************************************************************************
// *****************************************************************************

int main ( void )
{

    /* Initialize all modules */
    SYS_Initialize ( NULL );
//    WDT_Disable();
    printf("\r\n********************************************\r\n");
    printf("\r\n--------------------VHMS_CAN.V8.2.1 ,23/11/2021-----------------\r\n");
    printf("\r\n********************************************\r\n");
   
//    printf("\r\nGSM-GPS Initializing.....\r\n");
    
        
    WDT_Disable();    
    SYSTICK_TimerCallbackSet(&timeout_handler, (uintptr_t) NULL);
    SYSTICK_TimerStart();
    
    GSM_RST_PA05_Set();
    SYSTICK_DelayMs(300);
    GSM_RST_PA05_Clear();
    SYSTICK_DelayMs(2000);
    
    EIC_CallbackRegister(EIC_PIN_15,EIC_User_Handler, 0);
    TC0_TimerCallbackRegister(TC0_Callback_InterruptHandler, (uintptr_t)NULL);
    TC4_TimerCallbackRegister(TC4_Callback_InterruptHandler, (uintptr_t)NULL);
    TC3_TimerCallbackRegister(TC3_Callback_InterruptHandler, (uintptr_t)NULL);
    WDT_Disable();
//    WDT_Enable();  
//    WDT_Disable();
//    WDT_Clear();
//    SYSTICK_DelayMs(2000);
//    WDT_Clear();
//    SYSTICK_DelayMs(2000);
//    WDT_Clear();
//    SYSTICK_DelayMs(2000);
//    WDT_Clear();
//    SYSTICK_DelayMs(2000);
//    WDT_Clear();
//    SYSTICK_DelayMs(2000);
//    WDT_Clear();
//     while(1)
//        {
//            
//        }
    while ( true )
    {
        /* Maintain state machines of all polled MPLAB Harmony modules. */
        SYS_Tasks ( );
//        GPIO_PB30_Toggle();
    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}


/*******************************************************************************
 End of File
*/

