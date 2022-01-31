/*******************************************************************************
  MPLAB Harmony Application Source File

  Company:
    Microchip Technology Inc.

  File Name:
    app1.c

  Summary:
    This file contains the source code for the MPLAB Harmony application.

  Description:
    This file contains the source code for the MPLAB Harmony application.  It
    implements the logic of the application's state machine and it may call
    API routines of other MPLAB Harmony modules in the system, such as drivers,
    system services, and middleware.  However, it does not call any of the
    system interfaces (such as the "Initialize" and "Tasks" functions) of any of
    the modules in the system or make any assumptions about when those functions
    are called.  That is the responsibility of the configuration-specific system
    files.
 *******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "myapp.h"
#include <string.h>
// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    This structure should be initialized by the APP1_Initialize function.

    Application strings and buffers are be defined outside this structure.
*/

static MYAPP_DATA myappData;

//const static char message1Buffer[] =
//"*** Console 1 ****\r\n"
//"*** USART Driver Echo Demo Application ****\r\n"
//"*** Type a character and observe it echo back ***\r\n"
//"*** LED toggles on each time the character is echoed ***\r\n";
// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

//static void APP1_USARTBufferEventHandler(
//    DRV_USART_BUFFER_EVENT bufferEvent,
//    DRV_USART_BUFFER_HANDLE bufferHandle,
//    uintptr_t context
//)
//{
//    switch(bufferEvent)
//    {
//        case DRV_USART_BUFFER_EVENT_COMPLETE:
//            app1Data.transferStatus = true;
//            break;
//
//        case DRV_USART_BUFFER_EVENT_ERROR:
//            app1Data.state = APP1_STATE_ERROR;
//            break;
//
//        default:
//            break;
//
//    }
//}

// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP1_Initialize ( void )

  Remarks:
    See prototype in app1.h.
 */

void MYAPP_Initialize ( void )
{
    /* Place the App state machine in its initial state. */
    myappData.state          = MYAPP_STATE_INIT;
//    myappData.ledStatus = false;
//    app1Data.usartHandle    = DRV_HANDLE_INVALID;
//    app1Data.bufferHandle   = DRV_USART_BUFFER_HANDLE_INVALID;
}

// Reverses a string 'str' of length 'len'
void reverse(char* str, int len)
{
    int i = 0, j = len - 1, temp;
    while (i < j) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++;
        j--;
    }
}
  
// Converts a given integer x to string str[]. 
// d is the number of digits required in the output. 
// If d is more than the number of digits in x, 
// then 0s are added at the beginning.
int intToStr(int x, char str[], int d)
{
    int i = 0;
    while (x) {
        str[i++] = (x % 10) + '0';
        x = x / 10;
    }
  
    // If number of digits required is more, then
    // add 0s at the beginning
    while (i < d)
        str[i++] = '0';
  
    reverse(str, i);
    str[i] = '\0';
    return i;
}
  
// Converts a floating-point/double number to a string.
void ftoa(float n, char* res, int afterpoint)
{
    sprintf(res,"%.2f",n); //Convert to string
    /************************************/
//    uint16_t whole,decimal;
////    char array[10];
//    whole=n*100; //whole part
//    
//    decimal= whole%100;//(n-whole)*100.0; //decimal part
//    sprintf(res,"%d.%02d",whole/100,decimal); //Convert to string
    
    /**************************************************/
    /*// Extract integer part
    int ipart = (int)n;
  
    // Extract floating part
    float fpart = n - (float)ipart;
  
    // convert integer part to string
    int i = intToStr(ipart, res, 1);
  
    // check for display option after point
    if (afterpoint != 0) {
        res[i] = '.'; // add dot
  
        // Get the value of fraction part upto given no.
        // of points after dot. The third parameter 
        // is needed to handle cases like 233.007
        fpart = fpart * pow(10, afterpoint);
  
        intToStr((int)fpart, res + i + 1, afterpoint);
    }*/
    
}

/******************************************************************************
  Function:
    void APP1_Tasks ( void )

  Remarks:
    See prototype in app1.h.
 */

void MYAPP_Tasks ( void )
{
    /* Check the application's current state. */
    switch ( myappData.state )
    {
        /* Application's initial state. */
        case MYAPP_STATE_INIT:

//            app1Data.usartHandle = DRV_USART_Open(DRV_USART_INDEX_0, DRV_IO_INTENT_READWRITE);
//            if (app1Data.usartHandle != DRV_HANDLE_INVALID)
//            {
//                DRV_USART_BufferEventHandlerSet(app1Data.usartHandle, APP1_USARTBufferEventHandler, 0);
//                app1Data.state = APP1_STATE_TRANSMIT_MESSAGE;
//            }
//            else
//            {
//                app1Data.state = APP1_STATE_ERROR;
//            }
            SYSTICK_TimerStart();
            myappData.state = MYAPP_STATE_LEDTOGGLE;
            
            
            break;

        case MYAPP_STATE_LEDTOGGLE:

//            GPIO_PB30_Toggle();
//            SYSTICK_DelayMs(500);
            myappData.state = MYAPP_STATE_GSM_INITI;
            break;

        case MYAPP_STATE_GSM_INITI:

            if(myappData.transferStatus == true)
            {
//                app1Data.transferStatus = false;
//                app1Data.state = APP1_STATE_RECEIVE_DATA;
            }
            break;
//        case APP1_STATE_RECEIVE_DATA:
//
//            DRV_USART_ReadBufferAdd(app1Data.usartHandle, app1Data.readBuffer, APP1_DATA_SIZE, &app1Data.bufferHandle);
//            if (app1Data.bufferHandle != DRV_USART_BUFFER_HANDLE_INVALID)
//            {
//                app1Data.state = APP1_STATE_WAIT_RECEIVE_COMPLETE;
//            }
//            else
//            {
//                app1Data.state = APP1_STATE_ERROR;
//            }
//            break;
//
//        case APP1_STATE_WAIT_RECEIVE_COMPLETE:
//
//            if(app1Data.transferStatus == true)
//            {
//                app1Data.transferStatus = false;
//                app1Data.state = APP1_STATE_TRANSMIT_DATA;
//            }
//            break;
//
//        case APP1_STATE_TRANSMIT_DATA:
//
//            /* Echo the received data back on the terminal */
//            DRV_USART_WriteBufferAdd(app1Data.usartHandle, app1Data.readBuffer, APP1_DATA_SIZE, &app1Data.bufferHandle);
//            if (app1Data.bufferHandle != DRV_USART_BUFFER_HANDLE_INVALID)
//            {
//                app1Data.state = APP1_STATE_WAIT_TRANSMIT_COMPLETE;
//            }
//            else
//            {
//                app1Data.state = APP1_STATE_ERROR;
//            }
//            break;
//
//        case APP1_STATE_WAIT_TRANSMIT_COMPLETE:
//
//            if(app1Data.transferStatus == true)
//            {
//                app1Data.transferStatus = false;
//
////                LED_TOGGLE();
//                GPIO_PB06_Toggle();
//                app1Data.state = APP1_STATE_RECEIVE_DATA;
//            }
//            break;
//
//        case APP1_STATE_ERROR:
//            break;

        default:
            break;
    }
}
//void MYAPP_Tasks ( void )
//{
////    static uint32_t start = 0;
////    start = readcoretimer();
////    while ((readcoretimer() - start) < ((busclk/2) / 1000)) 
////    {
////        
////    }
//    SYSTICK_DelayMs(500);
//}

/*******************************************************************************
 End of File
 */
