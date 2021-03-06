/*******************************************************************************
  MPLAB Harmony Application Header File

  Company:
    Microchip Technology Inc.

  File Name:
    app2.h

  Summary:
    This header file provides prototypes and definitions for the application.

  Description:
    This header file provides function prototypes and data type definitions for
    the application.  Some of these are required by the system (such as the
    "APP2_Initialize" and "APP2_Tasks" prototypes) and some of them are only used
    internally by the application (such as the "APP2_STATES" definition).  Both
    are defined here for convenience.
*******************************************************************************/

#ifndef _APP2_H
#define _APP2_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "configuration.h"
#include <string.h>
#include "definitions.h"

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
#define APP2_USART_READ_BUFFER_SIZE   500
#define APP2_USART_WRITE_BUFFER_SIZE  500
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
    APP2_STATE_INIT=0,
    APP2_STATE_SERVICE_TASKS,
    APP2_STATE_ERROR        
    /* TODO: Define states used by the application state machine. */

} APP2_STATES;


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
    /* The application's current state */
    APP2_STATES state;

    /* TODO: Define any additional data used by the application. */
    /* USART driver handle */
    DRV_HANDLE usartHandle;

    /* Handle returned by USART for buffer submitted */
    DRV_USART_BUFFER_HANDLE usartReadBufferHandle;
    DRV_USART_BUFFER_HANDLE usartWriteBufferHandle;
    /* USART buffer for display */
    uint16_t writeBufferCount;
    uint16_t readBufferCount;
    char writeBuffer[APP2_USART_WRITE_BUFFER_SIZE];
    char readBuffer[APP2_USART_READ_BUFFER_SIZE];
    DRV_USART_BUFFER_HANDLE bufferHandle;
    /* Data Size in the USART Buffer */
    uint32_t bufferSize;
    volatile bool           datavalideStatus;
} APP2_DATA;


char *pt1;

char vcl_p1[20];
char vcl_p2[20];
char vcl_p3[20];
char vcl_p4[20];
char vcl_p5[20];
char vcl_p6[20];
char vcl_p7[20];

char gps_UTCTime[20];
char gps_Status[20];
char gps_Latitude[20];
char gps_NSIndicator[20];
char gps_Longitude[20];
char gps_SpeedOverGround[20];

char gps_CourseOverGround[20];

char gps_EWIndicator[20];
char gps_Date[20];

char gps_Latitude_dec[20];
char gps_Longitude_dec[20];
//void loadgpsdata(void);
bool loadgpsdata(char *ch_gps_UTCTime,char *ch_gps_UTCdate);
bool loadgpstime(char *ch_gps_UTCTime,char *ch_gps_UTCdate);
//char ch_gps_UTCTime[20];
char ch_gps_Status[20];

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
    void APP2_Initialize ( void )

  Summary:
     MPLAB Harmony application initialization routine.

  Description:
    This function initializes the Harmony application.  It places the
    application in its initial state and prepares it to run so that its
    APP2_Tasks function can be called.

  Precondition:
    All other system initialization routines should be called before calling
    this routine (in "SYS_Initialize").

  Parameters:
    None.

  Returns:
    None.

  Example:
    <code>
    APP2_Initialize();
    </code>

  Remarks:
    This routine must be called from the SYS_Initialize function.
*/

void APP2_Initialize ( void );


/*******************************************************************************
  Function:
    void APP2_Tasks ( void )

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
    APP2_Tasks();
    </code>

  Remarks:
    This routine must be called from SYS_Tasks() routine.
 */

void APP2_Tasks( void );



#endif /* _APP2_H */

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

/*******************************************************************************
 End of File
 */

