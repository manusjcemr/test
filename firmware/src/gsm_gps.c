/****************************************************************************
* Title                 :   GSM GPS App
* Filename              :   gsm_gps.c
* Author                :   MSV
* Origin Date           :   10/03/2016
* Notes                 :   None
*****************************************************************************/
/**************************CHANGE LIST **************************************
*
*    Date    Software Version    Initials   Description
*  10/03/16        1.0.0           MSV      App Created.
*  15/02/18        2.0.0           ST       App Customized. 
*  01/01/2020      3.0.0           MK       Custom Application
*****************************************************************************/
/****************************************************************************
* Note: In version 3.00, This file has been modified by MK to meet the custom 
* application requirements. Should you need to contact the modifier, Write an 
* Email to mohan.kumar@microchip.com or alternatively, write to 
* Mohan Kumar, Microchip Technology India Pvt Ltd
* Plot No. 1498, EPIP, 1st Phase Industrial Area, Whitefield, Bengaluru, 
* Karnataka 560066
* Note: In version 2.00, This file has been modified by ST to meet the custom 
* application requirements. Should you need to contact the modifier, Write an 
* Email to syed.thaseemuddin@microchip.com or alternatively, write to 
* Syed Thaseemuddin, Microchip Technology India Pvt Ltd
* Plot No. 1498, EPIP, 1st Phase Industrial Area, Whitefield, Bengaluru, 
* Karnataka 560066
*******************************************************************************/
/**
 * @file gsm_gps.c
 * @brief GSM GPS App
 */
/*******************************************************************************
 Copyright (C) 2017  Microchip Technology Incorporated and its subsidiaries.

This program is free software; you can redistribute it and/or modify it under 
the terms of the GNU General Public License as published by the Free Software 
Foundation; either version 2 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY 
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A 
PARTICULAR PURPOSE.  See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with 
this program; if not, write to the Free Software Foundation, Inc., 
51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*******************************************************************************/

/******************************************************************************
* Includes
*******************************************************************************/
#include "gsm_gps.h"
#include "app.h"
#include "app2.h"
#include "app3.h"
#include "config.h"
/******************************************************************************
* Module Preprocessor Constants
*******************************************************************************/

/******************************************************************************
* Module Preprocessor Macros
*******************************************************************************/
#define M_CMD_MSG_HEADER        ("AT+CMGS=")
#define M_CRLF                  ("\r\n")
#define M_CR                    ("\r")
#define M_QUOTES                ("\"")
#define M_CMD_MSG_END           (26)
// The Mobile Phone number to which the SMS would be sent
#define M_MOBILE_NUMBER         "+918123264628"//"+918884277728"////"+919742873519"//

/******************************************************************************
* Module Typedefs
*******************************************************************************/

/******************************************************************************
* Module Variable Definitions
*******************************************************************************/
extern APP_DATA appData;
/* Flags
 ******************************************************************************/
bool req_pend_f = false;
bool loc_update_f = false;
static bool ring_f = false;
static long latt = -1;
static long lonn = -1;
static long altt = -1;        
static char latitude[ 10 ] = { 0 };
static char longitude[ 10 ] = { 0 };
static char altitude[ 9 ] = { 0 };
static char tmp_num[ 20 ];
extern uint8_t nvm_user_start_address[NVMCTRL_FLASH_ROWSIZE];
volatile uint8_t    u8_atcmd_status;
char finaltxbuff[ 1024 ] = "&V000001,001001,101,0102211345,N1305.1572,E07733.3395,27.8,97.3,99.9,13.9,200000,01.2,12.2,07.2,255,000.0,000.0,000.0,000.0^";
extern bool b_IgnitionON;
extern bool b_Airfilterclog;
extern bool  b_Hydraulicoillevel;
extern bool b_EngineCoolantTemperature;
extern bool b_EngineON;
extern bool b_LubeOilPressure;
extern bool b_Hydraulicoilfilterclog;
extern bool b_SeatbeltWarning;
extern uint16_t uint_frq;
uint16_t uint_datasentcount = 0;
uint32_t u32_tempdiffaddr=0;
extern uint8_t newdataEN1,newdataEN2,u8_newdataset1,u8_newdataset2;
uint32_t tempstartaddr = 0,tempendaddr = 0;
extern uint8_t u8_gerrercode2;
uint8_t u8_datasendEN = 0;
uint8_t u8_SSid=0;
uint8_t onlinemode = 0;
static uint8_t onlinemodecnt = 0;
volatile uint8_t u8_SSid1error=0,u8_SSid2error=0,u8_SSid3error=0,u8_SSid4error=0,u8_SSid5error=0,u8_SSid6error=0;
extern uint8_t u8_SAVING2MEM;    

/******************************************************************************
* Function Prototypes
*******************************************************************************/

/******************************************************************************
* Private Function Definitions
*******************************************************************************/

/******************************************************************************
* Public Function Definitions
*******************************************************************************/
void gsm_gps_init (void)
{
    
    
    engine_init( gsm_gps_evn_default );
    at_cmd_save( "+CGNSINF", 20000, NULL, NULL, NULL, gps_evn_location );
//    //gps_act_pwr_control( true ); 
//    GSM_RST_PA05_Set();
//    SYSTICK_DelayMs(1000);
//    GSM_RST_PA05_Clear();
//    SYSTICK_DelayMs(1000);
//    SYSTICK_DelayMs(1000);
    SYSTICK_DelayMs(1000);
////    at_cmd( "AT+CGNSINF" );
//    at_cmd( "ATE0" );
//    at_cmd( "AT+CSCS=\"GSM\"" );
//    at_cmd( "AT+CMGF=1" );
//    at_cmd( "AT#SCFG=?" );
    
    //MYCODE2
    u8_atcmd_status = AT_NON;
    if(myat_cmd("AT",200000) == 1);//wait resppose for 200sec at_cmd( "ATE0" );
    while(!u8_atcmd_status);
    if(u8_atcmd_status != AT_OK)//error
    {
        u8_atcmd_status = AT_ERROR2;
        //goto cmd_terminat; 
        GSM_RST_PA05_Set();
        SYSTICK_DelayMs(30);
        GSM_RST_PA05_Clear();
        SYSTICK_DelayMs(10000);
    }
    u8_atcmd_status = AT_NON;
    if(myat_cmd("ATE0",10000) == 1);//at_cmd( "ATE0" );
    while(!u8_atcmd_status);
    if(u8_atcmd_status != AT_OK)//error
    {
        u8_atcmd_status = AT_ERROR2;
        //goto cmd_terminat;  
    }
    
    u8_atcmd_status = AT_NON;
    if(myat_cmd("AT&K0",10000) == 1);//at_cmd( "ATE0" );
    while(!u8_atcmd_status);
    if(u8_atcmd_status != AT_OK)//error
    {
        u8_atcmd_status = AT_ERROR2;
        //goto cmd_terminat;  
    }
    
//    u8_atcmd_status = AT_NON;
//    if(myat_cmd("AT+IPR?",10000) == 1);//at_cmd( "ATE0" );
//    while(!u8_atcmd_status);
//    if(u8_atcmd_status != AT_OK)//error
//    {
//        u8_atcmd_status = AT_ERROR2;
//        //goto cmd_terminat;  
//    }
    //DTE-Modem Character Framing ,3 - 8 Data, 1 Stop
    u8_atcmd_status = AT_NON;
    if(myat_cmd("AT+ICF=3",10000) == 1);//at_cmd( "ATE0" );
    while(!u8_atcmd_status);
    if(u8_atcmd_status != AT_OK)//error
    {
        u8_atcmd_status = AT_ERROR2;
        //goto cmd_terminat;  
    }
    u8_atcmd_status = AT_NON;
    if(myat_cmd("AT+IPR=57600",10000) == 1);//at_cmd( "ATE0" );
    while(!u8_atcmd_status);
    if(u8_atcmd_status != AT_OK)//error
    {
        u8_atcmd_status = AT_ERROR2;
        //goto cmd_terminat;  
    }
    //Checking the software version
    u8_atcmd_status = AT_NON;
    if(myat_cmd("AT+CGMR",10000) == 1);//at_cmd( "ATE0" );
    while(!u8_atcmd_status);
    if(u8_atcmd_status != AT_OK)//error
    {
        u8_atcmd_status = AT_ERROR2;
        //goto cmd_terminat;  
    }

    //Checking the module identification
    u8_atcmd_status = AT_NON;
    if(myat_cmd("AT+CGMM",10000) == 1);//at_cmd( "ATE0" );
    while(!u8_atcmd_status);
    if(u8_atcmd_status != AT_OK)//error
    {
        u8_atcmd_status = AT_ERROR2;
        //goto cmd_terminat;  
    }

    //SYSTICK_DelayMs(10000);
    u8_atcmd_status = AT_NON;
    if(myat_cmd("AT+CSCS=\"GSM\"",10000) == 1);//at_cmd( "ATE0" );
    while(!u8_atcmd_status);
    if(u8_atcmd_status != AT_OK)//error
    {
        u8_atcmd_status = AT_ERROR2;
        //goto cmd_terminat;  
    }
    u8_atcmd_status = AT_NON;
    if(myat_cmd("AT+CMGF=1",10000) == 1);//at_cmd( "ATE0" );
    while(!u8_atcmd_status);
    if(u8_atcmd_status != AT_OK)//error
    {
        u8_atcmd_status = AT_ERROR2;
        //goto cmd_terminat;  
    }
    
    u8_atcmd_status = AT_NON;
    if(myat_cmd("AT#SCFG=1,1,1500,0,600,50",10000) == 1);//at_cmd( "ATE0" );
    while(!u8_atcmd_status);
    if(u8_atcmd_status != AT_OK)//error
    {
        u8_atcmd_status = AT_ERROR2;
        //goto cmd_terminat;  
    }
//    
//    u8_atcmd_status = AT_NON;
//    if(myat_cmd("AT#SCFGEXT2?",10000) == 1);//at_cmd( "ATE0" );
//    while(!u8_atcmd_status);
//    if(u8_atcmd_status != AT_OK)//error
//    {
//        u8_atcmd_status = AT_ERROR2;
//        //goto cmd_terminat;  
//    }
//    
    u8_atcmd_status = AT_NON;
    if(myat_cmd("AT#SCFGEXT2=1,0,0,0,0,2",10000) == 1);//at_cmd( "ATE0" );
    while(!u8_atcmd_status);
    if(u8_atcmd_status != AT_OK)//error
    {
        u8_atcmd_status = AT_ERROR2;
        //goto cmd_terminat;  
    }

    u8_atcmd_status = AT_NON;
    if(myat_cmd("AT+CMEE=2",10000) == 1);//at_cmd("AT+CMEE=2");// Execution command sends to the network a message
    while(!u8_atcmd_status);
    if(u8_atcmd_status != AT_OK)//error
    {
        u8_atcmd_status = AT_ERROR2;
//        goto cmd_terminat; 
        
    }
    
    u8_atcmd_status = AT_NON;
    if(myat_cmd("AT+CPIN?",10000) == 1);//sim insert check
    while(!u8_atcmd_status);
    if(u8_atcmd_status != AT_OK)//error
    {
        u8_atcmd_status = AT_ERROR2;
//        u8_gerrercode2 = 1;
//        goto cmd_terminat;
    }
    else
    {
//        u8_gerrercode2 = 0; 
    }
    u8_atcmd_status = AT_NON;
    if(myat_cmd("AT+CNUM",10000) == 1);//sim insert check
    while(!u8_atcmd_status);
    if(u8_atcmd_status != AT_OK)//error
    {
        u8_atcmd_status = AT_ERROR2;
//        u8_gerrercode2 = 1;
//        goto cmd_terminat;
    }
    
}

void gsm_gps_evn_default (char *response)
{
}

void gsm_ev_ring (char *response)
{
    ring_f = true;
}


void gsm_evn_call_id (char *response)
{
    char *tmp_s = strchr( response, '\"' );
    char *tmp_e = strchr( tmp_s + 1, '\"' );

    strncpy( tmp_num, tmp_s , tmp_e - tmp_s + 1 );
   
}

void gsm_act_read_info (void)
{
    char tmp[ 60 ] = { 0 };    
    strcpy( tmp, "AT+CMGR=" );
    strcat( tmp, M_MOBILE_NUMBER );
    at_cmd( tmp ); 
}

//void gsm_act_send_info (void)
//{
////    char phn_num_updt_flg; 
////    char phn_num1[20];
//    
//    char tmp[ 60 ] = { 0 };
//    char msg[ 700 ] = { 0 };
//    uint16_t n=0;
//    //MYCODE1
//    at_cmd( "ATE0" );
//    at_cmd( "ATE0" );
//    at_cmd( "AT+GMI" );
//    at_cmd("AT+CREG=0,1");
//    at_cmd("AT+CMGF=1");//Set SMS for Text format
//    at_cmd("AT+CSMP=17,167,2,0");// SSet the parameters for an outgoing message with 24 hours of validity period and default properties:
//    at_cmd("AT+CSCS=\"GSM\"");//?GSM? - GSM default alphabet (3GPP TS 23.038)
//    //END1
//    
//    
//    strcpy( tmp, "AT+CMGS=" );
//    strcat( tmp, M_QUOTES );     
//    strcat( tmp, M_MOBILE_NUMBER );
//    strcat(tmp,M_QUOTES);    
//    strcat(tmp,M_CR);      
//
//    strcpy( latitude, "13.085675" );
//    strcpy( longitude, "77.55531667" );
//    
//    strcpy( msg, "Testing\r\n" );
//    strcat( msg, "location: \r\n" );
//    strcat( msg, "Latitude : " );
//    strcat( msg, latitude );
//    strcat( msg, "\r\nLongitude : " );
//    strcat( msg, longitude );
//    strcat(msg, "\r\nhttps://maps.google.com/maps?q=");
//    strcat( msg, latitude );
//    strcat(msg, ",");
//    strcat( msg, longitude );
//
//    n = strlen(msg);
//    msg[n-1]=26;
//    at_cmd( tmp );
//    SYSTICK_DelayMs(10);
//    at_cmd_addition( msg );
//    
//   
//}
//void gsm_act_sendiot_info (void)
//{
//    char msg[ 700 ] = { 0 };
//    uint16_t n=0;
//    static int count = 0;
//        //MYCODE2
//    u8_atcmd_status = AT_NON;
//    if(myat_cmd("ATE0",1000) == 1);//at_cmd( "ATE0" );
//    while(!u8_atcmd_status);
//    if(u8_atcmd_status != AT_OK)//error
//    {
//        goto cmd_terminat;
//        u8_atcmd_status = AT_ERROR2;
//    }
//    
//    u8_atcmd_status = AT_NON;
//    at_cmd( "AT+CSQ" );
//    while(!u8_atcmd_status);
//    if(u8_atcmd_status == AT_ERROR)//error
//    {
//        goto cmd_terminat; 
//        u8_atcmd_status = AT_ERROR2;
//    }
//    
//    u8_atcmd_status = AT_NON;
//    at_cmd( "AT+CMGF=1" );
//    while(!u8_atcmd_status);
//    if(u8_atcmd_status != AT_OK)//error
//    {
//        goto cmd_terminat; 
//        u8_atcmd_status = AT_ERROR2;
//    }
//    
//    u8_atcmd_status = AT_NON;
//    at_cmd("AT+CNMI=2,1,0,0,0");
//    while(!u8_atcmd_status);
//    if(u8_atcmd_status != AT_OK)//error
//    {
//        goto cmd_terminat; 
//        u8_atcmd_status = AT_ERROR2;
//    }
//    
//    u8_atcmd_status = AT_NON;
//    at_cmd("AT+CMGD=1,4");//Set SMS for Text format
//    while(!u8_atcmd_status);
//    if(u8_atcmd_status != AT_OK)//error
//    {
//        goto cmd_terminat; 
//        u8_atcmd_status = AT_ERROR2;
//    }
//    
//    u8_atcmd_status = AT_NON;
//    at_cmd("AT+CGSN");// SSet the parameters for an outgoing message with 24 hours of validity period and default properties:
//    while(!u8_atcmd_status);
//    if(u8_atcmd_status != AT_OK)//error
//    {
//        goto cmd_terminat; 
//        u8_atcmd_status = AT_ERROR2;
//    } 
//    
//    u8_atcmd_status = AT_NON;
//    at_cmd("AT+CGDCONT=1,\"IP\",\"airtelgprs.com\",\"0.0.0.0\",0,0");//Define PDP context:
//    while(!u8_atcmd_status);
//    if(u8_atcmd_status != AT_OK)//error
//    {
//        goto cmd_terminat; 
//        u8_atcmd_status = AT_ERROR2;
//    } 
//    
//    u8_atcmd_status = AT_NON;
//    at_cmd("AT+CMEE=2");// Execution command sends to the network a message
//    while(!u8_atcmd_status);
//    if(u8_atcmd_status != AT_OK)//error
//    {
//        goto cmd_terminat; 
//        u8_atcmd_status = AT_ERROR2;
//    } 
//    
//    u8_atcmd_status = AT_NON;
//    at_cmd("AT+CGACT=1,1");                   // 
//    while(!u8_atcmd_status);
//    if(u8_atcmd_status != AT_OK)//error
//    {
//        goto cmd_terminat; 
//        u8_atcmd_status = AT_ERROR2;
//    } 
//    
//    u8_atcmd_status = AT_NON;
//    at_cmd("AT+CGPADDR=1");                   //    
//    while(!u8_atcmd_status);
//    if(u8_atcmd_status != AT_OK)//error
//    {
//        goto cmd_terminat; 
//        u8_atcmd_status = AT_ERROR2;
//    }
//    
//    u8_atcmd_status = AT_NON;
//    at_cmd("AT#SGACT=1,1");//Context Activation, as response gives IP of the module:
//    while(!u8_atcmd_status);
//    if(u8_atcmd_status == AT_ERROR)//error
//    {
//        goto cmd_terminat; 
//        u8_atcmd_status = AT_ERROR2;
//    } 
//    
//    u8_atcmd_status = AT_NON;
//    at_cmd("AT+CREG?");                   //
//    while(!u8_atcmd_status);
//    if(u8_atcmd_status != AT_OK)//error
//    {
//        goto cmd_terminat; 
//        u8_atcmd_status = AT_ERROR2;
//    }
//    
//    u8_atcmd_status = AT_NON;
//    at_cmd("AT#SS");//Checking the socket status with #SS
//    while(!u8_atcmd_status);
//    if(u8_atcmd_status != AT_OK)//error
//    {
//        goto cmd_terminat; 
//        u8_atcmd_status = AT_ERROR2;
//    }
//    
//    u8_atcmd_status = AT_NON;
//    at_cmd("AT#SD=2,0,1011,\"49.206.26.81\",0,0,1");//Opening a socket connection in command mode
//    //SYSTICK_DelayMs(1000);
//    while(!u8_atcmd_status);
//    if(u8_atcmd_status == AT_ERROR)//error
//    {
//        goto cmd_terminat; 
//        u8_atcmd_status = AT_ERROR2;
//    } 
////    SYSTICK_DelayMs(2000);
////    SYSTICK_DelayMs(2000);
//    
//    u8_atcmd_status = AT_NON;
//    at_cmd("AT#SSEND=2");                   // sms text
//    //SYSTICK_DelayMs(1000);
//    while(!u8_atcmd_status);
//    if(u8_atcmd_status == AT_ERROR)//error
//    {
//        goto cmd_terminat; 
//        u8_atcmd_status = AT_ERROR2;
//    } 
////    SYSTICK_DelayMs(1000);
//    
//    u8_atcmd_status = AT_NON;
//    sprintf(msg,"d1-%d:&V000001,001001,101,0102211345,N1305.1572,E07733.3395,27.8,97.3,99.9,13.9,200000,01.2,12.2,07.2,255,000.0,000.0,000.0,000.0^",count);
////    strcpy( msg, "&V000001,001001,101,0102211345,N1305.1572,E07733.3395,27.8,97.3,99.9,13.9,200000,01.2,12.2,07.2,255,000.0,000.0,000.0,000.0^");
//    //strcat( msg, "this is the testing messages... \r\n" );
//    n = strlen(msg);
//    msg[n]=26;//msg[n-1]=26;
//    at_cmd_addition( msg ); 
//    while(!u8_atcmd_status);
//    if(u8_atcmd_status == AT_ERROR)//error
//    {
//        goto cmd_terminat; 
//        u8_atcmd_status = AT_ERROR2;
//    } 
//    
////    SYSTICK_DelayMs(1000);
//    
//    
//    cmd_terminat: 
//    {
//        if(u8_atcmd_status == AT_ERROR2)
//        {
//            printf("cmd_terminat:timedouted so gsm initializing..\r\n");
////            GSM_RST_PA05_Set();
////            SYSTICK_DelayMs(300);
////            GSM_RST_PA05_Clear();
////            SYSTICK_DelayMs(1000);
//        }
//        
//        else
//        {
//            count++;
//        }
//            
//    }
//     SYSTICK_DelayMs(200);   
//}
/*void mygsm_act_sendiot_info (void)
{
    char msg[ 2024 ] = { 0 };
    uint16_t n=0;
//    static int count = 0;
    uint16_t tempdata;
    char Slnobuff[ 10 ] = { 0 },Memtypebuff[ 3 ] = { 0 },datetimebuff[ 20 ] = { 0 },chr_locvalidbuff = 'V';
    char Latbuff[ 20 ] = { 0 },logbuff[ 20 ] = { 0 };
    float flt_Adc1 =0,flt_Adc2 =0,flt_Adc3 =0,flt_Adc4 =0,flt_Adc5 =0,flt_Adc7 =0,flt_Smr =0;
    uint8_t u8_DI1=0,u8_DI2=0,u8_DI3=0,u8_DI4=0,u8_DI5=0,u8_DI6=0,u8_DI7=0,u8_DI8=0;
    uint16_t u16_Adc6=0;
    
        //MYCODE2
    u8_atcmd_status = AT_NON;
    if(myat_cmd("ATE0",1000) == 1);//at_cmd( "ATE0" );
    while(!u8_atcmd_status);
    if(u8_atcmd_status != AT_OK)//error
    {
        u8_atcmd_status = AT_ERROR2;
        goto cmd_terminat;
        
    }
    
    u8_atcmd_status = AT_NON;
    if(myat_cmd("AT+CSQ",1000) == 1);//at_cmd( "AT+CSQ" );
    while(!u8_atcmd_status);
    if(u8_atcmd_status == AT_ERROR)//error
    {
        u8_atcmd_status = AT_ERROR2;
        goto cmd_terminat; 
        
    }
    
    u8_atcmd_status = AT_NON;
    if(myat_cmd("AT+CMGF=1",1000) == 1);//at_cmd( "AT+CMGF=1" );
    while(!u8_atcmd_status);
    if(u8_atcmd_status != AT_OK)//error
    {
        u8_atcmd_status = AT_ERROR2;
        goto cmd_terminat; 
        
    }
    
    u8_atcmd_status = AT_NON;
    if(myat_cmd("AT+CNMI=2,1,0,0,0",1000) == 1);//at_cmd("AT+CNMI=2,1,0,0,0");
    while(!u8_atcmd_status);
    if(u8_atcmd_status != AT_OK)//error
    {
        u8_atcmd_status = AT_ERROR2;
        goto cmd_terminat; 
        
    }
    
    u8_atcmd_status = AT_NON;
    if(myat_cmd("AT+CMGD=1,4",1000) == 1);//at_cmd("AT+CMGD=1,4");//Set SMS for Text format
    while(!u8_atcmd_status);
    if(u8_atcmd_status != AT_OK)//error
    {
        u8_atcmd_status = AT_ERROR2;
        goto cmd_terminat; 
        
    }
    
    u8_atcmd_status = AT_NON;
    if(myat_cmd("AT+CGSN",1000) == 1);//at_cmd("AT+CGSN");// SSet the parameters for an outgoing message with 24 hours of validity period and default properties:
    while(!u8_atcmd_status);
    if(u8_atcmd_status != AT_OK)//error
    {
        u8_atcmd_status = AT_ERROR2;
        goto cmd_terminat; 
        
    } 
    
    u8_atcmd_status = AT_NON;
    if(myat_cmd("AT+CGDCONT=1,\"IP\",\"airtelgprs.com\",\"0.0.0.0\",0,0",1000) == 1);//at_cmd("AT+CGDCONT=1,\"IP\",\"airtelgprs.com\",\"0.0.0.0\",0,0");//Define PDP context:
    while(!u8_atcmd_status);
    if(u8_atcmd_status != AT_OK)//error
    {
        u8_atcmd_status = AT_ERROR2;
        goto cmd_terminat; 
        
    } 
    
    u8_atcmd_status = AT_NON;
    if(myat_cmd("AT+CMEE=2",1000) == 1);//at_cmd("AT+CMEE=2");// Execution command sends to the network a message
    while(!u8_atcmd_status);
    if(u8_atcmd_status != AT_OK)//error
    {
        u8_atcmd_status = AT_ERROR2;
        goto cmd_terminat; 
        
    } 
    
    u8_atcmd_status = AT_NON;
    if(myat_cmd("AT+CGACT=1,1",1000) == 1);//at_cmd("AT+CGACT=1,1");                   // 
    while(!u8_atcmd_status);
    if(u8_atcmd_status != AT_OK)//error
    {
        u8_atcmd_status = AT_ERROR2;
        goto cmd_terminat; 
        
    } 
    
    u8_atcmd_status = AT_NON;
    if(myat_cmd("AT+CGPADDR=1",1000) == 1);//at_cmd("AT+CGPADDR=1");                   //    
    while(!u8_atcmd_status);
    if(u8_atcmd_status != AT_OK)//error
    {
        u8_atcmd_status = AT_ERROR2;
        goto cmd_terminat; 
        
    }
    
    u8_atcmd_status = AT_NON;
    if(myat_cmd("AT#SGACT=1,1",1000) == 1);//at_cmd("AT#SGACT=1,1");//Context Activation, as response gives IP of the module:
    while(!u8_atcmd_status);
    if(u8_atcmd_status == AT_ERROR)//error
    {
        u8_atcmd_status = AT_ERROR2;
        goto cmd_terminat; 
        
    } 
    
    u8_atcmd_status = AT_NON;
    if(myat_cmd("AT+CREG?",1000) == 1);//at_cmd("AT+CREG?");                   //
    while(!u8_atcmd_status);
    if(u8_atcmd_status != AT_OK)//error
    {
        u8_atcmd_status = AT_ERROR2;
        goto cmd_terminat; 
        
    }
    
    u8_atcmd_status = AT_NON;
    if(myat_cmd("AT#SS",2000) == 1);//at_cmd("AT#SS");//Checking the socket status with #SS
    while(!u8_atcmd_status);
    if(u8_atcmd_status != AT_OK)//error
    {
        u8_atcmd_status = AT_ERROR2;
        goto cmd_terminat; 
        
    }
    u8_atcmd_status = AT_NON;
    if(myat_cmd("AT#SS",2000) == 1);//at_cmd("AT#SS");//Checking the socket status with #SS
    while(!u8_atcmd_status);
    if(u8_atcmd_status != AT_OK)//error
    {
        u8_atcmd_status = AT_ERROR2;
        goto cmd_terminat;   
    }
    u8_atcmd_status = AT_NON;
    if(myat_cmd("AT#SS",2000) == 1);//at_cmd("AT#SS");//Checking the socket status with #SS
    while(!u8_atcmd_status);
    if(u8_atcmd_status != AT_OK)//error
    {
        u8_atcmd_status = AT_ERROR2;
        goto cmd_terminat;   
    }
    
    u8_atcmd_status = AT_NON;
    if(myat_cmd("AT#SD=2,0,1011,\"49.206.26.81\",0,0,1",16000) == 1);//Opening a socket connection in command mode
    //SYSTICK_DelayMs(1000);
    while(!u8_atcmd_status);
    if(u8_atcmd_status != AT_OK)//not ok
    {
        u8_atcmd_status = AT_ERROR2;
        goto cmd_terminat;    
    } 
//    SYSTICK_DelayMs(2000);
//    SYSTICK_DelayMs(2000);
    
    u8_atcmd_status = AT_NON;
    if(myat_cmd("AT#SSEND=2",5000) == 1);//at_cmd("AT#SSEND=2");                   // sms text
    //SYSTICK_DelayMs(1000);
    while(!u8_atcmd_status);
    if(u8_atcmd_status != AT_DATASEND)//error
    {
        u8_atcmd_status = AT_ERROR2;
        goto cmd_terminat; 
        
    } 
//    SYSTICK_DelayMs(1000);
    
    u8_atcmd_status = AT_NON;

   // sprintf(msg,"d1-%d:&V000001,001001,101,0102211345,N1305.1572,E07733.3395,27.8,97.3,99.9,13.9,200000,01.2,12.2,07.2,255,000.0,000.0,000.0,000.0^",count);
//    strcpy( msg, "&V000001,001001,101,0102211345,N1305.1572,E07733.3395,27.8,97.3,99.9,13.9,200000,01.2,12.2,07.2,255,000.0,000.0,000.0,000.0^");
    //strcat( msg, "this is the testing messages... \r\n" );
    
    
//    strcpy( Slnobuff, "0001");
     
    tempdata = uint_datasentcount;
    Slnobuff [0] = tempdata/1000 + 0x30;
    
    tempdata = tempdata % 1000 ;
    Slnobuff [1] = tempdata/100 + 0x30;
    tempdata = tempdata % 100 ;  
    Slnobuff [2] = tempdata/10 + 0x30;
    Slnobuff [3] = tempdata%10 + 0x30;
    Slnobuff [4] = '\0';
    
    strcpy( Memtypebuff, "1N");
//    Memtypebuff[0] = 'N';
//    Memtypebuff[1] = '1';
//    Memtypebuff[2] = '\0';
//    strcpy( datetimebuff, gps_Date);
//    strcat(datetimebuff,gps_UTCTime);
    
    datetimebuff[0] = gps_Date[0];
    datetimebuff[1] = gps_Date[1];
    datetimebuff[2] = gps_Date[2];
    datetimebuff[3] = gps_Date[3];
    datetimebuff[4] = gps_Date[4];
    datetimebuff[5] = gps_Date[5];
    datetimebuff[6] = gps_UTCTime[0];
    datetimebuff[7] = gps_UTCTime[1];
    datetimebuff[8] = gps_UTCTime[2];
    datetimebuff[9] = gps_UTCTime[3];
    datetimebuff[10] = gps_UTCTime[4];
    datetimebuff[11] = gps_UTCTime[5];
    datetimebuff[12] = '\0';
    
    chr_locvalidbuff = gps_Status[0];//'A';
    
    strcpy( Latbuff, gps_NSIndicator);
    strcat(Latbuff,gps_Latitude);
    strcpy( logbuff, gps_EWIndicator);
    strcat(logbuff,gps_Longitude);
    flt_Adc1 = 0.40;
    flt_Adc2 = 226.66;

    u8_DI1 = b_Airfilterclog;
    u8_DI2 = b_Hydraulicoillevel;
    u8_DI3 = b_EngineCoolantTemperature;
    u8_DI4 = b_EngineON;
    u8_DI5 = b_LubeOilPressure;
    u8_DI6 = b_Hydraulicoilfilterclog;
    u8_DI7 = b_SeatbeltWarning;
    u8_DI8 = b_IgnitionON;
    flt_Adc3 = 6.71;
    flt_Adc3 = 7.23;
    flt_Adc3 = 4.59;
    u16_Adc6 = uint_frq;//340;
    flt_Adc7 = 5.01;
    flt_Smr = 21.82;
    
    //&VDT3000001,2N,211020022655,A,N1305.1469,E07733.3391,0.40,226.66,1,1,1,1,1,1,1,0,6.71,7.23,4.59,340,5.01,21.82^
    sprintf(msg,"&VDT300%s,%s,%s,%c,%s,%s,%.2f,%.2f,%d,%d,%d,%d,%d,%d,%d,%d,%.2f,%.2f,%.2f,%d,%.2f,%.2f^",Slnobuff,Memtypebuff,datetimebuff,chr_locvalidbuff,Latbuff,logbuff,flt_Adc1,flt_Adc2,u8_DI1,u8_DI2,u8_DI3,u8_DI4,u8_DI5,u8_DI6,u8_DI7,u8_DI8,flt_Adc3,flt_Adc4,flt_Adc5,u16_Adc6,flt_Adc7,flt_Smr );
//    for(uint16_t i=0;i <2025;i++)
//    {
//        msg[i] = i%10 + 0x30;
//        if(i%100 == 0)
//        {
//            i++;
//            msg[i]='\n';
//        }
//    }

    n = strlen(msg);
    msg[n]=26;//msg[n-1]=26;
    if(myat_cmd(msg,10000) == 1);//at_cmd_addition( msg ); 
    while(!u8_atcmd_status);
    if(u8_atcmd_status != AT_OK)//error//if(u8_atcmd_status == AT_ERROR)//error
    {
        u8_atcmd_status = AT_ERROR2;
        goto cmd_terminat; 
        
    } 
    
//    u8_atcmd_status = AT_NON;
//    if(myat_cmd("ATE0",1000) == 1);//at_cmd( "ATE0" );
//    while(!u8_atcmd_status);
//    if(u8_atcmd_status != AT_OK)//error
//    {
//        u8_atcmd_status = AT_ERROR2;
//        goto cmd_terminat;
//        
//    }
    
    u8_atcmd_status = AT_NON;
    if(myat_cmd("AT#SI",2000) == 1);//at_cmd("AT#SSEND=2");                   // sms text
    //SYSTICK_DelayMs(1000);
    while(!u8_atcmd_status);
    if(u8_atcmd_status == AT_ERROR)//error
    {
        u8_atcmd_status = AT_ERROR2;
        goto cmd_terminat; 
        
    } 
    
    
    cmd_terminat: 
    {
        if(u8_atcmd_status == AT_ERROR2)
        {
            printf("cmd_terminat:timedouted so gsm initializing..\r\n");
            GSM_RST_PA05_Set();
            SYSTICK_DelayMs(300);
            GSM_RST_PA05_Clear();
            SYSTICK_DelayMs(1000);
            gsm_gps_init();
        }
        
        else
        {
            uint_datasentcount++;
//            gsm_gps_init();
        }
            
    }
     SYSTICK_DelayMs(200);   
}
 */
//void mygsm_act_sendiot_info (void)
//{
//    static uint8_t onlinemode = 0;
////    uint8_t onlinemodeEN = 0;
//    char msg[ 2024 ] = { 0 };
//    uint16_t n=0;
////    static int count = 0;
////    uint16_t tempdata;
////    char Slnobuff[ 10 ] = { 0 },Memtypebuff[ 3 ] = { 0 },datetimebuff[ 20 ] = { 0 },chr_locvalidbuff = 'V';
////    char Latbuff[ 20 ] = { 0 },logbuff[ 20 ] = { 0 };
////    float flt_Adc1 =0,flt_Adc2 =0,flt_Adc3 =0,flt_Adc4 =0,flt_Adc5 =0,flt_Adc7 =0,flt_Smr =0;
////    uint8_t u8_DI1=0,u8_DI2=0,u8_DI3=0,u8_DI4=0,u8_DI5=0,u8_DI6=0,u8_DI7=0,u8_DI8=0;
////    uint16_t u16_Adc6=0;
//    
//        //MYCODE2
//    
//    if(onlinemode == 0)
//    {
//        /************************************************/
//        if(newdataEN == 1)
//        {
//            memset(msg,0,sizeof(msg));
//            if(loadlivedata(&msg[0]) != true)
//            {
//                u8_atcmd_status = AT_SKIP;
//                goto cmd_terminat; 
//            }
//        }
//        else
//        {
//            u8_atcmd_status = AT_SKIP;
//            goto cmd_terminat; 
//        }
//        u8_atcmd_status = AT_NON;
//        if(myat_cmd("ATE0",1000) == 1);//at_cmd( "ATE0" );
//        while(!u8_atcmd_status);
//        if(u8_atcmd_status != AT_OK)//error
//        {
//            u8_atcmd_status = AT_ERROR2;
//            goto cmd_terminat;
//
//        }
//        /************Check Signal Quality*************/
//        u8_atcmd_status = AT_NON;
//        if(myat_cmd("AT+CSQ",1000) == 1);//at_cmd( "AT+CSQ" );
//        while(!u8_atcmd_status);
//        if(u8_atcmd_status == AT_ERROR)//error
//        {
//            u8_atcmd_status = AT_ERROR2;
//            goto cmd_terminat; 
//
//        }
//
//        u8_atcmd_status = AT_NON;
//        if(myat_cmd("AT+CMGF=1",1000) == 1);//at_cmd( "AT+CMGF=1" );
//        while(!u8_atcmd_status);
//        if(u8_atcmd_status != AT_OK)//error
//        {
//            u8_atcmd_status = AT_ERROR2;
//            goto cmd_terminat; 
//
//        }
//
//        u8_atcmd_status = AT_NON;
//        if(myat_cmd("AT+CNMI=2,1,0,0,0",1000) == 1);//at_cmd("AT+CNMI=2,1,0,0,0");
//        while(!u8_atcmd_status);
//        if(u8_atcmd_status != AT_OK)//error
//        {
//            u8_atcmd_status = AT_ERROR2;
//            goto cmd_terminat; 
//
//        }
//
//        u8_atcmd_status = AT_NON;
//        if(myat_cmd("AT+CMGD=1,4",1000) == 1);//at_cmd("AT+CMGD=1,4");//Set SMS for Text format
//        while(!u8_atcmd_status);
//        if(u8_atcmd_status != AT_OK)//error
//        {
//            u8_atcmd_status = AT_ERROR2;
//            goto cmd_terminat; 
//
//        }
//
//        u8_atcmd_status = AT_NON;
//        if(myat_cmd("AT+CGSN",1000) == 1);//at_cmd("AT+CGSN");// SSet the parameters for an outgoing message with 24 hours of validity period and default properties:
//        while(!u8_atcmd_status);
//        if(u8_atcmd_status != AT_OK)//error
//        {
//            u8_atcmd_status = AT_ERROR2;
//            goto cmd_terminat; 
//
//        } 
//
//        u8_atcmd_status = AT_NON;
//        if(myat_cmd("AT+CGDCONT=1,\"IP\",\"airtelgprs.com\",\"0.0.0.0\",0,0",1000) == 1);//at_cmd("AT+CGDCONT=1,\"IP\",\"airtelgprs.com\",\"0.0.0.0\",0,0");//Define PDP context:
////        if(myat_cmd("AT+CGDCONT=1,\"IP\",\"LTCEL\",\"0.0.0.0\",0,0",1000) == 1);
//        while(!u8_atcmd_status);
//        if(u8_atcmd_status != AT_OK)//error
//        {
//            u8_atcmd_status = AT_ERROR2;
//            goto cmd_terminat; 
//
//        } 
//
//        u8_atcmd_status = AT_NON;
//        //
//        if(myat_cmd("AT+CMEE=2",1000) == 1);// Enable ERROR report in verbose format.
//        while(!u8_atcmd_status);
//        if(u8_atcmd_status != AT_OK)//error
//        {
//            u8_atcmd_status = AT_ERROR2;
//            goto cmd_terminat; 
//        } 
//        u8_atcmd_status = AT_NON;
//        if(myat_cmd("AT+CGACT=1,1",1000) == 1);//at_cmd("AT+CGACT=1,1");                   // 
//        while(!u8_atcmd_status);
//        if(u8_atcmd_status != AT_OK)//error
//        {
//            u8_atcmd_status = AT_ERROR2;
//            goto cmd_terminat; 
//        } 
//        u8_atcmd_status = AT_NON;
//        if(myat_cmd("AT+CGPADDR=1",1000) == 1);//at_cmd("AT+CGPADDR=1");                   //    
//        while(!u8_atcmd_status);
//        if(u8_atcmd_status != AT_OK)//error
//        {
//            u8_atcmd_status = AT_ERROR2;
//            goto cmd_terminat; 
//        }
//        u8_atcmd_status = AT_NON;
//        //Activate <cid>=1: AT#SGACT=1,1
//        if(myat_cmd("AT#SGACT=1,1",1000) == 1);//AT#SGACT=<cid>,1 activates the PDP context identified by the <cid>,
//        while(!u8_atcmd_status);
//        if(u8_atcmd_status == AT_ERROR)//error
//        {
//            u8_atcmd_status = AT_ERROR2;
//            goto cmd_terminat; 
//        } 
//        u8_atcmd_status = AT_NON;
//        if(myat_cmd("AT+CREG?",1000) == 1);//at_cmd("AT+CREG?");                   //
//        while(!u8_atcmd_status);
//        if(u8_atcmd_status != AT_OK)//error
//        {
//            u8_atcmd_status = AT_ERROR2;
//            goto cmd_terminat; 
//        }
//        u8_atcmd_status = AT_NON;
//        if(myat_cmd("AT#SS",2000) == 1);//at_cmd("AT#SS");//Checking the socket status with #SS
//        while(!u8_atcmd_status);
//        if(u8_atcmd_status != AT_OK)//error
//        {
//            u8_atcmd_status = AT_ERROR2;
//            goto cmd_terminat; 
//        }
//        u8_atcmd_status = AT_NON;
//        if(myat_cmd("AT#SS",2000) == 1);//at_cmd("AT#SS");//Checking the socket status with #SS
//        while(!u8_atcmd_status);
//        if(u8_atcmd_status != AT_OK)//error
//        {
//            u8_atcmd_status = AT_ERROR2;
//            goto cmd_terminat;   
//        }
//        u8_atcmd_status = AT_NON;
//        if(myat_cmd("AT#SS",2000) == 1);//at_cmd("AT#SS");//Checking the socket status with #SS
//        while(!u8_atcmd_status);
//        if(u8_atcmd_status != AT_OK)//error
//        {
//            u8_atcmd_status = AT_ERROR2;
//            goto cmd_terminat;   
//        }    
//       /* u8_atcmd_status = AT_NON;
//        if(myat_cmd("AT#SD=2,0,1011,\"49.206.26.81\",0,0,0",6000) == 1);//Opening a socket connection in command mode
////        if(myat_cmd("AT#SD=2,0,5000,\"104.211.74.190\",0,0,0",6000) == 1);
//        while(!u8_atcmd_status);
//        if(u8_atcmd_status != AT_CONNECT)//NOT CONNECTED
//        {
//            u8_atcmd_status = AT_ERROR2;
//            goto cmd_terminat;    
//        } */
//        u8_atcmd_status = AT_NON;
//        if(myat_cmd("AT#SD=2,0,1011,\"49.206.26.81\",0,0,1",16000) == 1);//Opening a socket connection in command mode
//        //SYSTICK_DelayMs(1000);
//        while(!u8_atcmd_status);
//        if(u8_atcmd_status != AT_OK)//not ok
//        {
//            u8_atcmd_status = AT_ERROR2;
//            goto cmd_terminat;    
//        } 
//        u8_atcmd_status = AT_NON;
//        if(myat_cmd("AT#SSEND=2",5000) == 1);//at_cmd("AT#SSEND=2");                   // sms text
//        //SYSTICK_DelayMs(1000);
//        while(!u8_atcmd_status);
//        if(u8_atcmd_status != AT_DATASEND)//error
//        {
//            u8_atcmd_status = AT_ERROR2;
//            goto cmd_terminat; 
//        }
//    }
//    else
//    {
//        /************************************************/
//        if(newdataEN == 1)
//        {
//            memset(msg,0,sizeof(msg));
//            if(loadlivedata(&msg[0]) != true)
//            {
//                u8_atcmd_status = AT_SKIP;
//                goto cmd_terminat; 
//            }
//        }
//        else
//        {
////            newdataEN = 0;
//            readnewmemloc(&rnewmemloc.addrbuf[0]);
//            readyet2sendmemloc(&ryet2sendmemloc.addrbuf[0]);
//            printf("\r\n rnewmemloc:%ld,\r\n ryet2sendmemloc:%ld,\r\n rnewmemloc.PacketField.flag:%d\r\n ",rnewmemloc.PacketField.memaddr,ryet2sendmemloc.PacketField.memaddr,rnewmemloc.PacketField.flag);
//            if(rnewmemloc.PacketField.flag == 0)
//            {
//                if((ryet2sendmemloc.PacketField.memaddr < (rnewmemloc.PacketField.memaddr ))&&(rnewmemloc.PacketField.memaddr  != 0))
//                {
//                    tempstartaddr = ryet2sendmemloc.PacketField.memaddr;
//
//                    u32_tempdiffaddr = rnewmemloc.PacketField.memaddr  - ryet2sendmemloc.PacketField.memaddr;
//                    if(u32_tempdiffaddr >=NOOFDATAPERPACKET_MEM)
//                    {
//                        u32_tempdiffaddr = NOOFDATAPERPACKET_MEM;
//                        tempendaddr = ryet2sendmemloc.PacketField.memaddr + NOOFDATAPERPACKET_MEM;
//                    }
//                    else
//                    {
//                        tempendaddr = ryet2sendmemloc.PacketField.memaddr + u32_tempdiffaddr;
//                    }
//
//                    memset(msg,0,sizeof(msg));
//                    if(loadmemorydata(tempstartaddr,tempendaddr,&msg[0]) != true)
//                    {
//                        u8_atcmd_status = AT_TERMINAT;
//                        goto cmd_terminat; 
//                    }              
//                }
//                else
//                {
//                    u8_atcmd_status = AT_TERMINAT;
//                    goto cmd_terminat;
//                }
//            }
//            else
//            {
//                if(ryet2sendmemloc.PacketField.memaddr < (MEM_LEN))
//                {
//                    tempstartaddr = ryet2sendmemloc.PacketField.memaddr;
//
//                    u32_tempdiffaddr = (MEM_LEN)  - ryet2sendmemloc.PacketField.memaddr;
//                    if(u32_tempdiffaddr >=NOOFDATAPERPACKET_MEM)
//                    {
//                        u32_tempdiffaddr = NOOFDATAPERPACKET_MEM;
//                        tempendaddr = ryet2sendmemloc.PacketField.memaddr + NOOFDATAPERPACKET_MEM;
//                    }
//                    else
//                    {
//                        tempendaddr = ryet2sendmemloc.PacketField.memaddr + u32_tempdiffaddr;
//                    }
//
//                    memset(msg,0,sizeof(msg));
//                    if(loadmemorydata(tempstartaddr,tempendaddr,&msg[0]) != true)
//                    {
//                        u8_atcmd_status = AT_TERMINAT;
//                        goto cmd_terminat; 
//                    }              
//                }
//                else
//                {
//                    u8_atcmd_status = AT_TERMINAT;
//                    goto cmd_terminat;
//                }
//            }
//        }
//        /************Check Signal Quality*************/
////        u8_atcmd_status = AT_NON;
////        if(myat_cmd("AT+CSQ",1000) == 1);//at_cmd( "AT+CSQ" );
////        while(!u8_atcmd_status);
////        if(u8_atcmd_status == AT_ERROR)//error
////        {
////            u8_atcmd_status = AT_ERROR2;
////            goto cmd_terminat; 
////
////        }
//        /************************************************/
//        
//        u8_atcmd_status = AT_NON;
//        if(myat_cmd("ATE0",1000) == 1);//at_cmd( "ATE0" );
//        while(!u8_atcmd_status);
//        if(u8_atcmd_status != AT_OK)//error
//        {
//            u8_atcmd_status = AT_ERROR2;
//            goto cmd_terminat;
//
//        }
//        //Use #SO command to switch from COMMAND to ONLINE mode, and +++ escape
//        //sequence to go back in COMMAND mode.
//        u8_atcmd_status = AT_NON;
//        if(myat_cmd("AT#SO = 2",6000) == 1);//Opening a socket connection in command mode
//        //SYSTICK_DelayMs(1000);
//        while(!u8_atcmd_status);
//        if(u8_atcmd_status != AT_CONNECT)//not CONNECTED
//        {
//            
//            u8_atcmd_status = AT_ERROR2;
//            goto cmd_terminat;    
//        }
////        onlinemodeEN = 1;
//    }
//    SYSTICK_DelayMs(5000);
///*    u8_atcmd_status = AT_NON;
//    if(myat_cmd2(msg,10000) == 1)
//    while(!u8_atcmd_status);
//    if(u8_atcmd_status == AT_NOCARRIER)//error//if(u8_atcmd_status == AT_ERROR)//error
//    {
//        u8_atcmd_status = AT_ERROR2;
//        goto cmd_terminat; 
//
//    } */
//    n = strlen(msg);
//    msg[n]=26;//msg[n-1]=26;
//    if(myat_cmd(msg,10000) == 1);//at_cmd_addition( msg ); 
//    while(!u8_atcmd_status);
//    if(u8_atcmd_status != AT_OK)//error//if(u8_atcmd_status == AT_ERROR)//error
//    {
//        u8_atcmd_status = AT_ERROR2;
//        goto cmd_terminat; 
//        
//    }
//    
//        
//    cmd_terminat: 
//    { 
//        if(u8_atcmd_status ==  AT_SKIP )
//        {
//            u8_atcmd_status = AT_NON; 
////            newdataEN = 1;
//        }
//        else if(u8_atcmd_status == AT_TERMINAT)
//        { 
////            if(onlinemodeEN == 1)
//            {
//                u8_atcmd_status = AT_NON; 
//                printf("strlen(msg):%d\r\n",strlen(msg));
//                memset(msg,0,sizeof(msg));
//                sprintf((char*)msg,"+++");
//                //n = strlen(msg);
//                //msg[n]=13;
//                if(myat_cmd2(msg,6000) == 1)//at_cmd("AT#SSEND=2");                   // sms text
//                //SYSTICK_DelayMs(1000);
//                while(!u8_atcmd_status);
//
//                u8_atcmd_status = AT_NON;
//                if(myat_cmd("AT#SH=2",5000) == 1);//? the connection is closed.
//                while(!u8_atcmd_status);
//                if(u8_atcmd_status != AT_OK)//error
//                {
////                    u8_atcmd_status = AT_ERROR2;
//    //                goto cmd_terminat;
//                }
//                onlinemode = 0;
//            }
////            onlinemodeEN = 0;
////            newdataEN = 0;
//            printf("cmd_terminat:AT_TERMINAT..\r\n");
//            
//        }
//        else if(u8_atcmd_status == AT_ERROR2)
//        {
//            saveunsenddata(&logwdata.rcvpacket[0]);
//            printf("cmd_terminat:timedouted so gsm initializing..\r\n");
//            GSM_RST_PA05_Set();
//            SYSTICK_DelayMs(300);
//            GSM_RST_PA05_Clear();
//            SYSTICK_DelayMs(1000);
//            gsm_gps_init();
//            onlinemode = 0;
//            newdataEN = 0;
//        }       
//        else
//        {
//            u8_atcmd_status = AT_NON; 
//            printf("strlen(msg):%d\r\n",strlen(msg));
//            memset(msg,0,sizeof(msg));
//            sprintf((char*)msg,"+++");
//            //n = strlen(msg);
//            //msg[n]=13;
//            if(myat_cmd2(msg,6000) == 1)//at_cmd("AT#SSEND=2");                   // sms text
//            //SYSTICK_DelayMs(1000);
//            while(!u8_atcmd_status);
//            
//            uint_datasentcount++;
//            if(newdataEN == 1)
//            {
//                printf("Live data send successfully....\r\n");
//                newdataEN = 0;
//                freshdatamemloc.PacketField.memaddr = 0;
//                savefreshdatamemloc(&freshdatamemloc.addrbuf[0]);
//            }
//            else
//            {
////                printf("Memory =%ld , data send successfully....\r\n",ryet2sendmemloc.PacketField.memaddr);  
//                wyet2sendmemloc.PacketField.memaddr = tempendaddr;
//                if(wyet2sendmemloc.PacketField.memaddr >= MEM_LEN)
//                {
//                    wyet2sendmemloc.PacketField.memaddr = 0;
//                    readnewmemloc(&rnewmemloc.addrbuf[0]);
//                    rnewmemloc.PacketField.flag = 0;
//                    savenewmemloc(&rnewmemloc.addrbuf[0]); 
//                }
//                saveyet2sendmemloc(&wyet2sendmemloc.addrbuf[0]);
//                printf("Memory data from =%ld  to  %ld sent successfully....\r\n",ryet2sendmemloc.PacketField.memaddr,tempendaddr);
//            }
//            onlinemode = 0;//onlinemode = 1;
//            u8_atcmd_status = AT_NON;
//            if(myat_cmd("AT#SI",5000) == 1)//;//at_cmd("AT#SSEND=2");                   // sms text
//            while(!u8_atcmd_status);     
//        } 
//        
//          
//    }
//     SYSTICK_DelayMs(2000);   
//}
void mydata_sendiot_onlinemode(void)
{
//    packet logrdata;//logsdata;//,
//    rewrite wnewmemloc,rnewmemloc,wyet2sendmemloc,ryet2sendmemloc,wrecomemloc,rrecomemloc,wmaxmemloc,rmaxmemloc,freshdatamemloc1,freshdatamemloc2,smrvalue;
//    rewrite rnewmemloc,ryet2sendmemloc,freshdatamemloc1,freshdatamemloc2,wyet2sendmemloc;
    char msg[ 2024 ] = { 0 };
    uint16_t len=0;
    
    char tmp[ 2024 ] = { 0 };
    
    char chr_APNbuf[20] = { 0 };
    char chr_IPbuf[20] = { 0 };
    char chr_IPPORTbuf[20] = { 0 };
    
    static uint16_t sentdataofSI1=0,sentdataofSI2=0,sentdataofSI3=0,sentdataofSI4=0,sentdataofSI5=0,sentdataofSI6=0;
    if(onlinemode == 0)
    {
        onlinemodecnt = 0;
        sentdataofSI1=0;
        u8_atcmd_status = AT_NON;
        if(myat_cmd("ATE0",10000) == 1);//at_cmd( "ATE0" );
        while(!u8_atcmd_status);
        if(u8_atcmd_status != AT_OK)//error
        {
            GSM_RST_PA05_Set();
            SYSTICK_DelayMs(30);
            GSM_RST_PA05_Clear();
            SYSTICK_DelayMs(10000);
            gsm_gps_init();
            u8_atcmd_status = AT_ERROR2;
            goto cmd_terminat;

        }
        
        u8_atcmd_status = AT_NON;
        if(myat_cmd("AT+CPIN?",1000) == 1);//at_cmd( "ATE0" );
        while(!u8_atcmd_status);
        if(u8_atcmd_status != AT_OK)//error
        {
            u8_atcmd_status = AT_ERROR2;
            goto cmd_terminat;
        }
        
        u8_atcmd_status = AT_NON;
        if(myat_cmd("AT+CSQ",1000) == 1);//Check Signal Quality
        while(!u8_atcmd_status);
        if(u8_atcmd_status == AT_ERROR)//error
        {
            u8_atcmd_status = AT_ERROR2;
            u8_gerrercode2 = 1;
            goto cmd_terminat; 

        }
        u8_gerrercode2 = 0;
        
        u8_atcmd_status = AT_NON;
        if(myat_cmd("AT+CMGF=1",1000) == 1);//at_cmd( "AT+CMGF=1" );
        while(!u8_atcmd_status);
        if(u8_atcmd_status != AT_OK)//error
        {
            u8_atcmd_status = AT_ERROR2;
            goto cmd_terminat; 

        }

        u8_atcmd_status = AT_NON;
        if(myat_cmd("AT+CNMI=2,1,0,0,0",1000) == 1);//at_cmd("AT+CNMI=2,1,0,0,0");
        while(!u8_atcmd_status);
        if(u8_atcmd_status != AT_OK)//error
        {
            u8_atcmd_status = AT_ERROR2;
            goto cmd_terminat; 

        }
        
        u8_atcmd_status = AT_NON;
        if(myat_cmd("AT+CMGD=1,3",25000) == 1);//wait 25sec...//at_cmd( "ATE0" );
        while(!u8_atcmd_status);
        if(u8_atcmd_status != AT_OK)//error
        {
            u8_atcmd_status = AT_ERROR2;
                goto cmd_terminat;
        }

        u8_atcmd_status = AT_NON;
        if(myat_cmd3("AT+CMGL=\"ALL\"",20000) == 1);//wait 20sec...//at_cmd( "ATE0" );
//        printf("-------breakpt1\r\n"); 
        while(!u8_atcmd_status);
        if(u8_atcmd_status != AT_OK)//error
        {
            u8_atcmd_status = AT_ERROR2;
            goto cmd_terminat;
        }
        
        if(newdataEN1 == 1)
        {
            memset(msg,0,sizeof(msg));
            if(loadlivedata1(&msg[0]) != true)
            {
                u8_atcmd_status = AT_SKIP;
                goto cmd_terminat; 
            }
        }
        else if(newdataEN2 == 1)
        {
            memset(msg,0,sizeof(msg));
            if(loadlivedata2(&msg[0]) != true)
            {
                u8_atcmd_status = AT_SKIP;
                goto cmd_terminat; 
            }
        }
        else
        {
            readnewmemloc(&rnewmemloc.addrbuf[0]);
            readyet2sendmemloc(&ryet2sendmemloc.addrbuf[0]);
            readFLAG(&flagbit.addrbuf[0]);
//            printf("\r\n rnewmemloc:%ld,\r\n ryet2sendmemloc:%ld,\r\n rnewmemloc.PacketField.flag:%d\r\n ",rnewmemloc.PacketField.memaddr,ryet2sendmemloc.PacketField.memaddr,rnewmemloc.PacketField.flag);
//            if(rnewmemloc.PacketField.flag == 0)
            if(flagbit.PacketField.memaddr == 0)
                printf("\r\nNo.of strings in the MEMORY :%ld,\r\n",(rnewmemloc.PacketField.memaddr-ryet2sendmemloc.PacketField.memaddr));
            else
                printf("\r\nNo.of strings in the MEMORY :%ld,\r\n",((rnewmemloc.PacketField.memaddr+MEM_LEN)-ryet2sendmemloc.PacketField.memaddr));

//            if(rnewmemloc.PacketField.flag == 0)
            if(flagbit.PacketField.memaddr == 0)    
            {
                if((ryet2sendmemloc.PacketField.memaddr < (rnewmemloc.PacketField.memaddr ))&&(rnewmemloc.PacketField.memaddr  != 0))
                {
                    tempstartaddr = ryet2sendmemloc.PacketField.memaddr;

                    u32_tempdiffaddr = rnewmemloc.PacketField.memaddr  - ryet2sendmemloc.PacketField.memaddr;
                    if(u32_tempdiffaddr >=NOOFDATAPERPACKET_MEM)
                    {
                        u32_tempdiffaddr = NOOFDATAPERPACKET_MEM;
                        tempendaddr = ryet2sendmemloc.PacketField.memaddr + NOOFDATAPERPACKET_MEM;
                    }
                    else
                    {
                        tempendaddr = ryet2sendmemloc.PacketField.memaddr + u32_tempdiffaddr;
                    }

                    memset(msg,0,sizeof(msg));
                    if(loadmemorydata(tempstartaddr,tempendaddr,&msg[0]) != true)
                    {
                        u8_atcmd_status = AT_TERMINAT;
                        goto cmd_terminat; 
                    }              
                }
                else
                {
                    u8_atcmd_status = AT_TERMINAT;
                    goto cmd_terminat;
                }
            }
            else
            {
                if(ryet2sendmemloc.PacketField.memaddr < (MEM_LEN))
                {
                    tempstartaddr = ryet2sendmemloc.PacketField.memaddr;

                    u32_tempdiffaddr = (MEM_LEN)  - ryet2sendmemloc.PacketField.memaddr;
                    if(u32_tempdiffaddr >=NOOFDATAPERPACKET_MEM)
                    {
                        u32_tempdiffaddr = NOOFDATAPERPACKET_MEM;
                        tempendaddr = ryet2sendmemloc.PacketField.memaddr + NOOFDATAPERPACKET_MEM;
                    }
                    else
                    {
                        tempendaddr = ryet2sendmemloc.PacketField.memaddr + u32_tempdiffaddr;
                    }

                    memset(msg,0,sizeof(msg));
                    if(loadmemorydata(tempstartaddr,tempendaddr,&msg[0]) != true)
                    {
                        u8_atcmd_status = AT_TERMINAT;
                        goto cmd_terminat; 
                    }              
                }
                else
                {
                    u8_atcmd_status = AT_TERMINAT;
                    goto cmd_terminat;
                }
            }
        }
        
        if(u8_SAVING2MEM == 1 )
        {
            printf("SAVING2MEM mode for testing... ");
            u8_atcmd_status = AT_ERROR2;
            goto cmd_terminat;
        }
        u8_atcmd_status = AT_NON;
        if(myat_cmd("AT+CGSN",1000) == 1);//at_cmd("AT+CGSN");// SSet the parameters for an outgoing message with 24 hours of validity period and default properties:
        while(!u8_atcmd_status);
        if(u8_atcmd_status != AT_OK)//error
        {
            u8_atcmd_status = AT_ERROR2;
            goto cmd_terminat; 

        } 
        
//        readIPaddr((uint8_t*)&chr_IPbuf[0]);
        memset(tmp, 0x00, sizeof(tmp));
        readAPNaddr((uint8_t*)&tmp[0]);
        len = 0;
        for(uint8_t i=0;i< 20;i++)
        {
            if(tmp[i] != 0xFF)
            {
                chr_APNbuf[len++] = tmp[i];
                
            }
            else
                break;
        }
        if (len < 1)
        {
            strcpy ( chr_APNbuf, "airtelgprs.com" ) ;
        }
        
        u8_atcmd_status = AT_NON;
//        if(SERVERTO == SERVER_LT)
//        {
//            if(myat_cmd("AT+CGDCONT=1,\"IP\",\"LTCEL\",\"0.0.0.0\",0,0",1000) == 1);
            
//        }
//        else
//        {
//            if(myat_cmd("AT+CGDCONT=1,\"IP\",\"airtelgprs.com\",\"0.0.0.0\",0,0",1000) == 1);//at_cmd("AT+CGDCONT=1,\"IP\",\"airtelgprs.com\",\"0.0.0.0\",0,0");//Define PDP context:
//        }
//        while(!u8_atcmd_status);
//        if(u8_atcmd_status != AT_OK)//error
//        {
//            u8_atcmd_status = AT_ERROR2;
//            goto cmd_terminat; 
//
//        } 
        u8_atcmd_status = AT_NON;
        memset(tmp, 0x00, sizeof(tmp));
        sprintf(tmp,"AT+CGDCONT=1,\"IP\",\"%s\",\"0.0.0.0\",0,0",chr_APNbuf);

        if(myat_cmd(tmp,1000) == 1);//Opening a socket connection in command mode
        while(!u8_atcmd_status);
        if(u8_atcmd_status != AT_OK)//if(u8_atcmd_status != AT_CONNECT)//not ok
        {
            u8_atcmd_status = AT_ERROR2;
            goto cmd_terminat;    
        }
        
        u8_atcmd_status = AT_NON;
        //
        if(myat_cmd("AT+CMEE=2",1000) == 1);// Enable ERROR report in verbose format.
        while(!u8_atcmd_status);
        if(u8_atcmd_status != AT_OK)//error
        {
            u8_atcmd_status = AT_ERROR2;
            goto cmd_terminat; 
        } 
//when you discommend from server tries again, use "AT#SH=1",
//"AT#SGACT=1,0" 5 second gap "AT#SGACT=1,1" after that "AT#SD" command.
        u8_atcmd_status = AT_NON;
        //Activate <cid>=1: AT#SGACT=1,1
        if(myat_cmd("AT#SH=1",150000) == 1);//discommend from server tries again
        while(!u8_atcmd_status);
        if(u8_atcmd_status == AT_ERROR)//error
        {
            u8_atcmd_status = AT_ERROR2;
            goto cmd_terminat; 
        }
        
        u8_atcmd_status = AT_NON;
        //Activate <cid>=1: AT#SGACT=1,1
        if(myat_cmd("AT#SGACT=1,0",150000) == 1);//wait 150sec...//AT#SGACT=<cid>,1 activates the PDP context identified by the <cid>,
        while(!u8_atcmd_status);
        if(u8_atcmd_status == AT_ERROR)//error
        {
            u8_atcmd_status = AT_ERROR2;
            goto cmd_terminat; 
        } 
        //5 second gap
        SYSTICK_DelayMs(5000); 
        u8_atcmd_status = AT_NON;
        //Activate <cid>=1: AT#SGACT=1,1
        if(myat_cmd("AT#SGACT=1,1",150000) == 1);//wait 150sec...//AT#SGACT=<cid>,1 activates the PDP context identified by the <cid>,
        while(!u8_atcmd_status);
        if(u8_atcmd_status == AT_ERROR)//error
        {
            u8_atcmd_status = AT_ERROR2;
            goto cmd_terminat; 
        } 
        u8_SSid = 1;
        //SRING Unsolicited Mode: Data amount
        u8_atcmd_status = AT_NON;
        memset(tmp, 0x00, sizeof(tmp));
        sprintf(tmp,"AT#SCFGEXT=%d,1,0,0",u8_SSid);
//        if(myat_cmd("AT#SSEND=2",5000) == 1);//at_cmd("AT#SSEND=2");                   // sms text
        if(myat_cmd(tmp,6000) == 1);//at_cmd("AT#SSEND=2"); 
        while(!u8_atcmd_status);
        if(u8_atcmd_status != AT_OK)//error
        {
            u8_atcmd_status = AT_ERROR2;
            goto cmd_terminat; 
        }
        
         u8_atcmd_status = AT_NON;
        memset(tmp, 0x00, sizeof(tmp));
        sprintf(tmp,"AT#SLASTCLOSURE=%d",u8_SSid);
//        if(myat_cmd("AT#SSEND=2",5000) == 1);//at_cmd("AT#SSEND=2");                   // sms text
        if(myat_cmd(tmp,6000) == 1);//at_cmd("AT#SSEND=2"); 
        while(!u8_atcmd_status);
        if(u8_atcmd_status != AT_OK)//error
        {
            u8_atcmd_status = AT_ERROR2;
//            goto cmd_terminat; 
        }
        
        memset(tmp, 0x00, sizeof(tmp));
        readIPaddr((uint8_t*)&tmp[0]);
        bool ip2portset = 0;
        len = 0;
        for(uint8_t i=0;i< 100;i++)
        {
            if(tmp[i] != 0xFF)
            {
                if(tmp[i] == ':')
                {
                    ip2portset = 1;
                    i++;
                    len = 0;
                }
                if(ip2portset == 0)
                    chr_IPbuf[len++] = tmp[i];
                else
                    chr_IPPORTbuf[len++] = tmp[i];
            }      
            else
                break;
        }
        if ((len < 1)||(ip2portset == 0))
        {
            strcpy ( chr_IPbuf, "49.206.26.81" ) ;
            strcpy ( chr_IPPORTbuf, "1011" ) ;
        }
//        printf ("chr_IPbuf:%s\r\n",chr_IPbuf);
//        printf ("chr_IPPORTbuf:%s\r\n",chr_IPPORTbuf); 
        
        u8_atcmd_status = AT_NON;
        memset(tmp, 0x00, sizeof(tmp));
        if(TELIT_SERVER == 0)
            sprintf(tmp,"AT#SD=%d,0,%s,\"%s\",0,0,1",u8_SSid,chr_IPPORTbuf,chr_IPbuf);
        else
            sprintf(tmp,"AT#SD=1,0,10510,\"modules.telit.com\",0,0,1");

        if(myat_cmd(tmp,140000) == 1);//wait 140sec...//Opening a socket connection in command mode
        while(!u8_atcmd_status);
        if(u8_atcmd_status != AT_OK)//if(u8_atcmd_status != AT_CONNECT)//not ok
        {
            u8_atcmd_status = AT_ERROR2;
            goto cmd_terminat;    
        } 
        
        
        u8_atcmd_status = AT_NON;
        //Activate <cid>=1: AT#SGACT=1,1
        if(myat_cmd("AT+CCLK?",150000) == 1);//wait 150sec...//AT#SGACT=<cid>,1 activates the PDP context identified by the <cid>,
        while(!u8_atcmd_status);
        if(u8_atcmd_status == AT_ERROR)//error
        {
            u8_atcmd_status = AT_ERROR2;
            goto cmd_terminat; 
        }
        
        u8_atcmd_status = AT_NON;
        memset(tmp, 0x00, sizeof(tmp));
        sprintf(tmp,"AT#SSEND=%d",u8_SSid);
//        if(myat_cmd("AT#SSEND=2",5000) == 1);//at_cmd("AT#SSEND=2");                   // sms text
        if(myat_cmd(tmp,150000) == 1);//at_cmd("AT#SSEND=2"); 
        while(!u8_atcmd_status);
        if(u8_atcmd_status != AT_DATASEND)//error
        {
            u8_atcmd_status = AT_ERROR2;
            goto cmd_terminat; 
        }
    }
    else
    {
        if(newdataEN1 == 1)
        {
            memset(msg,0,sizeof(msg));
            if(loadlivedata1(&msg[0]) != true)
            {
                u8_atcmd_status = AT_SKIP;
                goto cmd_terminat; 
            }
        }
        else if(newdataEN2 == 1)
        {
            memset(msg,0,sizeof(msg));
            if(loadlivedata2(&msg[0]) != true)
            {
                u8_atcmd_status = AT_SKIP;
                goto cmd_terminat; 
            }
        }
        else
        {
            readnewmemloc(&rnewmemloc.addrbuf[0]);
            readyet2sendmemloc(&ryet2sendmemloc.addrbuf[0]);
            readFLAG(&flagbit.addrbuf[0]);
//            printf("\r\n rnewmemloc:%ld,\r\n ryet2sendmemloc:%ld,\r\n rnewmemloc.PacketField.flag:%d\r\n ",rnewmemloc.PacketField.memaddr,ryet2sendmemloc.PacketField.memaddr,rnewmemloc.PacketField.flag);
            //if(rnewmemloc.PacketField.flag == 0)
            if(flagbit.PacketField.memaddr == 0)
                printf("\r\nNo.of strings in the MEMORY :%ld,\r\n",(rnewmemloc.PacketField.memaddr-ryet2sendmemloc.PacketField.memaddr));
            else
                printf("\r\nNo.of strings in the MEMORY :%ld,\r\n",((rnewmemloc.PacketField.memaddr+MEM_LEN)-ryet2sendmemloc.PacketField.memaddr));

//            if(rnewmemloc.PacketField.flag == 0)
            if(flagbit.PacketField.memaddr == 0)
            {
                if((ryet2sendmemloc.PacketField.memaddr < (rnewmemloc.PacketField.memaddr ))&&(rnewmemloc.PacketField.memaddr  != 0))
                {
                    tempstartaddr = ryet2sendmemloc.PacketField.memaddr;

                    u32_tempdiffaddr = rnewmemloc.PacketField.memaddr  - ryet2sendmemloc.PacketField.memaddr;
                    if(u32_tempdiffaddr >=NOOFDATAPERPACKET_MEM)
                    {
                        u32_tempdiffaddr = NOOFDATAPERPACKET_MEM;
                        tempendaddr = ryet2sendmemloc.PacketField.memaddr + NOOFDATAPERPACKET_MEM;
                    }
                    else
                    {
                        tempendaddr = ryet2sendmemloc.PacketField.memaddr + u32_tempdiffaddr;
                    }

                    memset(msg,0,sizeof(msg));
                    if(loadmemorydata(tempstartaddr,tempendaddr,&msg[0]) != true)
                    {
                        u8_atcmd_status = AT_TERMINAT;
                        goto cmd_terminat; 
                    }              
                }
                else
                {
                    u8_atcmd_status = AT_TERMINAT;
                    goto cmd_terminat;
                }
            }
            else
            {
                if(ryet2sendmemloc.PacketField.memaddr < (MEM_LEN))
                {
                    tempstartaddr = ryet2sendmemloc.PacketField.memaddr;

                    u32_tempdiffaddr = (MEM_LEN)  - ryet2sendmemloc.PacketField.memaddr;
                    if(u32_tempdiffaddr >=NOOFDATAPERPACKET_MEM)
                    {
                        u32_tempdiffaddr = NOOFDATAPERPACKET_MEM;
                        tempendaddr = ryet2sendmemloc.PacketField.memaddr + NOOFDATAPERPACKET_MEM;
                    }
                    else
                    {
                        tempendaddr = ryet2sendmemloc.PacketField.memaddr + u32_tempdiffaddr;
                    }

                    memset(msg,0,sizeof(msg));
                    if(loadmemorydata(tempstartaddr,tempendaddr,&msg[0]) != true)
                    {
                        u8_atcmd_status = AT_TERMINAT;
                        goto cmd_terminat; 
                    }              
                }
                else
                {
                    u8_atcmd_status = AT_TERMINAT;
                    goto cmd_terminat;
                }
            }
        }
        /////////////////////////////////
        memset(tmp, 0x00, sizeof(tmp));
        readIPaddr((uint8_t*)&tmp[0]);
        bool ip2portset = 0;
        len = 0;
        for(uint8_t i=0;i< 100;i++)
        {
            if(tmp[i] != 0xFF)
            {
                if(tmp[i] == ':')
                {
                    ip2portset = 1;
                    i++;
                    len = 0;
                }
                if(ip2portset == 0)
                    chr_IPbuf[len++] = tmp[i];
                else
                    chr_IPPORTbuf[len++] = tmp[i];
            }      
            else
                break;
        }
        if ((len < 1)||(ip2portset == 0))
        {
            strcpy ( chr_IPbuf, "49.206.26.81" ) ;
            strcpy ( chr_IPPORTbuf, "1011" ) ;
        }
//        printf ("chr_IPbuf:%s\r\n",chr_IPbuf);
//        printf ("chr_IPPORTbuf:%s\r\n",chr_IPPORTbuf); 
        
        u8_atcmd_status = AT_NON;
        memset(tmp, 0x00, sizeof(tmp));
        if(TELIT_SERVER == 0)
            sprintf(tmp,"AT#SD=%d,0,%s,\"%s\",0,0,1",u8_SSid,chr_IPPORTbuf,chr_IPbuf);
        else
            sprintf(tmp,"AT#SD=1,0,10510,\"modules.telit.com\",0,0,1");

        if(myat_cmd(tmp,140000) == 1);//wait 140sec...//Opening a socket connection in command mode
        while(!u8_atcmd_status);
        if(u8_atcmd_status != AT_OK)//if(u8_atcmd_status != AT_CONNECT)//not ok
        {
            u8_atcmd_status = AT_ERROR2;
            goto cmd_terminat;    
        } 
     
        u8_atcmd_status = AT_NON;
        //Activate <cid>=1: AT#SGACT=1,1
        if(myat_cmd("AT+CCLK?",150000) == 1);//wait 150sec...//AT#SGACT=<cid>,1 activates the PDP context identified by the <cid>,
        while(!u8_atcmd_status);
        if(u8_atcmd_status == AT_ERROR)//error
        {
            u8_atcmd_status = AT_ERROR2;
            goto cmd_terminat; 
        }
        
        u8_atcmd_status = AT_NON;
        memset(tmp, 0x00, sizeof(tmp));
        sprintf(tmp,"AT#SSEND=%d",u8_SSid);
//        if(myat_cmd("AT#SSEND=2",5000) == 1);//at_cmd("AT#SSEND=2");                   // sms text
        if(myat_cmd(tmp,150000) == 1);//at_cmd("AT#SSEND=2"); 
        while(!u8_atcmd_status);
        if(u8_atcmd_status != AT_DATASEND)//error
        {
            u8_atcmd_status = AT_ERROR2;
            goto cmd_terminat; 
        }
        
    }
    u8_datasendEN = 1;
    u8_atcmd_status = AT_NON;
    uint16_t n = strlen(msg);
    msg[n]=26;
    if(myat_cmd2(msg,10000) == 1)//txout
    while(!u8_atcmd_status);
    if(u8_atcmd_status == AT_OK)
    {
        ;
    }
    else
    {
        if(((u8_SSid==1)&&(u8_atcmd_status == AT_NOCARRIER1))||((u8_SSid==2)&&(u8_atcmd_status == AT_NOCARRIER2))||((u8_SSid==3)&&(u8_atcmd_status == AT_NOCARRIER3))||((u8_SSid==4)&&(u8_atcmd_status == AT_NOCARRIER4))||((u8_SSid==5)&&(u8_atcmd_status == AT_NOCARRIER5))||((u8_SSid==6)&&(u8_atcmd_status == AT_NOCARRIER6)))//if(u8_atcmd_status == AT_NOCARRIER)//error//if(u8_atcmd_status == AT_ERROR)//error
        {
            u8_atcmd_status = AT_NON;
            memset(tmp, 0x00, sizeof(tmp));
            sprintf(tmp,"AT#SLASTCLOSURE=%d",u8_SSid);
    //        if(myat_cmd("AT#SSEND=2",5000) == 1);//at_cmd("AT#SSEND=2");                   // sms text
            if(myat_cmd(tmp,6000) == 1);//at_cmd("AT#SSEND=2"); 
            while(!u8_atcmd_status);
            if(u8_atcmd_status != AT_OK)//error
            {
                u8_atcmd_status = AT_ERROR2;
    //            goto cmd_terminat; 
            }

            u8_atcmd_status = AT_NON;
            if(myat_cmd("AT#SI",150000) == 1);//at_cmd("AT#SS");//Checking the socket status with #SS
    //        while(!u8_atcmd_status){;}
    //        if(u8_atcmd_status != AT_OK)
    //        {
    //            u8_atcmd_status = AT_ERROR2;
    //            goto cmd_terminat; 
    //        }
            u8_atcmd_status = AT_ERROR2;
            goto cmd_terminat; 
        } 
    }
    u8_datasendEN = 0; 
    
//    u8_atcmd_status = AT_NON;
//    if(myat_cmd("AT#SI",3000) == 1);//at_cmd("AT#SS");//Checking the socket status with #SS
//    while(!u8_atcmd_status){;}
//    if(u8_atcmd_status != AT_OK)
//    {
//        u8_atcmd_status = AT_ERROR2;
//        goto cmd_terminat; 
//    }
    ////////////Socket Info checking//////////////////
    uint8_t u8_connId =0 ,u8_datasendstatuseOK = 0,u8_datasendstatuseOKcnt =0;//0-non,1-ok,2-faild
    uint16_t u16_sent=0,u16_tempsent =0 ,u16_received=0,u16_buff_in=0,u16_ack_waiting=0;
    if(u8_SSid ==1)
    {
        sentdataofSI1 = sentdataofSI1 + n;
        u16_tempsent = sentdataofSI1;
    }
    else if(u8_SSid ==2)
    {
        sentdataofSI2 = sentdataofSI2 + n;
        u16_tempsent = sentdataofSI2;
    }
    else if(u8_SSid ==3)
    {
        sentdataofSI3 = sentdataofSI3 + n;
        u16_tempsent = sentdataofSI3;
    }
    else if(u8_SSid ==4)
    {
        sentdataofSI4 = sentdataofSI4 + n;
        u16_tempsent = sentdataofSI4;
    }
    else if(u8_SSid ==5)
    {
        sentdataofSI5 = sentdataofSI5 + n;
        u16_tempsent = sentdataofSI5;
    }
    else if(u8_SSid ==6)
    {
        sentdataofSI6 = sentdataofSI6 + n;
        u16_tempsent = sentdataofSI6;
    }
    while(u8_datasendstatuseOK == 0)
    {
        
        
        u8_atcmd_status = AT_NON;
        memset(tmp, 0x00, sizeof(tmp));
        sprintf(tmp,"AT#SI=%d",u8_SSid);
    //        if(myat_cmd("AT#SSEND=2",5000) == 1);//at_cmd("AT#SSEND=2");                   // sms text
//        if(myatSIstaus_cmd(tmp,1000,&u16_socketinfobuf[0]) == 1);//at_cmd("AT#SSEND=2"); 
        
        if(myatSIstaus_cmd(tmp,150000,&u8_connId,&u16_sent,&u16_received,&u16_buff_in,&u16_ack_waiting)==1)  
        while(!u8_atcmd_status);
//        printf("n=%d,u8_connId:%d,u16_sent=%d,u16_received=%d,,u16_buff_in=%d,u16_ack_waiting=%d\r\n",n,u8_connId,u16_sent,u16_received,u16_buff_in,u16_ack_waiting);
//        if(u8_atcmd_status != AT_DATASEND)//error
//        {
//            u8_atcmd_status = AT_ERROR2;
//            goto cmd_terminat; 
//        }
//        if((u16_buff_in >= u16_sent) &&(u16_received == 0) &&(u16_ack_waiting == 0))
        
        if((u16_sent >= u16_tempsent)&&(u16_ack_waiting == 0))
        {
            u8_datasendstatuseOK = 1;
        }
        else if(u8_atcmd_status == AT_NOCARRIER)
        {
            
            u8_datasendstatuseOK = 2;
            u8_atcmd_status = AT_ERROR2;
            goto cmd_terminat;
        }
        else
        {
            if(u8_datasendstatuseOKcnt >=20)
            {
                u8_datasendstatuseOK = 2;
                u8_atcmd_status = AT_ERROR2;
                goto cmd_terminat; 
            }
        }
        u8_datasendstatuseOKcnt++;
    }
    
    cmd_terminat: 
    { 
        if(u8_atcmd_status ==  AT_SKIP )
        {
            u8_atcmd_status = AT_NON; 
            printf("cmd_terminat:AT_SKIP..\r\n");
//            readsms();
//            newdataEN = 1;
            onlinemode = 0;
        }
        else if(u8_atcmd_status == AT_TERMINAT)
        { 
//            if(onlinemodeEN == 1)
            if(onlinemode == 1)
            {
                u8_atcmd_status = AT_NON;
                memset(tmp, 0x00, sizeof(tmp));
                sprintf(tmp,"AT#SH=%d",u8_SSid);//
        //        if(myat_cmd("AT#SSEND=2",5000) == 1);//at_cmd("AT#SSEND=2");                   // sms text
                if(myat_cmd(tmp,150000) == 1);//wait 3sec...//at_cmd("AT#SSEND=2"); 
                while(!u8_atcmd_status);
                if(u8_atcmd_status != AT_DATASEND)//error
                {
                    u8_atcmd_status = AT_ERROR2;
//                    goto cmd_terminat; 
                }
                
//                onlinemode = 0;
            }
//            onlinemodeEN = 0;
//            newdataEN = 0;
            printf("cmd_terminat:AT_TERMINAT and socket stop(SH)..\r\n");
            onlinemode = 0;
        }
        else if(u8_atcmd_status == AT_ERROR2)
        {
            if(newdataEN1==1)
            {
                saveunsenddata1(&logrdata.rcvpacket[0]);
                newdataEN1 = 0;
                u8_newdataset1 = 0;
            }
            else if(newdataEN2==1)
            {
                saveunsenddata2(&logrdata.rcvpacket[0]);
                newdataEN2 = 0;
                u8_newdataset2 = 0;
            }
            printf("cmd_terminat:AT_ERROR2!\r\n");
//            GSM_RST_PA05_Set();
//            SYSTICK_DelayMs(30);
//            GSM_RST_PA05_Clear();
//            SYSTICK_DelayMs(1000);
//            gsm_gps_init();
            onlinemode = 0;
            
        }       
        else
        {
           /* u8_atcmd_status = AT_NON; 
//            printf("strlen(msg):%d\r\n",strlen(msg));
            memset(msg,0,sizeof(msg));
            sprintf((char*)msg,"+++");
            //n = strlen(msg);
            //msg[n]=13;
            if(myat_cmd2(msg,26000) == 1)//at_cmd("AT#SSEND=2");                   // sms text
            //SYSTICK_DelayMs(1000);
            while(!u8_atcmd_status);*/
            
//            u8_atcmd_status = AT_NON;
//            memset(tmp, 0x00, sizeof(tmp));
//            sprintf(tmp,"AT#BASE64=%d,1,0",u8_SSid);
//    //        if(myat_cmd("AT#SSEND=2",5000) == 1);//at_cmd("AT#SSEND=2");                   // sms text
//            if(myat_cmd(tmp,16000) == 1);//at_cmd("AT#SSEND=2"); 
//            while(!u8_atcmd_status);
//            if(u8_atcmd_status != AT_CONNECT)//error
//            {
//                u8_atcmd_status = AT_ERROR2;
//                goto cmd_terminat; 
//            }
            if(TELIT_SERVER == 1)
            {
                u8_atcmd_status = AT_NON;
                //Activate <cid>=1: AT#SGACT=1,1
                if(myat_cmd("AT#SRECV=1,1500",150000) == 1);//wait 150sec...//AT#SGACT=<cid>,1 activates the PDP context identified by the <cid>,
                while(!u8_atcmd_status);
                if(u8_atcmd_status == AT_ERROR)//error
                {
    //                u8_atcmd_status = AT_ERROR2;
    //                goto cmd_terminat; 
                }

                u8_atcmd_status = AT_NON;
                //Activate <cid>=1: AT#SGACT=1,1
                if(myat_cmd("AT#SI=1",150000) == 1);//wait 150sec...//AT#SGACT=<cid>,1 activates the PDP context identified by the <cid>,
                while(!u8_atcmd_status);
                if(u8_atcmd_status == AT_ERROR)//error
                {
    //                u8_atcmd_status = AT_ERROR2;
    //                goto cmd_terminat; 
                }
            }
            uint_datasentcount++;
            if(newdataEN1 == 1)
            {
                u8_atcmd_status = AT_NON;
                memset(tmp, 0x00, sizeof(tmp));
                sprintf(tmp,"AT#SH=%d",u8_SSid);//
        //        if(myat_cmd("AT#SSEND=2",5000) == 1);//at_cmd("AT#SSEND=2");                   // sms text
                if(myat_cmd(tmp,150000) == 1);//wait 3sec...//at_cmd("AT#SSEND=2"); 
                while(!u8_atcmd_status);
                if(u8_atcmd_status != AT_DATASEND)//error
                {
                    u8_atcmd_status = AT_ERROR2;
//                    goto cmd_terminat; 
                }
                
                printf("Live data send successfully....\r\n");
                newdataEN1 = 0;
                u8_newdataset1 = 0;
                sentdataofSI1=0;
                freshdatamemloc1.PacketField.memaddr = 0;
                savefreshdatamemloc1(&freshdatamemloc1.addrbuf[0]);
            }
            else if(newdataEN2 == 1)
            {
                u8_atcmd_status = AT_NON;
                memset(tmp, 0x00, sizeof(tmp));
                sprintf(tmp,"AT#SH=%d",u8_SSid);//
        //        if(myat_cmd("AT#SSEND=2",5000) == 1);//at_cmd("AT#SSEND=2");                   // sms text
                if(myat_cmd(tmp,150000) == 1);//wait 3sec...//at_cmd("AT#SSEND=2"); 
                while(!u8_atcmd_status);
                if(u8_atcmd_status != AT_DATASEND)//error
                {
                    u8_atcmd_status = AT_ERROR2;
//                    goto cmd_terminat; 
                }
                
                printf("Live data send successfully....\r\n");
                newdataEN2 = 0;
                u8_newdataset2 = 0;
                sentdataofSI1=0;
                freshdatamemloc2.PacketField.memaddr = 0;
                savefreshdatamemloc2(&freshdatamemloc2.addrbuf[0]);
            }
            else
            {
                u8_atcmd_status = AT_NON;
                memset(tmp, 0x00, sizeof(tmp));
                sprintf(tmp,"AT#SH=%d",u8_SSid);//
        //        if(myat_cmd("AT#SSEND=2",5000) == 1);//at_cmd("AT#SSEND=2");                   // sms text
                if(myat_cmd(tmp,150000) == 1);//wait 3sec...//at_cmd("AT#SSEND=2"); 
                while(!u8_atcmd_status);
                if(u8_atcmd_status != AT_DATASEND)//error
                {
                    u8_atcmd_status = AT_ERROR2;
//                    goto cmd_terminat; 
                }
                sentdataofSI1=0;

//                printf("Memory =%ld , data send successfully....\r\n",ryet2sendmemloc.PacketField.memaddr);  
                wyet2sendmemloc.PacketField.memaddr = tempendaddr;
                if(wyet2sendmemloc.PacketField.memaddr >= MEM_LEN)
                {
                    wyet2sendmemloc.PacketField.memaddr = 0;
                    readnewmemloc(&rnewmemloc.addrbuf[0]);
//                    rnewmemloc.PacketField.flag = 0;
                    flagbit.PacketField.memaddr = 0;
                    saveFLAG(&flagbit.addrbuf[0]);
                    savenewmemloc(&rnewmemloc.addrbuf[0]); 
                }
                saveyet2sendmemloc(&wyet2sendmemloc.addrbuf[0]);
                printf("Memory data from =%ld  to  %ld sent successfully....\r\n",ryet2sendmemloc.PacketField.memaddr,tempendaddr);
            
            }
            
            onlinemode = 1;  
            onlinemodecnt++;
            if(onlinemodecnt >= 20)// packets limitting
            {
                onlinemodecnt = 0;
                onlinemode = 0;
            }
//            printf("onlinemode=%d,onlinemodecnt=%d\r\n",onlinemode,onlinemodecnt);
        }      
    }
     SYSTICK_DelayMs(2000);   
}
void readsms(void)
{
    u8_atcmd_status = AT_NON;
        if(myat_cmd3("ATE0",1000) == 1);//at_cmd( "ATE0" );
        while(!u8_atcmd_status);
        if(u8_atcmd_status != AT_OK)//error
        {
            u8_atcmd_status = AT_ERROR2;
//            goto cmd_terminat;

        }
        
//        u8_atcmd_status = AT_NON;
//        if(myat_cmd3("AT+CPIN?",1000) == 1);//at_cmd( "ATE0" );
//        while(!u8_atcmd_status);
//        if(u8_atcmd_status != AT_OK)//error
//        {
//            u8_atcmd_status = AT_ERROR2;
////            goto cmd_terminat;
//        }
        
        u8_atcmd_status = AT_NON;
        if(myat_cmd3("AT+CSQ",1000) == 1);//Check Signal Quality
        while(!u8_atcmd_status);
        if(u8_atcmd_status == AT_ERROR)//error
        {
            u8_atcmd_status = AT_ERROR2;
            u8_gerrercode2 = 1;
//            goto cmd_terminat; 

        }
        u8_gerrercode2 = 0;
        
        u8_atcmd_status = AT_NON;
        if(myat_cmd3("AT+CMGF=1",1000) == 1);//at_cmd( "AT+CMGF=1" );
        while(!u8_atcmd_status);
        if(u8_atcmd_status != AT_OK)//error
        {
            u8_atcmd_status = AT_ERROR2;
//            goto cmd_terminat; 

        }

        u8_atcmd_status = AT_NON;
        if(myat_cmd3("AT+CNMI=2,1,0,0,0",1000) == 1);//at_cmd("AT+CNMI=2,1,0,0,0");
        while(!u8_atcmd_status);
        if(u8_atcmd_status != AT_OK)//error
        {
            u8_atcmd_status = AT_ERROR2;
//            goto cmd_terminat; 

        }

//        u8_atcmd_status = AT_NON;
//        if(myat_cmd("AT+CMGD=1,4",1000) == 1);//at_cmd("AT+CMGD=1,4");//Set SMS for Text format
//        while(!u8_atcmd_status);
//        if(u8_atcmd_status != AT_OK)//error
//        {
//            u8_atcmd_status = AT_ERROR2;
//            goto cmd_terminat; 
//
//        }
        
        u8_atcmd_status = AT_NON;
        if(myat_cmd3("AT+CMGD=1,3",1000) == 1);//at_cmd( "ATE0" );
        while(!u8_atcmd_status);
        if(u8_atcmd_status != AT_OK)//error
        {
            u8_atcmd_status = AT_ERROR2;
//                goto cmd_terminat;
        }

        u8_atcmd_status = AT_NON;
        if(myat_cmd3("AT+CMGL=\"ALL\"",3000) == 1);//at_cmd( "ATE0" );
//        printf("-------breakpt1\r\n"); 
        while(!u8_atcmd_status);
        if(u8_atcmd_status != AT_OK)//error
        {
            u8_atcmd_status = AT_ERROR2;
//                goto cmd_terminat;
        }
        u8_datasendEN =0;
        u8_atcmd_status = AT_NON;
        if(myat_cmd3("ATE0",1000) == 1);//at_cmd( "ATE0" );
        while(!u8_atcmd_status);
        if(u8_atcmd_status != AT_OK)//error
        {
            u8_atcmd_status = AT_ERROR2;
//            goto cmd_terminat;

        }
        
        SYSTICK_DelayMs(2000); 
//        gsm_gps_init();
//        printf("-------breakpt2\r\n"); 
}
/*****************************************************/
//void mydata_sendiot_commandmode(void)
//{
////    static uint8_t onlinemode = 0;
//    char msg[ 2024 ] = { 0 };
//    uint16_t n=0;
//    char tmp[ 2024 ] = { 0 };
//    if(onlinemode == 0)
//    {
//        if(newdataEN == 1)
//        {
//            memset(msg,0,sizeof(msg));
//            if(loadlivedata(&msg[0]) != true)
//            {
//                u8_atcmd_status = AT_SKIP;
//                goto cmd_terminat; 
//            }
//        }
//        else
//        { 
//            readnewmemloc(&rnewmemloc.addrbuf[0]);
//            readyet2sendmemloc(&ryet2sendmemloc.addrbuf[0]);
//            printf("\r\n rnewmemloc:%ld,\r\n ryet2sendmemloc:%ld,\r\n rnewmemloc.PacketField.flag:%d\r\n ",rnewmemloc.PacketField.memaddr,ryet2sendmemloc.PacketField.memaddr,rnewmemloc.PacketField.flag);
//            if(rnewmemloc.PacketField.flag == 0)
//            {
//                if((ryet2sendmemloc.PacketField.memaddr < (rnewmemloc.PacketField.memaddr ))&&(rnewmemloc.PacketField.memaddr  != 0))
//                {
//                    tempstartaddr = ryet2sendmemloc.PacketField.memaddr;
//
//                    u32_tempdiffaddr = rnewmemloc.PacketField.memaddr  - ryet2sendmemloc.PacketField.memaddr;
//                    if(u32_tempdiffaddr >=NOOFDATAPERPACKET_MEM)
//                    {
//                        u32_tempdiffaddr = NOOFDATAPERPACKET_MEM;
//                        tempendaddr = ryet2sendmemloc.PacketField.memaddr + NOOFDATAPERPACKET_MEM;
//                    }
//                    else
//                    {
//                        tempendaddr = ryet2sendmemloc.PacketField.memaddr + u32_tempdiffaddr;
//                    }
//
//                    memset(msg,0,sizeof(msg));
//                    if(loadmemorydata(tempstartaddr,tempendaddr,&msg[0]) != true)
//                    {
//                        u8_atcmd_status = AT_TERMINAT;
//                        goto cmd_terminat; 
//                    }              
//                }
//                else
//                {
//                    u8_atcmd_status = AT_TERMINAT;
//                    goto cmd_terminat;
//                }
//            }
//            else
//            {
//                if(ryet2sendmemloc.PacketField.memaddr < (MEM_LEN))
//                {
//                    tempstartaddr = ryet2sendmemloc.PacketField.memaddr;
//
//                    u32_tempdiffaddr = (MEM_LEN)  - ryet2sendmemloc.PacketField.memaddr;
//                    if(u32_tempdiffaddr >=NOOFDATAPERPACKET_MEM)
//                    {
//                        u32_tempdiffaddr = NOOFDATAPERPACKET_MEM;
//                        tempendaddr = ryet2sendmemloc.PacketField.memaddr + NOOFDATAPERPACKET_MEM;
//                    }
//                    else
//                    {
//                        tempendaddr = ryet2sendmemloc.PacketField.memaddr + u32_tempdiffaddr;
//                    }
//
//                    memset(msg,0,sizeof(msg));
//                    if(loadmemorydata(tempstartaddr,tempendaddr,&msg[0]) != true)
//                    {
//                        u8_atcmd_status = AT_TERMINAT;
//                        goto cmd_terminat; 
//                    }              
//                }
//                else
//                {
//                    u8_atcmd_status = AT_TERMINAT;
//                    goto cmd_terminat;
//                }
//            }
//        }
//        u8_atcmd_status = AT_NON;
//        if(myat_cmd("ATE0",1000) == 1);//at_cmd( "ATE0" );
//        while(!u8_atcmd_status);
//        if(u8_atcmd_status != AT_OK)//error
//        {
//            u8_atcmd_status = AT_ERROR2;
//            goto cmd_terminat;
//
//        }
//        
//        u8_atcmd_status = AT_NON;
//        if(myat_cmd("AT+CPIN?",1000) == 1);//at_cmd( "ATE0" );
//        while(!u8_atcmd_status);
//        if(u8_atcmd_status != AT_OK)//error
//        {
//            u8_atcmd_status = AT_ERROR2;
//            goto cmd_terminat;
//        }
//        u8_atcmd_status = AT_NON;
//        if(myat_cmd("AT+CSQ",1000) == 1);//Check Signal Quality
//        while(!u8_atcmd_status);
//        if(u8_atcmd_status == AT_ERROR)//error
//        {
//            u8_atcmd_status = AT_ERROR2;
//            u8_gerrercode2 = 1;
//            goto cmd_terminat; 
//
//        }
//        u8_gerrercode2 = 0;
//        
//        u8_atcmd_status = AT_NON;
//        if(myat_cmd("AT+CMGF=1",1000) == 1);//at_cmd( "AT+CMGF=1" );
//        while(!u8_atcmd_status);
//        if(u8_atcmd_status != AT_OK)//error
//        {
//            u8_atcmd_status = AT_ERROR2;
//            goto cmd_terminat; 
//
//        }
//
//        u8_atcmd_status = AT_NON;
//        if(myat_cmd("AT+CNMI=2,1,0,0,0",1000) == 1);//at_cmd("AT+CNMI=2,1,0,0,0");
//        while(!u8_atcmd_status);
//        if(u8_atcmd_status != AT_OK)//error
//        {
//            u8_atcmd_status = AT_ERROR2;
//            goto cmd_terminat; 
//
//        }
//
////        u8_atcmd_status = AT_NON;
////        if(myat_cmd("AT+CMGD=1,4",1000) == 1);//at_cmd("AT+CMGD=1,4");//Set SMS for Text format
////        while(!u8_atcmd_status);
////        if(u8_atcmd_status != AT_OK)//error
////        {
////            u8_atcmd_status = AT_ERROR2;
////            goto cmd_terminat; 
////
////        }
//        u8_atcmd_status = AT_NON;
//        if(myat_cmd("AT+CMGD=1,3",1000) == 1);//at_cmd( "ATE0" );
//        while(!u8_atcmd_status);
//        if(u8_atcmd_status != AT_OK)//error
//        {
//            u8_atcmd_status = AT_ERROR2;
//                goto cmd_terminat;
//        }
//
//        u8_atcmd_status = AT_NON;
//        if(myat_cmd("AT+CMGL=\"ALL\"",6000) == 1);//at_cmd( "ATE0" );
//        while(!u8_atcmd_status);
//        if(u8_atcmd_status != AT_OK)//error
//        {
//            u8_atcmd_status = AT_ERROR2;
//                goto cmd_terminat;
//        }
//
//        u8_atcmd_status = AT_NON;
//        if(myat_cmd("AT+CGSN",1000) == 1);//at_cmd("AT+CGSN");// SSet the parameters for an outgoing message with 24 hours of validity period and default properties:
//        while(!u8_atcmd_status);
//        if(u8_atcmd_status != AT_OK)//error
//        {
//            u8_atcmd_status = AT_ERROR2;
//            goto cmd_terminat; 
//
//        } 
//
//        u8_atcmd_status = AT_NON;
////        if(myat_cmd("AT+CGDCONT=1,\"IP\",\"airtelgprs.com\",\"0.0.0.0\",0,0",1000) == 1);//at_cmd("AT+CGDCONT=1,\"IP\",\"airtelgprs.com\",\"0.0.0.0\",0,0");//Define PDP context:
//////        if(myat_cmd("AT+CGDCONT=1,\"IP\",\"LTCEL\",\"0.0.0.0\",0,0",1000) == 1);
//        if(SERVERTO == SERVER_LT)
//        {
//            if(myat_cmd("AT+CGDCONT=1,\"IP\",\"LTCEL\",\"0.0.0.0\",0,0",1000) == 1);
//            
//        }
//        else
//        {
//            if(myat_cmd("AT+CGDCONT=1,\"IP\",\"airtelgprs.com\",\"0.0.0.0\",0,0",1000) == 1);//at_cmd("AT+CGDCONT=1,\"IP\",\"airtelgprs.com\",\"0.0.0.0\",0,0");//Define PDP context:
//        }
//        while(!u8_atcmd_status);
//        if(u8_atcmd_status != AT_OK)//error
//        {
//            u8_atcmd_status = AT_ERROR2;
//            goto cmd_terminat; 
//
//        } 
//
//        u8_atcmd_status = AT_NON;
//        if(myat_cmd("AT+CMEE=2",1000) == 1);// Enable ERROR report in verbose format.
//        while(!u8_atcmd_status);
//        if(u8_atcmd_status != AT_OK)//error
//        {
//            u8_atcmd_status = AT_ERROR2;
//            goto cmd_terminat; 
//        } 
//        u8_atcmd_status = AT_NON;
//        if(myat_cmd("AT+CGACT=1,1",1000) == 1);//at_cmd("AT+CGACT=1,1");                   // 
//        while(!u8_atcmd_status);
//        if(u8_atcmd_status != AT_OK)//error
//        {
//            u8_atcmd_status = AT_ERROR2;
//            goto cmd_terminat; 
//        } 
//        u8_atcmd_status = AT_NON;
//        if(myat_cmd("AT+CGPADDR=1",1000) == 1);//at_cmd("AT+CGPADDR=1");                   //    
//        while(!u8_atcmd_status);
//        if(u8_atcmd_status != AT_OK)//error
//        {
//            u8_atcmd_status = AT_ERROR2;
//            goto cmd_terminat; 
//        }
//        u8_atcmd_status = AT_NON;
//        //Activate <cid>=1: AT#SGACT=1,1
//        if(myat_cmd("AT#SGACT=1,1",1000) == 1);//AT#SGACT=<cid>,1 activates the PDP context identified by the <cid>,
//        while(!u8_atcmd_status);
//        if(u8_atcmd_status == AT_ERROR)//error
//        {
//            u8_atcmd_status = AT_ERROR2;
//            goto cmd_terminat; 
//        } 
//        u8_atcmd_status = AT_NON;
//        if(myat_cmd("AT+CREG?",1000) == 1);//at_cmd("AT+CREG?");                   //
//        while(!u8_atcmd_status);
//        if(u8_atcmd_status != AT_OK)//error
//        {
//            u8_atcmd_status = AT_ERROR2;
//            goto cmd_terminat; 
//        }
//        u8_atcmd_status = AT_NON;
//        if(myat_cmd("AT#SS",2000) == 1);//at_cmd("AT#SS");//Checking the socket status with #SS
//        while(!u8_atcmd_status);
//
//        u8_atcmd_status = AT_NON;
//        if(myat_cmd("AT#SS",6000) == 1);//at_cmd("AT#SS");//Checking the socket status with #SS
//        while(!u8_atcmd_status){;}
//        if(u8_atcmd_status == AT_SS1)
//            u8_SSid = 1;
//        else if(u8_atcmd_status == AT_SS2)
//            u8_SSid = 2;
//        else if(u8_atcmd_status == AT_SS3)
//            u8_SSid = 3;
//        else if(u8_atcmd_status == AT_SS4)
//            u8_SSid = 4;
//        else if(u8_atcmd_status == AT_SS5)
//            u8_SSid = 5;
//        else if(u8_atcmd_status == AT_SS6)
//            u8_SSid = 6;
//        else
//        {
//            u8_atcmd_status = AT_ERROR2;
//            goto cmd_terminat; 
//        }
//
//        u8_atcmd_status = AT_NON;
//        memset(tmp, 0x00, sizeof(tmp));
//////        sprintf(tmp,"AT#SD=%d,0,1011,\"49.206.26.81\",0,0,1",u8_SSid);
////        sprintf(tmp,"AT#SD=%d,0,1011,\"49.206.26.81\",0,0,1",u8_SSid);
//////        sprintf(tmp,"AT#SD=%d,0,5000,\"104.211.74.190\",0,0,1",u8_SSid);
//        if(SERVERTO == SERVER_LT)
//        {
//            sprintf(tmp,"AT#SD=%d,0,5000,\"104.211.74.190\",0,0,1",u8_SSid);
//        }
//        else if(SERVERTO == SERVER_1012)
//        {
//            sprintf(tmp,"AT#SD=%d,0,1012,\"49.206.26.81\",0,0,1",u8_SSid);
//        }
//        else
//        {
//            sprintf(tmp,"AT#SD=%d,0,1011,\"49.206.26.81\",0,0,1",u8_SSid);
//        }
//        if(myat_cmd(tmp,16000) == 1);//Opening a socket connection in command mode
//        while(!u8_atcmd_status);
//        if(u8_atcmd_status != AT_OK)//not ok
//        {
//            u8_atcmd_status = AT_ERROR2;
//            goto cmd_terminat;    
//        } 
//        u8_atcmd_status = AT_NON;
//        memset(tmp, 0x00, sizeof(tmp));
//        sprintf(tmp,"AT#SSEND=%d",u8_SSid);
////        if(myat_cmd("AT#SSEND=2",5000) == 1);//at_cmd("AT#SSEND=2");                   // sms text
//        if(myat_cmd(tmp,10000) == 1);//at_cmd("AT#SSEND=2"); 
//        while(!u8_atcmd_status);
//        if(u8_atcmd_status != AT_DATASEND)//error
//        {
//            u8_atcmd_status = AT_ERROR2;
//            goto cmd_terminat; 
//        }
//    }
//    else
//    {
//        if(newdataEN == 1)
//        {
//            memset(msg,0,sizeof(msg));
//            if(loadlivedata(&msg[0]) != true)
//            {
//                u8_atcmd_status = AT_SKIP;
//                goto cmd_terminat; 
//            }
//        }
//        else
//        {
//            readnewmemloc(&rnewmemloc.addrbuf[0]);
//            readyet2sendmemloc(&ryet2sendmemloc.addrbuf[0]);
//            printf("\r\n rnewmemloc:%ld,\r\n ryet2sendmemloc:%ld,\r\n rnewmemloc.PacketField.flag:%d\r\n ",rnewmemloc.PacketField.memaddr,ryet2sendmemloc.PacketField.memaddr,rnewmemloc.PacketField.flag);
//            if(rnewmemloc.PacketField.flag == 0)
//            {
//                if((ryet2sendmemloc.PacketField.memaddr < (rnewmemloc.PacketField.memaddr ))&&(rnewmemloc.PacketField.memaddr  != 0))
//                {
//                    tempstartaddr = ryet2sendmemloc.PacketField.memaddr;
//
//                    u32_tempdiffaddr = rnewmemloc.PacketField.memaddr  - ryet2sendmemloc.PacketField.memaddr;
//                    if(u32_tempdiffaddr >=NOOFDATAPERPACKET_MEM)
//                    {
//                        u32_tempdiffaddr = NOOFDATAPERPACKET_MEM;
//                        tempendaddr = ryet2sendmemloc.PacketField.memaddr + NOOFDATAPERPACKET_MEM;
//                    }
//                    else
//                    {
//                        tempendaddr = ryet2sendmemloc.PacketField.memaddr + u32_tempdiffaddr;
//                    }
//
//                    memset(msg,0,sizeof(msg));
//                    if(loadmemorydata(tempstartaddr,tempendaddr,&msg[0]) != true)
//                    {
//                        u8_atcmd_status = AT_TERMINAT;
//                        goto cmd_terminat; 
//                    }              
//                }
//                else
//                {
//                    u8_atcmd_status = AT_TERMINAT;
//                    goto cmd_terminat;
//                }
//            }
//            else
//            {
//                if(ryet2sendmemloc.PacketField.memaddr < (MEM_LEN))
//                {
//                    tempstartaddr = ryet2sendmemloc.PacketField.memaddr;
//
//                    u32_tempdiffaddr = (MEM_LEN)  - ryet2sendmemloc.PacketField.memaddr;
//                    if(u32_tempdiffaddr >=NOOFDATAPERPACKET_MEM)
//                    {
//                        u32_tempdiffaddr = NOOFDATAPERPACKET_MEM;
//                        tempendaddr = ryet2sendmemloc.PacketField.memaddr + NOOFDATAPERPACKET_MEM;
//                    }
//                    else
//                    {
//                        tempendaddr = ryet2sendmemloc.PacketField.memaddr + u32_tempdiffaddr;
//                    }
//
//                    memset(msg,0,sizeof(msg));
//                    if(loadmemorydata(tempstartaddr,tempendaddr,&msg[0]) != true)
//                    {
//                        u8_atcmd_status = AT_TERMINAT;
//                        goto cmd_terminat; 
//                    }              
//                }
//                else
//                {
//                    u8_atcmd_status = AT_TERMINAT;
//                    goto cmd_terminat;
//                }
//            }
//        }
//        u8_atcmd_status = AT_NON;
//        if(myat_cmd("AT#SSEND=2",5000) == 1);//at_cmd("AT#SSEND=2");                   // sms text
//        //SYSTICK_DelayMs(1000);
//        while(!u8_atcmd_status);
//        if(u8_atcmd_status != AT_DATASEND)//error
//        {
//            u8_atcmd_status = AT_ERROR2;
//            goto cmd_terminat; 
//        }
//    }
//    u8_datasendEN = 1;
//    n = strlen(msg);
//    msg[n]=26;//msg[n-1]=26;
//    if(myat_cmd(msg,10000) == 1);//at_cmd_addition( msg ); 
//    while(!u8_atcmd_status);
//    if(u8_atcmd_status != AT_OK)//error//if(u8_atcmd_status == AT_ERROR)//error
//    {
//        u8_atcmd_status = AT_ERROR2;
//        goto cmd_terminat;         
//    }
//    u8_datasendEN = 0;    
//    cmd_terminat: 
//    { 
//        if(u8_atcmd_status ==  AT_SKIP )
//        {
//            u8_atcmd_status = AT_NON; 
////            readsms();
//        }
//        else if(u8_atcmd_status == AT_TERMINAT)
//        { 
//            onlinemode = 0;
//            printf("cmd_terminat:AT_TERMINAT..\r\n"); 
////            readsms();
//        }
//        else if(u8_atcmd_status == AT_ERROR2)
//        {
//            if(newdataEN==1)
//            {
//                saveunsenddata(&logwdata.rcvpacket[0]);
//            }
//            printf("cmd_terminat:timedouted so gsm initializing..\r\n");
//            GSM_RST_PA05_Set();
//            SYSTICK_DelayMs(300);
//            GSM_RST_PA05_Clear();
//            SYSTICK_DelayMs(1000);
//            gsm_gps_init();
//            onlinemode = 0;
//            newdataEN = 0;
//            
//        }       
//        else
//        {
//            uint_datasentcount++;
//            if(newdataEN == 1)
//            {
//                printf("Live data send successfully....\r\n");
//                newdataEN = 0;
//                freshdatamemloc.PacketField.memaddr = 0;
//                savefreshdatamemloc(&freshdatamemloc.addrbuf[0]);
//            }
//            else
//            {
////                printf("Memory =%ld , data send successfully....\r\n",ryet2sendmemloc.PacketField.memaddr);  
//                wyet2sendmemloc.PacketField.memaddr = tempendaddr;
//                if(wyet2sendmemloc.PacketField.memaddr >= MEM_LEN)
//                {
//                    wyet2sendmemloc.PacketField.memaddr = 0;
//                    readnewmemloc(&rnewmemloc.addrbuf[0]);
//                    rnewmemloc.PacketField.flag = 0;
//                    savenewmemloc(&rnewmemloc.addrbuf[0]); 
//                }
//                saveyet2sendmemloc(&wyet2sendmemloc.addrbuf[0]);
//                printf("Memory data from =%ld  to  %ld sent successfully....\r\n",ryet2sendmemloc.PacketField.memaddr,tempendaddr);
//            }
////            onlinemode = 1;//disable online mode
//            u8_atcmd_status = AT_NON;
//            if(myat_cmd("AT#SI",2000) == 1)//;//at_cmd("AT#SSEND=2");                   // sms text
//            while(!u8_atcmd_status);     
//        }      
//    }
//     //SYSTICK_DelayMs(2000);   
//}
//void mygsm_act_sendthinkspeak_info (void)
//{
//    char msg[ 1024 ] = { 0 };
//    uint16_t n=0;
//    static int count = 0;
//        //MYCODE2
//    u8_atcmd_status = AT_NON;
//    if(myat_cmd("ATE0",1000) == 1);//at_cmd( "ATE0" );
//    while(!u8_atcmd_status);
//    if(u8_atcmd_status != AT_OK)//error
//    {
//        u8_atcmd_status = AT_ERROR2;
//        goto cmd_terminat;
//        
//    }
//    
//    u8_atcmd_status = AT_NON;
//    if(myat_cmd("AT+CSQ",1000) == 1);//at_cmd( "AT+CSQ" );
//    while(!u8_atcmd_status);
//    if(u8_atcmd_status == AT_ERROR)//error
//    {
//        u8_atcmd_status = AT_ERROR2;
//        goto cmd_terminat; 
//        
//    }
//    
//    u8_atcmd_status = AT_NON;
//    if(myat_cmd("AT+CMGF=1",1000) == 1);//at_cmd( "AT+CMGF=1" );
//    while(!u8_atcmd_status);
//    if(u8_atcmd_status != AT_OK)//error
//    {
//        u8_atcmd_status = AT_ERROR2;
//        goto cmd_terminat; 
//        
//    }
//    
//    u8_atcmd_status = AT_NON;
//    if(myat_cmd("AT+CNMI=2,1,0,0,0",1000) == 1);//at_cmd("AT+CNMI=2,1,0,0,0");
//    while(!u8_atcmd_status);
//    if(u8_atcmd_status != AT_OK)//error
//    {
//        u8_atcmd_status = AT_ERROR2;
//        goto cmd_terminat; 
//        
//    }
//    
//    u8_atcmd_status = AT_NON;
//    if(myat_cmd("AT+CMGD=1,4",1000) == 1);//at_cmd("AT+CMGD=1,4");//Set SMS for Text format
//    while(!u8_atcmd_status);
//    if(u8_atcmd_status != AT_OK)//error
//    {
//        u8_atcmd_status = AT_ERROR2;
//        goto cmd_terminat; 
//        
//    }
//    
//    u8_atcmd_status = AT_NON;
//    if(myat_cmd("AT+CGSN",1000) == 1);//at_cmd("AT+CGSN");// SSet the parameters for an outgoing message with 24 hours of validity period and default properties:
//    while(!u8_atcmd_status);
//    if(u8_atcmd_status != AT_OK)//error
//    {
//        u8_atcmd_status = AT_ERROR2;
//        goto cmd_terminat; 
//        
//    } 
//    
//    u8_atcmd_status = AT_NON;
//    if(myat_cmd("AT+CGDCONT=1,\"IP\",\"airtelgprs.com\",\"0.0.0.0\",0,0",1000) == 1);//at_cmd("AT+CGDCONT=1,\"IP\",\"airtelgprs.com\",\"0.0.0.0\",0,0");//Define PDP context:
//    while(!u8_atcmd_status);
//    if(u8_atcmd_status != AT_OK)//error
//    {
//        u8_atcmd_status = AT_ERROR2;
//        goto cmd_terminat; 
//        
//    } 
//    
//    u8_atcmd_status = AT_NON;
//    if(myat_cmd("AT+CMEE=2",1000) == 1);//at_cmd("AT+CMEE=2");// Execution command sends to the network a message
//    while(!u8_atcmd_status);
//    if(u8_atcmd_status != AT_OK)//error
//    {
//        u8_atcmd_status = AT_ERROR2;
//        goto cmd_terminat; 
//        
//    } 
//    
//    u8_atcmd_status = AT_NON;
//    if(myat_cmd("AT+CGACT=1,1",1000) == 1);//at_cmd("AT+CGACT=1,1");                   // 
//    while(!u8_atcmd_status);
//    if(u8_atcmd_status != AT_OK)//error
//    {
//        u8_atcmd_status = AT_ERROR2;
//        goto cmd_terminat; 
//        
//    } 
//    
//    u8_atcmd_status = AT_NON;
//    if(myat_cmd("AT+CGPADDR=1",1000) == 1);//at_cmd("AT+CGPADDR=1");                   //    
//    while(!u8_atcmd_status);
//    if(u8_atcmd_status != AT_OK)//error
//    {
//        u8_atcmd_status = AT_ERROR2;
//        goto cmd_terminat; 
//        
//    }
//    
//    u8_atcmd_status = AT_NON;
//    if(myat_cmd("AT#SGACT=1,1",1000) == 1);//at_cmd("AT#SGACT=1,1");//Context Activation, as response gives IP of the module:
//    while(!u8_atcmd_status);
//    if(u8_atcmd_status == AT_ERROR)//error
//    {
//        u8_atcmd_status = AT_ERROR2;
//        goto cmd_terminat; 
//        
//    } 
//    
//    u8_atcmd_status = AT_NON;
//    if(myat_cmd("AT+CREG?",1000) == 1);//at_cmd("AT+CREG?");                   //
//    while(!u8_atcmd_status);
//    if(u8_atcmd_status != AT_OK)//error
//    {
//        u8_atcmd_status = AT_ERROR2;
//        goto cmd_terminat; 
//        
//    }
//    
//    u8_atcmd_status = AT_NON;
//    if(myat_cmd("AT#SS",1000) == 1);//at_cmd("AT#SS");//Checking the socket status with #SS
//    while(!u8_atcmd_status);
//    if(u8_atcmd_status != AT_OK)//error
//    {
//        u8_atcmd_status = AT_ERROR2;
//        goto cmd_terminat; 
//        
//    }
//    
//    u8_atcmd_status = AT_NON;
//    if(myat_cmd("AT#SS",1000) == 1);//at_cmd("AT#SS");//Checking the socket status with #SS
//    while(!u8_atcmd_status);
//    if(u8_atcmd_status != AT_OK)//error
//    {
//        u8_atcmd_status = AT_ERROR2;
//        goto cmd_terminat; 
//        
//    }
//    
//    u8_atcmd_status = AT_NON;
//    if(myat_cmd("AT#SS",1000) == 1);//at_cmd("AT#SS");//Checking the socket status with #SS
//    while(!u8_atcmd_status);
//    if(u8_atcmd_status != AT_OK)//error
//    {
//        u8_atcmd_status = AT_ERROR2;
//        goto cmd_terminat; 
//        
//    }
//    
//    u8_atcmd_status = AT_NON;
//    if(myat_cmd("AT#SGACT=1,0",1000) == 1);//at_cmd("AT#SS");//Checking the socket status with #SS
//    while(!u8_atcmd_status);
//    if(u8_atcmd_status == AT_ERROR)//error
//    {
//        u8_atcmd_status = AT_ERROR2;
//        goto cmd_terminat; 
//        
//    }
//    
//    u8_atcmd_status = AT_NON;
//    if(myat_cmd("AT#CPUMODE=2",1000) == 1);//at_cmd("AT#SS");//Checking the socket status with #SS
//    while(!u8_atcmd_status);
//    if(u8_atcmd_status == AT_ERROR)//error
//    {
//        u8_atcmd_status = AT_ERROR2;
//        goto cmd_terminat; 
//        
//    }
//    
//    u8_atcmd_status = AT_NON;
//    if(myat_cmd("AT#SGACT=1,1",1000) == 1);//at_cmd("AT#SS");//Checking the socket status with #SS
//    while(!u8_atcmd_status);
//    if(u8_atcmd_status == AT_ERROR)//error
//    {
//        u8_atcmd_status = AT_ERROR2;
//        goto cmd_terminat; 
//        
//    }
//    
//    u8_atcmd_status = AT_NON;
//    if(myat_cmd("AT#SSLEN=1,1",1000) == 1);//at_cmd("AT#SS");//Checking the socket status with #SS
//    while(!u8_atcmd_status);
//    if(u8_atcmd_status == AT_ERROR)//error
//    {
//        u8_atcmd_status = AT_ERROR2;
//        goto cmd_terminat; 
//        
//    }
//    
//    u8_atcmd_status = AT_NON;
//    if(myat_cmd("AT#SSLCFG=1,1,300,90,100,50,0,0,0,0",1000) == 1);//at_cmd("AT#SS");//Checking the socket status with #SS
//    while(!u8_atcmd_status);
//    if(u8_atcmd_status == AT_ERROR)//error
//    {
//        u8_atcmd_status = AT_ERROR2;
//        goto cmd_terminat; 
//        
//    }
//    
//    u8_atcmd_status = AT_NON;
//    if(myat_cmd("AT#SSLSECCFG=1,0,0",1000) == 1);//at_cmd("AT#SS");//Checking the socket status with #SS
//    while(!u8_atcmd_status);
//    if(u8_atcmd_status == AT_ERROR)//error
//    {
//        u8_atcmd_status = AT_ERROR2;
//        goto cmd_terminat; 
//        
//    }
//    
//    u8_atcmd_status = AT_NON;
//   // if(myat_cmd("AT#SD=1,0,80,\"api.thingspeak.com\",0,0,0",16000) == 1);//at_cmd("AT#SS");//Checking the socket status with #SS
//    if(myat_cmd("AT#SD=1,0,80,\"manumr.000webhostapp.com\",0,0,0",5000) == 1);
//    while(!u8_atcmd_status);
//    if(u8_atcmd_status == AT_ERROR)//error
//    {
//        u8_atcmd_status = AT_ERROR2;
//        goto cmd_terminat; 
//        
//    }
//    
//    u8_atcmd_status = AT_NON;
//   // sprintf(msg,"d1-%d:&V000001,001001,101,0102211345,N1305.1572,E07733.3395,27.8,97.3,99.9,13.9,200000,01.2,12.2,07.2,255,000.0,000.0,000.0,000.0^",count);
//    memset(msg, 0x00, sizeof(msg));
//    // sprintf(Nbuff1, "GET https://api.thingspeak.com/update?api_key=9R9O57O4TP6T2XZL&field1=%s&field2=%s&field3=%s&field4=%s",temperatur1,temperatur3,temperatur2,hummidity2);
////    sprintf(Nbuff1, "GET https://api.thingspeak.com/update?api_key=BA1HY7U23B4Y4WGW&field1=%s&field2=%s&field3=%s&field4=%s&field5=%s&field6=%s",temperatur1,hummidity1,temperatur2,hummidity2,temperatur3,hummidity3);
//    /*************************/
//    //sprintf(msg, "GET https://api.thingspeak.com/update?api_key=BA1HY7U23B4Y4WGW&field1=27&field2=67&field3=26&field4=68&field5=27&field6=70");
//    /////////////////
//    //sprintf(msg, "GET https://manumr.000webhostapp.com/api/smartfarm/insert.php?SerialNo=0001&Gatewayid=1001&NodeNo=101&DateTime=0102211345&latitude=N1305.1572&longitude=E07733.3395&Ambitemp=27.8&Humidity=97.3&Moisture=99.9&pH=13.9&lightIntensity=200000&RainFall=01.2&Gatebatvoltage=12.2&Nodebatvoltage=07.2&Para1=255&Para2=255&Para3=255&Para4=255&Para5=255 HTTP/1.1\r\nHost: manumr.000webhostapp.com\r\nConnection: close\r\n\r\n");
//    sprintf(msg, "GET /api/smartfarm/insert.php?SerialNo=0001&Gatewayid=1001&NodeNo=101&DateTime=0102211345&latitude=N1305.1572&longitude=E07733.3395&Ambitemp=27.8&Humidity=97.3&Moisture=99.9&pH=13.9&lightIntensity=200000&RainFall=01.2&Gatebatvoltage=12.2&Nodebatvoltage=07.2&Para1=255&Para2=255&Para3=255&Para4=255&Para5=255 HTTP/1.1\r\nHost: manumr.000webhostapp.com\r\nConnection: close\r\n\r\n");
//    
//    //////////////
//    //sprintf(msg, "GET https://manumr.000webhostapp.com/api/smartfarm/insert.php?SerialNo=0001&Gatewayid=1001&NodeNo=101&DateTime=0102211345&latitude=N1305.1572&longitude=E07733.3395&Ambitemp=27.8&Humidity=97.3&Moisture=99.9&pH=13.9&lightIntensity=200000&RainFall=01.2&Gatebatvoltage=12.2&Nodebatvoltage=07.2&Para1=255&Para2=255&Para3=255&Para4=255&Para5=255");
//    
//    /*********************************/
//    n = strlen(msg);
//    msg[n]=26;//msg[n-1]=26;
//    if(myat_cmd(msg,20000) == 1);//at_cmd_addition( msg ); 
//    while(!u8_atcmd_status);
//    if(u8_atcmd_status == AT_ERROR)//error//if(u8_atcmd_status == AT_ERROR)//error
//    {
//        u8_atcmd_status = AT_ERROR2;
//        goto cmd_terminat;    
//    } 
//    
////    SYSTICK_DelayMs(1000);
//    
//    
//    cmd_terminat: 
//    {
//        if(u8_atcmd_status == AT_ERROR2)
//        {
//            printf("cmd_terminat:timedouted so gsm initializing..\r\n");
//            GSM_RST_PA05_Set();
//            SYSTICK_DelayMs(300);
//            GSM_RST_PA05_Clear();
//            SYSTICK_DelayMs(1000);
//            gsm_gps_init();
//        }
//        
//        else
//        {
//            count++;
////            gsm_gps_init();
//        }
//            
//    }
//     SYSTICK_DelayMs(200);   
//}
//void gsm_act_sendsms_info (void)
//{
//    char msg[ 700 ] = { 0 };
//    char tmp[ 60 ] = { 0 };
//    uint16_t n=0;
//    static int count = 0;
//        //MYCODE2
//    u8_atcmd_status = AT_NON;
//    myat_cmd( "ATE0" ,1000);
//    while(!u8_atcmd_status);
//    if(u8_atcmd_status != AT_OK)//error
//    {
//        goto cmd_terminat;
//        u8_atcmd_status = AT_ERROR2;
//    }
//    
//    u8_atcmd_status = AT_NON;
//    myat_cmd( "AT+GMI" ,1000);
//    while(!u8_atcmd_status);
//    if(u8_atcmd_status == AT_ERROR)//error
//    {
//        goto cmd_terminat; 
//        u8_atcmd_status = AT_ERROR2;
//    }
//    
//    u8_atcmd_status = AT_NON;
//    myat_cmd( "AT+CREG=0,1" ,1000);
//    while(!u8_atcmd_status);
//    if(u8_atcmd_status != AT_OK)//error
//    {
//        goto cmd_terminat; 
//        u8_atcmd_status = AT_ERROR2;
//    }
//    
//    u8_atcmd_status = AT_NON;
//    myat_cmd("AT+CMGF=1",1000);
//    while(!u8_atcmd_status);
//    if(u8_atcmd_status != AT_OK)//error
//    {
//        goto cmd_terminat; 
//        u8_atcmd_status = AT_ERROR2;
//    }
//    
//    u8_atcmd_status = AT_NON;
//    myat_cmd("AT+CSMP=17,167,2,0",1000);//Set SMS for Text format
//    while(!u8_atcmd_status);
//    if(u8_atcmd_status != AT_OK)//error
//    {
//        goto cmd_terminat; 
//        u8_atcmd_status = AT_ERROR2;
//    }
//    
//    u8_atcmd_status = AT_NON;
//    myat_cmd("AT+CSCS=\"GSM\"",1000);// SSet the parameters for an outgoing message with 24 hours of validity period and default properties:
//    while(!u8_atcmd_status);
//    if(u8_atcmd_status != AT_OK)//error
//    {
//        goto cmd_terminat; 
//        u8_atcmd_status = AT_ERROR2;
//    } 
//    
//    u8_atcmd_status = AT_NON;
//    memset(tmp, 0x00, sizeof(tmp));
//    sprintf(tmp,"AT+CMGS=\"%s\"",M_MOBILE_NUMBER);
//    
//    myat_cmd(tmp,5000);// SSet the parameters for an outgoing message with 24 hours of validity period and default properties:
//    while(!u8_atcmd_status);
//    if(u8_atcmd_status == AT_ERROR)//error
//    {
//        goto cmd_terminat; 
//        u8_atcmd_status = AT_ERROR2;
//    } 
//    
//    u8_atcmd_status = AT_NON;
//    strcpy( latitude, gps_Latitude_dec);//"13.085675" );
//    strcpy( longitude, gps_Longitude_dec);//"77.55531667" );
//    
//    sprintf(msg,"\r\n my location is: https://maps.google.com/maps?q=%s,%s\r\n",latitude,longitude);
//    n = strlen(msg);
//    msg[n]=26;//msg[n-1]=26;
//    myat_cmd( msg ,5000); 
//    while(!u8_atcmd_status);
//    if(u8_atcmd_status == AT_ERROR)//error
//    {
//        goto cmd_terminat; 
//        u8_atcmd_status = AT_ERROR2;
//    } 
//    
////    SYSTICK_DelayMs(1000);
//    
//    
//    cmd_terminat: 
//    {
//        if(u8_atcmd_status == AT_ERROR2)
//        {
//            printf("cmd_terminat:timedouted so gsm initializing..\r\n");
////            GSM_RST_PA05_Set();
////            SYSTICK_DelayMs(300);
////            GSM_RST_PA05_Clear();
////            SYSTICK_DelayMs(1000);
//        }
//        
//        else
//        {
//            count++;
//        }
//            
//    }
//     SYSTICK_DelayMs(200);   
//}
void gsm_manualAT_info (char *at_msg)
{
    //at_cmd(at_msg);
    myat_cmd(at_msg,1000);
}
void gps_act_pwr_control (bool state)
{
    if( state )
    {
        at_cmd( "AT+CGNSPWR=1" );
    }
    else
        at_cmd( "AT+CGNSPWR=0" );
}

void gsm_gps_task (void)
{
    at_process();
    
//    if (loc_update_f) 
//    {
//        //at_cmd( "AT" );
//        at_cmd( "AT+CGNSINF" );       
//        loc_update_f = false;
//    }    
    
  
    if (req_pend_f) 
    {
        SYSTICK_DelayMs(50); 

        //mygsm_act_sendiot_info();
        if(SENDIOTMODE == ONLINE)
        {
            mydata_sendiot_onlinemode();//onlinemode     
        }
        else
        {
            mydata_sendiot_commandmode();//commandmode
        }
        req_pend_f = false; 
        SYSTICK_DelayMs(100); 
        //at_cmd("AT");
//        printf("-------------------INFO--------------------------");
//        printf("\r\nLong press switch to configure phone number or \r\nShort press to send SMS\r\n");
        printf("-------------------------2-----------------------\r\n");
//        gsm_sms_task ();
//        LED_Clear();
    }
}
void gsm_sms_task (void)
{
    at_process();
    
//    if (loc_update_f) 
//    {
//        //at_cmd( "AT" );
//        at_cmd( "AT+CGNSINF" );       
//        loc_update_f = false;
//    }    
    
  
    if (req_pend_f) 
    {
        SYSTICK_DelayMs(50); 
        readsms();
        //mygsm_act_sendiot_info();
        if(SENDIOTMODE == ONLINE)
        {
//            mydata_sendiot_onlinemode();//onlinemode   
            
        }
        else
        {
//            mydata_sendiot_commandmode();//commandmode
        }
        req_pend_f = false; 
        SYSTICK_DelayMs(100); 
        //at_cmd("AT");
//        printf("-------------------INFO--------------------------");
//        printf("\r\nLong press switch to configure phone number or \r\nShort press to send SMS\r\n");
        printf("-------------------------1-----------------------\r\n");
        
//        LED_Clear();
    }
}
void gps_evn_location (char *response )
{
    char* end;
    end = strchr( response + 66, ',' );

    if(end != NULL)
    {
        if( *( end - 1 ) != ',' )
        {
            my_strncpy( latitude, response + 46, 9 );
            my_strncpy( longitude, response + 56, 9 );
            my_strncpy( altitude, response + 66, end - ( response + 66 ) );
            latt = atol( latitude );
            lonn = atol( longitude );    
            altt = atol( altitude );           
            if(latt <= 0 ||  lonn <= 0 || altt <= 0)
            {
                loc_update_f = true;
            }
            else
            {
                req_pend_f = true;
                latt = -1;
                lonn = -1;
                altt = -1;
            }
        }
        else 
        {   
            strcpy( latitude, "NA" );
            strcpy( longitude, "NA" );
            strcpy( altitude, "NA" );
            loc_update_f = true;
        }
    }
    else
    {
        loc_update_f = true;
    }
}

/*************** END OF FUNCTIONS *********************************************/