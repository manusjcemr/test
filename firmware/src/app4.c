/*******************************************************************************
  MPLAB Harmony Application Source File

  Company:
    Microchip Technology Inc.

  File Name:
    app4.c

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

#include "app4.h"
#include <stdio.h>                     // Defines NULL
#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include <string.h>
//#include "plib_can0.h"
#include "definitions.h"                // SYS function prototypes
#include "myapp.h"
#include "configuration.h"
#include "config.h"
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
    This structure should be initialized by the APP4_Initialize function.

    Application strings and buffers are be defined outside this structure.
*/

APP4_DATA app4Data;
//#define CAN_SOURCEADRR   17//17//OR 0
// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

/* TODO:  Add any necessary callback functions.
*/

// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************


/* TODO:  Add any necessary local functions.
*/
uint8_t Can0MessageRAM[CAN0_MESSAGE_RAM_CONFIG_SIZE] __attribute__((aligned (32)));
/* Standard identifier id[28:18]*/
#define WRITE_ID(id) (id << 18)
#define READ_ID(id)  (id >> 18)

/* Application's state machine enum */
typedef enum
{
    APP4_STATE_CAN_RECEIVE,
    APP4_STATE_CAN_TRANSMIT,
    APP4_STATE_CAN_IDLE,
    APP4_STATE_CAN_XFER_SUCCESSFUL,
    APP4_STATE_CAN_XFER_ERROR,
    APP4_STATE_CAN_USER_INPUT
} APP4_CAN_STATES;
/* Variable to save Tx/Rx transfer status and context */
static uint32_t status = 0;
static uint32_t xferContext = 0;
/* Variable to save Tx/Rx message */
//static uint8_t loop_count = 0;
//static uint8_t user_input = 0;
/* Variable to save application state */
//volatile static APP_STATES state = APP_STATE_CAN_USER_INPUT;
//volatile static APP4_CAN_STATES state = APP4_STATE_CAN_USER_INPUT;

//static uint8_t txFiFo[CAN0_TX_FIFO_BUFFER_SIZE];
static uint8_t rxFiFo0[CAN0_RX_FIFO0_SIZE];
static uint8_t rxFiFo1[CAN0_RX_FIFO1_SIZE];
//static uint8_t rxBuffer[CAN0_RX_BUFFER_SIZE];

// *****************************************************************************
// *****************************************************************************
// Section: Local functions
// *****************************************************************************
// *****************************************************************************

//uint8_t user_input = 0;
volatile static APP4_CAN_STATES state = APP4_STATE_CAN_USER_INPUT;
uint32_t messageID = 0;
uint8_t message[8];
uint8_t messageLength = 0;

uint8_t rx_message[8];
uint32_t rx_messageID = 0,temprx_messageID=0;
uint8_t rx_messageLength = 0;
//CAN_MSG_RX_FRAME_ATTRIBUTE msgFrameAttr = CAN_MSG_RX_DATA_FRAME;
    
uint8_t length;
    
uint8_t rx_set = 0,tx_set =0;       
uint8_t rx_FEFC[8],rx_FEFCset = 0;
uint8_t rx_FEEE[8],rx_FEEEset = 0;
uint8_t rx_FEEF[8],rx_FEEFset = 0;
uint8_t rx_FE68[8],rx_FE68set = 0;
uint8_t rx_F004[8],rx_F004set = 0;
uint8_t rx_FEF7[8],rx_FEF7set = 0;
uint8_t rx_E000[8],rx_E000set = 0;
uint8_t rx_FD07[8],rx_FD07set = 0;
uint8_t rx_FEE5[8],rx_FEE5set = 0;
    
//static uint32_t xferContext = 0;
//static uint32_t status = 0;//,readStatus = 0;
//static uint16_t timestamp = 0;
//static uint32_t u32_loopcnt = 0;
float flt_CANfuallevel,flt_CANEngineCoolantTemperature,flt_CANLuboiltemp,flt_CANHydoiltemp;
float flt_CANEngineLuboilpressure,flt_CANEngineLuboilpressure_kgpcmsq,flt_CANEngineLuboilpressure_bar;
float flt_CANEngineRPM;
uint16_t u16_CANSeatBelt,u16_CANAirfilterclogged,u16_CANHydoilfilterclogged,u16_CANHydoillevel;
float flt_CANBatteryVoltage,flt_CANEnginetotalhourofoperation;
//void interrupt_my(void);
void can_recdata(void);
uint32_t u32_loopcnt;
extern uint8_t u8_gerrercode3;

uint16_t u16_tempflt,u16_tempint;
void datacpy(uint8_t *val1,uint8_t *val2,uint8_t size)
{
    for(uint8_t i=0;i<size;i++)
    {
        val1[i] = val2[i];
    }
}
// *****************************************************************************
// *****************************************************************************
// Section: Local functions
// *****************************************************************************
// *****************************************************************************

/* Message Length to Data length code */
//static uint8_t CANLengthToDlcGet(uint8_t length)
//{
//    uint8_t dlc = 0;
//
//    if (length <= 8U)
//    {
//        dlc = length;
//    }
//    else if (length <= 12U)
//    {
//        dlc = 0x9U;
//    }
//    else if (length <= 16U)
//    {
//        dlc = 0xAU;
//    }
//    else if (length <= 20U)
//    {
//        dlc = 0xBU;
//    }
//    else if (length <= 24U)
//    {
//        dlc = 0xCU;
//    }
//    else if (length <= 32U)
//    {
//        dlc = 0xDU;
//    }
//    else if (length <= 48U)
//    {
//        dlc = 0xEU;
//    }
//    else
//    {
//        dlc = 0xFU;
//    }
//    return dlc;
//}

/* Data length code to Message Length */
static uint8_t CANDlcToLengthGet(uint8_t dlc)
{
    uint8_t msgLength[] = {0U, 1U, 2U, 3U, 4U, 5U, 6U, 7U, 8U, 12U, 16U, 20U, 24U, 32U, 48U, 64U};
    return msgLength[dlc];
}
/* Menu */
//static void display_menu(void)
//{
////	printf("Menu :\r\n"
////	       "  -- Select the action:\r\n"
////	       "  0: Send FD standard message with ID: 0x45A and 64 byte data 0 to 63. \r\n"
////	       "  1: Send FD standard message with ID: 0x469 and 64 byte data 128 to 191. \r\n"
////	       "  2: Send FD extended message with ID: 0x100000A5 and 64 byte data 0 to 63. \r\n"
////	       "  3: Send FD extended message with ID: 0x10000096 and 64 byte data 128 to 191. \r\n"
////	       "  4: Send normal standard message with ID: 0x469 and 8 byte data 0 to 7. \r\n"
////	       "  m: Display menu \r\n\r\n");
//}

/* Print Rx Message */
static void print_message(uint8_t numberOfMessage, CAN_RX_BUFFER *rxBuf, uint8_t rxBufLen, uint8_t rxFifoBuf)
{
//    uint8_t length = 0;
    uint8_t msgLength = 0;
    uint32_t id = 0;

//    if (rxFifoBuf == 0)
//        printf(" Rx FIFO0 :");
//    else if (rxFifoBuf == 1)
//        printf(" Rx FIFO1 :");
//    else if (rxFifoBuf == 2)
//        printf(" Rx Buffer :");

    for (uint8_t count = 0; count < numberOfMessage; count++)
    {
        /* Print message to Console */
//        printf(" New Message Received\r\n");
        id = rxBuf->xtd ? rxBuf->id : READ_ID(rxBuf->id);
        msgLength = CANDlcToLengthGet(rxBuf->dlc);
        length = msgLength;
//        printf(" Message - Timestamp : 0x%x ID : 0x%x Length : 0x%x ", (unsigned int)rxBuf->rxts, (unsigned int)id, (unsigned int)msgLength);
//        printf("Message : ");
//        while(length)
//        {
//            printf("0x%x ", rxBuf->data[msgLength - length--]);
//        }
//        printf("\r\n");
        /****mycode**********/
        rx_set = 1;
        /************************************************/
//                printf("Message Received. \r\n");
//                if((rx_messageID == 0x18FEFC17)&&(rx_FEFCset == 0))
        if(CAN_SOURCEADRR == 17)
        {
            if(id ==0x18FEFC17)// if(rx_messageID == 0x18FEFC17)
            {
//                        memcpy(rx_FEFC,rx_message,8);
                datacpy(rx_FEFC,rxBuf->data,msgLength);//datacpy(rx_FEFC,rx_message,8);
                rx_FEFCset = 1;
            }
//                else if((rx_messageID == 0x18FEEE17)&&(rx_FEEEset == 0))
            else if(id ==0x18FEEE17)//else if(rx_messageID == 0x18FEEE17)
            {
//                        memcpy(rx_FEEE,rx_message,8);
                datacpy(rx_FEEE,rxBuf->data,msgLength);//datacpy(rx_FEEE,rx_message,8);
                rx_FEEEset = 1;
            }
//                else if((rx_messageID == 0x18FEEF17)&&(rx_FEEFset == 0))
            else if(id ==0x18FEEF17)//else if(rx_messageID == 0x18FEEF17)
            {
                datacpy(rx_FEEF,rxBuf->data,msgLength);//datacpy(rx_FEEF,rx_message,8);
                rx_FEEFset = 1;
            }
//                else if((rx_messageID == 0x18FE6817)&&(rx_FE68set == 0))
            else if(id ==0x18FE6817)//else if(rx_messageID == 0x18FE6817)
            {
                datacpy(rx_FE68,rxBuf->data,msgLength);//datacpy(rx_FE68,rx_message,8);
                rx_FE68set = 1;
            }
//                else if((rx_messageID == 0x18F00417)&&(rx_F004set == 0))
            else if(id ==0x18F00417)//else if(rx_messageID == 0x18F00417)
//                else if(rx_messageID == 0x0CF00400)
            {
                datacpy(rx_F004,rxBuf->data,msgLength);//datacpy(rx_F004,rx_message,8);
                rx_F004set = 1;
            }
//                else if((rx_messageID == 0x18FEF717)&&(rx_FEF7set == 0))
            else if(id ==0x18FEF717)//else if(rx_messageID == 0x18FEF717)
            {
                datacpy(rx_FEF7,rxBuf->data,msgLength);//datacpy(rx_FEF7,rx_message,8);
                rx_FEF7set = 1;
            }
//                else if((rx_messageID == 0x18E00017)&&(rx_E000set == 0))
            else if(id ==0x18E00017)//else if((rx_messageID == 0x18E00017)||(rx_messageID == 0x18E0FF17))
            {
                datacpy(rx_E000,rxBuf->data,msgLength);//datacpy(rx_E000,rx_message,8);
                rx_E000set = 1;
            }
//                else if((rx_messageID == 0x18FD0717)&&(rx_FD07set == 0))
            else if(id ==0x18FD0717)//else if(rx_messageID == 0x18FD0717)
            {
                datacpy(rx_FD07,rxBuf->data,msgLength);//datacpy(rx_FD07,rx_message,8);
                rx_FD07set = 1;
            }
//                else if((rx_messageID == 0x18FEE517)&&(rx_FEE5set == 0))
            else if(id ==0x18FEE517)//else if(rx_messageID == 0x18FEE517)
            {
                datacpy(rx_FEE5,rxBuf->data,msgLength);//datacpy(rx_FEE5,rx_message,8);
                rx_FEE5set = 1;
//                        printf("can:rx_FEE5 = 0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x, \r\n",rx_FEE5[7],rx_FEE5[6],rx_FEE5[5],rx_FEE5[4],rx_FEE5[3],rx_FEE5[2],rx_FEE5[1],rx_FEE5[0]);
            }
            else
            {
                datacpy(rx_E000,rxBuf->data,msgLength);//datacpy(rx_E000,rx_message,8);
                rx_E000set = 1;
                temprx_messageID = rx_messageID;
            }
        }
        else //if(CAN_SOURCEADRR == 0)
        {
            if(id ==0x18FEFC00)//if(rx_messageID == 0x18FEFC00)
            {
                datacpy(rx_FEFC,rxBuf->data,msgLength);//datacpy(rx_FEFC,rx_message,8);
                rx_FEFCset = 1;
            }
//                else if((rx_messageID == 0x18FEEE17)&&(rx_FEEEset == 0))
            else if(id ==0x18FEEE00)//else if(rx_messageID == 0x18FEEE00)
            {
                datacpy(rx_FEEE,rxBuf->data,msgLength);//datacpy(rx_FEEE,rx_message,8);
                rx_FEEEset = 1;
            }
//                else if((rx_messageID == 0x18FEEF17)&&(rx_FEEFset == 0))
            else if(id ==0x18FEEF00)//else if(rx_messageID == 0x18FEEF00)
            {
                datacpy(rx_FEEF,rxBuf->data,msgLength);//datacpy(rx_FEEF,rx_message,8);
                rx_FEEFset = 1;
            }
//                else if((rx_messageID == 0x18FE6817)&&(rx_FE68set == 0))
            else if(id ==0x18FE6800)//else if(rx_messageID == 0x18FE6800)
            {
                datacpy(rx_FE68,rxBuf->data,msgLength);//datacpy(rx_FE68,rx_message,8);
                rx_FE68set = 1;
            }
//                else if((rx_messageID == 0x18F00417)&&(rx_F004set == 0))
            else if(id ==0x0CF00400)//else if(rx_messageID == 0x0CF00400)
//                else if(rx_messageID == 0x0CF00400)
            {
                datacpy(rx_F004,rxBuf->data,msgLength);//datacpy(rx_F004,rx_message,8);
                rx_F004set = 1;
            }
//                else if((rx_messageID == 0x18FEF717)&&(rx_FEF7set == 0))
            else if(id ==0x18FEF700)//else if(rx_messageID == 0x18FEF700)
            {
                datacpy(rx_FEF7,rxBuf->data,msgLength);//datacpy(rx_FEF7,rx_message,8);
                rx_FEF7set = 1;
            }
//                else if((rx_messageID == 0x18E00017)&&(rx_E000set == 0))
            else if((id ==0x18E00000)||(id ==0x18E0FF00))//else if((rx_messageID == 0x18E00000)||(rx_messageID == 0x18E0FF00))
            {
                datacpy(rx_E000,rxBuf->data,msgLength);//datacpy(rx_E000,rx_message,8);
                rx_E000set = 1;
            }
//                else if((rx_messageID == 0x18FD0717)&&(rx_FD07set == 0))
            else if(id ==0x18FD0700)//else if(rx_messageID == 0x18FD0700)
            {
                datacpy(rx_FD07,rxBuf->data,msgLength);//datacpy(rx_FD07,rx_message,8);
                rx_FD07set = 1;
            }
//                else if((rx_messageID == 0x18FEE517)&&(rx_FEE5set == 0))
            else if(id ==0x18FEE500)//else if(rx_messageID == 0x18FEE500)
            {
                datacpy(rx_FEE5,rxBuf->data,msgLength);//datacpy(rx_FEE5,rx_message,8);
                rx_FEE5set = 1;
            }
            else
            {
                datacpy(rx_E000,rxBuf->data,msgLength);//datacpy(rx_E000,rx_message,8);
                rx_E000set = 1;
                temprx_messageID = rx_messageID;
            }
        }
        u32_loopcnt = 0;
        u8_gerrercode3 = 0;

        /*******************/
        
        rxBuf += rxBufLen;
    }
}
/* This function will be called by CAN PLIB when transfer is completed from Tx FIFO */
void APP4_CAN_TxFifoCallback(uintptr_t context)
{
    xferContext = context;

    /* Check CAN Status */
    status = CAN0_ErrorGet();

    if (((status & CAN_PSR_LEC_Msk) == CAN_ERROR_NONE) || ((status & CAN_PSR_LEC_Msk) == CAN_ERROR_LEC_NC))
    {
        switch ((APP_STATES)context)
        {
            case APP4_STATE_CAN_TRANSMIT:
            {
                state = APP4_STATE_CAN_XFER_SUCCESSFUL;
                break;
            }
            default:
                break;
        }
    }
    else
    {
        state = APP4_STATE_CAN_XFER_ERROR;
    }
}

/* This function will be called by CAN PLIB when Message received in Rx Buffer */
//void APP_CAN_RxBufferCallback(uint8_t bufferNumber, uintptr_t context)
//{
//    xferContext = context;
//
//    /* Check CAN Status */
//    status = CAN0_ErrorGet();
//
//    if (((status & CAN_PSR_LEC_Msk) == CAN_ERROR_NONE) || ((status & CAN_PSR_LEC_Msk) == CAN_ERROR_LEC_NC))
//    {
//        switch ((APP_STATES)context)
//        {
//            case APP4_STATE_CAN_RECEIVE:
//            {
//                memset(rxBuffer, 0x00, CAN0_RX_BUFFER_ELEMENT_SIZE);
//                if (CAN0_MessageReceive(bufferNumber, (CAN_RX_BUFFER *)rxBuffer) == true)
//                {
//                    print_message(1, (CAN_RX_BUFFER *)rxBuffer, CAN0_RX_BUFFER_ELEMENT_SIZE, 2);
//                    state = APP4_STATE_CAN_XFER_SUCCESSFUL;
//                }
//                else
//                {
//                    state = APP4_STATE_CAN_XFER_ERROR;
//                }
//                break;
//            }
//            default:
//                break;
//        }
//    }
//    else
//    {
//        state = APP_STATE_CAN_XFER_ERROR;
//    }
//}

/* This function will be called by CAN PLIB when Message received in Rx FIFO0 */
void APP4_CAN_RxFifo0Callback(uint8_t numberOfMessage, uintptr_t context)
{
    xferContext = context;

    /* Check CAN Status */
    status = CAN0_ErrorGet();

    if (((status & CAN_PSR_LEC_Msk) == CAN_ERROR_NONE) || ((status & CAN_PSR_LEC_Msk) == CAN_ERROR_LEC_NC))
    {
        switch ((APP_STATES)context)
        {
            case APP4_STATE_CAN_RECEIVE:
            {
                memset(rxFiFo0, 0x00, (numberOfMessage * CAN0_RX_FIFO0_ELEMENT_SIZE));
                if (CAN0_MessageReceiveFifo(CAN_RX_FIFO_0, numberOfMessage, (CAN_RX_BUFFER *)rxFiFo0) == true)
                {
                    print_message(numberOfMessage, (CAN_RX_BUFFER *)rxFiFo0, CAN0_RX_FIFO0_ELEMENT_SIZE, 0);
                    state = APP4_STATE_CAN_XFER_SUCCESSFUL;
                }
                else
                {
                    state = APP4_STATE_CAN_XFER_ERROR;
                }
                break;
            }
            default:
                break;
        }
    }
    else
    {
        state = APP4_STATE_CAN_XFER_ERROR;
    }
}

/* This function will be called by CAN PLIB when Message received in Rx FIFO1 */
void APP4_CAN_RxFifo1Callback(uint8_t numberOfMessage, uintptr_t context)
{
    xferContext = context;

    /* Check CAN Status */
    status = CAN0_ErrorGet();

    if (((status & CAN_PSR_LEC_Msk) == CAN_ERROR_NONE) || ((status & CAN_PSR_LEC_Msk) == CAN_ERROR_LEC_NC))
    {
        switch ((APP_STATES)context)
        {
            case APP4_STATE_CAN_RECEIVE:
            {
                memset(rxFiFo1, 0x00, (numberOfMessage * CAN0_RX_FIFO1_ELEMENT_SIZE));
                if (CAN0_MessageReceiveFifo(CAN_RX_FIFO_1, numberOfMessage, (CAN_RX_BUFFER *)rxFiFo1) == true)
                {
                    print_message(numberOfMessage, (CAN_RX_BUFFER *)rxFiFo1, CAN0_RX_FIFO1_ELEMENT_SIZE, 1);
                    state = APP4_STATE_CAN_XFER_SUCCESSFUL;
                }
                else
                {
                    state = APP4_STATE_CAN_XFER_ERROR;
                }
                break;
            }
            default:
                break;
        }
    }
    else
    {
        state = APP4_STATE_CAN_XFER_ERROR;
    }
}
/************************************************/
//void APP4_CAN_Callback(uintptr_t context)
//{
//    xferContext = context;
//    WDT_Clear();
//    /* Check CAN Status */
//    status = CAN0_ErrorGet();
//    if (((status & CAN_PSR_LEC_Msk) == CAN_ERROR_NONE) || ((status & CAN_PSR_LEC_Msk) == CAN_ERROR_LEC_NC))
////    if (((status & CAN_PSR_LEC_Msk) == CAN_ERROR_NONE) || ((status & CAN_PSR_LEC_Msk) == CAN_ERROR_LEC_NC)||((status & CAN_ERROR_LEC_ACK) == CAN_ERROR_LEC_ACK))
//    {
//        switch ((APP4_STATES)context)
//        {
//            case APP4_STATE_CAN_RECEIVE:
//            case APP4_STATE_CAN_TRANSMIT:
//            {
//                state = APP4_STATE_CAN_XFER_SUCCESSFUL;
//                rx_set = 1;
//                /************************************************/
////                printf("Message Received. \r\n");
////                if((rx_messageID == 0x18FEFC17)&&(rx_FEFCset == 0))
//                if(CAN_SOURCEADRR == 17)
//                {
//                    if(rx_messageID == 0x18FEFC17)
//                    {
////                        memcpy(rx_FEFC,rx_message,8);
//                        datacpy(rx_FEFC,rx_message,8);
//                        rx_FEFCset = 1;
//                    }
//    //                else if((rx_messageID == 0x18FEEE17)&&(rx_FEEEset == 0))
//                    else if(rx_messageID == 0x18FEEE17)
//                    {
////                        memcpy(rx_FEEE,rx_message,8);
//                        datacpy(rx_FEEE,rx_message,8);
//                        rx_FEEEset = 1;
//                    }
//    //                else if((rx_messageID == 0x18FEEF17)&&(rx_FEEFset == 0))
//                    else if(rx_messageID == 0x18FEEF17)
//                    {
//                        datacpy(rx_FEEF,rx_message,8);
//                        rx_FEEFset = 1;
//                    }
//    //                else if((rx_messageID == 0x18FE6817)&&(rx_FE68set == 0))
//                    else if(rx_messageID == 0x18FE6817)
//                    {
//                        datacpy(rx_FE68,rx_message,8);
//                        rx_FE68set = 1;
//                    }
//    //                else if((rx_messageID == 0x18F00417)&&(rx_F004set == 0))
//                    else if(rx_messageID == 0x18F00417)
//    //                else if(rx_messageID == 0x0CF00400)
//                    {
//                        datacpy(rx_F004,rx_message,8);
//                        rx_F004set = 1;
//                    }
//    //                else if((rx_messageID == 0x18FEF717)&&(rx_FEF7set == 0))
//                    else if(rx_messageID == 0x18FEF717)
//                    {
//                        datacpy(rx_FEF7,rx_message,8);
//                        rx_FEF7set = 1;
//                    }
//    //                else if((rx_messageID == 0x18E00017)&&(rx_E000set == 0))
//                    else if((rx_messageID == 0x18E00017)||(rx_messageID == 0x18E0FF17))
//                    {
//                        datacpy(rx_E000,rx_message,8);
//                        rx_E000set = 1;
//                    }
//    //                else if((rx_messageID == 0x18FD0717)&&(rx_FD07set == 0))
//                    else if(rx_messageID == 0x18FD0717)
//                    {
//                        datacpy(rx_FD07,rx_message,8);
//                        rx_FD07set = 1;
//                    }
//    //                else if((rx_messageID == 0x18FEE517)&&(rx_FEE5set == 0))
//                    else if(rx_messageID == 0x18FEE517)
//                    {
//                        datacpy(rx_FEE5,rx_message,8);
//                        rx_FEE5set = 1;
////                        printf("can:rx_FEE5 = 0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x, \r\n",rx_FEE5[7],rx_FEE5[6],rx_FEE5[5],rx_FEE5[4],rx_FEE5[3],rx_FEE5[2],rx_FEE5[1],rx_FEE5[0]);
//                    }
//                    else
//                    {
//                        datacpy(rx_E000,rx_message,8);
//                        rx_E000set = 1;
//                        temprx_messageID = rx_messageID;
//                    }
//                }
//                else //if(CAN_SOURCEADRR == 0)
//                {
//                    if(rx_messageID == 0x18FEFC00)
//                    {
//                        datacpy(rx_FEFC,rx_message,8);
//                        rx_FEFCset = 1;
//                    }
//    //                else if((rx_messageID == 0x18FEEE17)&&(rx_FEEEset == 0))
//                    else if(rx_messageID == 0x18FEEE00)
//                    {
//                        datacpy(rx_FEEE,rx_message,8);
//                        rx_FEEEset = 1;
//                    }
//    //                else if((rx_messageID == 0x18FEEF17)&&(rx_FEEFset == 0))
//                    else if(rx_messageID == 0x18FEEF00)
//                    {
//                        datacpy(rx_FEEF,rx_message,8);
//                        rx_FEEFset = 1;
//                    }
//    //                else if((rx_messageID == 0x18FE6817)&&(rx_FE68set == 0))
//                    else if(rx_messageID == 0x18FE6800)
//                    {
//                        datacpy(rx_FE68,rx_message,8);
//                        rx_FE68set = 1;
//                    }
//    //                else if((rx_messageID == 0x18F00417)&&(rx_F004set == 0))
//                    else if(rx_messageID == 0x0CF00400)
//    //                else if(rx_messageID == 0x0CF00400)
//                    {
//                        datacpy(rx_F004,rx_message,8);
//                        rx_F004set = 1;
//                    }
//    //                else if((rx_messageID == 0x18FEF717)&&(rx_FEF7set == 0))
//                    else if(rx_messageID == 0x18FEF700)
//                    {
//                        datacpy(rx_FEF7,rx_message,8);
//                        rx_FEF7set = 1;
//                    }
//    //                else if((rx_messageID == 0x18E00017)&&(rx_E000set == 0))
//                    else if((rx_messageID == 0x18E00000)||(rx_messageID == 0x18E0FF00))
//                    {
//                        datacpy(rx_E000,rx_message,8);
//                        rx_E000set = 1;
//                    }
//    //                else if((rx_messageID == 0x18FD0717)&&(rx_FD07set == 0))
//                    else if(rx_messageID == 0x18FD0700)
//                    {
//                        datacpy(rx_FD07,rx_message,8);
//                        rx_FD07set = 1;
//                    }
//    //                else if((rx_messageID == 0x18FEE517)&&(rx_FEE5set == 0))
//                    else if(rx_messageID == 0x18FEE500)
//                    {
//                        datacpy(rx_FEE5,rx_message,8);
//                        rx_FEE5set = 1;
//                    }
//                    else
//                    {
//                        datacpy(rx_E000,rx_message,8);
//                        rx_E000set = 1;
//                        temprx_messageID = rx_messageID;
//                    }
//                }
//                /************************************************/
//                //CAN0_RxCallbackRegister( APP4_CAN_Callback, (uintptr_t)APP4_STATE_CAN_RECEIVE, CAN_MSG_ATTR_RX_FIFO1 );
//                state = APP4_STATE_CAN_IDLE;
//                memset(rx_message, 0x00, sizeof(rx_message));
//                /* Receive New Message */
//                if (CAN0_MessageReceive(&rx_messageID, &rx_messageLength, rx_message, &timestamp, CAN_MSG_ATTR_RX_FIFO1, &msgFrameAttr) == false)  
//                {
//                    printf("Message Reception Failed \r\n");
//                }
//                u32_loopcnt = 0;
//                u8_gerrercode3 = 0;
//                break;
//            }
//            default:
//                break;
//        }
//    }
//    else
//    {
//        state = APP4_STATE_CAN_IDLE;
//        memset(rx_message, 0x00, sizeof(rx_message));
//        /* Receive New Message */
//        if (CAN0_MessageReceive(&rx_messageID, &rx_messageLength, rx_message, &timestamp, CAN_MSG_ATTR_RX_FIFO1, &msgFrameAttr) == false)  
//        {
//            printf("Message Reception Failed \r\n");
//        }
//        state = APP4_STATE_CAN_XFER_ERROR;
//    }
//    
//}

void print_menu(void)
{
    printf(" ------------------------------ \r\n");   
//    printf(" Press '1' to Transmit message \r\n");
//    printf(" Press '2' to Receive message \r\n");
}


// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP4_Initialize ( void )

  Remarks:
    See prototype in app4.h.
 */

void APP4_Initialize ( void )
{
    /* Place the App state machine in its initial state. */
    app4Data.state = APP4_STATE_INIT;



    /* TODO: Initialize your application's state machine and other
     * parameters.
     */
}


/******************************************************************************
  Function:
    void APP4_Tasks ( void )

  Remarks:
    See prototype in app4.h.
 */

void APP4_Tasks ( void )
{

    /* Check the application's current state. */
    switch ( app4Data.state )
    {
        /* Application's initial state. */
        case APP4_STATE_INIT:
        {
            bool appInitialized = true;


            if (appInitialized)
            {
/******************************old code*initialization**************/
////                printf(" ------------------------------ \r\n");
////                printf("            CAN Demo            \r\n");
////                printf(" ------------------------------ \r\n");
//
//                /* Set Message RAM Configuration */
//                CAN0_MessageRAMConfigSet(Can0MessageRAM);
////                /***********************/
//                if(CANMONITERMODE == 1)
//                {
//                    /* Set CAN CCCR Init for Message RAM Configuration */
//                    CAN0_REGS->CAN_CCCR = CAN_CCCR_INIT_Msk;
//                    while ((CAN0_REGS->CAN_CCCR & CAN_CCCR_INIT_Msk) != CAN_CCCR_INIT_Msk)
//                    {
//                        /* Wait for initialization complete */
//                    }
//
//                    /* Set CCE to unlock the configuration registers */
//                    CAN0_REGS->CAN_CCCR |= CAN_CCCR_CCE_Msk;
//                    CAN0_REGS->CAN_CCCR |= CAN_CCCR_INIT_Msk;
//
//                    /* Wait for the sync. */
//                    while (!(CAN0_REGS->CAN_CCCR & CAN_CCCR_INIT_Msk));
//                    CAN0_REGS->CAN_CCCR |= CAN_CCCR_CCE_Msk;
//
//                    CAN0_REGS->CAN_CCCR |= CAN_CCCR_MON_Msk;
//                    /* Complete Message RAM Configuration by clearing CAN CCCR Init */
//                    CAN0_REGS->CAN_CCCR = (CAN0_REGS->CAN_CCCR & ~CAN_CCCR_INIT_Msk);
//                    while ((CAN0_REGS->CAN_CCCR & CAN_CCCR_INIT_Msk) == CAN_CCCR_INIT_Msk)
//                    {
//                        /* Wait for configuration complete */
//                    }
//                }
//                /*********************************/
////                //    void can_enable_bus_monitor_mode(struct can_module *const module_inst)
////                //    {
////                        CAN0_REGS->CAN_CCCR |= CAN_CCCR_INIT_Msk;
////                        /* Wait for the sync. */
////                        while (!(CAN0_REGS->CAN_CCCR & CAN_CCCR_INIT_Msk));
////                        CAN0_REGS->CAN_CCCR |= CAN_CCCR_CCE_Msk;
////
////                        CAN0_REGS->CAN_CCCR |= CAN_CCCR_MON_Msk;
////                //    }
////
////                    /*********************/
//                print_menu();
//
//                /* Prepare the message to send*/
//                messageID = 0x18E0FF17;
//                messageLength = 8;
//                for (uint8_t count = 8; count >=1; count--){
//                    message[count - 1] = count;
//                }
//            //    CAN0_RxCallbackRegister( APP_CAN_Callback, (uintptr_t)APP_STATE_CAN_RECEIVE, CAN_MSG_ATTR_RX_BUFFER );
//            //    CAN0_RxCallbackRegister( APP_CAN_Callback, 0, CAN_MSG_ATTR_RX_FIFO0 );
//
////                printf(" ID set in the range already \r\n");
////                printf(" Waiting for message: \r\n");
//                CAN0_RxCallbackRegister( APP4_CAN_Callback, (uintptr_t)APP4_STATE_CAN_RECEIVE, CAN_MSG_ATTR_RX_FIFO1 );
//                state = APP4_STATE_CAN_IDLE;
//                memset(rx_message, 0x00, sizeof(rx_message));
//                /* Receive New Message */
//                if (CAN0_MessageReceive(&rx_messageID, &rx_messageLength, rx_message, &timestamp, CAN_MSG_ATTR_RX_FIFO1, &msgFrameAttr) == false)  
//                {
//                    printf("Message Reception Failed \r\n");
//                }
/******************************New code*initialization**************/ 
//                CAN_TX_BUFFER *txBuffer = NULL;

                printf(" ------------------------------ \r\n");
                printf("        CAN0 Initialize            \r\n");
                printf(" ------------------------------ \r\n");

                /* Set Message RAM Configuration */
                CAN0_MessageRAMConfigSet(Can0MessageRAM);

//                CAN0_RxFifoCallbackRegister(CAN_RX_FIFO_0, APP_CAN_RxFifo0Callback, APP_STATE_CAN_RECEIVE);
                CAN0_RxFifoCallbackRegister(CAN_RX_FIFO_1, APP4_CAN_RxFifo1Callback, APP4_STATE_CAN_RECEIVE);
//                CAN0_RxBuffersCallbackRegister(APP_CAN_RxBufferCallback, APP_STATE_CAN_RECEIVE);

//                display_menu();
                app4Data.state = APP4_STATE_SERVICE_TASKS;
            }
            break;
        }

        case APP4_STATE_SERVICE_TASKS:
        {
            /* Maintain state machines of all polled MPLAB Harmony modules. */
            u32_loopcnt++;
            if(u32_loopcnt >= 1000000)
            { 
                u32_loopcnt = 0;
                u8_gerrercode3 = 1;
//                 printf(" ID set in the range already \r\n");
                printf(" Waiting for CAN message... \r\n");
//                CAN0_RxCallbackRegister( APP4_CAN_Callback, (uintptr_t)APP4_STATE_CAN_RECEIVE, CAN_MSG_ATTR_RX_FIFO1 );
//                state = APP4_STATE_CAN_IDLE;
//                memset(rx_message, 0x00, sizeof(rx_message));
//                /* Receive New Message */
//                if (CAN0_MessageReceive(&rx_messageID, &rx_messageLength, rx_message, &timestamp, CAN_MSG_ATTR_RX_FIFO1, &msgFrameAttr) == false)  
//                {
//                    printf("Message Reception Failed \r\n");
//                }
            }
            
            /* Check the application's current state. */
            switch (state)
            {
                case APP4_STATE_CAN_IDLE:
                {
                    /* Application can do other task here */
                    break;
                }
                case APP4_STATE_CAN_XFER_SUCCESSFUL:
                {
                    if ((APP4_CAN_STATES)xferContext == APP4_STATE_CAN_RECEIVE)
                    {
                        /* Print message to Console */
    //                    printf(" New Message Received\r\n");
    //                    uint8_t length = rx_messageLength;
    //                    printf(" Message - Timestamp : 0x%x ID : 0x%x Length : 0x%x ", (unsigned int)timestamp, (unsigned int)rx_messageID, (unsigned int)rx_messageLength);
    //                    printf("Message : ");
    //                    while(length)
    //                    {
    //                        printf("0x%x ", rx_message[rx_messageLength - length--]);
    //                    }
    //                    printf("\r\n");

                    } 
                    else if ((APP4_CAN_STATES)xferContext == APP4_STATE_CAN_TRANSMIT)
                    {
                        printf(" Success\r\n");
                    }
    //                display_menu();
                    state = APP4_STATE_CAN_USER_INPUT;
                    break;
                }
                case APP4_STATE_CAN_XFER_ERROR:
                {
                    if ((APP4_CAN_STATES)xferContext == APP4_STATE_CAN_RECEIVE)
                    {
                        printf(" Error in received message\r\n");
                    }
                    else
                    {
                        printf(" Failed\r\n");
                    }
    //                display_menu();
                    state = APP4_STATE_CAN_USER_INPUT;
                    break;
                }
                default:
                    break;
            }
            break;
        }

        /* TODO: implement your application state machine.*/


        /* The default state should never be executed. */
        default:
        {
            /* TODO: Handle error in application's state machine. */
            break;
        }
    }
}

void can_recdata(void)
{
//    printf(" ID set in the range already \r\n");
//    printf(" Waiting for message: \r\n");
//    CAN0_RxCallbackRegister( APP4_CAN_Callback, (uintptr_t)APP4_STATE_CAN_RECEIVE, CAN_MSG_ATTR_RX_FIFO0 );
//
//    memset(rx_message, 0x00, sizeof(rx_message));
//    /* Receive New Message */
//    if (CAN0_MessageReceive(&rx_messageID, &rx_messageLength, rx_message, &timestamp, CAN_MSG_ATTR_RX_FIFO0, &msgFrameAttr) == false)  
//    {
//        printf("Message Reception Failed \r\n");
//    }

    //if((rx_FEFCset == 1)&&(rx_FEEEset == 1)&&(rx_FEEFset == 1)&&(rx_FE68set == 1)&&(rx_F004set == 1)&&(rx_FEF7set == 1)&&(rx_E000set == 1)&&(rx_FD07set == 1)&&(rx_FEE5set == 1))
    {
        if(rx_FEFCset == 1)
        {
            printf("1.rx_FEFC = 0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x, \r\n",rx_FEFC[7],rx_FEFC[6],rx_FEFC[5],rx_FEFC[4],rx_FEFC[3],rx_FEFC[2],rx_FEFC[1],rx_FEFC[0]);

            flt_CANfuallevel = 0 + (rx_FEFC[1] * 0.4);

            u16_tempint = flt_CANfuallevel;
            u16_tempflt = flt_CANfuallevel * 100.0;
            u16_tempflt = u16_tempflt % 100;
            printf("FUAL LEVEL:%d.%d\r\n",u16_tempint,u16_tempflt);
//                rx_FEFCset = 0;
        }
        else
        {
            flt_CANfuallevel = 0;
        }
            
        if(rx_FEEEset == 1)
        {
            printf("2.rx_FEEE = 0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x, \r\n",rx_FEEE[7],rx_FEEE[6],rx_FEEE[5],rx_FEEE[4],rx_FEEE[3],rx_FEEE[2],rx_FEEE[1],rx_FEEE[0]);
            flt_CANEngineCoolantTemperature = -40 + (rx_FEEE[0] * 1.0);
            u16_tempint = flt_CANEngineCoolantTemperature;
            u16_tempflt = flt_CANEngineCoolantTemperature * 100.0;
            u16_tempflt = u16_tempflt % 100;
            printf("Engine Coolant Temperature:%d.%d C,",u16_tempint,u16_tempflt);

            flt_CANLuboiltemp = -273 + (((rx_FEEE[3]<<8)|rx_FEEE[2])*0.03125);
            u16_tempint = flt_CANLuboiltemp;
            u16_tempflt = flt_CANLuboiltemp * 100.0;
            u16_tempflt = u16_tempflt % 100;
            printf("Lub oil temp = %d.%d C\r\n",u16_tempint,u16_tempflt);

//                        printf("Engine Coolant Temperature:%d C,Lub oil temp = %d C\r\n",u16_CANEngineCoolantTemperature,u16_CANLuboiltemp);
            //                rx_FEEEset = 0;
        }
        else
        {
            flt_CANEngineCoolantTemperature = 0;
            flt_CANLuboiltemp = 0;
        }
        if(rx_FEEFset == 1)
        {
            printf("3.rx_FEEF = 0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x, \r\n",rx_FEEF[7],rx_FEEF[6],rx_FEEF[5],rx_FEEF[4],rx_FEEF[3],rx_FEEF[2],rx_FEEF[1],rx_FEEF[0]);
//                rx_FEEFset = 0;
            flt_CANEngineLuboilpressure = 0 + (rx_FEEF[3] * 4.0);
            u16_tempint = flt_CANEngineLuboilpressure;
            u16_tempflt = flt_CANEngineLuboilpressure * 100.0;
            u16_tempflt = u16_tempflt % 100;
            printf("Engine Lub oil pressure:%d.%d kPa or :",u16_tempint,u16_tempflt);

            flt_CANEngineLuboilpressure_kgpcmsq = flt_CANEngineLuboilpressure * 0.0101972;
            u16_tempint = flt_CANEngineLuboilpressure_kgpcmsq;
            u16_tempflt = flt_CANEngineLuboilpressure_kgpcmsq * 100.0;
            u16_tempflt = u16_tempflt % 100;
            printf("%d.%d kg/cm2 or ",u16_tempint,u16_tempflt);
            
            char res[20]={0};
            flt_CANEngineLuboilpressure_bar = (flt_CANEngineLuboilpressure /100.0); 
            ftoa(flt_CANEngineLuboilpressure_bar, res, 2);
            printf("%s bar\r\n",res);
            
//                        printf("Engine Lub oil pressure:%d kPa or :%d kg/cm2\r\n",u16_CANEngineLuboilpressure,u16_CANEngineLuboilpressure_kgpcmsq);
        }
        else
        {
            flt_CANEngineLuboilpressure = 0;
            flt_CANEngineLuboilpressure_kgpcmsq = 0;
            flt_CANEngineLuboilpressure_bar = 0;
        }
        if(rx_FE68set == 1)
        {
            printf("4.rx_FE68 = 0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x, \r\n",rx_FE68[7],rx_FE68[6],rx_FE68[5],rx_FE68[4],rx_FE68[3],rx_FE68[2],rx_FE68[1],rx_FE68[0]);
//                rx_FE68set = 0;
            flt_CANHydoiltemp = -40 + (rx_FE68[0] * 1.0);
            u16_tempint = flt_CANHydoiltemp;
            u16_tempflt = flt_CANHydoiltemp * 100.0;
            u16_tempflt = u16_tempflt % 100;
            printf("Hyd.oil temp.:%d.%d C,",u16_tempint,u16_tempflt);

            u16_CANHydoilfilterclogged = rx_FE68[1] & 0b00000011;

            u16_CANHydoillevel = 0 + (rx_FE68[2] * 0.4);
            printf("Hyd.oil filter clogged:%d,Hyd.oil level:%d \r\n",u16_CANHydoilfilterclogged,u16_CANHydoillevel);
        }
        else
        {
            flt_CANHydoiltemp = 0;
            u16_CANHydoilfilterclogged = 0;
            u16_CANHydoillevel = 0;
        }
        if(rx_F004set == 1)
        {
            printf("5.rx_F004 = 0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x, \r\n",rx_F004[7],rx_F004[6],rx_F004[5],rx_F004[4],rx_F004[3],rx_F004[2],rx_F004[1],rx_F004[0]);
//                rx_F004set = 0;
            flt_CANEngineRPM = 0 + (((rx_F004[4]<<8)|rx_F004[3])*0.125);
            u16_tempint = flt_CANEngineRPM;
            u16_tempflt = flt_CANEngineRPM * 100.0;
            u16_tempflt = u16_tempflt % 100;
            printf("Engine RPM:%d.%d rpm\r\n",u16_tempint,u16_tempflt);

//                        printf("Engine RPM:%d rpm\r\n",u16_CANEngineRPM);
        }
        else
        {
            flt_CANEngineRPM =0;
            
        }
        if(rx_FEF7set == 1)
        {    
            printf("6.rx_FEF7 = 0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x, \r\n",rx_FEF7[7],rx_FEF7[6],rx_FEF7[5],rx_FEF7[4],rx_FEF7[3],rx_FEF7[2],rx_FEF7[1],rx_FEF7[0]);
//                rx_FEF7set = 0;
            flt_CANBatteryVoltage = (((rx_FEF7[5]<<8)|rx_FEF7[4])*0.05);
            u16_tempint = flt_CANBatteryVoltage;
            u16_tempflt = flt_CANBatteryVoltage * 100.0;
            u16_tempflt = u16_tempflt % 100;
            printf("Battery Voltage:%d.%d V\r\n",u16_tempint,u16_tempflt);

//                    flt_BatteryVoltage = 12.2;
//                        uint16_t u16_CANBatteryVoltage = flt_CANBatteryVoltage;
//
//    //                    char tempbuff[64];
//    //                    memset(tempbuff,0,sizeof(tempbuff));
//                        printf("Battery Voltage:%d V\r\n",u16_CANBatteryVoltage);
//                    printf("%s\r\n",tempbuff);
        }
        else
        {
            flt_CANBatteryVoltage = 0;
        }
        if(rx_E000set == 1)
        {
            printf("7.rx_E000 = 0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x, \r\n",rx_E000[7],rx_E000[6],rx_E000[5],rx_E000[4],rx_E000[3],rx_E000[2],rx_E000[1],rx_E000[0]);
//                rx_E000set = 0;
            printf("temprx_messageID:%ld\r\n",temprx_messageID);
            u16_CANSeatBelt = 0 + ((rx_E000[3] & 0b11000000) >> 6);
            printf("Seat Belt:%d\r\n",u16_CANSeatBelt);
        }
        else
        {
            u16_CANSeatBelt = 0;
        }
        if(rx_FD07set == 1)
        {
            printf("8.rx_FD07 = 0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x, \r\n",rx_FD07[7],rx_FD07[6],rx_FD07[5],rx_FD07[4],rx_FD07[3],rx_FD07[2],rx_FD07[1],rx_FD07[0]);
//                rx_FD07set = 0;
//            u16_CANAirfilterclogged = (rx_FD07[2] & 0b00010000);
            u16_CANAirfilterclogged = 0 + ((rx_FD07[2] & 0b00110000) >> 4);
            printf("Air filter clogged:%d\r\n",u16_CANAirfilterclogged);
        }
        else
        {
            u16_CANAirfilterclogged = 0;
        }
        if(rx_FEE5set == 1)
        {
            printf("9.rx_FEE5 = 0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x, \r\n",rx_FEE5[7],rx_FEE5[6],rx_FEE5[5],rx_FEE5[4],rx_FEE5[3],rx_FEE5[2],rx_FEE5[1],rx_FEE5[0]);
//                rx_FEE5set = 0;
            uint32_t tempdata = 0;
            tempdata = (rx_FEE5[3]<<24)|(rx_FEE5[2]<<16)|(rx_FEE5[1]<<8)|rx_FEE5[0];
            
            //flt_CANEnginetotalhourofoperation = (0 + ((float)((rx_FEE5[3]*16777216.0)+(rx_FEE5[2]*65535.0)+(rx_FEE5[1]*255.0)+rx_FEE5[0])*0.05));
            flt_CANEnginetotalhourofoperation = (0+(float)tempdata)*0.05;
            //            u16_tempint = flt_CANEnginetotalhourofoperation;
//            u16_tempflt = flt_CANEnginetotalhourofoperation * 100.0;
//            u16_tempflt = u16_tempflt % 100;
            char res[20]={0};
            
            ftoa(flt_CANEnginetotalhourofoperation, res, 2);
            
//            printf("Engine total hour of operation:%d.%d hr\r\n",u16_tempint,u16_tempflt);
            printf("Engine total hour of operation:%s hr\r\n",res);
//                        printf("Engine total hour of operation:%d hr\r\n",flt_CANEnginetotalhourofoperation);        
        }
        else
        {
            flt_CANEnginetotalhourofoperation = 0;
        }
        printf("---------------------------------------------------------\r\n");
        if((rx_FEFCset == 1)||(rx_FEEEset == 1)||(rx_FEEFset == 1)||(rx_FE68set == 1)||(rx_F004set == 1)||(rx_FEF7set == 1)||(rx_E000set == 1)||(rx_FD07set == 1)||(rx_FEE5set == 1))
            u8_gerrercode3 = 0;
        else
            u8_gerrercode3 = 1;
        rx_FEFCset = 0;
        rx_FEEEset = 0;
        rx_FEEFset = 0;
        rx_FE68set = 0;
        rx_F004set = 0;
        rx_FEF7set = 0;
        rx_E000set = 0;
        rx_FD07set = 0;
        rx_FEE5set = 0;
        memset(rx_FEFC,0,sizeof(rx_FEFC));
        memset(rx_FEEE,0,sizeof(rx_FEEE));
        memset(rx_FEEF,0,sizeof(rx_FEEF));
        memset(rx_FE68,0,sizeof(rx_FE68));
        memset(rx_F004,0,sizeof(rx_F004));
        memset(rx_FEF7,0,sizeof(rx_FEF7));
        memset(rx_E000,0,sizeof(rx_E000));
        memset(rx_FD07,0,sizeof(rx_FD07));
        memset(rx_FEE5,0,sizeof(rx_FEE5));
    }
    memset(rx_message, 0x00, sizeof(rx_message));
//    /* Receive New Message */
//    if (CAN0_MessageReceive(&rx_messageID, &rx_messageLength, rx_message, &timestamp, CAN_MSG_ATTR_RX_FIFO1, &msgFrameAttr) == false)  
//    {
//        printf("Message Reception Failed \r\n");
//    }
}
//void can_datarefresh(void)
//{
//    flt_CANfuallevel = 0;
//}



/*******************************************************************************
 End of File
 */
