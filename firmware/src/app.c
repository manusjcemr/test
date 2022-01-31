/****************************************************************************
* Title                 :   Location tagged SOS Application
* Filename              :   app.c
* Author                :   ST
* Origin Date           :   15/08/2018
* Notes                 :   None
*****************************************************************************/
/**************************CHANGE LIST **************************************
*
*    Date    Software Version    Initials   Description
*  15/02/18        1.0.0           ST       App Created. 
 * 01/01/2020      2.0.0           MK       App Modified.
*****************************************************************************/
/****************************************************************************
* Note: In version 2.00, This file has been modified by MK to meet the custom 
* application requirements. Should you need to contact the modifier, Write an 
* Email to mohan.kumar@microchip.com or alternatively, write to 
* Mohan Kumar, Microchip Technology India Pvt Ltd
* Plot No. 1498, EPIP, 1st Phase Industrial Area, Whitefield, Bengaluru, 
* Karnataka 560066
* Note: In version 1.00, This file has been modified by ST to meet the custom 
* application requirements. Should you need to contact the modifier, Write an 
* Email to syed.thaseemuddin@microchip.com or alternatively, write to 
* Syed Thaseemuddin, Microchip Technology India Pvt Ltd
* Plot No. 1498, EPIP, 1st Phase Industrial Area, Whitefield, Bengaluru, 
* Karnataka 560066
*******************************************************************************/
/**
 * @file app.c
 * @brief Location tagged SOS App
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


// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "app.h"
#include "dev_hal.h"
#include "dev_adapter.h"
#include "driver/usart/drv_usart.h"
#include "gsm_gps.h"
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
    This structure should be initialized by the APP_Initialize function.

    Application strings and buffers are be defined outside this structure.
*/

APP_DATA appData;
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
static void _APP_BUTTON_PRESS_Tasks(void);
//static void _APP_TimerTickHandler ( uintptr_t context, uint32_t currTick );
static void _APP_UART_ReceiveCallback(    DRV_USART_BUFFER_EVENT bufferEvent,
    DRV_USART_BUFFER_HANDLE bufferHandle,
    uintptr_t context);
/* TODO:  Add any necessary local functions.
*/
extern void gsm_gps_task();
extern void dev_tick_isr();
extern void gsm_gps_init(void);
extern void dev_rx(char);
uint8_t new_gpsdataset=0;
// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************
const uint8_t nvm_user_start_address[NVMCTRL_FLASH_ROWSIZE] __attribute__((aligned(NVMCTRL_FLASH_ROWSIZE),keep,externally_visible,space(prog)))= {0};
char manual_ATcmm[50] = {0};  
volatile uint16_t u16_loopcounter=0,u16_loopof1sec=0;
extern bool req_pend_f;
extern bool loc_update_f;
bool updated_phn_num = 0;

bool b_IgnitionON = 0;
bool b_speare1 = 0;
bool  b_Hydraulicoilfilterclog = 0;
bool b_airfiltercool = 0;
bool b_LubeOilPressure = 0;
bool b_highenginteperature = 0;
bool b_speare2 = 0;
bool b_speare3 = 0;

volatile bool bl_pulsevalidestate=0;
volatile uint32_t u32_pulsecunt =0,u32_watchdogtimercnt=0;
float low_pass_filter(float x);
uint16_t uint_frq = 0,uint_avgfrqcnt = 0;
float flt_avgfrq=0;
uint8_t newdataEN1 = 0,newdataEN2 = 0,newdataupdated =0,u8_newdataset1 =0,u8_newdataset2 =0; 
uint8_t uchr_pastMin = 0;

uint8_t u8_gerrercode1 =0,u8_gerrercode2 =0,u8_gerrercode3 =0;
uint16_t u16_gerrercode1blkcnt =0,u16_gerrercode2blkcnt =0,u16_gerrercode3blkcnt =0;
extern uint8_t onlinemode;

extern void can_recdata(void);
uint8_t u8_freshdatamemlocNo = 0;
extern bool ch_gpstimereloadstatuse;
uint8_t u8_SAVING2MEM =0; 
/*******************************************************************************
  Function:
    void APP_Initialize ( void )

  Remarks:
    See prototype in app.h.
 */
bool alarm_triggered;
struct tm sys_time;
struct tm alarm_time;
char gps_tempUTCTime[20];
char gps_pasttempUTCTime[20];
char gps_tempUTCdate[20];
//void Timeout_Handler(RTC_TIMER32_INT_MASK intCause, uintptr_t context)
//{
//    if((intCause & RTC_TIMER32_INT_MASK_CMP0) == RTC_TIMER32_INT_MASK_CMP0)
//    {
//        LED_Toggle();
//        u16_loopof1sec++;
//        if(u16_loopof1sec >= 60)
//        {
//            if(savelivedatatotempmem() == true)
//            {
//                newdataEN = 1;
//            }
//            u16_loopof1sec = 0;
//        }
//    }    
//}
void APP_Initialize ( void )
{
    /* Place the App state machine in its initial state. */
    appData.state = APP_STATE_INIT;

}

void TC0_Callback_InterruptHandler(TC_TIMER_STATUS status, uintptr_t context)
{
    /* Toggle LED */
//    LED_Toggle();
    RTC_RTCCTimeGet(&sys_time);
//    loadgpsdata(char *ch_gps_UTCTime,char *ch_gps_UTCdate)
//    if(loadgpstime(&gps_tempUTCTime[0],&gps_tempUTCdate[0]) == 1)
    if(loadgpsdata(&gps_tempUTCTime[0],&gps_tempUTCdate[0]) == 1)    
    {
        if((gps_tempUTCdate[0]==0)&&(gps_tempUTCdate[1]==0)&&(gps_tempUTCdate[2]==0)&&(gps_tempUTCdate[3]==0)&&(gps_tempUTCdate[4]==0)&&(gps_tempUTCdate[5]==0))
        {
            printf ("Invalide,tempgps_UTCdate:%s!!! Comeback to uCrtc\n ",gps_tempUTCdate);
            //15-01-2018 12:00:00 Monday
            sys_time.tm_hour = 12;      /* hour [0,23] */
            sys_time.tm_sec = 00;       /* seconds [0,61] */
            sys_time.tm_min = 00;       /* minutes [0,59] */
            sys_time.tm_mon = 0;        /* month of year [0,11] */
            sys_time.tm_year = 118;     /* years since 1900 */
            sys_time.tm_mday = 15;      /* day of month [1,31] */
            sys_time.tm_wday = 1;       /* day of week [0,6] (Sunday = 0) */
                                        /* tm_yday - day of year [0,365] */
                                        /* tm_isdst - daylight savings flag */
            RTC_RTCCTimeSet(&sys_time);
            ch_gpstimereloadstatuse =0;
        }
        else
        {
//            printf ("tempgps_UTCdate:%s\n",gps_tempUTCdate);
//            if((gps_tempUTCTime[4]=='0')&&(gps_tempUTCTime[5]=='0')&&(gps_pasttempUTCTime[3] != gps_tempUTCTime[3])) 
            
            if(gps_pasttempUTCTime[3] != gps_tempUTCTime[3])    
            {
                gps_pasttempUTCTime[3] = gps_tempUTCTime[3];
                        
    //            printf("GPSUTCtime is valid:%s\r\n",gps_tempUTCTime);
                printf("uCRTCtime is:%02d:%02d:%02d\r\n",sys_time.tm_hour, sys_time.tm_min, sys_time.tm_sec);
                uchr_pastMin = sys_time.tm_min;
                can_recdata();
                if(u8_freshdatamemlocNo == 0)
                {
                    if(savelivedatatotempmem1() == 1)
                    {
                        u8_newdataset1 = 1;//newdataEN = 1;
                        u8_newdataset2 = 0;
                        u8_freshdatamemlocNo = 1;
                    }
                }
                else
                {
                    if(savelivedatatotempmem2() == 1)
                    {
                        u8_newdataset1 = 0;
                        u8_newdataset2 = 1;//newdataEN = 1; 
                        u8_freshdatamemlocNo = 0;
                    }
                }
        //        can_datarefresh();
                newdataupdated = 1;
                new_gpsdataset = 0;
                u16_gerrercode3blkcnt = 0;
                if(u8_gerrercode3 == 0)
                    GPIO_PB30_Set();//blue led 
                else    
                    GPIO_PB30_Clear();//blue led
            }
        }
    }
    else
    {
        if(sys_time.tm_min != uchr_pastMin)//&&(new_gpsdataset == 1))
    //    if((sys_time.tm_sec%5)==  uchr_pastMin)  
    //    if(sys_time.tm_sec !=  uchr_pastMin)
        {

            uchr_pastMin = sys_time.tm_min;
    //        uchr_pastMin = (sys_time.tm_sec%5);
    //        uchr_pastMin = sys_time.tm_sec;

            printf("System time is:   %02d:%02d:%02d\r",sys_time.tm_hour, sys_time.tm_min, sys_time.tm_sec);
            can_recdata();
            if(u8_freshdatamemlocNo == 0)
            {
                if(savelivedatatotempmem1() == 1)
                {
                    u8_newdataset1 = 1;//newdataEN = 1;
                    u8_newdataset2 = 0;
                    u8_freshdatamemlocNo = 1;
                }
            }
            else
            {
                if(savelivedatatotempmem2() == 1)
                {
                    u8_newdataset1 = 0;
                    u8_newdataset2 = 1;//newdataEN = 1; 
                    u8_freshdatamemlocNo = 0;
                }
            }
    //        can_datarefresh();
            newdataupdated = 1;
            new_gpsdataset = 0;
            u16_gerrercode3blkcnt = 0;
            if(u8_gerrercode3 == 0)
                GPIO_PB30_Set();//blue led 
            else    
                GPIO_PB30_Clear();//blue led
        }
    }
}
volatile uint16_t counter=0;

void TC4_Callback_InterruptHandler(TC_TIMER_STATUS status, uintptr_t context)
{
    /* Toggle LED */
    counter++;
}
volatile bool timedout=0;

void TC3_Callback_InterruptHandler(TC_TIMER_STATUS status, uintptr_t context)
{
   timedout = 1;
   TC3_TimerStop();
}
volatile bool switchLngpress = 0,switchsrtpress = 0;
volatile bool low_edge = 0;
void EIC_User_Handler(uintptr_t context)
{
//    if(low_edge == 1){ 
//       TC4_TimerStop();
//        if(counter >= 4){
//           switchLngpress = 1;
//        }else{
//           switchsrtpress = 1;
//        }
//       counter = 0;
//       low_edge = 0;
//    }else if(low_edge == 0){
//      low_edge = 1;
//      TC4_TimerStart();
//    }
 
//bool pin_state = port_pin_get_input_level(BUTTON_1_PIN);
	   //port_pin_set_output_level(LED_0_PIN, pin_state);
	//port_pin_set_output_level(LED_0_PIN, pin_state);
	   //port_pin_toggle_output_level(LED_0_PIN);
    if(bl_pulsevalidestate == false)
    {
        u32_pulsecunt ++; 
    }
//    printf("u32_pulsecunt:%ld\r\n",u32_pulsecunt);
}

/******************************************************************************
  Function:
    void APP_Tasks ( void )

  Remarks:
    See prototype in app.h.
 */
void APP_Tasks ( void )
{
    /* Check the application's current state. */
    switch ( appData.state )
    {
        /* Application's initial state. */
        case APP_STATE_INIT:
        {        
            SYSTICK_DelayMs(300);  
            
            appData.state = APP_STATE_TIMER_TICK_INIT;
        }
        break;

        case APP_STATE_TIMER_TICK_INIT:
        {
            TC0_TimerStart();
            SYSTICK_DelayMs(10);  
//            _APP_TimerTickHandler(0,0);
            

//            alarm_triggered = false;

            //15-01-2018 12:00:00 Monday
            sys_time.tm_hour = 12;      /* hour [0,23] */
            sys_time.tm_sec = 00;       /* seconds [0,61] */
            sys_time.tm_min = 00;       /* minutes [0,59] */
            sys_time.tm_mon = 0;        /* month of year [0,11] */
            sys_time.tm_year = 118;     /* years since 1900 */
            sys_time.tm_mday = 15;      /* day of month [1,31] */
            sys_time.tm_wday = 1;       /* day of week [0,6] (Sunday = 0) */
                                        /* tm_yday - day of year [0,365] */
                                        /* tm_isdst - daylight savings flag */

//            //15-01-2018 12:00:20 Monday
//            alarm_time.tm_hour = 12;
//            alarm_time.tm_sec = 20;
//            alarm_time.tm_min = 00;
//            alarm_time.tm_mon = 0;
//            alarm_time.tm_year = 118;
//            alarm_time.tm_mday = 15;
//            alarm_time.tm_wday = 1;

//            printf("\n\r---------------------------------------------------------");
//            printf("\n\r                    RTC Demo                 ");
//            printf("\n\r---------------------------------------------------------\n\r");

//            RTC_RTCCCallbackRegister(RTC_Callback, (uintptr_t) NULL);
//            RTC_FrequencyCorrect (-10);
            RTC_RTCCTimeSet(&sys_time);
//            RTC_RTCCAlarmSet(&alarm_time, RTC_ALARM_MASK_HHMMSS);

//            printf("\n\rThe Alarm will Trigger at 12:00:00\n\n\r");
//            RTC_Timer32CallbackRegister(Timeout_Handler,0);
//            RTC_Timer32InterruptEnable(RTC_TIMER32_INT_MASK_CMP0);
//            RTC_Timer32Start();
            appData.state = APP_USART_DRIVER_INIT;
        }
        break;

        case APP_USART_DRIVER_INIT:
        {
            /* Open an instance of USART driver */
            appData.usartHandle = DRV_USART_Open(DRV_USART_INDEX_0,
                         (DRV_IO_INTENT_READWRITE | DRV_IO_INTENT_BLOCKING));
            
            
            /* Check the USART driver handler */
            if (appData.usartHandle != DRV_HANDLE_INVALID )
            {
                DRV_USART_BufferEventHandlerSet(appData.usartHandle,&_APP_UART_ReceiveCallback,0);
                appData.state = APP_STATE_DEV_ADAPTER_INIT_PWR_CTRL_1;
            }
            else
            {
                    // Try again to get handle
            }
        }
        break;

        case APP_STATE_DEV_ADAPTER_INIT_PWR_CTRL_1:
        {
            dev_hal_init();
            dev_hal_pwr_ctl(1);
            SYSTICK_DelayMs(1000);
            appData.state = APP_STATE_DEV_ADAPTER_INIT_PWR_CTRL_2;
            break;
        }

        case APP_STATE_DEV_ADAPTER_INIT_PWR_CTRL_2:
        {
            dev_hal_pwr_ctl(0);
            SYSTICK_DelayMs(5000);
            appData.state = APP_STATE_GSM_GPS_INIT_COMPLETE;
            break;
        }

        case APP_STATE_GSM_GPS_INIT_COMPLETE:
        {
            dev_adapter_init();
//            GSM_RST_PA05_Set();
//            SYSTICK_DelayMs(10);
//            GSM_RST_PA05_Clear();
//            SYSTICK_DelayMs(2000);
            gsm_gps_init();          
//            printf("\r\nGSM-GPS Initialized\r\n");
//            printf("-------------------INFO--------------------------");
//            printf("\r\nLong press switch to configure phone number or \r\nShort press to send SMS\r\n");
//            printf("-------------------------------------------------\r\n");
            LED_Clear();
            appData.state = APP_STATE_SERVICE_TASKS;
            u16_loopcounter = 120;
            WDT_Enable(); 
            u32_watchdogtimercnt = 0;
            break;
        }

        case APP_STATE_SERVICE_TASKS:
        {
            
//            WDT_Clear();
            u32_watchdogtimercnt = 0;
//            if(u16_loopcounter >= 20)
            {
//                u16_loopcounter = 0;
//            gsm_gps_task();
                
            _APP_BUTTON_PRESS_Tasks();
//            scanf("\r\n%s",manual_ATcmm);
//            //printf("\r\n mAT=%s",manual_ATcmm);
//            gsm_manualAT_info (manual_ATcmm);
////            gsm_manualAT_info ("AT\r\n");
                
//            if(GPIO_PA25_Get()==0)
                b_speare2 = 1;//b_IgnitionON = 1;
//            else
//                b_speare2 = 0;//b_IgnitionON = 0;
//            if(GPIO_PA24_Get()==0)
                b_speare1 = 1;
//            else
//                b_speare1 = 0;
            if(GPIO_PA21_Get()==0)
                b_airfiltercool = 1;//b_Hydraulicoilfilterclog = 1;
            else
                b_airfiltercool = 0;//b_Hydraulicoilfilterclog = 0;
            if(GPIO_PA20_Get() == 0)
            {
                b_Hydraulicoilfilterclog = 1;//b_airfiltercool = 1;
                u8_SAVING2MEM =0;
            }
            else
            {
                b_Hydraulicoilfilterclog = 0;//b_airfiltercool = 0;
                if(TESINGMODE ==0)//||(MEMTEST==1))
                    u8_SAVING2MEM = 0;
                else
                    u8_SAVING2MEM = 1;
            }

//            if(uint_frq >=115)
//                b_EngineON = 1;
//            else
//                b_EngineON = 0;
            if(GPIO_PB17_Get() == 0)
                b_LubeOilPressure = 1;
            else
                b_LubeOilPressure = 0;
            if(GPIO_PB16_Get() == 0)
                b_highenginteperature = 1;
            else
                b_highenginteperature = 0;
//            if(GPIO_PA19_Get()==0)
//                b_IgnitionON = 1;//b_speare2 = 1;
//            else
//                b_IgnitionON = 0;//b_speare2 = 0;
            uint8_t debouncecnt=0;    
            for(uint8_t i =0;i<10;i++)
            {
                if(GPIO_PA19_Get()==0)
                    debouncecnt++;
                SYSTICK_DelayMs(1);
//                    b_IgnitionON = 1;//b_speare2 = 1;
//                else
//                    b_IgnitionON = 0;//b_speare2 = 0;
            }
            if(debouncecnt>5)
            {
                b_IgnitionON = 1;//b_speare2 = 1;
            }
            else
            {
                b_IgnitionON = 0;//b_speare2 = 0;
            }    

            b_speare3 = 0;//notconnected
            
//            if((u8_newdataset==1)||(newdataupdated==1)||(onlinemode==1))//(u16_loopcounter > (120*LOGTIME))//500msloop
            {
                if(u8_newdataset1 == 1)
                {
                    newdataEN1 = 1;
                }
                else if(u8_newdataset2 == 1)
                {
                    newdataEN2 = 1;
                }
//                u16_loopcounter = 0;
                newdataupdated = 0;
                DRV_USART_WriteQueuePurge(appData.usartHandle);
                DRV_USART_ReadQueuePurge(appData.usartHandle);
                loc_update_f = true;
                req_pend_f = true;
                gsm_gps_task();
//                gsm_sms_task ();
//                printf("-------breakpt3\r\n"); 
            }
//            else
//            {
//                if(u16_loopcounter >= 40)
//                {
//                    DRV_USART_WriteQueuePurge(appData.usartHandle);
//                    DRV_USART_ReadQueuePurge(appData.usartHandle);
//                    loc_update_f = true;
//                    req_pend_f = true;
//                    gsm_sms_task ();
//                    u16_loopcounter = 0;
//                }
//            }
            
            }
            break;
        }
        default:
        {      
            break;
        }
    }
}


static void _APP_BUTTON_PRESS_Tasks(void)
{
   
//    uint8_t phn_num[20] = {0};  
    
//    char select = 0,select1 = 0;
    
    
    if(switchsrtpress){
        LED_Set();
        DRV_USART_WriteQueuePurge(appData.usartHandle);
        DRV_USART_ReadQueuePurge(appData.usartHandle);
        loc_update_f = true;
        req_pend_f = true;
        gsm_gps_task();
        switchsrtpress = 0;           
    }
    
    
//    else if(switchLngpress){
//        LED_Set();
//        printf("\r\nEnter phone number with '+' and country code\r\n");
//        printf("\r\nExample: <+><country_code><mobile_no>, +919934567890 and press Enter\r\n");
//        scanf("\r\n%s",phn_num);
//        printf("\r\nVerify Phn number =%s",phn_num);
//        scanf("%c",&select);
//        printf("\r\nEnter 'y' to update phone number");
//        scanf("%c",&select1);
//        if(select1 == 'y'){
//             phn_num[18] = 'S';
//             while(NVMCTRL_IsBusy());
//
//             NVMCTRL_RowErase((uint32_t)nvm_user_start_address);
//
//             while(NVMCTRL_IsBusy());
//
//             NVMCTRL_PageWrite((uint32_t *)phn_num, (uint32_t)nvm_user_start_address);
//
//             while(NVMCTRL_IsBusy());
//
//             printf("\r\nPhone number updated\r\n");
//   
//            
//        }else{
//            printf("\r\nPhone number not updated\r\n");
//        }
//        printf("-------------------INFO--------------------------");
//        printf("\r\nLong press switch to configure phone number or \r\nShort press to send SMS\r\n");
//        printf("-------------------------------------------------\r\n");
//        switchLngpress = 0;
//        LED_Clear();
//    }

}

//static void _APP_TimerTickHandler ( uintptr_t context, uint32_t currTick )
//{
//    static uint16_t mincount = 0;
//    mincount++;
//    if(mincount > 1)
//    {
//        mincount = 0;
//        LED_Toggle();
//    }
//
//    dev_tick_isr();
//}
float low_pass_filter(float x)
{
	//methode1
	static float samples[11];
	static int i = 0;
	static float total = 0;
	
	/* Update the moving average */
	total += (x - samples[i]);
	samples[i] = x;

	/* Update the index */
	i = (i==9 ? 0 : i+1);

	return (total/10.0);
}
void timeout_handler(uintptr_t context)
{
    static uint16_t mincount = 0;//,first=0,firstcnt=0;//,wdt_clearcnt=0;
    u32_watchdogtimercnt++;
    if(u32_watchdogtimercnt > 300000)//*300))//5min 
    {    
        u32_watchdogtimercnt= 300000;
        NVIC_SystemReset();
//         if(first==0)
//        {
//            first=1;
//
//        }
//        if(firstcnt>1000)
//        {
//            firstcnt=0;
//            printf("u32_watchdogtimercnt=%ld",u32_watchdogtimercnt);
//        }
    }
    else
    {
//        wdt_clearcnt++;
//        if(wdt_clearcnt>=100)
//        {
//            
        WDT_Clear();
//        }
       
    }
    
    if(u8_gerrercode1 == 0)
    {
        u16_gerrercode1blkcnt++;
        if(u16_gerrercode1blkcnt > 1000)
        {
            u16_gerrercode1blkcnt=0;
            LED_Set();//green led
        }
        else if(u16_gerrercode1blkcnt > 200)
        {
            LED_Clear();//green led
        }
        else
        {
            LED_Set();//green led
        }
    }
    else
    {
        LED_Set();//green led
    }
    if(u8_gerrercode2 == 0)
    {
        
        u16_gerrercode2blkcnt++;
        if(u16_gerrercode2blkcnt > 1000)
        {
            u16_gerrercode2blkcnt=0;
            POWER_KEY_Set();//red led
        }
        else if(u16_gerrercode2blkcnt > 100)
        {
            POWER_KEY_Clear();//red led
        }
        else
        {
            POWER_KEY_Set();//red led
        }
    }
    else
    {
        POWER_KEY_Set();//red led
    }
    
    if(u8_gerrercode3 == 0)
    {
        
        u16_gerrercode3blkcnt++;
        if(u16_gerrercode3blkcnt > 1000)
        {
            u16_gerrercode3blkcnt=1000;
//            GPIO_PB30_Set();//blue led
        }
        else if(u16_gerrercode3blkcnt > 200)
        {
            GPIO_PB30_Clear();//blue led
        }
        else
        {
            GPIO_PB30_Set();//blue led
        }
    }
    else
    {
        u16_gerrercode3blkcnt++;
        if(u16_gerrercode3blkcnt > 1000)
        {
            u16_gerrercode3blkcnt=1000;
            GPIO_PB30_Set();//blue led
        }
    }
//    GPIO_PB30_Clear();//blue led
        
        
    mincount++;
    if(mincount >= 500)
    {
        mincount = 0;
//        LED_Toggle();
        u16_loopcounter++; 
//        u16_loopofhalfsec++;
//        if(u16_loopofhalfsec >= 119)
//        {
//            if(savelivedatatotempmem() == true)
//            {
//                newdataEN = 1;
//            }
//            u16_loopofhalfsec = 0;
//        }
        /***********frq*************/
        if(bl_pulsevalidestate == false)
        {
            uint_avgfrqcnt++;
            flt_avgfrq = low_pass_filter(u32_pulsecunt);
            if(uint_avgfrqcnt >= 1)
            {
                uint_frq = (flt_avgfrq/1.0)*2.0;
                flt_avgfrq = 0;
                uint_avgfrqcnt = 0;
            }
//            printf("uint_frq:%d,flt_avgfrq:%f\r\n",uint_frq,flt_avgfrq);
            u32_pulsecunt = 0;
            bl_pulsevalidestate = true;
        }
        else
        {
            u32_pulsecunt = 0;
            bl_pulsevalidestate = false;
        }
    }
    
    dev_tick_isr();
    
}
volatile char transfer_status = 0;
volatile char rxChar ; 

static void _APP_UART_ReceiveCallback(    DRV_USART_BUFFER_EVENT bufferEvent,
    DRV_USART_BUFFER_HANDLE bufferHandle,
    uintptr_t context)
{
    
    DRV_USART_ReadBufferAdd(appData.usartHandle,(void*)&rxChar,1,&appData.bufferHandle);
    dev_rx( rxChar);
//    mydev_rx( rxChar);
}

/*******************************************************************************
 End of File
 */
