/*******************************************************************************
  MPLAB Harmony Application Source File

  Company:
    Microchip Technology Inc.

  File Name:
    app3.c

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

#include "app3.h"
#include "app2.h"
//#include "driver/usart/drv_usart.h"
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "ext_flash.h"
#include "config.h"
#include "myapp.h"
//#include "peripheral/sercom/spim/plib_sercom0_spi.h"
//#include "peripheral/port/plib_port.h"
//#include <stdio.h>
// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************
volatile bool isTransferDone = false;
char Manufacturer_Id=0x00;
char Device_Id=0x00;
char Device_Type=0x00;
char check,tempcheck,status;
unsigned int block_protection_18[18];
void exflash_erras(void);
void smr_clear(void);

extern bool b_IgnitionON;
extern bool b_speare1;
extern bool  b_Hydraulicoilfilterclog;
extern bool b_airfiltercool;
extern bool b_LubeOilPressure;
extern bool b_highenginteperature;
extern bool b_speare2;
extern bool b_speare3;
extern uint16_t uint_frq;

extern float flt_CANfuallevel,flt_CANEngineCoolantTemperature,flt_CANLuboiltemp,flt_CANHydoiltemp;
extern float flt_CANEngineLuboilpressure,flt_CANEngineLuboilpressure_kgpcmsq;
extern float flt_CANEngineRPM;
extern uint16_t u16_CANSeatBelt,u16_CANAirfilterclogged,u16_CANHydoilfilterclogged,u16_CANHydoillevel;
extern float flt_CANBatteryVoltage,flt_CANEnginetotalhourofoperation;
extern float flt_CANEngineLuboilpressure_bar;

extern float flt_gps_SpeedOverGround;
extern float flt_gps_CourseOverGround;

extern uint8_t u8_SAVING2MEM;   
//packet logwdata,logrdata;
//rewrite wnewmemloc,rnewmemloc,wyet2sendmemloc,ryet2sendmemloc,wrecomemloc,rrecomemloc,wmaxmemloc,rmaxmemloc,freshdatamemloc1,freshdatamemloc2,smrvalue;

// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    This structure should be initialized by the APP3_Initialize function.

    Application strings and buffers are be defined outside this structure.
*/

APP3_DATA app3Data;

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************
APP3_STATES state = APP3_STATE_INITIALIZE;
//extern bool alarm_triggered;
//struct tm sys_time;
//struct tm alarm_time;
void SPIEventHandler(uintptr_t context )
{
    /* De-assert the chip select */
//    EEPROM_CS_Set();
    FLASH_CS_Set();
    isTransferDone = true;
    printf("SPIEventHandler...");
}
/* TODO:  Add any necessary callback functions.
*/

// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************

//void EXTFLASH_init()
//{
//    //EEPROM_HOLD_Set();
//    FLASH_WP_Set();
////    FLASH_WP_Clear();
//    FLASH_CS_Set();
//}
/* TODO:  Add any necessary local functions.
*/


// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************
/* This function will be called by SPI PLIB when transfer is completed */

/*******************************************************************************
  Function:
    void APP3_Initialize ( void )

  Remarks:
    See prototype in app3.h.
 */

void APP3_Initialize ( void )
{
    /* Place the App state machine in its initial state. */
    app3Data.state = APP3_STATE_INITIALIZE;



    /* TODO: Initialize your application's state machine and other
     * parameters.
     */
}

/*CRC-16 CCITT
    CRC 16 bits
    Polynomial 0x1021
    Initial value 0xFFFF
    No inverted input
    No inverted output
    No final XOR (0x0000)
*/
uint16_t crc16_ccitt(uint8_t* data, int16_t data_len) {
  uint16_t crc = 0xFFFF;

  if (data_len == 0)
    return 0;

  for (unsigned int i = 0; i < data_len; ++i) {
    uint16_t dbyte = data[i];
    crc ^= dbyte << 8;

    for (unsigned char j = 0; j < 8; ++j) {
      uint16_t mix = crc & 0x8000;
      crc = (crc << 1);
      if (mix)
        crc = crc ^ 0x1021;
    }
  }

  return crc;
//    unsigned int crc16 = 0xFFFF;
//    int pos = 0;
//    int i = 0;
//
//    /*Main Code*/
//      for (pos = 0; pos < data_len; pos++) {
//        crc16 ^= data[pos];          // XOR byte into least sig. byte of crc
//
//        for (i = 8; i != 0; i--) {    // Loop over each bit
//          if ((crc16 & 0x0001) != 0) {      // If the LSB is set
//            crc16 >>= 1;                    // Shift right and XOR 0xA001
//            crc16 ^= 0xA001;
//          }
//          else                            // Else LSB is not set
//            crc16 >>= 1;                    // Just shift right
//        }
//      }
//      /*Note, this number has low and high bytes swapped,
//      so swap bytes*/
//      return crc16;
}
uint16_t crcresult = 0;

void exflash_erras(void)
{
    SPI_WREN();	      
    SPI_Chip_Erase();	//Erase the chip
//                  SPI_Sector_Erase(0);	//Do Sector Erase	      
    SPI_Wait_Busy();
    app3Data.state = APP3_STATE_INITIALIZE;
    APP3_Tasks ();
}
void smr_clear(void)
{
//    rewrite smrvalue;

    smrvalue.PacketField.memaddr = 0 ;
    savesmr(&smrvalue.addrbuf[0]);
}
/******************************************************************************
  Function:
    void APP3_Tasks ( void )

  Remarks:
    See prototype in app3.h.
 */

void APP3_Tasks ( void )
{
//    rewrite smrvalue;

    /* Check the application's current state. */
    switch ( app3Data.state )
    {
        /* Application's initial state. */
        case APP3_STATE_INITIALIZE:
                EXTFLASH_init();
                /* Register callback with the SPI PLIB */
//                SERCOM0_SPI_CallbackRegister(SPIEventHandler, (uintptr_t) 0);
                isTransferDone = false;
                /************* 1. Test Jedec ID *********/
                SPI_Jedec_ID_Read(&Manufacturer_Id, &Device_Type, &Device_Id);
                if ((Manufacturer_Id == 0xbf)&& (Device_Type==0x26) && (Device_Id==0x43))
                {check=(check + 1);}
                else
                {check=0;}
//                printf("Test Jedec ID: %d,Manufacturer_Id=%d,Device_Type=%d,Device_Id=%d\r\n", check,Manufacturer_Id,Device_Type,Device_Id);
                SPI_WREN();

                block_protection_18[0]=0x00;
                block_protection_18[1]=0x00;
                block_protection_18[2]=0x00;
                block_protection_18[3]=0x00;
                block_protection_18[4]=0x00;
                block_protection_18[5]=0x00;
                block_protection_18[6]=0x00;
                block_protection_18[7]=0x00;
                block_protection_18[8]=0x00;
                block_protection_18[9]=0x00;
                block_protection_18[10]=0x00;
                block_protection_18[11]=0x00;
                block_protection_18[12]=0x00;
                block_protection_18[13]=0x00;
                block_protection_18[14]=0x00;
                block_protection_18[15]=0x00;
                block_protection_18[16]=0x00;
                block_protection_18[17]=0x00;

                SPI_WriteBlockProtection(&block_protection_18[0]);
                SPI_Wait_Busy();
               /*********************test only*************/
                if(CHIP_ERASE == 1)
                {
                    SPI_WREN();	      
                    SPI_Chip_Erase();	//Erase the chip
   //                  SPI_Sector_Erase(0);	//Do Sector Erase	      
                    SPI_Wait_Busy();
                }
                /*********************************************/
//                wyet2sendmemloc.PacketField.memaddr = 40;
//                saveyet2sendmemloc(&wyet2sendmemloc.addrbuf[0]);
//                wnewmemloc.PacketField.memaddr = 48;
//                savenewmemloc(&wnewmemloc.addrbuf[0]);
                
//                wrecomemloc.PacketField.memaddr = 0;
//                saverecomemloc(&wrecomemloc.addrbuf[0]); 
                /********************************************/
//                if(rnewmemloc.PacketField.memaddr > MEM_LEN)
//                {
//                    rnewmemloc.PacketField.memaddr = 49;
//                    rnewmemloc.PacketField.flag = 0;
//                    savenewmemloc(&rnewmemloc.addrbuf[0]);
//                }
//
//                if(ryet2sendmemloc.PacketField.memaddr > MEM_LEN)
//                {
//                    ryet2sendmemloc.PacketField.memaddr = 200;
//                    saveyet2sendmemloc(&ryet2sendmemloc.addrbuf[0]);
//                }
                 /******************************************/
                
                
                SYSTICK_DelayMs(300);
                uint8_t tempbuff[100];
                readserialNo((uint8_t*)&tempbuff);
                printf ("readserialNo:%s\r\n",tempbuff);
                readIPaddr((uint8_t*)&tempbuff);
                printf ("readIPaddr:%s\r\n",tempbuff);
                readAPNaddr((uint8_t*)&tempbuff);
                printf ("readAPNaddr:%s\r\n",tempbuff);
                
                
                readnewmemloc(&rnewmemloc.addrbuf[0]);
                readyet2sendmemloc(&ryet2sendmemloc.addrbuf[0]);
                readmaxmemloc(&rmaxmemloc.addrbuf[0]);
                readfreshdatamemloc1(&freshdatamemloc1.addrbuf[0]);
                readfreshdatamemloc2(&freshdatamemloc2.addrbuf[0]);
                readFLAG(&flagbit.addrbuf[0]);
                readsmr(&smrvalue.addrbuf[0]);
//                printf("\r\n before: rnewmemloc:%ld,\r\n ryet2sendmemloc:%ld,\r\n rnewmemloc.PacketField.flag:%d\r\nrmaxmemloc.PacketField.memaddr:%ld\r\nfreshdatamemloc1:%ld\r\nfreshdatamemloc2:%ld\r\n ",rnewmemloc.PacketField.memaddr,ryet2sendmemloc.PacketField.memaddr,rnewmemloc.PacketField.flag,rmaxmemloc.PacketField.memaddr,freshdatamemloc1.PacketField.memaddr,freshdatamemloc2.PacketField.memaddr);
                printf("\r\n before: rnewmemloc:%ld,\r\n ryet2sendmemloc:%ld,\r\n flagbit.PacketField.memaddr:%ld\r\nrmaxmemloc.PacketField.memaddr:%ld\r\nfreshdatamemloc1:%ld\r\nfreshdatamemloc2:%ld\r\n ",rnewmemloc.PacketField.memaddr,ryet2sendmemloc.PacketField.memaddr,flagbit.PacketField.memaddr,rmaxmemloc.PacketField.memaddr,freshdatamemloc1.PacketField.memaddr,freshdatamemloc2.PacketField.memaddr);
                
                /*********testing urpess***********/
//                rnewmemloc.PacketField.memaddr = 44530;
//                rnewmemloc.PacketField.flag = 0;
//                savenewmemloc(&rnewmemloc.addrbuf[0]);
//                
//                ryet2sendmemloc.PacketField.memaddr = 44538;
//                saveyet2sendmemloc(&ryet2sendmemloc.addrbuf[0]);
//                flagbit.PacketField.memaddr=1;
//                saveFLAG(&flagbit.addrbuf[0]);
                
                /***********************************/
                
                if(LOGDATA_ERASE==1)
                {
                    ryet2sendmemloc.PacketField.memaddr = rnewmemloc.PacketField.memaddr;
                    saveyet2sendmemloc(&ryet2sendmemloc.addrbuf[0]);
                    
                    flagbit.PacketField.memaddr=0;
                    saveFLAG(&flagbit.addrbuf[0]);
                    
                }
                if((rnewmemloc.PacketField.memaddr > 100000))//||(rnewmemloc.PacketField.flag > 1))
                {
                    if(rnewmemloc.PacketField.memaddr > 100000)
                        rnewmemloc.PacketField.memaddr = 0;
                    if(rnewmemloc.PacketField.flag > 1)
                        rnewmemloc.PacketField.flag = 0;
                    savenewmemloc(&rnewmemloc.addrbuf[0]);
                }
                
                if(ryet2sendmemloc.PacketField.memaddr > 100000)
                {
                    ryet2sendmemloc.PacketField.memaddr = 0;
                    saveyet2sendmemloc(&ryet2sendmemloc.addrbuf[0]);
                }
                if(rmaxmemloc.PacketField.memaddr > 100000)
                {
                    rmaxmemloc.PacketField.memaddr = 0;
                    savemaxmemloc(&rmaxmemloc.addrbuf[0]);
                }
                if(freshdatamemloc1.PacketField.memaddr >= 10)
                {
                    freshdatamemloc1.PacketField.memaddr = 0;
                    savefreshdatamemloc1(&freshdatamemloc1.addrbuf[0]);
                }
                if(freshdatamemloc2.PacketField.memaddr >= 10)
                {
                    freshdatamemloc2.PacketField.memaddr = 0;
                    savefreshdatamemloc2(&freshdatamemloc2.addrbuf[0]);
                }
                if(smrvalue.PacketField.memaddr > 99999999)//8dig
                {
                    smrvalue.PacketField.memaddr=0;
                    savesmr(&smrvalue.addrbuf[0]);
                }
                
                if(flagbit.PacketField.memaddr > 1)
                {
                    flagbit.PacketField.memaddr=0;
                    saveFLAG(&flagbit.addrbuf[0]);
                }
                /*********************************/
                readnewmemloc(&rnewmemloc.addrbuf[0]);
                readyet2sendmemloc(&ryet2sendmemloc.addrbuf[0]);
                readmaxmemloc(&rmaxmemloc.addrbuf[0]);
                readfreshdatamemloc1(&freshdatamemloc1.addrbuf[0]);
                readfreshdatamemloc2(&freshdatamemloc2.addrbuf[0]);
                readsmr(&smrvalue.addrbuf[0]);
                readFLAG(&flagbit.addrbuf[0]);
                
//                printf("\r\nAfter :rnewmemloc:%ld,\r\n ryet2sendmemloc:%ld,\r\n rnewmemloc.PacketField.flag:%d\r\nrmaxmemloc.PacketField.memaddr:%ld\r\nfreshdatamemloc1:%ld\r\nfreshdatamemloc2:%ld\r\n",rnewmemloc.PacketField.memaddr,ryet2sendmemloc.PacketField.memaddr,rnewmemloc.PacketField.flag,rmaxmemloc.PacketField.memaddr,freshdatamemloc1.PacketField.memaddr,freshdatamemloc2.PacketField.memaddr);
                printf("\r\nAfter :rnewmemloc:%ld,\r\n ryet2sendmemloc:%ld,\r\n flagbit.PacketField.memaddr:%ld\r\nrmaxmemloc.PacketField.memaddr:%ld\r\nfreshdatamemloc1:%ld\r\nfreshdatamemloc2:%ld\r\n",rnewmemloc.PacketField.memaddr,ryet2sendmemloc.PacketField.memaddr,flagbit.PacketField.memaddr,rmaxmemloc.PacketField.memaddr,freshdatamemloc1.PacketField.memaddr,freshdatamemloc2.PacketField.memaddr);
                
//                if(rnewmemloc.PacketField.flag == 0)
                if(flagbit.PacketField.memaddr == 0)
                    printf("\r\nNo.of strings in the MEMORY :%ld,\r\n",(rnewmemloc.PacketField.memaddr-ryet2sendmemloc.PacketField.memaddr));
                else
                    printf("\r\nNo.of strings in the MEMORY :%ld,\r\n",((rnewmemloc.PacketField.memaddr+MEM_LEN)-ryet2sendmemloc.PacketField.memaddr));
                printf("\r\nsmrvalue:%.2f\r\n",(smrvalue.PacketField.memaddr/100.0));
                printf("\r\nMEM_LEN:%d\r\n",MEM_LEN);
                
                
                /**************/
                
                /*********************************/

                //                logwdata.PacketField.Startchar = '&';
//                memcpy(logwdata.PacketField.SLheader,"VDT300",6);
//                logwdata.PacketField.serialno = 12;
//                memcpy(logwdata.PacketField.datetime,"050321105715",12);
//                logwdata.PacketField.valid = 'A';
//                memcpy(logwdata.PacketField.lat,"N1305.1402",10);
//                memcpy(logwdata.PacketField.lng,"E07733.3241",11);
//                logwdata.PacketField.adc1 = 0.40;
//                logwdata.PacketField.adc2 = 226.66;
//                logwdata.PacketField.digdata = 0xFE;
//                logwdata.PacketField.adc3 = 4.59;
//                logwdata.PacketField.adc4 = 0;
//                logwdata.PacketField.adc5 = 0;
//                logwdata.PacketField.frq = 340;
//                logwdata.PacketField.adc6 = 5.01;
//                logwdata.PacketField.smr = 21.82;
//                logwdata.PacketField.Endchar = '^';
//                
//                //crc calculate/////////
//                //crcresult = crc16_ccitt(test_data, 9);
//                logwdata.PacketField.CRC_check = crc16_ccitt(&logwdata.rcvpacket[0], 81);//rcvpacket[83];
//                printf("logwdata.PacketField.CRC_check :%d\r\n",logwdata.PacketField.CRC_check);
//                
//                printf("\r\n....................................\r\n");
//                for(uint8_t i=0;i<85;i++)
//                {
//                    printf("logwdata.rcvpacket[%d] :%c\r\n",i,logwdata.rcvpacket[i]);
//                    SYSTICK_DelayMs(30);
//                }
//                printf("\r\n....................................\r\n");
                
//                writelogdata(logwdata.rcvpacket,85,1);
//                SYSTICK_DelayMs(300);
//                writelogdata(logwdata.rcvpacket,85,2);
//                SYSTICK_DelayMs(300);
//                writelogdata(logwdata.rcvpacket,85,3);
//                SYSTICK_DelayMs(300);
//                writelogdata(logwdata.rcvpacket,85,4);
//                SYSTICK_DelayMs(300);
//                writelogdata(logwdata.rcvpacket,85,5);
//                SYSTICK_DelayMs(300);
//                writelogdata(logwdata.rcvpacket,85,6);
//                SYSTICK_DelayMs(300);
//                writelogdata(logwdata.rcvpacket,85,7);
//                SYSTICK_DelayMs(300);
//                writelogdata(logwdata.rcvpacket,85,8);
//                SYSTICK_DelayMs(300);
//                readlogdata(&logrdata.rcvpacket[0],85,1);
//                
//                printf("logrdata.PacketField.serialno:%d\r\n",logrdata.PacketField.serialno);
//                printf("logrdata.PacketField.datetime:%.12s\r\n",logrdata.PacketField.datetime);
//                printf("logrdata.PacketField.valid:%c\r\n",logrdata.PacketField.valid);
//                printf("logrdata.PacketField.lat:%.10s\r\n",logrdata.PacketField.lat);
//                printf("logrdata.PacketField.smr :%.2f\r\n",logrdata.PacketField.smr );
//                printf("logwdata.PacketField.Endchar :%c\r\n",logwdata.PacketField.Endchar);
//                printf("logwdata.rcvpacket[74] :%c\r\n",logwdata.rcvpacket[74]);
                
                //logrdata.PacketField.CRC_check = crc16_ccitt(&logrdata.rcvpacket[0], 77);

//                printf("\r\n....................................\r\n");
//                //char *ptr1 = logrdata.rcvpacket;
//                for(uint8_t i=0;i<85;i++)
//                {
//                    //printf("%c,",*ptr1 );
//                    printf("logrdata.rcvpacket[%d] :%c\r\n",i,logrdata.rcvpacket[i]);
//                    SYSTICK_DelayMs(30);
//                }
//                printf("\r\n....................................\r\n");
                
//                printf("logrdata.PacketField.CRC_check :%d\r\n",crc16_ccitt(&logrdata.rcvpacket[0], 81) );
                
//                printf("sizeof(logrdata.PacketField.digdata):%d\r\n",sizeof(logrdata.PacketField.digdata));
                app3Data.state = APP3_STATE_FLASH_WRITE_ENABLE;
                break;

            case APP3_STATE_FLASH_WRITE_ENABLE:
                // Enable Writes to EEPROM
//                flashtxData[0] = FLASH_CMD_READ_STATUS;
//                flashtxData[0] = FLASH_CMD_MDID;
//                FLASH_CS_Clear();
//                printf("FLASH_CS_Clear");
//                SERCOM0_SPI_Write(flashtxData, 1);
                
//                SERCOM0_SPI_WriteRead(flashtxData, 1, flashrxData, 2);
//                state = APP3_STATE_FLASH_WRITE;
                /************* 1. Test Jedec ID *********/
//                SPI_Jedec_ID_Read(&Manufacturer_Id, &Device_Type, &Device_Id);
//                if ((Manufacturer_Id == 0xbf)&& (Device_Type==0x26) && (Device_Id==0x43))
//                {check=(check + 1);}
//                else
//                {check=0;}
//                printf("Test Jedec ID: %d,Manufacturer_Id=%d,Device_Type=%d,Device_Id=%d\r\n", check,Manufacturer_Id,Device_Type,Device_Id);
                
                break;

            default:
                break;
    }
}
float candata_filter(float value)
{
   static float samples[5]={0};
   static int x = 4;
//   static double total = 0;
   uint8_t validcnt =0;
   if((value==samples[0])||(samples[0]+1.0)>(value))
      validcnt++;
   if((value==samples[1])||(samples[1]+1.0)>(value))
      validcnt++;
   if((value==samples[2])||(samples[2]+1.0)>(value))
      validcnt++;
   if((value==samples[3])||(samples[3]+1.0)>(value))
      validcnt++;
   if((value==samples[4])||(samples[4]+1.0)>(value))
      validcnt++;
//       {
//           validcnt++;
//           
//       }
//   for(uint8_t y=0;y<5;y++)
//   {
//       if((value==samples[y])||(value>(samples[y]+10)))
//       {
//           validcnt++;
//           
//       }
//   }
//   samples[i-9] = samples[i-8];
//   samples[i-8] = samples[i-7];
//   samples[i-7] = samples[i-6];
//   samples[i-6] = samples[i-5];
//   samples[i-5] = samples[i-4];
   samples[0] = samples[1];
   samples[1] = samples[2];
   samples[2] = samples[3];
   samples[3] = samples[4];
   samples[4] = value;
   printf ("samples[0]:%.2f,samples[1]:%.2f,samples[2]:%.2f,samples[3]:%.2f,samples[4]:%.2f,validcnt:%d\r\n",samples[0],samples[1],samples[2],samples[3],samples[4],validcnt);
   
   
//   /* Update the moving average */ 
//   total += (x - samples[i]);
//   samples[i] = x;
//
//   /* Update the index */
    x = (x==4 ? 0 : x+1);
    if((validcnt >=2)&&(value <=99999.9))
    {
        return value;
    }
    else
        return 0;  
}
bool savelivedatatotempmem1(void)
{
//    packet logwdata;
//    rewrite smrvalue;

    bool retval = 0;
    uint8_t u8l_DI1 = 0,u8l_DI2=0,u8l_DI3=0,u8l_DI4=0,u8l_DI5=0,u8l_DI6=0,u8l_DI7=0,u8l_DI8=0;
    char tempbuff[1024] = {0};
//    char tempSLheader[12]={0};
//    char tempStartchar;
    static uint32_t tempsmr1=0;
    char adc1buf[10] = {0},adc2buf[10] = {0},adc3buf[10] = {0},adc4buf[10] = {0},adc5buf[10] = {0},adc6buf[10] = {0},smrbuf[10] = {0};
    //    rewrite11 smrvalue;
//    uint16_t adc1_int,adc1_flt,adc2_int,adc2_flt,adc3_int,adc3_flt,adc4_int,adc4_flt,adc5_int,adc5_flt,adc6_int,adc6_flt;
//    uint16_t smr_int,smr_flt;
    
//    memset(smrvalue.addrbuf,0,sizeof(smrvalue.addrbuf));
//    readsmr(&smrvalue.addrbuf[0]);
//    tempsmr1 = smrvalue.PacketField.memaddr;
    
    /********read smr*/
//    memset(smrvalue.addrbuf,0,sizeof(smrvalue.addrbuf));
//    readsmr(&smrvalue.addrbuf[0]);
    tempsmr1 = smrvalue.PacketField.memaddr;
    printf ("tempsmr1:%ld\r\n",tempsmr1);
    /*********read record nos*************************/
    readrecomemloc(&rrecomemloc.addrbuf[0]);
    rrecomemloc.PacketField.memaddr++;
    wrecomemloc.PacketField.memaddr = rrecomemloc.PacketField.memaddr;
    if(wrecomemloc.PacketField.memaddr > MEM_RECNO)
    {
        wrecomemloc.PacketField.memaddr = 0;
        rrecomemloc.PacketField.memaddr = 0;
    }
    saverecomemloc(&wrecomemloc.addrbuf[0]); 
    /**************************************************/
//    loadgpsdata();
    logwdata.PacketField.Startchar = '&';
//    tempStartchar =logwdata.PacketField.Startchar;
    readserialNo((uint8_t*)&logwdata.PacketField.SLheader[0]);
    if((logwdata.PacketField.SLheader[0] > 100)||(logwdata.PacketField.SLheader[1] > 100)||(logwdata.PacketField.SLheader[2] > 100)||(logwdata.PacketField.SLheader[3] > 100)||(logwdata.PacketField.SLheader[4] > 100)||(logwdata.PacketField.SLheader[5] > 100)||(logwdata.PacketField.SLheader[6] > 100)||(logwdata.PacketField.SLheader[7] > 100)||(logwdata.PacketField.SLheader[8] > 100)||(logwdata.PacketField.SLheader[9] > 100))
    {
        logwdata.PacketField.SLheader[0] = 'V';
        logwdata.PacketField.SLheader[1] = 'L';
        logwdata.PacketField.SLheader[2] = 'T';
        logwdata.PacketField.SLheader[3] = '3';
        logwdata.PacketField.SLheader[4] = '0';
        logwdata.PacketField.SLheader[5] = '0';
        logwdata.PacketField.SLheader[6] = '0';
        logwdata.PacketField.SLheader[7] = '0';
        logwdata.PacketField.SLheader[8] = '0';
        logwdata.PacketField.SLheader[9] = '0';
//        logwdata.PacketField.SLheader[10] = 0;
    }
//    memcpy(tempSLheader,logwdata.PacketField.SLheader,10);
    
    printf ("logwdata.PacketField.SLheader:%s\r\n",logwdata.PacketField.SLheader);

    //    memcpy(logwdata.PacketField.SLheader,"VLT300",6);
//    logwdata.PacketField.serialno = UNITSLNO;//3;//wrecomemloc.PacketField.memaddr;//12;
    
    //memcpy(logwdata.PacketField.date,gps_Date,6);
    for(uint8_t i=0;i<6;i++)
        logwdata.PacketField.date[i] = gps_Date[i];

//    memcpy(logwdata.PacketField.time,gps_UTCTime,6);
    for(uint8_t i=0;i<6;i++)
        logwdata.PacketField.time[i] = gps_UTCTime[i];
    logwdata.PacketField.time[5]='0';//make 00 sec
    
    
    
    logwdata.PacketField.valid = gps_Status[0];//'A';
//    memcpy(logwdata.PacketField.lat,gps_Latitude,9);
    for(uint8_t i=0;i<9;i++)
        logwdata.PacketField.lat[i] = gps_Latitude[i];
    
    logwdata.PacketField.NSIndicator = gps_NSIndicator[0];
    
//    memcpy(logwdata.PacketField.lng,gps_Longitude,10);
    for(uint8_t i=0;i<10;i++)
        logwdata.PacketField.lng[i] = gps_Longitude[i];
    
    logwdata.PacketField.EWIndicator = gps_EWIndicator[0];

    logwdata.PacketField.adc1 = flt_gps_SpeedOverGround;//0.40;
    ftoa(logwdata.PacketField.adc1, adc1buf, 2);
    
//    adc1_int = logwdata.PacketField.adc1;
//    adc1_flt = logwdata.PacketField.adc1 * 100.0;
//    adc1_flt = adc1_flt % 100;
            
    logwdata.PacketField.adc2 = flt_gps_CourseOverGround;//226.66;
    ftoa(logwdata.PacketField.adc2, adc2buf, 2);
//    adc2_int = logwdata.PacketField.adc2;
//    adc2_flt = logwdata.PacketField.adc2 * 100.0;
//    adc2_flt = adc2_flt % 100;
//    logwdata.PacketField.digdata = 0xFF;

    if(TESINGMODE == 0)
    {
        u8l_DI1 = (uint8_t)b_IgnitionON;//
    }
    else
    {
        u8l_DI1 = 1;//
    }
    u8l_DI2 = 0;//(uint8_t)b_speare1;//
//    u8l_DI3 = (uint8_t)b_Hydraulicoilfilterclog;//
    if(u8_SAVING2MEM == 0)
    {
        if(u16_CANHydoilfilterclogged == 0)
        {
            u8l_DI3 = 0;
        }
        else 
        {
            u8l_DI3 = 1;
        }  
    }
    else
    {
//        u8l_DI3 = 1;
        u8l_DI3 = (uint8_t)b_Hydraulicoilfilterclog;
    }   
//    u8l_DI4 = (uint8_t)b_airfiltercool;//
    if(u16_CANAirfilterclogged == 0)
    {
        u8l_DI4 = 0;
    }
    else
    {
        u8l_DI4 = 1;
    }
    if(flt_CANEngineLuboilpressure_bar < 1.0)
    {
        u8l_DI5 = 1;//(uint8_t)b_LubeOilPressure;//
    }
    else
    {
        u8l_DI5 = 0;
    }
    if(flt_CANEngineCoolantTemperature > 103)
    {
        u8l_DI6 = 1;//(uint8_t)b_highenginteperature;//
    }
    else
    {
        u8l_DI6 = 0;
    }
    
    u8l_DI7 = 0;//(uint8_t)b_speare2;//
    if(u16_CANSeatBelt == 0)
    {
        u8l_DI8 = 1;//(uint8_t)b_speare3;//
    }
    else
    {
        u8l_DI8 = 0;//(uint8_t)b_speare3;//
    }
    logwdata.PacketField.digdata = ((0x01&&u8l_DI1)<<7)|((0x01&&u8l_DI2)<<6)|((0x01&&u8l_DI3)<<5)|((0x01&&u8l_DI4)<<4)|((0x01&&u8l_DI5)<<3)|((0x01&&u8l_DI6)<<2)|((0x01&&u8l_DI7)<<1)|(0x01&&u8l_DI8);
//    u8l_DI1 = (logwdata.PacketField.digdata & 0x01);
//    u8l_DI2 = ((logwdata.PacketField.digdata >> 1) & 0x01);
//    u8l_DI3 = ((logwdata.PacketField.digdata >> 1) & 0x01);
//    u8l_DI4 = ((logwdata.PacketField.digdata >> 1) & 0x01);
//    u8l_DI5 = ((logwdata.PacketField.digdata >> 1) & 0x01);
//    u8l_DI6 = ((logwdata.PacketField.digdata >> 1) & 0x01);
//    u8l_DI7 = ((logwdata.PacketField.digdata >> 1) & 0x01);
//    u8l_DI8 = ((logwdata.PacketField.digdata >> 1) & 0x01);
    logwdata.PacketField.adc3 = flt_CANEngineCoolantTemperature;//4.59;
    ftoa(logwdata.PacketField.adc3, adc3buf, 2);
//    adc3_int = logwdata.PacketField.adc3;
//    adc3_flt = logwdata.PacketField.adc3 * 100.0;
//    adc3_flt = adc3_flt % 100;
    logwdata.PacketField.adc4 = flt_CANfuallevel;//0;
    ftoa(logwdata.PacketField.adc4, adc4buf, 2);
//    adc4_int = logwdata.PacketField.adc4;
//    adc4_flt = logwdata.PacketField.adc4 * 100.0;
//    adc4_flt = adc4_flt % 100;
    logwdata.PacketField.adc5 = 0;
    ftoa(logwdata.PacketField.adc5, adc5buf, 2);
//    adc5_int = logwdata.PacketField.adc5;
//    adc5_flt = logwdata.PacketField.adc5 * 100.0;
//    adc5_flt = adc5_flt % 100;
    if(TESINGMODE == 0)
    {
        //    logwdata.PacketField.frq = uint_frq;//200;
        logwdata.PacketField.frq = flt_CANEngineRPM;//200;//uint_frq;//200;
    }
    else
    {
        logwdata.PacketField.frq = 200;//uint_frq;//200;
    }

    logwdata.PacketField.adc6 = flt_CANHydoiltemp;//wrecomemloc.PacketField.memaddr * 0.01;//5.01;
    ftoa(logwdata.PacketField.adc6, adc6buf, 2);
//    adc6_int = logwdata.PacketField.adc6;
//    adc6_flt = logwdata.PacketField.adc6 * 100.0;
//    adc6_flt = adc6_flt % 100;
    
////    readsmr(&smrvalue.addrbuf[0]);
//    if(tempsmr1  > 99999959)//9999hh and 59min
//    {
//        tempsmr1  = 0;
////        savesmr(&smrvalue.addrbuf[0]);
//    }
    /*****************SMR*****************************/
//    memset(smrvalue.addrbuf,0,sizeof(smrvalue.addrbuf));
//    readsmr(&smrvalue.addrbuf[0]);
//    tempsmr1 = smrvalue.PacketField.memaddr;

    if(TESINGMODE == 0)
    {   
        if(candata_filter(flt_CANEnginetotalhourofoperation)>0)
//        if(flt_CANEnginetotalhourofoperation > 0)
        {
            logwdata.PacketField.smr = flt_CANEnginetotalhourofoperation;
            tempsmr1 = logwdata.PacketField.smr*100.0;
        }
        else
        {
            logwdata.PacketField.smr = tempsmr1/100.0;
        }
        
    }
    else
    {
        if(tempsmr1  > 99999959)//9999hh and 59min
        {
//        memset(smrvalue.addrbuf,0,sizeof(smrvalue.addrbuf));
//        readsmr(&smrvalue.addrbuf[0]);
        tempsmr1 = smrvalue.PacketField.memaddr;
        if(tempsmr1  > 99999959)//9999hh and 59min
            tempsmr1  = 0;
        }
        if((u8l_DI1 == 1)&&(logwdata.PacketField.frq > 115))//Ignition ON && Engine ON
    //    if(logwdata.PacketField.frq > 115)//Ignition ON && Engine ON
        {
                tempsmr1++;//max 4digit and one decibel 9999.9
                if(tempsmr1 < 100)
                {
                    if(tempsmr1  >= 60)
                    tempsmr1 = tempsmr1 + 40;
                }										
                else if((tempsmr1 % 100) >= 60)
                    tempsmr1 = tempsmr1 + 40;

    //            savesmr(&smrvalue.addrbuf[0]);
        }
        logwdata.PacketField.smr = tempsmr1/100.0;
    }
    ftoa(logwdata.PacketField.smr, smrbuf, 2);
    /************************************************/
//    smr_int = logwdata.PacketField.smr;
//    smr_flt = logwdata.PacketField.smr * 100.0;
//    smr_flt = smr_flt % 100;
    logwdata.PacketField.Endchar = '^';
//    printf("freshdatamemloc:\n\r");
//    sprintf(tempbuff,"%c%s%.4d,1N,%.6s%.6s,%c,%c%.9s,%c%.10s,%d.%.2d,%d.%.2d,%d,%d,%d,%d,%d,%d,%d,%d,%d.%.2d,%d.%.2d,%d.%.2d,%d,%d.%.2d,%d.%.2d%c"
//            ,logwdata.PacketField.Startchar,logwdata.PacketField.SLheader,logwdata.PacketField.serialno,
//            logwdata.PacketField.date,logwdata.PacketField.time,logwdata.PacketField.valid,
//            logwdata.PacketField.NSIndicator,logwdata.PacketField.lat,logwdata.PacketField.EWIndicator,logwdata.PacketField.lng,
//            adc1_int,adc1_flt,adc2_int,adc2_flt,u8l_DI1,u8l_DI2,u8l_DI3,u8l_DI4,u8l_DI5,u8l_DI6,u8l_DI7,u8l_DI8,
//            adc3_int,adc3_flt,adc4_int,adc4_flt,adc5_int,adc5_flt,logwdata.PacketField.frq,
//            adc6_int,adc6_flt,smr_int,smr_flt,logwdata.PacketField.Endchar );
//    
//    sprintf(tempbuff,"%c%.10s,1N,%.6s%.6s,%c,%c%.9s,%c%.10s,%d.%.2d,%d.%.2d,%d,%d,%d,%d,%d,%d,%d,%d,%d.%.2d,%d.%.2d,%d.%.2d,%d,%d.%.2d,%d.%.2d%c"
//            ,logwdata.PacketField.Startchar,logwdata.PacketField.SLheader,
//            logwdata.PacketField.date,logwdata.PacketField.time,logwdata.PacketField.valid,
//            logwdata.PacketField.NSIndicator,logwdata.PacketField.lat,logwdata.PacketField.EWIndicator,logwdata.PacketField.lng,
//            adc1_int,adc1_flt,adc2_int,adc2_flt,u8l_DI1,u8l_DI2,u8l_DI3,u8l_DI4,u8l_DI5,u8l_DI6,u8l_DI7,u8l_DI8,
//            adc3_int,adc3_flt,adc4_int,adc4_flt,adc5_int,adc5_flt,logwdata.PacketField.frq,
//            adc6_int,adc6_flt,smr_int,smr_flt,logwdata.PacketField.Endchar );
    memset(tempbuff,0,sizeof(tempbuff));
    sprintf(tempbuff,"%c%.10s,1N,%.6s%.6s,%c,%c%.9s,%c%.10s,%.2f,%.2f,%d,%d,%d,%d,%d,%d,%d,%d,%.2f,%.2f,%.2f,%d,%.2f,%.2f%c"
            ,logwdata.PacketField.Startchar,logwdata.PacketField.SLheader,
            logwdata.PacketField.date,logwdata.PacketField.time,logwdata.PacketField.valid,
            logwdata.PacketField.NSIndicator,logwdata.PacketField.lat,logwdata.PacketField.EWIndicator,logwdata.PacketField.lng,
            logwdata.PacketField.adc1,logwdata.PacketField.adc2,u8l_DI1,u8l_DI2,u8l_DI3,u8l_DI4,u8l_DI5,u8l_DI6,u8l_DI7,u8l_DI8,
            logwdata.PacketField.adc3,logwdata.PacketField.adc4,logwdata.PacketField.adc5,logwdata.PacketField.frq,
            logwdata.PacketField.adc6,logwdata.PacketField.smr,logwdata.PacketField.Endchar );
//    sprintf(tempbuff,"%c%.10s,1N,%.6s%.6s,%c,%c%.9s,%c%.10s,%.2f,%.2f,%d,%d,%d,%d,%d,%d,%d,%d,%.2f,%.2f,%.2f,%d,%.2f,%.2f%c"
//            ,tempStartchar,tempSLheader,
//            logwdata.PacketField.date,logwdata.PacketField.time,logwdata.PacketField.valid,
//            logwdata.PacketField.NSIndicator,logwdata.PacketField.lat,logwdata.PacketField.EWIndicator,logwdata.PacketField.lng,
//            logwdata.PacketField.adc1,logwdata.PacketField.adc2,u8l_DI1,u8l_DI2,u8l_DI3,u8l_DI4,u8l_DI5,u8l_DI6,u8l_DI7,u8l_DI8,
//            logwdata.PacketField.adc3,logwdata.PacketField.adc4,logwdata.PacketField.adc5,logwdata.PacketField.frq,
//            logwdata.PacketField.adc6,logwdata.PacketField.smr,logwdata.PacketField.Endchar );

    
    
    
    //        sprintf(tempbuff,"%c%.10s,1N,%.6s%.6s,%c,%c%.9s,%c%.10s,%s,%s,%d,%d,%d,%d,%d,%d,%d,%d,%s,%s,%s,%d,%s,%s%c"
//            ,logwdata.PacketField.Startchar,logwdata.PacketField.SLheader,
//            logwdata.PacketField.date,logwdata.PacketField.time,logwdata.PacketField.valid,
//            logwdata.PacketField.NSIndicator,logwdata.PacketField.lat,logwdata.PacketField.EWIndicator,logwdata.PacketField.lng,
//            adc1buf,adc2buf,u8l_DI1,u8l_DI2,u8l_DI3,u8l_DI4,u8l_DI5,u8l_DI6,u8l_DI7,u8l_DI8,
//            adc3buf,adc4buf,adc5buf,logwdata.PacketField.frq,
//            adc6buf,smrbuf,logwdata.PacketField.Endchar );
        /*****************************************/
    /********read no of fresh data is equal to 6 nos***************/
    readfreshdatamemloc1(&freshdatamemloc1.addrbuf[0]);
    printf("freshdatamemloc1:%ld of data :%s\n\r",freshdatamemloc1.PacketField.memaddr,tempbuff);
 
    if(freshdatamemloc1.PacketField.memaddr >= 10)
    {
//        freshdatamemloc.PacketField.memaddr = 10;
//        savefreshdatamemloc(&freshdatamemloc.addrbuf[0]);
    }
    else
    {
        savefreshlogdata1(logwdata.rcvpacket,85,freshdatamemloc1.PacketField.memaddr);
    //    printf("freshdatamemloc:%ld\n\r",freshdatamemloc.PacketField.memaddr);

        freshdatamemloc1.PacketField.memaddr++;

        savefreshdatamemloc1(&freshdatamemloc1.addrbuf[0]);
        memset(smrvalue.addrbuf,0,sizeof(smrvalue.addrbuf));
        smrvalue.PacketField.memaddr = tempsmr1 ;
        savesmr(&smrvalue.addrbuf[0]);
    }
    if(freshdatamemloc1.PacketField.memaddr >= NOOFDATAPERPACKET)
    {
        retval = true;
    }
    return retval;
}
bool savelivedatatotempmem2(void)
{
//    packet logwdata;
//    rewrite smrvalue;

    bool retval = 0;
    uint8_t u8l_DI1 = 0,u8l_DI2=0,u8l_DI3=0,u8l_DI4=0,u8l_DI5=0,u8l_DI6=0,u8l_DI7=0,u8l_DI8=0;
    char tempbuff[1024] = {0};
//    char tempStartchar;
    char tempSLheader[12]={0};
    static uint32_t tempsmr2=0;
    char adc1buf[10] = {0},adc2buf[10] = {0},adc3buf[10] = {0},adc4buf[10] = {0},adc5buf[10] = {0},adc6buf[10] = {0},smrbuf[10] = {0};
    
//    uint16_t adc1_int,adc1_flt,adc2_int,adc2_flt,adc3_int,adc3_flt,adc4_int,adc4_flt,adc5_int,adc5_flt,adc6_int,adc6_flt;
//    uint16_t smr_int,smr_flt;
    /**********read smr*********/
//    memset(smrvalue.addrbuf,0,sizeof(smrvalue.addrbuf));
//    readsmr(&smrvalue.addrbuf[0]);
    tempsmr2 = smrvalue.PacketField.memaddr;
    printf ("tempsmr2:%ld\r\n",tempsmr2);
    /*********read record nos*************************/
    readrecomemloc(&rrecomemloc.addrbuf[0]);
    rrecomemloc.PacketField.memaddr++;
    wrecomemloc.PacketField.memaddr = rrecomemloc.PacketField.memaddr;
    if(wrecomemloc.PacketField.memaddr > MEM_RECNO)
    {
        wrecomemloc.PacketField.memaddr = 0;
        rrecomemloc.PacketField.memaddr = 0;
    }
    saverecomemloc(&wrecomemloc.addrbuf[0]); 
    /**************************************************/
//    loadgpsdata();
    logwdata.PacketField.Startchar = '&';
//    tempStartchar = logwdata.PacketField.Startchar;
    readserialNo((uint8_t*)&logwdata.PacketField.SLheader[0]);
    if((logwdata.PacketField.SLheader[0] > 100)||(logwdata.PacketField.SLheader[1] > 100)||(logwdata.PacketField.SLheader[2] > 100)||(logwdata.PacketField.SLheader[3] > 100)||(logwdata.PacketField.SLheader[4] > 100)||(logwdata.PacketField.SLheader[5] > 100)||(logwdata.PacketField.SLheader[6] > 100)||(logwdata.PacketField.SLheader[7] > 100)||(logwdata.PacketField.SLheader[8] > 100)||(logwdata.PacketField.SLheader[9] > 100))
    {
        logwdata.PacketField.SLheader[0] = 'V';
        logwdata.PacketField.SLheader[1] = 'L';
        logwdata.PacketField.SLheader[2] = 'T';
        logwdata.PacketField.SLheader[3] = '3';
        logwdata.PacketField.SLheader[4] = '0';
        logwdata.PacketField.SLheader[5] = '0';
        logwdata.PacketField.SLheader[6] = '0';
        logwdata.PacketField.SLheader[7] = '0';
        logwdata.PacketField.SLheader[8] = '0';
        logwdata.PacketField.SLheader[9] = '0';
    }
    memcpy(tempSLheader,logwdata.PacketField.SLheader,10);
//    printf ("logwdata.PacketField.SLheader:%s\r\n",logwdata.PacketField.SLheader);

    //    memcpy(logwdata.PacketField.SLheader,"VLT300",6);
//    logwdata.PacketField.serialno = UNITSLNO;//3;//wrecomemloc.PacketField.memaddr;//12;
    
    memcpy(logwdata.PacketField.date,gps_Date,6);
    memcpy(logwdata.PacketField.time,gps_UTCTime,6);
    logwdata.PacketField.time[5]='0';//make 00 sec
    logwdata.PacketField.valid = gps_Status[0];//'A';
    
    memcpy(logwdata.PacketField.lat,gps_Latitude,9);
    logwdata.PacketField.NSIndicator = gps_NSIndicator[0];
    memcpy(logwdata.PacketField.lng,gps_Longitude,10);
    logwdata.PacketField.EWIndicator = gps_EWIndicator[0];

    logwdata.PacketField.adc1 = flt_gps_SpeedOverGround;//0.40;
    ftoa(logwdata.PacketField.adc1, adc1buf, 2);
    
//    adc1_int = logwdata.PacketField.adc1;
//    adc1_flt = logwdata.PacketField.adc1 * 100.0;
//    adc1_flt = adc1_flt % 100;
            
    logwdata.PacketField.adc2 = flt_gps_CourseOverGround;//226.66;
    ftoa(logwdata.PacketField.adc2, adc2buf, 2);
//    adc2_int = logwdata.PacketField.adc2;
//    adc2_flt = logwdata.PacketField.adc2 * 100.0;
//    adc2_flt = adc2_flt % 100;
//    logwdata.PacketField.digdata = 0xFF;

//    b_IgnitionON = 1;//
//    u8l_DI1 = (uint8_t)b_IgnitionON;//
    if(TESINGMODE == 0)
    {
        u8l_DI1 = (uint8_t)b_IgnitionON;//
    }
    else
    {
        u8l_DI1 = 1;//
    }
    u8l_DI2 = 0;//(uint8_t)b_speare1;//
//    u8l_DI3 = (uint8_t)b_Hydraulicoilfilterclog;//
    
    if(u8_SAVING2MEM == 0)
    {
        if(u16_CANHydoilfilterclogged == 0)
        {
            u8l_DI3 = 0;
        }
        else 
        {
            u8l_DI3 = 1;
        }  
    }
    else
    {
//        u8l_DI3 = 1;
        u8l_DI3 = (uint8_t)b_Hydraulicoilfilterclog;
    }
//    u8l_DI4 = (uint8_t)b_airfiltercool;//
    if(u16_CANAirfilterclogged == 0)
    {
        u8l_DI4 = 0;
    }
    else
    {
        u8l_DI4 = 1;
    }
    if(flt_CANEngineLuboilpressure_bar < 1.0)
    {
        u8l_DI5 = 1;//(uint8_t)b_LubeOilPressure;//
    }
    else
    {
        u8l_DI5 = 0;
    }
    if(flt_CANEngineCoolantTemperature > 103)
    {
        u8l_DI6 = 1;//(uint8_t)b_highenginteperature;//
    }
    else
    {
        u8l_DI6 = 0;
    }
    
    u8l_DI7 = 0;//(uint8_t)b_speare2;//
    if(u16_CANSeatBelt == 0)
    {
        u8l_DI8 = 1;//(uint8_t)b_speare3;//
    }
    else
    {
        u8l_DI8 = 0;//(uint8_t)b_speare3;//
    }
    logwdata.PacketField.digdata = ((0x01&&u8l_DI1)<<7)|((0x01&&u8l_DI2)<<6)|((0x01&&u8l_DI3)<<5)|((0x01&&u8l_DI4)<<4)|((0x01&&u8l_DI5)<<3)|((0x01&&u8l_DI6)<<2)|((0x01&&u8l_DI7)<<1)|(0x01&&u8l_DI8);
//    u8l_DI1 = (logwdata.PacketField.digdata & 0x01);
//    u8l_DI2 = ((logwdata.PacketField.digdata >> 1) & 0x01);
//    u8l_DI3 = ((logwdata.PacketField.digdata >> 1) & 0x01);
//    u8l_DI4 = ((logwdata.PacketField.digdata >> 1) & 0x01);
//    u8l_DI5 = ((logwdata.PacketField.digdata >> 1) & 0x01);
//    u8l_DI6 = ((logwdata.PacketField.digdata >> 1) & 0x01);
//    u8l_DI7 = ((logwdata.PacketField.digdata >> 1) & 0x01);
//    u8l_DI8 = ((logwdata.PacketField.digdata >> 1) & 0x01);

    logwdata.PacketField.adc3 = flt_CANEngineCoolantTemperature;//4.59;
    ftoa(logwdata.PacketField.adc3, adc3buf, 2);
//    adc3_int = logwdata.PacketField.adc3;
//    adc3_flt = logwdata.PacketField.adc3 * 100.0;
//    adc3_flt = adc3_flt % 100;
    
    logwdata.PacketField.adc4 = flt_CANfuallevel;//0;
    ftoa(logwdata.PacketField.adc4, adc4buf, 2);
//    adc4_int = logwdata.PacketField.adc4;
//    adc4_flt = logwdata.PacketField.adc4 * 100.0;
//    adc4_flt = adc4_flt % 100;
    
    logwdata.PacketField.adc5 = 0;
    ftoa(logwdata.PacketField.adc5, adc5buf, 2);
//    adc5_int = logwdata.PacketField.adc5;
//    adc5_flt = logwdata.PacketField.adc5 * 100.0;
//    adc5_flt = adc5_flt % 100;
    
//    logwdata.PacketField.frq = 200;//uint_frq;//200;
    if(TESINGMODE == 0)
    {
        //    logwdata.PacketField.frq = uint_frq;//200;
        logwdata.PacketField.frq = flt_CANEngineRPM;//200;//uint_frq;//200;
    }
    else
    {
        logwdata.PacketField.frq = 200;//uint_frq;//200;
    }
//    logwdata.PacketField.frq = uint_frq;//200;
//    logwdata.PacketField.frq = flt_CANEngineRPM;//200;//uint_frq;//200;
    
    logwdata.PacketField.adc6 = flt_CANHydoiltemp;//wrecomemloc.PacketField.memaddr * 0.01;//5.01;
    ftoa(logwdata.PacketField.adc6, adc6buf, 2);
//    adc6_int = logwdata.PacketField.adc6;
//    adc6_flt = logwdata.PacketField.adc6 * 100.0;
//    adc6_flt = adc6_flt % 100;
    /*
    memset(smrvalue.addrbuf,0,sizeof(smrvalue.addrbuf));
    readsmr(&smrvalue.addrbuf[0]);
    tempsmr2 = smrvalue.PacketField.memaddr;
    
    if(tempsmr2  > 99999959)//9999hh and 59min
    {
        memset(smrvalue.addrbuf,0,sizeof(smrvalue.addrbuf));
        readsmr(&smrvalue.addrbuf[0]);
        tempsmr2 = smrvalue.PacketField.memaddr;
        if(tempsmr2  > 99999959)//9999hh and 59min
            tempsmr2  = 0;
    }
    if((u8l_DI1 == 1)&&(logwdata.PacketField.frq > 115))//Ignition ON && Engine ON
//    if(logwdata.PacketField.frq > 115)//Ignition ON && Engine ON
    {
            tempsmr2++;//max 4digit and one decibel 9999.9
            if(tempsmr2 < 100)
            {
                if(tempsmr2  >= 60)
                tempsmr2 = tempsmr2 + 40;
            }										
            else if((tempsmr2 % 100) >= 60)
                tempsmr2 = tempsmr2 + 40;

//            savesmr(&smrvalue.addrbuf[0]);
    }
//    logwdata.PacketField.smr = tempsmr2/100.0;
    if(TESINGMODE == 0)
        logwdata.PacketField.smr = flt_CANEnginetotalhourofoperation;
    else
        logwdata.PacketField.smr = tempsmr2/100.0;
    
    ftoa(logwdata.PacketField.smr, smrbuf, 2);
//    if(TESINGMODE == 0)
//    {
//        ftoa(flt_CANEnginetotalhourofoperation, smrbuf, 2);
//    }
//    else
//    {
//        ftoa(logwdata.PacketField.smr, smrbuf, 2);
//    }
    
//    smr_int = logwdata.PacketField.smr;
//    smr_flt = logwdata.PacketField.smr * 100.0;
//    smr_flt = smr_flt % 100;
     */
    /*****************SMR*****************************/
//    memset(smrvalue.addrbuf,0,sizeof(smrvalue.addrbuf));
//    readsmr(&smrvalue.addrbuf[0]);
//    tempsmr2 = smrvalue.PacketField.memaddr;

    if(TESINGMODE == 0)
    {
        if(candata_filter(flt_CANEnginetotalhourofoperation)> 0)
//        if(flt_CANEnginetotalhourofoperation > 0)
        {
            logwdata.PacketField.smr = flt_CANEnginetotalhourofoperation;
            tempsmr2 = logwdata.PacketField.smr*100.0;
        }
        else
        {
            logwdata.PacketField.smr = tempsmr2/100.0;
        }
        
    }
    else
    {
        if(tempsmr2  > 99999959)//9999hh and 59min
        {
//        memset(smrvalue.addrbuf,0,sizeof(smrvalue.addrbuf));
//        readsmr(&smrvalue.addrbuf[0]);
        tempsmr2 = smrvalue.PacketField.memaddr;
        if(tempsmr2  > 99999959)//9999hh and 59min
            tempsmr2  = 0;
        }
        if((u8l_DI1 == 1)&&(logwdata.PacketField.frq > 115))//Ignition ON && Engine ON
    //    if(logwdata.PacketField.frq > 115)//Ignition ON && Engine ON
        {
                tempsmr2++;//max 4digit and one decibel 9999.9
                if(tempsmr2 < 100)
                {
                    if(tempsmr2  >= 60)
                    tempsmr2 = tempsmr2 + 40;
                }										
                else if((tempsmr2 % 100) >= 60)
                    tempsmr2 = tempsmr2 + 40;

    //            savesmr(&smrvalue.addrbuf[0]);
        }
        logwdata.PacketField.smr = tempsmr2/100.0;
    }
    
    ftoa(logwdata.PacketField.smr, smrbuf, 2);
    /************************************************/
    logwdata.PacketField.Endchar = '^';
//    printf("freshdatamemloc:\n\r");
//    sprintf(tempbuff,"%c%s%.4d,1N,%.6s%.6s,%c,%c%.9s,%c%.10s,%d.%.2d,%d.%.2d,%d,%d,%d,%d,%d,%d,%d,%d,%d.%.2d,%d.%.2d,%d.%.2d,%d,%d.%.2d,%d.%.2d%c"
//            ,logwdata.PacketField.Startchar,logwdata.PacketField.SLheader,logwdata.PacketField.serialno,
//            logwdata.PacketField.date,logwdata.PacketField.time,logwdata.PacketField.valid,
//            logwdata.PacketField.NSIndicator,logwdata.PacketField.lat,logwdata.PacketField.EWIndicator,logwdata.PacketField.lng,
//            adc1_int,adc1_flt,adc2_int,adc2_flt,u8l_DI1,u8l_DI2,u8l_DI3,u8l_DI4,u8l_DI5,u8l_DI6,u8l_DI7,u8l_DI8,
//            adc3_int,adc3_flt,adc4_int,adc4_flt,adc5_int,adc5_flt,logwdata.PacketField.frq,
//            adc6_int,adc6_flt,smr_int,smr_flt,logwdata.PacketField.Endchar );
//    
//    sprintf(tempbuff,"%c%.10s,1N,%.6s%.6s,%c,%c%.9s,%c%.10s,%d.%.2d,%d.%.2d,%d,%d,%d,%d,%d,%d,%d,%d,%d.%.2d,%d.%.2d,%d.%.2d,%d,%d.%.2d,%d.%.2d%c"
//            ,logwdata.PacketField.Startchar,logwdata.PacketField.SLheader,
//            logwdata.PacketField.date,logwdata.PacketField.time,logwdata.PacketField.valid,
//            logwdata.PacketField.NSIndicator,logwdata.PacketField.lat,logwdata.PacketField.EWIndicator,logwdata.PacketField.lng,
//            adc1_int,adc1_flt,adc2_int,adc2_flt,u8l_DI1,u8l_DI2,u8l_DI3,u8l_DI4,u8l_DI5,u8l_DI6,u8l_DI7,u8l_DI8,
//            adc3_int,adc3_flt,adc4_int,adc4_flt,adc5_int,adc5_flt,logwdata.PacketField.frq,
//            adc6_int,adc6_flt,smr_int,smr_flt,logwdata.PacketField.Endchar );
    memset(tempbuff,0,sizeof(tempbuff));
    sprintf(tempbuff,"%c%.10s,1N,%.6s%.6s,%c,%c%.9s,%c%.10s,%.2f,%.2f,%d,%d,%d,%d,%d,%d,%d,%d,%.2f,%.2f,%.2f,%d,%.2f,%.2f%c"
            ,logwdata.PacketField.Startchar,logwdata.PacketField.SLheader,
            logwdata.PacketField.date,logwdata.PacketField.time,logwdata.PacketField.valid,
            logwdata.PacketField.NSIndicator,logwdata.PacketField.lat,logwdata.PacketField.EWIndicator,logwdata.PacketField.lng,
            logwdata.PacketField.adc1,logwdata.PacketField.adc2,u8l_DI1,u8l_DI2,u8l_DI3,u8l_DI4,u8l_DI5,u8l_DI6,u8l_DI7,u8l_DI8,
            logwdata.PacketField.adc3,logwdata.PacketField.adc4,logwdata.PacketField.adc5,logwdata.PacketField.frq,
            logwdata.PacketField.adc6,logwdata.PacketField.smr,logwdata.PacketField.Endchar );
//    sprintf(tempbuff,"%c%.10s,1N,%.6s%.6s,%c,%c%.9s,%c%.10s,%.2f,%.2f,%d,%d,%d,%d,%d,%d,%d,%d,%.2f,%.2f,%.2f,%d,%.2f,%.2f%c"
//            ,tempStartchar,tempSLheader,
//            logwdata.PacketField.date,logwdata.PacketField.time,logwdata.PacketField.valid,
//            logwdata.PacketField.NSIndicator,logwdata.PacketField.lat,logwdata.PacketField.EWIndicator,logwdata.PacketField.lng,
//            logwdata.PacketField.adc1,logwdata.PacketField.adc2,u8l_DI1,u8l_DI2,u8l_DI3,u8l_DI4,u8l_DI5,u8l_DI6,u8l_DI7,u8l_DI8,
//            logwdata.PacketField.adc3,logwdata.PacketField.adc4,logwdata.PacketField.adc5,logwdata.PacketField.frq,
//            logwdata.PacketField.adc6,logwdata.PacketField.smr,logwdata.PacketField.Endchar );

    
    //        sprintf(tempbuff,"%c%.10s,1N,%.6s%.6s,%c,%c%.9s,%c%.10s,%s,%s,%d,%d,%d,%d,%d,%d,%d,%d,%s,%s,%s,%d,%s,%s%c"
//            ,logwdata.PacketField.Startchar,logwdata.PacketField.SLheader,
//            logwdata.PacketField.date,logwdata.PacketField.time,logwdata.PacketField.valid,
//            logwdata.PacketField.NSIndicator,logwdata.PacketField.lat,logwdata.PacketField.EWIndicator,logwdata.PacketField.lng,
//            adc1buf,adc2buf,u8l_DI1,u8l_DI2,u8l_DI3,u8l_DI4,u8l_DI5,u8l_DI6,u8l_DI7,u8l_DI8,
//            adc3buf,adc4buf,adc5buf,logwdata.PacketField.frq,
//            adc6buf,smrbuf,logwdata.PacketField.Endchar );
        /*****************************************/
    /********read no of fresh data is equal to 6 nos***************/
    readfreshdatamemloc2(&freshdatamemloc2.addrbuf[0]);
    printf("freshdatamemloc2:%ld of data :%s\n\r",freshdatamemloc2.PacketField.memaddr,tempbuff);
    
    if(freshdatamemloc2.PacketField.memaddr >= 10)
    {
//        freshdatamemloc.PacketField.memaddr = 10;
//        savefreshdatamemloc(&freshdatamemloc.addrbuf[0]);
    }
    else
    {
        savefreshlogdata2(logwdata.rcvpacket,85,freshdatamemloc2.PacketField.memaddr);
    //    printf("freshdatamemloc:%ld\n\r",freshdatamemloc.PacketField.memaddr);

        freshdatamemloc2.PacketField.memaddr++;
        savefreshdatamemloc2(&freshdatamemloc2.addrbuf[0]);
        
        memset(smrvalue.addrbuf,0,sizeof(smrvalue.addrbuf));
        smrvalue.PacketField.memaddr = tempsmr2 ;
        savesmr(&smrvalue.addrbuf[0]);
    }
    if(freshdatamemloc2.PacketField.memaddr >= NOOFDATAPERPACKET)
    {
        retval = true;
    }
    return retval;
}
bool loadlivedata1(char * data)
{
//    packet logrdata;
//    rewrite freshdatamemloc1;

    bool retval = false;
    uint8_t u8l_DI1,u8l_DI2,u8l_DI3,u8l_DI4,u8l_DI5,u8l_DI6,u8l_DI7,u8l_DI8;
    char tempbuff[1024] = {0};
    
    char adc1buf[10] = {0},adc2buf[10] = {0},adc3buf[10] = {0},adc4buf[10] = {0},adc5buf[10] = {0},adc6buf[10] = {0},smrbuf[10] = {0};
        
    readfreshdatamemloc1(&freshdatamemloc1.addrbuf[0]);
    
//    printf("freshdatamemloc1:%ld\n\r",freshdatamemloc1.PacketField.memaddr);            
        
//        for(uint32_t temp_i = 0;((temp_i < freshdatamemloc.PacketField.memaddr)&&(temp_i<10)); temp_i++)
        for(uint32_t temp_i = 0;((temp_i < freshdatamemloc1.PacketField.memaddr)); temp_i++)
        {
            readfreshlogdata1(&logrdata.rcvpacket[0],85,temp_i);
//            readfreshlogdata1(&memdata[0],85,temp_i);
//            printf("logrdata.rcvpacket[] :%s\n\r",logrdata.rcvpacket);
//            if((logrdata.rcvpacket[0] > 100)&&(logrdata.rcvpacket[1] >100)&&(logrdata.rcvpacket[2] >100)&&(logrdata.rcvpacket[3] >100))
            if((logrdata.PacketField.Startchar == '&')&&(logrdata.PacketField.Endchar == '^'))
            {
              ftoa(logrdata.PacketField.adc1, adc1buf, 2);  
//            adc1_int = logrdata.PacketField.adc1;
//            adc1_flt = logrdata.PacketField.adc1 * 100.0;
//            adc1_flt = adc1_flt % 100;
              ftoa(logrdata.PacketField.adc2, adc2buf, 2); 
//            adc2_int = logrdata.PacketField.adc2;
//            adc2_flt = logrdata.PacketField.adc2 * 100.0;
//            adc2_flt = adc2_flt % 100;
    
            u8l_DI1 = ((logrdata.PacketField.digdata >>7) & 0x01);
            u8l_DI2 = ((logrdata.PacketField.digdata >> 6) & 0x01);
            u8l_DI3 = ((logrdata.PacketField.digdata >> 5) & 0x01);
            u8l_DI4 = ((logrdata.PacketField.digdata >> 4) & 0x01);
            u8l_DI5 = ((logrdata.PacketField.digdata >> 3) & 0x01);
            u8l_DI6 = ((logrdata.PacketField.digdata >> 2) & 0x01);
            u8l_DI7 = ((logrdata.PacketField.digdata >> 1) & 0x01);
            u8l_DI8 = (logrdata.PacketField.digdata & 0x01);
            
            ftoa(logrdata.PacketField.adc3, adc3buf, 2); 
//            adc3_int = logrdata.PacketField.adc3;
//            adc3_flt = logrdata.PacketField.adc3 * 100.0;
//            adc3_flt = adc3_flt % 100;
            ftoa(logrdata.PacketField.adc4, adc4buf, 2); 
//            adc4_int = logrdata.PacketField.adc4;
//            adc4_flt = logrdata.PacketField.adc4 * 100.0;
//            adc4_flt = adc4_flt % 100;
            ftoa(logrdata.PacketField.adc5, adc5buf, 2); 
//            adc5_int = logrdata.PacketField.adc5;
//            adc5_flt = logrdata.PacketField.adc5 * 100.0;
//            adc5_flt = adc5_flt % 100;
            ftoa(logrdata.PacketField.adc6, adc6buf, 2); 
//            adc6_int = logrdata.PacketField.adc6;
//            adc6_flt = logrdata.PacketField.adc6 * 100.0;
//            adc6_flt = adc6_flt % 100;
            ftoa(logrdata.PacketField.smr, smrbuf, 2);
//            smr_int = logrdata.PacketField.smr;
//            smr_flt = logrdata.PacketField.smr * 100.0;
//            smr_flt = smr_flt % 100;
            
//            sprintf(tempbuff,"%c%s%.4d,1N,%.6s%.6s,%c,%c%.9s,%c%.10s,%d.%d,%d.%d,%d,%d,%d,%d,%d,%d,%d,%d,%d.%d,%d.%d,%d.%d,%d,%d.%d,%d.%d%c"
//                ,logrdata.PacketField.Startchar,logrdata.PacketField.SLheader,logrdata.PacketField.serialno,
//                logrdata.PacketField.date,logrdata.PacketField.time,logrdata.PacketField.valid,
//                logrdata.PacketField.NSIndicator,logrdata.PacketField.lat,logrdata.PacketField.EWIndicator,logrdata.PacketField.lng,
//                adc1_int,adc1_flt,adc2_int,adc2_flt,u8l_DI1,u8l_DI2,u8l_DI3,u8l_DI4,u8l_DI5,u8l_DI6,u8l_DI7,u8l_DI8,
//                adc3_int,adc3_flt,adc4_int,adc4_flt,adc5_int,adc5_flt,logrdata.PacketField.frq,
//                adc6_int,adc6_flt,smr_int,smr_flt,logrdata.PacketField.Endchar );
//            
//            sprintf(tempbuff,"%c%.10s,1N,%.6s%.6s,%c,%c%.9s,%c%.10s,%d.%d,%d.%d,%d,%d,%d,%d,%d,%d,%d,%d,%d.%d,%d.%d,%d.%d,%d,%d.%d,%d.%d%c"
//                ,logrdata.PacketField.Startchar,logrdata.PacketField.SLheader,
//                logrdata.PacketField.date,logrdata.PacketField.time,logrdata.PacketField.valid,
//                logrdata.PacketField.NSIndicator,logrdata.PacketField.lat,logrdata.PacketField.EWIndicator,logrdata.PacketField.lng,
//                adc1_int,adc1_flt,adc2_int,adc2_flt,u8l_DI1,u8l_DI2,u8l_DI3,u8l_DI4,u8l_DI5,u8l_DI6,u8l_DI7,u8l_DI8,
//                adc3_int,adc3_flt,adc4_int,adc4_flt,adc5_int,adc5_flt,logrdata.PacketField.frq,
//                adc6_int,adc6_flt,smr_int,smr_flt,logrdata.PacketField.Endchar );
            memset(tempbuff,0,sizeof(tempbuff));
            sprintf(tempbuff,"%c%.10s,1N,%.6s%.6s,%c,%c%.9s,%c%.10s,%.2f,%.2f,%d,%d,%d,%d,%d,%d,%d,%d,%.2f,%.2f,%.2f,%d,%.2f,%.2f%c"
            ,logrdata.PacketField.Startchar,logrdata.PacketField.SLheader,
            logrdata.PacketField.date,logrdata.PacketField.time,logrdata.PacketField.valid,
            logrdata.PacketField.NSIndicator,logrdata.PacketField.lat,logrdata.PacketField.EWIndicator,logrdata.PacketField.lng,
            logrdata.PacketField.adc1,logrdata.PacketField.adc2,u8l_DI1,u8l_DI2,u8l_DI3,u8l_DI4,u8l_DI5,u8l_DI6,u8l_DI7,u8l_DI8,
            logrdata.PacketField.adc3,logrdata.PacketField.adc4,logrdata.PacketField.adc5,logrdata.PacketField.frq,
            logrdata.PacketField.adc6,logrdata.PacketField.smr,logrdata.PacketField.Endchar );
//           sprintf(tempbuff,"%c%.10s,1N,%.6s%.6s,%c,%c%.9s,%c%.10s,%s,%s,%d,%d,%d,%d,%d,%d,%d,%d,%s,%s,%s,%d,%s,%s%c"
//            ,logrdata.PacketField.Startchar,logrdata.PacketField.SLheader,
//            logrdata.PacketField.date,logrdata.PacketField.time,logrdata.PacketField.valid,
//            logrdata.PacketField.NSIndicator,logrdata.PacketField.lat,logrdata.PacketField.EWIndicator,logrdata.PacketField.lng,
//            adc1buf,adc2buf,u8l_DI1,u8l_DI2,u8l_DI3,u8l_DI4,u8l_DI5,u8l_DI6,u8l_DI7,u8l_DI8,
//            adc3buf,adc4buf,adc5buf,logrdata.PacketField.frq,
//            adc6buf,smrbuf,logrdata.PacketField.Endchar ); 
            strcat(data,tempbuff);
//            printf("freshdatamemloc:%ld of data :%s\n\r",temp_i,tempbuff);
            }
        }
        printf("freshdatamemloc1:%ld No. data :%s\n\r",freshdatamemloc1.PacketField.memaddr,data);
        retval = true;
//    }
    return retval;
}
bool loadlivedata2(char * data)
{
//    packet logrdata;
//    rewrite freshdatamemloc2;

    bool retval = false;
    uint8_t u8l_DI1,u8l_DI2,u8l_DI3,u8l_DI4,u8l_DI5,u8l_DI6,u8l_DI7,u8l_DI8;
    char tempbuff[1024] = {0};
    
    char adc1buf[10] = {0},adc2buf[10] = {0},adc3buf[10] = {0},adc4buf[10] = {0},adc5buf[10] = {0},adc6buf[10] = {0},smrbuf[10] = {0};
        
    readfreshdatamemloc2(&freshdatamemloc2.addrbuf[0]);
    
//    printf("freshdatamemloc2:%ld\n\r",freshdatamemloc2.PacketField.memaddr);            
        
//        for(uint32_t temp_i = 0;((temp_i < freshdatamemloc.PacketField.memaddr)&&(temp_i<10)); temp_i++)
        for(uint32_t temp_i = 0;((temp_i < freshdatamemloc2.PacketField.memaddr)); temp_i++)
        {
            readfreshlogdata2(&logrdata.rcvpacket[0],85,temp_i);
//            printf("logrdata.rcvpacket[] :%s\n\r",logrdata.rcvpacket);
//            if((logrdata.rcvpacket[0] > 100)&&(logrdata.rcvpacket[1] >100)&&(logrdata.rcvpacket[2] >100)&&(logrdata.rcvpacket[3] >100))
            if((logrdata.PacketField.Startchar == '&')&&(logrdata.PacketField.Endchar == '^'))
            {
              ftoa(logrdata.PacketField.adc1, adc1buf, 2);  
//            adc1_int = logrdata.PacketField.adc1;
//            adc1_flt = logrdata.PacketField.adc1 * 100.0;
//            adc1_flt = adc1_flt % 100;
              ftoa(logrdata.PacketField.adc2, adc2buf, 2); 
//            adc2_int = logrdata.PacketField.adc2;
//            adc2_flt = logrdata.PacketField.adc2 * 100.0;
//            adc2_flt = adc2_flt % 100;
    
            u8l_DI1 = ((logrdata.PacketField.digdata >>7) & 0x01);
            u8l_DI2 = ((logrdata.PacketField.digdata >> 6) & 0x01);
            u8l_DI3 = ((logrdata.PacketField.digdata >> 5) & 0x01);
            u8l_DI4 = ((logrdata.PacketField.digdata >> 4) & 0x01);
            u8l_DI5 = ((logrdata.PacketField.digdata >> 3) & 0x01);
            u8l_DI6 = ((logrdata.PacketField.digdata >> 2) & 0x01);
            u8l_DI7 = ((logrdata.PacketField.digdata >> 1) & 0x01);
            u8l_DI8 = (logrdata.PacketField.digdata & 0x01);
            
            ftoa(logrdata.PacketField.adc3, adc3buf, 2); 
//            adc3_int = logrdata.PacketField.adc3;
//            adc3_flt = logrdata.PacketField.adc3 * 100.0;
//            adc3_flt = adc3_flt % 100;
            ftoa(logrdata.PacketField.adc4, adc4buf, 2); 
//            adc4_int = logrdata.PacketField.adc4;
//            adc4_flt = logrdata.PacketField.adc4 * 100.0;
//            adc4_flt = adc4_flt % 100;
            ftoa(logrdata.PacketField.adc5, adc5buf, 2); 
//            adc5_int = logrdata.PacketField.adc5;
//            adc5_flt = logrdata.PacketField.adc5 * 100.0;
//            adc5_flt = adc5_flt % 100;
            ftoa(logrdata.PacketField.adc6, adc6buf, 2); 
//            adc6_int = logrdata.PacketField.adc6;
//            adc6_flt = logrdata.PacketField.adc6 * 100.0;
//            adc6_flt = adc6_flt % 100;
            ftoa(logrdata.PacketField.smr, smrbuf, 2);
//            smr_int = logrdata.PacketField.smr;
//            smr_flt = logrdata.PacketField.smr * 100.0;
//            smr_flt = smr_flt % 100;
            
//            sprintf(tempbuff,"%c%s%.4d,1N,%.6s%.6s,%c,%c%.9s,%c%.10s,%d.%d,%d.%d,%d,%d,%d,%d,%d,%d,%d,%d,%d.%d,%d.%d,%d.%d,%d,%d.%d,%d.%d%c"
//                ,logrdata.PacketField.Startchar,logrdata.PacketField.SLheader,logrdata.PacketField.serialno,
//                logrdata.PacketField.date,logrdata.PacketField.time,logrdata.PacketField.valid,
//                logrdata.PacketField.NSIndicator,logrdata.PacketField.lat,logrdata.PacketField.EWIndicator,logrdata.PacketField.lng,
//                adc1_int,adc1_flt,adc2_int,adc2_flt,u8l_DI1,u8l_DI2,u8l_DI3,u8l_DI4,u8l_DI5,u8l_DI6,u8l_DI7,u8l_DI8,
//                adc3_int,adc3_flt,adc4_int,adc4_flt,adc5_int,adc5_flt,logrdata.PacketField.frq,
//                adc6_int,adc6_flt,smr_int,smr_flt,logrdata.PacketField.Endchar );
//            
//            sprintf(tempbuff,"%c%.10s,1N,%.6s%.6s,%c,%c%.9s,%c%.10s,%d.%d,%d.%d,%d,%d,%d,%d,%d,%d,%d,%d,%d.%d,%d.%d,%d.%d,%d,%d.%d,%d.%d%c"
//                ,logrdata.PacketField.Startchar,logrdata.PacketField.SLheader,
//                logrdata.PacketField.date,logrdata.PacketField.time,logrdata.PacketField.valid,
//                logrdata.PacketField.NSIndicator,logrdata.PacketField.lat,logrdata.PacketField.EWIndicator,logrdata.PacketField.lng,
//                adc1_int,adc1_flt,adc2_int,adc2_flt,u8l_DI1,u8l_DI2,u8l_DI3,u8l_DI4,u8l_DI5,u8l_DI6,u8l_DI7,u8l_DI8,
//                adc3_int,adc3_flt,adc4_int,adc4_flt,adc5_int,adc5_flt,logrdata.PacketField.frq,
//                adc6_int,adc6_flt,smr_int,smr_flt,logrdata.PacketField.Endchar );
            memset(tempbuff,0,sizeof(tempbuff));
            sprintf(tempbuff,"%c%.10s,1N,%.6s%.6s,%c,%c%.9s,%c%.10s,%.2f,%.2f,%d,%d,%d,%d,%d,%d,%d,%d,%.2f,%.2f,%.2f,%d,%.2f,%.2f%c"
            ,logrdata.PacketField.Startchar,logrdata.PacketField.SLheader,
            logrdata.PacketField.date,logrdata.PacketField.time,logrdata.PacketField.valid,
            logrdata.PacketField.NSIndicator,logrdata.PacketField.lat,logrdata.PacketField.EWIndicator,logrdata.PacketField.lng,
            logrdata.PacketField.adc1,logrdata.PacketField.adc2,u8l_DI1,u8l_DI2,u8l_DI3,u8l_DI4,u8l_DI5,u8l_DI6,u8l_DI7,u8l_DI8,
            logrdata.PacketField.adc3,logrdata.PacketField.adc4,logrdata.PacketField.adc5,logrdata.PacketField.frq,
            logrdata.PacketField.adc6,logrdata.PacketField.smr,logrdata.PacketField.Endchar );
//           sprintf(tempbuff,"%c%.10s,1N,%.6s%.6s,%c,%c%.9s,%c%.10s,%s,%s,%d,%d,%d,%d,%d,%d,%d,%d,%s,%s,%s,%d,%s,%s%c"
//            ,logrdata.PacketField.Startchar,logrdata.PacketField.SLheader,
//            logrdata.PacketField.date,logrdata.PacketField.time,logrdata.PacketField.valid,
//            logrdata.PacketField.NSIndicator,logrdata.PacketField.lat,logrdata.PacketField.EWIndicator,logrdata.PacketField.lng,
//            adc1buf,adc2buf,u8l_DI1,u8l_DI2,u8l_DI3,u8l_DI4,u8l_DI5,u8l_DI6,u8l_DI7,u8l_DI8,
//            adc3buf,adc4buf,adc5buf,logrdata.PacketField.frq,
//            adc6buf,smrbuf,logrdata.PacketField.Endchar ); 
            strcat(data,tempbuff);
//            printf("freshdatamemloc:%ld of data :%s\n\r",temp_i,tempbuff);
            }
        }
        printf("freshdatamemloc2:%ld No. data :%s\n\r",freshdatamemloc2.PacketField.memaddr,data);
        retval = true;
//    }
    return retval;
}
bool loadmemorydata(uint32_t startaddr,uint32_t endaddr,char * data)
{
//    packet logrdata;
//    rewrite ryet2sendmemloc;

    bool retval = false;
    uint8_t u8l_DI1,u8l_DI2,u8l_DI3,u8l_DI4,u8l_DI5,u8l_DI6,u8l_DI7,u8l_DI8;
    char tempbuff[1024] = {0};
    char adc1buf[10] = {0},adc2buf[10] = {0},adc3buf[10] = {0},adc4buf[10] = {0},adc5buf[10] = {0},adc6buf[10] = {0},smrbuf[10] = {0};
    

//    for(uint32_t temp_i = startaddr;(temp_i < endaddr)&&(temp_i< 50); temp_i++)
    for(uint32_t temp_i = startaddr;(temp_i < endaddr); temp_i++)
    {       
        logrdata.PacketField.frq = temp_i;//mem location for testing
        readlogdata(&logrdata.rcvpacket[0],85,temp_i);
//        if((logrdata.rcvpacket[0] > 100)&&(logrdata.rcvpacket[1] >100)&&(logrdata.rcvpacket[2] >100)&&(logrdata.rcvpacket[3] >100))
        if((logrdata.PacketField.Startchar == '&')&&(logrdata.PacketField.Endchar == '^'))
        {
            ftoa(logrdata.PacketField.adc1, adc1buf, 2); 
//        adc1_int = logrdata.PacketField.adc1;
//        adc1_flt = logrdata.PacketField.adc1 * 100.0;
//        adc1_flt = adc1_flt % 100;
            ftoa(logrdata.PacketField.adc2, adc2buf, 2); 
//        adc2_int = logrdata.PacketField.adc2;
//        adc2_flt = logrdata.PacketField.adc2 * 100.0;
//        adc2_flt = adc2_flt % 100;
            
        u8l_DI1 = ((logrdata.PacketField.digdata >>7) & 0x01);
        u8l_DI2 = ((logrdata.PacketField.digdata >> 6) & 0x01);
        u8l_DI3 = ((logrdata.PacketField.digdata >> 5) & 0x01);
        u8l_DI4 = ((logrdata.PacketField.digdata >> 4) & 0x01);
        u8l_DI5 = ((logrdata.PacketField.digdata >> 3) & 0x01);
        u8l_DI6 = ((logrdata.PacketField.digdata >> 2) & 0x01);
        u8l_DI7 = ((logrdata.PacketField.digdata >> 1) & 0x01);
        u8l_DI8 = (logrdata.PacketField.digdata & 0x01);
        
        ftoa(logrdata.PacketField.adc3, adc3buf, 2); 
//        adc3_int = logrdata.PacketField.adc3;
//        adc3_flt = logrdata.PacketField.adc3 * 100.0;
//        adc3_flt = adc3_flt % 100;
        ftoa(logrdata.PacketField.adc4, adc4buf, 2); 
//        adc4_int = logrdata.PacketField.adc4;
//        adc4_flt = logrdata.PacketField.adc4 * 100.0;
//        adc4_flt = adc4_flt % 100;
        ftoa(logrdata.PacketField.adc5, adc5buf, 2); 
//        adc5_int = logrdata.PacketField.adc5;
//        adc5_flt = logrdata.PacketField.adc5 * 100.0;
//        adc5_flt = adc5_flt % 100;
        ftoa(logrdata.PacketField.adc6, adc6buf, 2); 
//        adc6_int = logrdata.PacketField.adc6;
//        adc6_flt = logrdata.PacketField.adc6 * 100.0;
//        adc6_flt = adc6_flt % 100;
        ftoa(logrdata.PacketField.smr, smrbuf, 2); 
//        smr_int = logrdata.PacketField.smr;
//        smr_flt = logrdata.PacketField.smr * 100.0;
//        smr_flt = smr_flt % 100;
         
//        sprintf(tempbuff,"%c%s%.4d,2N,%.6s%.6s,%c,%c%.9s,%c%.10s,%d.%d,%d.%d,%d,%d,%d,%d,%d,%d,%d,%d,%d.%d,%d.%d,%d.%d,%d,%d.%d,%d.%d%c"
//                ,logrdata.PacketField.Startchar,logrdata.PacketField.SLheader,logrdata.PacketField.serialno,
//                logrdata.PacketField.date,logrdata.PacketField.time,logrdata.PacketField.valid,
//                logrdata.PacketField.NSIndicator,logrdata.PacketField.lat,logrdata.PacketField.EWIndicator,logrdata.PacketField.lng,
//                adc1_int,adc1_flt,adc2_int,adc2_flt,u8l_DI1,u8l_DI2,u8l_DI3,u8l_DI4,u8l_DI5,u8l_DI6,u8l_DI7,u8l_DI8,
//                adc3_int,adc3_flt,adc4_int,adc4_flt,adc5_int,adc5_flt,logrdata.PacketField.frq,
//                adc6_int,adc6_flt,smr_int,smr_flt,logrdata.PacketField.Endchar );

//        sprintf(tempbuff,"%c%.10s,2N,%.6s%.6s,%c,%c%.9s,%c%.10s,%d.%d,%d.%d,%d,%d,%d,%d,%d,%d,%d,%d,%d.%d,%d.%d,%d.%d,%d,%d.%d,%d.%d%c"
//                ,logrdata.PacketField.Startchar,logrdata.PacketField.SLheader,
//                logrdata.PacketField.date,logrdata.PacketField.time,logrdata.PacketField.valid,
//                logrdata.PacketField.NSIndicator,logrdata.PacketField.lat,logrdata.PacketField.EWIndicator,logrdata.PacketField.lng,
//                adc1_int,adc1_flt,adc2_int,adc2_flt,u8l_DI1,u8l_DI2,u8l_DI3,u8l_DI4,u8l_DI5,u8l_DI6,u8l_DI7,u8l_DI8,
//                adc3_int,adc3_flt,adc4_int,adc4_flt,adc5_int,adc5_flt,logrdata.PacketField.frq,
//                adc6_int,adc6_flt,smr_int,smr_flt,logrdata.PacketField.Endchar );
        memset(tempbuff,0,sizeof(tempbuff));
        sprintf(tempbuff,"%c%.10s,2N,%.6s%.6s,%c,%c%.9s,%c%.10s,%.2f,%.2f,%d,%d,%d,%d,%d,%d,%d,%d,%.2f,%.2f,%.2f,%d,%.2f,%.2f%c"
            ,logrdata.PacketField.Startchar,logrdata.PacketField.SLheader,
            logrdata.PacketField.date,logrdata.PacketField.time,logrdata.PacketField.valid,
            logrdata.PacketField.NSIndicator,logrdata.PacketField.lat,logrdata.PacketField.EWIndicator,logrdata.PacketField.lng,
            logrdata.PacketField.adc1,logrdata.PacketField.adc2,u8l_DI1,u8l_DI2,u8l_DI3,u8l_DI4,u8l_DI5,u8l_DI6,u8l_DI7,u8l_DI8,
            logrdata.PacketField.adc3,logrdata.PacketField.adc4,logrdata.PacketField.adc5,logrdata.PacketField.frq,
            logrdata.PacketField.adc6,logrdata.PacketField.smr,logrdata.PacketField.Endchar );
//        sprintf(tempbuff,"%c%.10s,2N,%.6s%.6s,%c,%c%.9s,%c%.10s,%s,%s,%d,%d,%d,%d,%d,%d,%d,%d,%s,%s,%s,%d,%s,%s%c"
//            ,logrdata.PacketField.Startchar,logrdata.PacketField.SLheader,
//            logrdata.PacketField.date,logrdata.PacketField.time,logrdata.PacketField.valid,
//            logrdata.PacketField.NSIndicator,logrdata.PacketField.lat,logrdata.PacketField.EWIndicator,logrdata.PacketField.lng,
//            adc1buf,adc2buf,u8l_DI1,u8l_DI2,u8l_DI3,u8l_DI4,u8l_DI5,u8l_DI6,u8l_DI7,u8l_DI8,
//            adc3buf,adc4buf,adc5buf,logrdata.PacketField.frq,
//            adc6buf,smrbuf,logrdata.PacketField.Endchar );
        strcat(data,tempbuff);
//        printf("startaddr:%ld,temp_i:%ld,data:%s\n\r",startaddr,temp_i,data);
        }
        retval= true;
    }
    
    printf("mem:%ld,data:%s\n\r",ryet2sendmemloc.PacketField.memaddr,data);
//    printf("rnewmemloc:%ld,ryet2sendmemloc:%ld\r\n",rnewmemloc.PacketField.memaddr,ryet2sendmemloc.PacketField.memaddr);
                    
    return retval;
}

void saveunsenddata1(uint8_t *data)
{
//    packet logrdata;
//    rewrite wnewmemloc,rnewmemloc,wyet2sendmemloc,ryet2sendmemloc,wmaxmemloc,rmaxmemloc,freshdatamemloc1;

    readnewmemloc(&rnewmemloc.addrbuf[0]);
    readyet2sendmemloc(&ryet2sendmemloc.addrbuf[0]);
    readmaxmemloc(&rmaxmemloc.addrbuf[0]);
    
    wnewmemloc.PacketField.memaddr = rnewmemloc.PacketField.memaddr;
    
    /******save unsend data */
    readfreshdatamemloc1(&freshdatamemloc1.addrbuf[0]);
    
//    for(uint32_t temp_i = 0;temp_i < NOOFDATAPERPACKET; temp_i++)
    for(uint32_t temp_i = 0;((temp_i < freshdatamemloc1.PacketField.memaddr)&&(temp_i<15)); temp_i++)
    {
        readfreshlogdata1(&logrdata.rcvpacket[0],85,temp_i);
        
        savelogdata(logrdata.rcvpacket,85,rnewmemloc.PacketField.memaddr);
    
        printf("saveunsenddata...rnewmemloc:%ld,wnewmemloc:%ld,ryet2sendmemloc:%ld\r\n",rnewmemloc.PacketField.memaddr,wnewmemloc.PacketField.memaddr,ryet2sendmemloc.PacketField.memaddr);
        rnewmemloc.PacketField.memaddr++;
    //    wnewmemloc.PacketField.memaddr = rnewmemloc.PacketField.memaddr;

        if(rnewmemloc.PacketField.memaddr >= MEM_LEN)
        {
            //save max memory location it is saved 
            rmaxmemloc.PacketField.memaddr = rnewmemloc.PacketField.memaddr;


            rnewmemloc.PacketField.memaddr = 0;
//            rnewmemloc.PacketField.flag = 1;
            flagbit.PacketField.memaddr = 1;
            saveFLAG(&flagbit.addrbuf[0]);

    //        wnewmemloc.PacketField.memaddr = rnewmemloc.PacketField.memaddr;
    //        wnewmemloc.PacketField.flag = rnewmemloc.PacketField.flag;
        }
    //    wnewmemloc.PacketField.memaddr = rnewmemloc.PacketField.memaddr;
    //    wnewmemloc.PacketField.flag = rnewmemloc.PacketField.flag;
    //    savenewmemloc(&wnewmemloc.addrbuf[0]);   
        /*******************************************************/
//        printf("\r\n rnewmemloc:%ld,\r\n ryet2sendmemloc:%ld,\r\n rnewmemloc.PacketField.flag:%d\r\nrmaxmemloc.PacketField.memaddr:%ld\r\n ",rnewmemloc.PacketField.memaddr,ryet2sendmemloc.PacketField.memaddr,rnewmemloc.PacketField.flag,rmaxmemloc.PacketField.memaddr);
        printf("\r\n rnewmemloc:%ld,\r\n ryet2sendmemloc:%ld,\r\n flagbit.PacketField.memaddr:%ld\r\nrmaxmemloc.PacketField.memaddr:%ld\r\n ",rnewmemloc.PacketField.memaddr,ryet2sendmemloc.PacketField.memaddr,flagbit.PacketField.memaddr,rmaxmemloc.PacketField.memaddr);
        
//        if(rnewmemloc.PacketField.flag == 0)
        if(flagbit.PacketField.memaddr == 0)
            printf("\r\nNo.of strings in the MEMORY :%ld,\r\n",(rnewmemloc.PacketField.memaddr-ryet2sendmemloc.PacketField.memaddr));
        else
            printf("\r\nNo.of strings in the MEMORY :%ld,\r\n",((rnewmemloc.PacketField.memaddr+MEM_LEN)-ryet2sendmemloc.PacketField.memaddr));
                
//        if(rnewmemloc.PacketField.flag == 1)
        if(flagbit.PacketField.memaddr == 1)
        {
            //new data and old data difference should be more than 1 sector = 4096 = 32 packets
            if((rnewmemloc.PacketField.memaddr + 34) > ryet2sendmemloc.PacketField.memaddr)
            {
                ryet2sendmemloc.PacketField.memaddr =  rnewmemloc.PacketField.memaddr + 34;

                if(ryet2sendmemloc.PacketField.memaddr >= MEM_LEN)//rmaxmemloc.PacketField.memaddr)//MEM_LEN)
                {
                    ryet2sendmemloc.PacketField.memaddr = 0;
//                    rnewmemloc.PacketField.flag = 0;
                    flagbit.PacketField.memaddr = 0;
                    saveFLAG(&flagbit.addrbuf[0]);
                }
//                printf("\r\n MEMORY FULL:\r\n rnewmemloc:%ld,\r\n ryet2sendmemloc:%ld,\r\n rnewmemloc.PacketField.flag:%d\r\n ",rnewmemloc.PacketField.memaddr,ryet2sendmemloc.PacketField.memaddr,rnewmemloc.PacketField.flag);
                printf("\r\n MEMORY FULL:\r\n rnewmemloc:%ld,\r\n ryet2sendmemloc:%ld,\r\n flagbit.PacketField.memaddr:%ld\r\n ",rnewmemloc.PacketField.memaddr,ryet2sendmemloc.PacketField.memaddr,flagbit.PacketField.memaddr);

    //            wyet2sendmemloc.PacketField.memaddr =  ryet2sendmemloc.PacketField.memaddr;
    //            saveyet2sendmemloc(&wyet2sendmemloc.addrbuf[0]);
            }
        }
//        rnewmemloc.PacketField.memaddr++;
    }
    wnewmemloc.PacketField.memaddr = rnewmemloc.PacketField.memaddr;
    wnewmemloc.PacketField.flag = rnewmemloc.PacketField.flag;
    savenewmemloc(&wnewmemloc.addrbuf[0]);  
    
    wyet2sendmemloc.PacketField.memaddr =  ryet2sendmemloc.PacketField.memaddr;
    saveyet2sendmemloc(&wyet2sendmemloc.addrbuf[0]);
    
    wmaxmemloc.PacketField.memaddr = rmaxmemloc.PacketField.memaddr;
    savemaxmemloc(&wmaxmemloc.addrbuf[0]);
    
    freshdatamemloc1.PacketField.memaddr = 0;
    savefreshdatamemloc1(&freshdatamemloc1.addrbuf[0]);
    
//    printf("\r\n MEMORY UPDATED TO:rnewmemloc:%ld,\r\n ryet2sendmemloc:%ld,\r\n rnewmemloc.PacketField.flag:%d\r\nrmaxmemloc.PacketField.memaddr:%ld\r\n ",rnewmemloc.PacketField.memaddr,ryet2sendmemloc.PacketField.memaddr,rnewmemloc.PacketField.flag,rmaxmemloc.PacketField.memaddr);
    printf("\r\n MEMORY UPDATED TO:rnewmemloc:%ld,\r\n ryet2sendmemloc:%ld,\r\n flagbit.PacketField.memaddr:%ld\r\nrmaxmemloc.PacketField.memaddr:%ld\r\n ",rnewmemloc.PacketField.memaddr,ryet2sendmemloc.PacketField.memaddr,flagbit.PacketField.memaddr,rmaxmemloc.PacketField.memaddr);

    /***************************************************/
}
void saveunsenddata2(uint8_t *data)
{
//    packet logrdata;
//    rewrite wnewmemloc,rnewmemloc,wyet2sendmemloc,ryet2sendmemloc,wmaxmemloc,rmaxmemloc,freshdatamemloc2;

    readnewmemloc(&rnewmemloc.addrbuf[0]);
    readyet2sendmemloc(&ryet2sendmemloc.addrbuf[0]);
    readmaxmemloc(&rmaxmemloc.addrbuf[0]);
    
    wnewmemloc.PacketField.memaddr = rnewmemloc.PacketField.memaddr;
    
    /******save unsend data */
    readfreshdatamemloc2(&freshdatamemloc2.addrbuf[0]);
    
//    for(uint32_t temp_i = 0;temp_i < NOOFDATAPERPACKET; temp_i++)
    for(uint32_t temp_i = 0;((temp_i < freshdatamemloc2.PacketField.memaddr)&&(temp_i<15)); temp_i++)
    {
        readfreshlogdata2(&logrdata.rcvpacket[0],85,temp_i);
        
        savelogdata(logrdata.rcvpacket,85,rnewmemloc.PacketField.memaddr);
    
        printf("saveunsenddata...rnewmemloc:%ld,wnewmemloc:%ld,ryet2sendmemloc:%ld\r\n",rnewmemloc.PacketField.memaddr,wnewmemloc.PacketField.memaddr,ryet2sendmemloc.PacketField.memaddr);
        rnewmemloc.PacketField.memaddr++;
    //    wnewmemloc.PacketField.memaddr = rnewmemloc.PacketField.memaddr;

        if(rnewmemloc.PacketField.memaddr >= MEM_LEN)
        {
            //save max memory location it is saved 
            rmaxmemloc.PacketField.memaddr = rnewmemloc.PacketField.memaddr;


            rnewmemloc.PacketField.memaddr = 0;
//            rnewmemloc.PacketField.flag = 1;
            flagbit.PacketField.memaddr = 1;
            saveFLAG(&flagbit.addrbuf[0]);

    //        wnewmemloc.PacketField.memaddr = rnewmemloc.PacketField.memaddr;
    //        wnewmemloc.PacketField.flag = rnewmemloc.PacketField.flag;
        }
    //    wnewmemloc.PacketField.memaddr = rnewmemloc.PacketField.memaddr;
    //    wnewmemloc.PacketField.flag = rnewmemloc.PacketField.flag;
    //    savenewmemloc(&wnewmemloc.addrbuf[0]);   
        /*******************************************************/
//        printf("\r\n rnewmemloc:%ld,\r\n ryet2sendmemloc:%ld,\r\n rnewmemloc.PacketField.flag:%d\r\nrmaxmemloc.PacketField.memaddr:%ld\r\n ",rnewmemloc.PacketField.memaddr,ryet2sendmemloc.PacketField.memaddr,rnewmemloc.PacketField.flag,rmaxmemloc.PacketField.memaddr);
        printf("\r\n rnewmemloc:%ld,\r\n ryet2sendmemloc:%ld,\r\n flagbit.PacketField.memaddr:%ld\r\nrmaxmemloc.PacketField.memaddr:%ld\r\n ",rnewmemloc.PacketField.memaddr,ryet2sendmemloc.PacketField.memaddr,flagbit.PacketField.memaddr,rmaxmemloc.PacketField.memaddr);
        
        
//        if(rnewmemloc.PacketField.flag == 0)
        if(flagbit.PacketField.memaddr == 0)    
            printf("\r\nNo.of strings in the MEMORY :%ld,\r\n",(rnewmemloc.PacketField.memaddr-ryet2sendmemloc.PacketField.memaddr));
        else
            printf("\r\nNo.of strings in the MEMORY :%ld,\r\n",((rnewmemloc.PacketField.memaddr+MEM_LEN)-ryet2sendmemloc.PacketField.memaddr));
                
        
//        if(rnewmemloc.PacketField.flag == 1)
        if(flagbit.PacketField.memaddr == 1)
        {
            //new data and old data difference should be more than 1 sector = 4096 = 32 packets
            if((rnewmemloc.PacketField.memaddr + 34) > ryet2sendmemloc.PacketField.memaddr)
            {
                ryet2sendmemloc.PacketField.memaddr =  rnewmemloc.PacketField.memaddr + 34;

                if(ryet2sendmemloc.PacketField.memaddr >= MEM_LEN)//rmaxmemloc.PacketField.memaddr)//MEM_LEN)
                {
                    ryet2sendmemloc.PacketField.memaddr = 0;
//                    rnewmemloc.PacketField.flag = 0;
                    flagbit.PacketField.memaddr = 0;
                    saveFLAG(&flagbit.addrbuf[0]);
                }
//                printf("\r\n MEMORY FULL:\r\n rnewmemloc:%ld,\r\n ryet2sendmemloc:%ld,\r\n rnewmemloc.PacketField.flag:%d\r\n ",rnewmemloc.PacketField.memaddr,ryet2sendmemloc.PacketField.memaddr,rnewmemloc.PacketField.flag);
                printf("\r\n MEMORY FULL:\r\n rnewmemloc:%ld,\r\n ryet2sendmemloc:%ld,\r\n flagbit.PacketField.memaddr:%ld\r\n ",rnewmemloc.PacketField.memaddr,ryet2sendmemloc.PacketField.memaddr,flagbit.PacketField.memaddr);

    //            wyet2sendmemloc.PacketField.memaddr =  ryet2sendmemloc.PacketField.memaddr;
    //            saveyet2sendmemloc(&wyet2sendmemloc.addrbuf[0]);
            }
        }
//        rnewmemloc.PacketField.memaddr++;
    }
    wnewmemloc.PacketField.memaddr = rnewmemloc.PacketField.memaddr;
    wnewmemloc.PacketField.flag = rnewmemloc.PacketField.flag;
    savenewmemloc(&wnewmemloc.addrbuf[0]);  
    
    wyet2sendmemloc.PacketField.memaddr =  ryet2sendmemloc.PacketField.memaddr;
    saveyet2sendmemloc(&wyet2sendmemloc.addrbuf[0]);
    
    wmaxmemloc.PacketField.memaddr = rmaxmemloc.PacketField.memaddr;
    savemaxmemloc(&wmaxmemloc.addrbuf[0]);
    
    freshdatamemloc2.PacketField.memaddr = 0;
    savefreshdatamemloc2(&freshdatamemloc2.addrbuf[0]);
    
//    printf("\r\n MEMORY UPDATED TO:rnewmemloc:%ld,\r\n ryet2sendmemloc:%ld,\r\n rnewmemloc.PacketField.flag:%d\r\nrmaxmemloc.PacketField.memaddr:%ld\r\n ",rnewmemloc.PacketField.memaddr,ryet2sendmemloc.PacketField.memaddr,rnewmemloc.PacketField.flag,rmaxmemloc.PacketField.memaddr);
    printf("\r\n MEMORY UPDATED TO:rnewmemloc:%ld,\r\n ryet2sendmemloc:%ld,\r\n flagbit.PacketField.memaddr:%ld\r\nrmaxmemloc.PacketField.memaddr:%ld\r\n ",rnewmemloc.PacketField.memaddr,ryet2sendmemloc.PacketField.memaddr,flagbit.PacketField.memaddr,rmaxmemloc.PacketField.memaddr);

    /***************************************************/
}
void savelogdata(uint8_t * data,unsigned long bufsize,unsigned long memloc)
{
    
	unsigned long adrss,vmhs_newsector;
//	char write_buf[256];
    uint8_t read_buf2[256];
//	noofbytspermin = 32;
	//adrss =  (((date-1)*23040)+((hours*60)+ min)*16) + (4096*10);//16 no's char
	
	//tempval = 60 * 24 * 32 ;//(min*hours*noofbytspermin)
	adrss = (4096*20) + (memloc*128); //(((date-1)*tempval)+((hours*60)+ min)*noofbytspermin) + (4096*10);//32 no's char
	
	
	vmhs_newsector = (adrss % 4096);
	
	if(vmhs_newsector == 0)
	{
		//erase new sector befor writing
		SPI_WREN();
		SPI_Sector_Erase(adrss);	//Do Sector Erase
		SPI_Wait_Busy();
		
		//memset(txbuff, 0x00, sizeof(txbuff));
//		printf("vmhs_newsector page_no: %ld\r\n", adrss);
		
		// Print to Console
		//io_write(debug_io, txbuff, strlen(txbuff));
//		delay_ms(1);
	}
	/***************/
	//befor saving the data we r going check data is erased befor or what if not erased it needs to erase

    memset(read_buf2, 0x00, 256);
	//SPI_HighSpeed_Read_Cont(adrss, 16, &read_buf[0]);//16char
	SPI_HighSpeed_Read_Cont(adrss, bufsize, &read_buf2[0]);//32char
	
	//printf("read_buf = %s,adrss=%d,vmhs_newsector=%d\r\n", read_buf,adrss,vmhs_newsector);
	uint8_t uchr_firstblkerras = 0;
	//for(i=0;i<16;i++)//16char
	for(uint8_t i=0;i<bufsize;i++)//32char
	{
		if(read_buf2[i] != 0xFF)
		{
			uchr_firstblkerras = 1;
//			printf("data: %s,read_buf[i]=%d,i=%d,uchr_firstblkerras=%d\r\n", read_buf2,read_buf2[i],i,uchr_firstblkerras);
			break;
		}
	}
	
	if(uchr_firstblkerras == 1)
	{
		//erase new sector befor writing
		uchr_firstblkerras = 0;
		SPI_WREN();
		SPI_Sector_Erase((adrss-vmhs_newsector));	//Do Sector Erase
		SPI_Wait_Busy();

//		printf("uchr_firstblkerras page_no: %ld,vmhs_newsector=%ld\r\n", adrss,vmhs_newsector);
//		delay_ms(1);	
	}
	/***************/
	//if(vmhs_adrss < temp_highest_address)
	{	SPI_WREN();
		//SPI_byte_Program(adrss, data,16);//16char
		SPI_byte_Program(adrss, data,bufsize);//32char
		SPI_Wait_Busy();
//		printf("saveddata: %s,adrss=%ld\r\n", data,adrss);
	}
}

void readlogdata(uint8_t * data,unsigned long bufsize,unsigned long memloc)
{
    unsigned long adrss;
	adrss = (4096*20)+(memloc*128);
    
    SPI_HighSpeed_Read_Cont(adrss, bufsize, &data[0]);
}

/*************Fresh log data memory activity*****************/
/*
 * data type          : memory location 
 * savefreshdatamemloc1 = 10
 * readfreshdatamemloc1 = 10
 * savefreshlogdata1    = 11
 * readfreshlogdata1    = 11
 * savefreshdatamemloc2 = 12
 * readfreshdatamemloc2 = 12
 * savefreshlogdata2    = 13
 * readfreshlogdata2    = 13
 *
 */


void savefreshdatamemloc1(uint8_t *data)
{
	unsigned long adrss;
    uint16_t uint_bufsize;
	adrss = (4096*10);
	/***erase new sector befor writing****/
	SPI_WREN();
	SPI_Sector_Erase(adrss);	//Do Sector Erase
	SPI_Wait_Busy();	
	uint_bufsize = 20;
//	while(data[uint_bufsize++] != 0)
//	{
//		//delay_ms(1);
//	}
//    printf("saveserialNo data: %s,uint_bufsize:%d\r\n", data,uint_bufsize);
	//if(vmhs_adrss < temp_highest_address)
	{	SPI_WREN();
		SPI_byte_Program(adrss, data,uint_bufsize-1);//SPI_Page_Program(vmhs_adrss, &write_buf[0]);
		SPI_Wait_Busy();
	}
}

void readfreshdatamemloc1(uint8_t *data)
{
	unsigned long adrss;
	uint8_t read_buf[256];
	// 1st sector for saving pages to get find out last save address so add first 256 bytes so page_no should >1	
	adrss = (4096*10);
	memset(read_buf, 0x00, 256);
//	if(adrss < 256)
//	{
		SPI_HighSpeed_Read_Cont(adrss, 20, &read_buf[0]);
//	}
	for(uint k=0;k<20;k++)
	{
//		if(read_buf[k] != 0xff)
//		{
			*data = read_buf[k];
			data++;
//		}
//		else
//		{
//			*data = 0;
////			break;	
//		}
	}	
}
void savefreshlogdata1(uint8_t * data,unsigned long bufsize,unsigned long memloc)
{
	unsigned long adrss,vmhs_newsector;
//	char write_buf[256];
    uint8_t read_buf2[256];
//	noofbytspermin = 32;
	//adrss =  (((date-1)*23040)+((hours*60)+ min)*16) + (4096*10);//16 no's char
	
	//tempval = 60 * 24 * 32 ;//(min*hours*noofbytspermin)
	adrss = (4096*11) + (memloc*128); //(((date-1)*tempval)+((hours*60)+ min)*noofbytspermin) + (4096*10);//32 no's char
	
	
	vmhs_newsector = (adrss % 4096);
	
	if(vmhs_newsector == 0)
	{
		//erase new sector befor writing
		SPI_WREN();
		SPI_Sector_Erase(adrss);	//Do Sector Erase
		SPI_Wait_Busy();
		
		//memset(txbuff, 0x00, sizeof(txbuff));
//		printf("vmhs_newsector page_no: %ld\r\n", adrss);
		
		// Print to Console
		//io_write(debug_io, txbuff, strlen(txbuff));
//		delay_ms(1);
	}
	/***************/
	//befor saving the data we r going check data is erased befor or what if not erased it needs to erase

    memset(read_buf2, 0x00, 256);
	//SPI_HighSpeed_Read_Cont(adrss, 16, &read_buf[0]);//16char
	SPI_HighSpeed_Read_Cont(adrss, bufsize, &read_buf2[0]);//32char
	
	//printf("read_buf = %s,adrss=%d,vmhs_newsector=%d\r\n", read_buf,adrss,vmhs_newsector);
	uint8_t uchr_firstblkerras = 0;
	//for(i=0;i<16;i++)//16char
	for(uint8_t i=0;i<bufsize;i++)//32char
	{
		if(read_buf2[i] != 0xFF)
		{
			uchr_firstblkerras = 1;
//			printf("data: %s,read_buf[i]=%d,i=%d,uchr_firstblkerras=%d\r\n", read_buf2,read_buf2[i],i,uchr_firstblkerras);
			break;
		}
	}
	
	if(uchr_firstblkerras == 1)
	{
		//erase new sector befor writing
		uchr_firstblkerras = 0;
		SPI_WREN();
		SPI_Sector_Erase((adrss-vmhs_newsector));	//Do Sector Erase
		SPI_Wait_Busy();

//		printf("uchr_firstblkerras page_no: %ld,vmhs_newsector=%ld\r\n", adrss,vmhs_newsector);
//		delay_ms(1);	
	}
	/***************/
	//if(vmhs_adrss < temp_highest_address)
	{	SPI_WREN();
		//SPI_byte_Program(adrss, data,16);//16char
		SPI_byte_Program(adrss, data,bufsize);//32char
		SPI_Wait_Busy();
//		printf("saveddata: %s,adrss=%ld\r\n", data,adrss);
	}
}
void readfreshlogdata1(uint8_t * data,unsigned long bufsize,unsigned long memloc)
{
    unsigned long adrss;
	adrss = (4096*11)+(memloc*128);
    
    SPI_HighSpeed_Read_Cont(adrss, bufsize, &data[0]);
}
/*************/
void savefreshdatamemloc2(uint8_t *data)
{
	unsigned long adrss;
    uint16_t uint_bufsize;
	adrss = (4096*12);
	/***erase new sector befor writing****/
	SPI_WREN();
	SPI_Sector_Erase(adrss);	//Do Sector Erase
	SPI_Wait_Busy();	
	uint_bufsize = 20;
//	while(data[uint_bufsize++] != 0)
//	{
//		//delay_ms(1);
//	}
//    printf("saveserialNo data: %s,uint_bufsize:%d\r\n", data,uint_bufsize);
	//if(vmhs_adrss < temp_highest_address)
	{	SPI_WREN();
		SPI_byte_Program(adrss, data,uint_bufsize-1);//SPI_Page_Program(vmhs_adrss, &write_buf[0]);
		SPI_Wait_Busy();
	}
}

void readfreshdatamemloc2(uint8_t *data)
{
	unsigned long adrss;
	uint8_t read_buf[256];
	// 1st sector for saving pages to get find out last save address so add first 256 bytes so page_no should >1	
	adrss = (4096*12);
	memset(read_buf, 0x00, 256);
//	if(adrss < 256)
//	{
		SPI_HighSpeed_Read_Cont(adrss, 20, &read_buf[0]);
//	}
	for(uint k=0;k<20;k++)
	{
//		if(read_buf[k] != 0xff)
//		{
			*data = read_buf[k];
			data++;
//		}
//		else
//		{
//			*data = 0;
////			break;	
//		}
	}	
}
void savefreshlogdata2(uint8_t * data,unsigned long bufsize,unsigned long memloc)
{
	unsigned long adrss,vmhs_newsector;
//	char write_buf[256];
    uint8_t read_buf2[256];
//	noofbytspermin = 32;
	//adrss =  (((date-1)*23040)+((hours*60)+ min)*16) + (4096*10);//16 no's char
	
	//tempval = 60 * 24 * 32 ;//(min*hours*noofbytspermin)
	adrss = (4096*13) + (memloc*128); //(((date-1)*tempval)+((hours*60)+ min)*noofbytspermin) + (4096*10);//32 no's char
	
	
	vmhs_newsector = (adrss % 4096);
	
	if(vmhs_newsector == 0)
	{
		//erase new sector befor writing
		SPI_WREN();
		SPI_Sector_Erase(adrss);	//Do Sector Erase
		SPI_Wait_Busy();
		
		//memset(txbuff, 0x00, sizeof(txbuff));
//		printf("vmhs_newsector page_no: %ld\r\n", adrss);
		
		// Print to Console
		//io_write(debug_io, txbuff, strlen(txbuff));
//		delay_ms(1);
	}
	/***************/
	//befor saving the data we r going check data is erased befor or what if not erased it needs to erase

    memset(read_buf2, 0x00, 256);
	//SPI_HighSpeed_Read_Cont(adrss, 16, &read_buf[0]);//16char
	SPI_HighSpeed_Read_Cont(adrss, bufsize, &read_buf2[0]);//32char
	
	//printf("read_buf = %s,adrss=%d,vmhs_newsector=%d\r\n", read_buf,adrss,vmhs_newsector);
	uint8_t uchr_firstblkerras = 0;
	//for(i=0;i<16;i++)//16char
	for(uint8_t i=0;i<bufsize;i++)//32char
	{
		if(read_buf2[i] != 0xFF)
		{
			uchr_firstblkerras = 1;
//			printf("data: %s,read_buf[i]=%d,i=%d,uchr_firstblkerras=%d\r\n", read_buf2,read_buf2[i],i,uchr_firstblkerras);
			break;
		}
	}
	
	if(uchr_firstblkerras == 1)
	{
		//erase new sector befor writing
		uchr_firstblkerras = 0;
		SPI_WREN();
		SPI_Sector_Erase((adrss-vmhs_newsector));	//Do Sector Erase
		SPI_Wait_Busy();

//		printf("uchr_firstblkerras page_no: %ld,vmhs_newsector=%ld\r\n", adrss,vmhs_newsector);
//		delay_ms(1);	
	}
	/***************/
	//if(vmhs_adrss < temp_highest_address)
	{	SPI_WREN();
		//SPI_byte_Program(adrss, data,16);//16char
		SPI_byte_Program(adrss, data,bufsize);//32char
		SPI_Wait_Busy();
//		printf("saveddata: %s,adrss=%ld\r\n", data,adrss);
	}
}
void readfreshlogdata2(uint8_t * data,unsigned long bufsize,unsigned long memloc)
{
    unsigned long adrss;
	adrss = (4096*13)+(memloc*128);
    
    SPI_HighSpeed_Read_Cont(adrss, bufsize, &data[0]);
}
/**********************************************/
void saveserialNo(uint8_t *data)
{
	unsigned long adrss;
    uint16_t uint_bufsize;
	adrss = (4096*0);
	/***erase new sector befor writing****/
	SPI_WREN();
	SPI_Sector_Erase(adrss);	//Do Sector Erase
	SPI_Wait_Busy();	
	uint_bufsize = 20;
	//if(vmhs_adrss < temp_highest_address)
	{	SPI_WREN();
		SPI_byte_Program(adrss, data,uint_bufsize-1);//SPI_Page_Program(vmhs_adrss, &write_buf[0]);
		SPI_Wait_Busy();
	}
}

void readserialNo(uint8_t *data)
{
	unsigned long adrss;
	uint8_t read_buf[256];
	// 1st sector for saving pages to get find out last save address so add first 256 bytes so page_no should >1	
	adrss = (4096*0);
	memset(read_buf, 0x00, 256);

    SPI_HighSpeed_Read_Cont(adrss, 20, &read_buf[0]);

	for(uint k=0;k<20;k++)
	{
        *data = read_buf[k];
        data++;
	}	
} 
void saveIPaddr(uint8_t *data)
{
	unsigned long adrss;
    uint16_t uint_bufsize;
	adrss = (4096*1);
	/***erase new sector befor writing****/
	SPI_WREN();
	SPI_Sector_Erase(adrss);	//Do Sector Erase
	SPI_Wait_Busy();	
	uint_bufsize = 20;
	//if(vmhs_adrss < temp_highest_address)
	{	SPI_WREN();
		SPI_byte_Program(adrss, data,uint_bufsize-1);//SPI_Page_Program(vmhs_adrss, &write_buf[0]);
		SPI_Wait_Busy();
	}
}

void readIPaddr(uint8_t *data)
{
	unsigned long adrss;
	uint8_t read_buf[256];
	// 1st sector for saving pages to get find out last save address so add first 256 bytes so page_no should >1	
	adrss = (4096*1);
	memset(read_buf, 0x00, 256);

    SPI_HighSpeed_Read_Cont(adrss, 20, &read_buf[0]);

	for(uint k=0;k<20;k++)
	{
        *data = read_buf[k];
        data++;
	}	
}
void saveAPNaddr(uint8_t *data)
{
	unsigned long adrss;
    uint16_t uint_bufsize;
	adrss = (4096*2);
	/***erase new sector befor writing****/
	SPI_WREN();
	SPI_Sector_Erase(adrss);	//Do Sector Erase
	SPI_Wait_Busy();	
	uint_bufsize = 20;
	//if(vmhs_adrss < temp_highest_address)
	{	SPI_WREN();
		SPI_byte_Program(adrss, data,uint_bufsize-1);//SPI_Page_Program(vmhs_adrss, &write_buf[0]);
		SPI_Wait_Busy();
	}
}

void readAPNaddr(uint8_t *data)
{
	unsigned long adrss;
	uint8_t read_buf[256];
	// 1st sector for saving pages to get find out last save address so add first 256 bytes so page_no should >1	
	adrss = (4096*2);
	memset(read_buf, 0x00, 256);

    SPI_HighSpeed_Read_Cont(adrss, 20, &read_buf[0]);

	for(uint k=0;k<20;k++)
	{
        *data = read_buf[k];
        data++;
	}	
}
void savesmr(uint8_t *data)
{
	unsigned long adrss;
    uint16_t uint_bufsize;
	adrss = (4096*4);
	/***erase new sector befor writing****/
	SPI_WREN();
	SPI_Sector_Erase(adrss);	//Do Sector Erase
	SPI_Wait_Busy();	
	uint_bufsize = 20;
//	while(data[uint_bufsize++] != 0)
//	{
//		//delay_ms(1);
//	}
//    printf("saveserialNo data: %s,uint_bufsize:%d\r\n", data,uint_bufsize);
	//if(vmhs_adrss < temp_highest_address)
	{	SPI_WREN();
		SPI_byte_Program(adrss, data,uint_bufsize-1);//SPI_Page_Program(vmhs_adrss, &write_buf[0]);
		SPI_Wait_Busy();
	}
}

void readsmr(uint8_t *data)
{
	unsigned long adrss;
	uint8_t read_buf[256];
	// 1st sector for saving pages to get find out last save address so add first 256 bytes so page_no should >1	
	adrss = (4096*4);
	memset(read_buf, 0x00, 256);
//	if(adrss < 256)
//	{
		SPI_HighSpeed_Read_Cont(adrss, 20, &read_buf[0]);
//	}
	for(uint k=0;k<20;k++)
	{
//		if(read_buf[k] != 0xff)
//		{
			*data = read_buf[k];
			data++;
//		}
//		else
//		{
//			*data = 0;
////			break;	
//		}
	}	
}
//5
void saveFLAG(uint8_t *data)
{
	unsigned long adrss;
    uint16_t uint_bufsize;
	adrss = (4096*5);
	/***erase new sector befor writing****/
	SPI_WREN();
	SPI_Sector_Erase(adrss);	//Do Sector Erase
	SPI_Wait_Busy();	
	uint_bufsize = 20;
//	while(data[uint_bufsize++] != 0)
//	{
//		//delay_ms(1);
//	}
//    printf("saveserialNo data: %s,uint_bufsize:%d\r\n", data,uint_bufsize);
	//if(vmhs_adrss < temp_highest_address)
	{	SPI_WREN();
		SPI_byte_Program(adrss, data,uint_bufsize-1);//SPI_Page_Program(vmhs_adrss, &write_buf[0]);
		SPI_Wait_Busy();
	}
}

void readFLAG(uint8_t *data)
{
	unsigned long adrss;
	uint8_t read_buf[256];
	// 1st sector for saving pages to get find out last save address so add first 256 bytes so page_no should >1	
	adrss = (4096*5);
	memset(read_buf, 0x00, 256);
//	if(adrss < 256)
//	{
		SPI_HighSpeed_Read_Cont(adrss, 20, &read_buf[0]);
//	}
	for(uint k=0;k<20;k++)
	{
//		if(read_buf[k] != 0xff)
//		{
			*data = read_buf[k];
			data++;
//		}
//		else
//		{
//			*data = 0;
////			break;	
//		}
	}	
}
void savemaxmemloc(uint8_t *data)
{
	unsigned long adrss;
    uint16_t uint_bufsize;
	adrss = (4096*6);
	/***erase new sector befor writing****/
	SPI_WREN();
	SPI_Sector_Erase(adrss);	//Do Sector Erase
	SPI_Wait_Busy();	
	uint_bufsize = 20;
//	while(data[uint_bufsize++] != 0)
//	{
//		//delay_ms(1);
//	}
//    printf("saveserialNo data: %s,uint_bufsize:%d\r\n", data,uint_bufsize);
	//if(vmhs_adrss < temp_highest_address)
	{	SPI_WREN();
		SPI_byte_Program(adrss, data,uint_bufsize-1);//SPI_Page_Program(vmhs_adrss, &write_buf[0]);
		SPI_Wait_Busy();
	}
}

void readmaxmemloc(uint8_t *data)
{
	unsigned long adrss;
	uint8_t read_buf[256];
	// 1st sector for saving pages to get find out last save address so add first 256 bytes so page_no should >1	
	adrss = (4096*6);
	memset(read_buf, 0x00, 256);
//	if(adrss < 256)
//	{
		SPI_HighSpeed_Read_Cont(adrss, 20, &read_buf[0]);
//	}
	for(uint k=0;k<20;k++)
	{
//		if(read_buf[k] != 0xff)
//		{
			*data = read_buf[k];
			data++;
//		}
//		else
//		{
//			*data = 0;
////			break;	
//		}
	}	
} 
void saverecomemloc(uint8_t *data)
{
	unsigned long adrss;
    uint16_t uint_bufsize;
	adrss = (4096*7);
	/***erase new sector befor writing****/
	SPI_WREN();
	SPI_Sector_Erase(adrss);	//Do Sector Erase
	SPI_Wait_Busy();	
	uint_bufsize = 20;
//	while(data[uint_bufsize++] != 0)
//	{
//		//delay_ms(1);
//	}
//    printf("saveserialNo data: %s,uint_bufsize:%d\r\n", data,uint_bufsize);
	//if(vmhs_adrss < temp_highest_address)
	{	SPI_WREN();
		SPI_byte_Program(adrss, data,uint_bufsize-1);//SPI_Page_Program(vmhs_adrss, &write_buf[0]);
		SPI_Wait_Busy();
	}
}

void readrecomemloc(uint8_t *data)
{
	unsigned long adrss;
	uint8_t read_buf[256];
	// 1st sector for saving pages to get find out last save address so add first 256 bytes so page_no should >1	
	adrss = (4096*7);
	memset(read_buf, 0x00, 256);
//	if(adrss < 256)
//	{
		SPI_HighSpeed_Read_Cont(adrss, 20, &read_buf[0]);
//	}
	for(uint k=0;k<20;k++)
	{
//		if(read_buf[k] != 0xff)
//		{
			*data = read_buf[k];
			data++;
//		}
//		else
//		{
//			*data = 0;
////			break;	
//		}
	}	
} 
void savenewmemloc(uint8_t *data)
{
	unsigned long adrss;
    uint16_t uint_bufsize;
	adrss = (4096*8);
	/***erase new sector befor writing****/
	SPI_WREN();
	SPI_Sector_Erase(adrss);	//Do Sector Erase
	SPI_Wait_Busy();	
	uint_bufsize = 20;
//	while(data[uint_bufsize++] != 0)
//	{
//		//delay_ms(1);
//	}
//    printf("saveserialNo data: %s,uint_bufsize:%d\r\n", data,uint_bufsize);
	//if(vmhs_adrss < temp_highest_address)
	{	SPI_WREN();
		SPI_byte_Program(adrss, data,uint_bufsize-1);//SPI_Page_Program(vmhs_adrss, &write_buf[0]);
		SPI_Wait_Busy();
	}
}

void readnewmemloc(uint8_t *data)
{
	unsigned long adrss;
	uint8_t read_buf[256];
	// 1st sector for saving pages to get find out last save address so add first 256 bytes so page_no should >1	
	adrss = (4096*8);
	memset(read_buf, 0x00, 256);
//	if(adrss < 256)
//	{
		SPI_HighSpeed_Read_Cont(adrss, 20, &read_buf[0]);
//	}
	for(uint k=0;k<20;k++)
	{
//		if(read_buf[k] != 0xff)
//		{
			*data = read_buf[k];
			data++;
//		}
//		else
//		{
//			*data = 0;
////			break;	
//		}
	}	
} 
void saveyet2sendmemloc(uint8_t *data)
{
	unsigned long adrss;
    uint16_t uint_bufsize;
	adrss = (4096*9);
	/***erase new sector befor writing****/
	SPI_WREN();
	SPI_Sector_Erase(adrss);	//Do Sector Erase
	SPI_Wait_Busy();	
	uint_bufsize = 20;
//	while(data[uint_bufsize++] != 0)
//	{
//		//delay_ms(1);
//	}
//    printf("saveserialNo data: %s,uint_bufsize:%d\r\n", data,uint_bufsize);
	//if(vmhs_adrss < temp_highest_address)
	{	SPI_WREN();
		SPI_byte_Program(adrss, data,uint_bufsize-1);//SPI_Page_Program(vmhs_adrss, &write_buf[0]);
		SPI_Wait_Busy();
	}
}

void readyet2sendmemloc(uint8_t *data)
{
	unsigned long adrss;
	uint8_t read_buf[256];
	// 1st sector for saving pages to get find out last save address so add first 256 bytes so page_no should >1	
	adrss = (4096*9);
	memset(read_buf, 0x00, 256);
//	if(adrss < 256)
//	{
		SPI_HighSpeed_Read_Cont(adrss, 20, &read_buf[0]);
//	}
	for(uint k=0;k<20;k++)
	{
//		if(read_buf[k] != 0xff)
//		{
			*data = read_buf[k];
			data++;
//		}
//		else
//		{
//			*data = 0;
////			break;	
//		}
	}	
} 
 
/*******************************************************************************
 End of File
 */
