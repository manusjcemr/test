/*******************************************************************************
  MPLAB Harmony Application Header File

  Company:
    Microchip Technology Inc.

  File Name:
    app3.h

  Summary:
    This header file provides prototypes and definitions for the application.

  Description:
    This header file provides function prototypes and data type definitions for
    the application.  Some of these are required by the system (such as the
    "APP3_Initialize" and "APP3_Tasks" prototypes) and some of them are only used
    internally by the application (such as the "APP3_STATES" definition).  Both
    are defined here for convenience.
*******************************************************************************/

#ifndef _APP3_H
#define _APP3_H

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
#include "definitions.h"                // SYS function prototypes

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
    APP3_STATE_INITIALIZE,
    APP3_STATE_FLASH_WRITE_ENABLE,
    APP3_STATE_FLASH_WRITE,
    APP3_STATE_FLASH_READ_STATUS,
    APP3_STATE_FLASH_CHECK_STATUS,
    APP3_STATE_FLASH_READ,
    APP3_STATE_DATA_COMPARISON,
    APP3_STATE_XFER_SUCCESSFUL,
    APP3_STATE_XFER_ERROR
    /* TODO: Define states used by the application state machine. */

} APP3_STATES;


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
    APP3_STATES state;

    /* TODO: Define any additional data used by the application. */

} APP3_DATA;

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
    void APP3_Initialize ( void )

  Summary:
     MPLAB Harmony application initialization routine.

  Description:
    This function initializes the Harmony application.  It places the
    application in its initial state and prepares it to run so that its
    APP3_Tasks function can be called.

  Precondition:
    All other system initialization routines should be called before calling
    this routine (in "SYS_Initialize").

  Parameters:
    None.

  Returns:
    None.

  Example:
    <code>
    APP3_Initialize();
    </code>

  Remarks:
    This routine must be called from the SYS_Initialize function.
*/

void APP3_Initialize ( void );


/*******************************************************************************
  Function:
    void APP3_Tasks ( void )

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
    APP3_Tasks();
    </code>

  Remarks:
    This routine must be called from SYS_Tasks() routine.
 */
#define FLASH_DATA                         "WRITING AND READING DATA FROM FLASH!"
#define FLASH_DATA_LEN                     sizeof(FLASH_DATA)

void APP3_Tasks( void );
uint8_t  flashtxData[(4 + FLASH_DATA_LEN)];
uint8_t  flashrxData[(4 + FLASH_DATA_LEN)];



///**************************/
typedef union  
{
	struct
	{
        uint8_t Startchar;          //:1//"&"
        uint8_t SLheader[10]; //:10//uint8_t SLheader[6];       //:6//"VDT300"
//        uint16_t serialno;        //:4 
        uint8_t date[6];          //:6
        uint8_t time[6];     //:6
        uint8_t valid;           //:1
        uint8_t lat[9];         //:9
        char NSIndicator;     //1
        uint8_t lng[10];         //:10 
        char EWIndicator; //1
        float adc1;           //:4
        float adc2;           //:4
        uint8_t digdata;      //:1
        float adc3;           //:4
        float adc4;           //:4
        float adc5;           //:4
        uint16_t frq;         //:4
        float adc6;           //:4
        float smr;            //:4
        uint8_t Endchar;       //:1//"^"
        uint16_t CRC_check;   //:4 
	}PacketField;
	
	uint8_t rcvpacket[85];//256/2 = 128max
}packet;
packet logwdata,logrdata;

typedef union  
{
	struct
	{
        uint32_t memaddr;   //:4 
        uint8_t flag;       //:1
        
	}PacketField;
	
	uint8_t addrbuf[5];//256/2 = 128max
}rewrite;
rewrite wnewmemloc,rnewmemloc,wyet2sendmemloc,ryet2sendmemloc,wrecomemloc,rrecomemloc,wmaxmemloc,rmaxmemloc,freshdatamemloc1,freshdatamemloc2,smrvalue,flagbit;

void saveserialNo(uint8_t *data);
void readserialNo(uint8_t *data);
void saveIPaddr(uint8_t *data);
void readIPaddr(uint8_t *data);
void saveAPNaddr(uint8_t *data);
void readAPNaddr(uint8_t *data);

void savenewmemloc(uint8_t *data);
void readnewmemloc(uint8_t *data);

void saveyet2sendmemloc(uint8_t *data);
void readyet2sendmemloc(uint8_t *data);
void saverecomemloc(uint8_t *data);
void readrecomemloc(uint8_t *data);
void savemaxmemloc(uint8_t *data);
void readmaxmemloc(uint8_t *data);

void savefreshdatamemloc1(uint8_t *data);
void readfreshdatamemloc1(uint8_t *data);
void savefreshdatamemloc2(uint8_t *data);
void readfreshdatamemloc2(uint8_t *data);
void savesmr(uint8_t *data);
void readsmr(uint8_t *data);
void saveFLAG(uint8_t *data);
void readFLAG(uint8_t *data);
void saveunsenddata1(uint8_t *data);
void saveunsenddata2(uint8_t *data);
extern void SPI_HighSpeed_Read_Cont(unsigned long Dst,unsigned long no_bytes, uint8_t *read_data);
void savelogdata(uint8_t * data,unsigned long bufsize,unsigned long memloc);
void readlogdata(uint8_t * data,unsigned long bufsize,unsigned long memloc);
void savefreshlogdata1(uint8_t * data,unsigned long bufsize,unsigned long memloc);
void readfreshlogdata1(uint8_t * data,unsigned long bufsize,unsigned long memloc);
void savefreshlogdata2(uint8_t * data,unsigned long bufsize,unsigned long memloc);
void readfreshlogdata2(uint8_t * data,unsigned long bufsize,unsigned long memloc);
bool savelivedatatotempmem1(void);
bool savelivedatatotempmem2(void);
bool loadlivedata1(char * data);
//bool loadlivedata1(char * data,uint8_t *memdata);
bool loadlivedata2(char * data);
//bool loadlivedata2(char * data,uint8_t *memdata);
bool loadmemorydata(uint32_t startaddr,uint32_t endaddr,char * data);
#endif /* _APP3_H */

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

/*******************************************************************************
 End of File
 */

