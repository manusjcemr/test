/****************************************************************************
* Title                 :   GSM ENGINE
* Filename        :   at_engine.c
* Author            :   MSV
* Origin Date    :   10/03/2016
* Notes              :   None
*****************************************************************************/
/**************************CHANGE LIST **************************************
*
*    Date    Software Version    Initials   Description
*  10/03/16        1.0.0               MSV      Interface Created.
*  15/02/18        2.0.0               ST       Customized for Application 
 * 01/01/2020      3.0.0               MK       Customized for Application
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
 * @file at_engine.c
 * @brief GSM Engine
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
#include "at_engine.h"
#include "app.h"
#include "driver/usart/drv_usart.h"
/******************************************************************************
* Module Preprocessor Constants
*******************************************************************************/

/******************************************************************************
* Module Preprocessor Macros
*******************************************************************************/

/******************************************************************************
* Module Typedefs
*******************************************************************************/

/******************************************************************************
* Module Variable Definitions
*******************************************************************************/

/* TEMPS */
static uint32_t     temp_timer;
static at_cmd_cb    temp_cb;

/* FLAGS */
volatile bool       timeout_f;
volatile bool       exception_f;
volatile bool       response_f;
volatile bool       cue_f;


/* CALLBACKS */
static at_cmd_cb    cb;
static at_cmd_cb    cb_default;

/* BUFFERS */
char                tx_buffer[ AT_TRANSFER_SIZE ];
char                rx_buffer[ AT_TRANSFER_SIZE ];

extern uint8_t u8_datasendEN;

char passwordbuf[10],paratypebuf[10];
char ipaddrbuf[20];
char apnbuf[20];
char slnobuf[20];
char *temp_ptr1;
/******************************************************************************
* Function Prototypes
*******************************************************************************/

/******************************************************************************
* Private Function Definitions
*******************************************************************************/

/******************************************************************************
* Public Function Definitions
*******************************************************************************/

void engine_init
(
                at_cmd_cb default_callback
)
{    
    dev_timer_init();
    at_parser_init();
    
    cb_default = default_callback;
    
    at_cmd_save( "+CMS ERROR :", AT_DEFAULT_TIMEOUT, default_callback, 
                                                  default_callback, 
                                                  default_callback, 
                                                  default_callback );

    exception_f   = false;
    response_f    = false;
    cue_f         = false;

    memset( ( void* )tx_buffer, 0, AT_TRANSFER_SIZE );
}

void at_cmd
(
                char *input
)
{
    char* temp_input = input;

    at_parse( temp_input, &temp_cb, &temp_timer );//
    dev_timer_load( temp_timer );
    while( cue_f ) 
        at_process();

    while( !dev_tx( *( temp_input++ ) ) );

    dev_adapter_reset();
    dev_timer_start();
    
}
bool myat_cmd(char *inbuf,uint32_t respdelay)
{
    extern volatile bool       response_f,exception_f;
    extern volatile uint8_t u8_atcmd_status;
    extern volatile uint8_t u8_SSid1error,u8_SSid2error,u8_SSid3error,u8_SSid4error,u8_SSid5error,u8_SSid6error;
    
    extern APP_DATA appData;
    char u8_ltempbuf[100] = {0};
    uint8_t u8_lrssi =0;
//    uint8_t u8_lber =0;
    //char s1[] = "Fun with STL"; 
    //char s2[] = "OK"; 
//    char* p;
    char temp_input[AT_TRANSFER_SIZE];
    uint16_t tx_index = 0,u16_ledblinkcnt=0;
    uint32_t response_fcnt=0,loopinfinetcnt=0;
    memset( ( void* )temp_input, 0, AT_TRANSFER_SIZE );
    while (*inbuf != '\0') 
    {
        temp_input[ tx_index++ ] = *inbuf;
        inbuf++;
    } 
    temp_input[ tx_index++ ] = '\r';
    temp_input[ tx_index++ ] = '\n';
    tx_buffer[ tx_index ] = '\0';
//    at_parse( temp_input, &temp_cb, &temp_timer );//
//    dev_timer_load( temp_timer );
//    while( cue_f ) 
//        at_process();
//
//    while( !dev_tx( *( temp_input++ ) ) );
//
//    dev_adapter_reset();
//    dev_timer_start();
    
    dev_timer_load( respdelay );
    dev_timer_start();
    memset( ( void* )rx_buffer, 0, AT_TRANSFER_SIZE );
    dev_adapter_reset ();
    timeout_f = false;
    response_f = false;
    
    printf("tx:%s\r\n",temp_input);
    DRV_USART_WriteBufferAdd(appData.usartHandle, temp_input,tx_index,&appData.bufferHandle);
    while(DRV_USART_BufferStatusGet(appData.bufferHandle) != DRV_USART_BUFFER_EVENT_COMPLETE)
    {
        loopinfinetcnt++;
        
        if(u8_datasendEN == 1)
        {
            u16_ledblinkcnt++;
            if(u16_ledblinkcnt > 30000)
            {
                u16_ledblinkcnt = 0;
                GPIO_PB30_Set();//blue led
            }
            else if(u16_ledblinkcnt > 20000)
            {
                GPIO_PB30_Clear();//blue led
            }
            else
            {
                GPIO_PB30_Set();//blue led
            }
        }
        if(response_f == 1)//||(exception_f = true))
        {
            response_fcnt++; 
        }
        if((timeout_f == 1)||(response_fcnt >100000)||(loopinfinetcnt>100000000))
        {   
            response_fcnt = 100000;
            printf("rpy:-%s\r\n",rx_buffer);
            memset( ( void* )u8_ltempbuf, 0, 100 );
//            memcpy(u8_ltempbuf,rx_buffer,100);
            // Find first occurrence of s2 in s1 
//            p = strstr(rx_buffer, "OK");
            
//            printf("u8_ltempbuf:-%s\r\n",u8_ltempbuf);
            if ((strstr(rx_buffer, "#SS: 1,0"))&&(u8_SSid1error == 0))
            { 
                u8_atcmd_status = AT_SS1;
                printf("u8_atcmd_status = AT_SS1\r\n");
            }
            else if ((strstr(rx_buffer, "#SS: 2,0")) &&(u8_SSid2error == 0))
            { 
                printf("u8_atcmd_status = AT_SS2\r\n");
                u8_atcmd_status = AT_SS2;
            }
            else if ((strstr(rx_buffer, "#SS: 3,0")) &&(u8_SSid3error == 0))
            { 
                printf("u8_atcmd_status = AT_SS3\r\n");
                u8_atcmd_status = AT_SS3;
            }
            else if ((strstr(rx_buffer, "#SS: 4,0")) &&(u8_SSid4error == 0))
            { 
                printf("u8_atcmd_status = AT_SS4\r\n");
                u8_atcmd_status = AT_SS4;
            }
            else if ((strstr(rx_buffer, "#SS: 5,0")) &&(u8_SSid5error == 0))
            { 
                printf("u8_atcmd_status = AT_SS5\r\n");
                u8_atcmd_status = AT_SS5;
            }
            else if ((strstr(rx_buffer, "#SS: 6,0")) &&(u8_SSid6error == 0))
            { 
                printf("u8_atcmd_status = AT_SS6\r\n");
                u8_atcmd_status = AT_SS6;
            }
            else if (strstr(rx_buffer, "+CSQ")) 
            { 
                for(uint8_t i= 0;i<strlen(rx_buffer);i++)
                {
                    if(rx_buffer[i] == '+')
                    {
                        for(uint8_t j= 0;((j<10)&&(i<strlen(rx_buffer)));j++)
                            u8_ltempbuf[j] = rx_buffer[i++];
                        break;
                    }
                }
//                pt1= strtok (u8_ltempbuf,"+");
//                 
//                strcpy ( u8_lbuf, pt1 ) ;
//                printf("u8_ltempbuf:-%s\r\n",u8_ltempbuf);
                if(u8_ltempbuf[7] == ',')
                {
                    u8_lrssi = (u8_ltempbuf[6] - 0x30);
//                    u8_lber = (u8_ltempbuf[8] - 0x30);
                }
                else
                {
                    u8_lrssi = (u8_ltempbuf[6] - 0x30)*10 + (u8_ltempbuf[7] - 0x30);
//                    u8_lber = (u8_ltempbuf[9] - 0x30);
                }
                
                if((u8_lrssi >= 10)&&(u8_lrssi <=31))//17
                {
//                    printf("signal Quality(+CSQ:):rssi =%d,ber=%d--GOOD \r\n",u8_lrssi,u8_lber);// +CSQ: 29,7     
                    u8_atcmd_status = AT_OK;
                }
                else
                {
//                    printf("signal Quality(+CSQ:):rssi =%d,ber=%d--BAD \r\n",u8_lrssi,u8_lber);// +CSQ: 29,7               
//                    GSM_RST_PA05_Set();
//                    SYSTICK_DelayMs(1000);
//                    GSM_RST_PA05_Clear();
//                    SYSTICK_DelayMs(1000);
//                    SYSTICK_DelayMs(1000);
//                    SYSTICK_DelayMs(1000);
                    u8_atcmd_status = AT_ERROR;
                }
//                printf("-------Ok\r\n"); 
            }
            else if(strstr(rx_buffer, ">"))
            {
                u8_atcmd_status = AT_DATASEND;
//                printf("------->\r\n"); 
//                u8_atcmd_status = AT_ERROR;
            }
            else if(strstr(rx_buffer, "CONNECT"))
            {
                u8_atcmd_status = AT_CONNECT;
//                printf("------->\r\n"); 
//                u8_atcmd_status = AT_ERROR;
            }     
//            else if(strstr(rx_buffer, "NO CARRIER"))
//            {
//                u8_atcmd_status = AT_NOCARRIER;
////                printf("------->\r\n"); 
////                u8_atcmd_status = AT_ERROR;
//            }
            else if (strstr(rx_buffer, "OK")) 
            { 
                u8_atcmd_status = AT_OK;
//                printf("-------Ok\r\n"); 
                u8_datasendEN=0;
                GPIO_PB30_Clear();//blue led
            }
            else
            {
                u8_atcmd_status = AT_UNKNOWN;
//                printf("-------Error3\r\n"); 
                u8_datasendEN = 0;
                GPIO_PB30_Clear();//blue led
//                u8_atcmd_status = AT_ERROR;
            }
            break;
        }
//        else if(timedout == 1)
//        {
//            printf("timedout\r\n");
//            u8_atcmd_status = AT_ERROR;
//            printf("%s",rx_buffer); 
//            timedout = 0;
//            timeout_f = 1; 
//            break;
//        }
    }  
    return 1;
}
bool myat_cmd2(char *inbuf,uint32_t respdelay)
{
    extern volatile bool       response_f,exception_f;
    extern volatile uint8_t u8_atcmd_status;
    extern APP_DATA appData;
    uint16_t u16_ledblinkcnt =0;
    //char s1[] = "Fun with STL"; 
    //char s2[] = "OK"; 
//    char* p;
    char temp_input[AT_TRANSFER_SIZE];
    uint16_t tx_index = 0;
    uint32_t response_fcnt =0,loopinfinetcnt=0;
    memset( ( void* )temp_input, 0, AT_TRANSFER_SIZE );
    while (*inbuf != '\0') 
    {
        temp_input[ tx_index++ ] = *inbuf;
        inbuf++;
    } 
    tx_buffer[ tx_index ] = '\0';

    dev_timer_load( respdelay );
    dev_timer_start();
    memset( ( void* )rx_buffer, 0, AT_TRANSFER_SIZE );
    dev_adapter_reset ();
    timeout_f = false;
    printf("tx:%s\r\n",temp_input);
    DRV_USART_WriteBufferAdd(appData.usartHandle, temp_input,tx_index,&appData.bufferHandle);
    while(DRV_USART_BufferStatusGet(appData.bufferHandle) != DRV_USART_BUFFER_EVENT_COMPLETE)
    {
        loopinfinetcnt++;
        if(u8_datasendEN == 1)
        {
            u16_ledblinkcnt++;
            if(u16_ledblinkcnt > 10000)
            {
                u16_ledblinkcnt = 0;
                GPIO_PB30_Set();//blue led
            }
            else if(u16_ledblinkcnt > 5000)
            {
                GPIO_PB30_Clear();//blue led
            }
            else
            {
                GPIO_PB30_Set();//blue led
            }
        }
        if(response_f == 1)
        {
            response_fcnt++; 
        }
        if((timeout_f == 1)||(response_fcnt >100000)||(loopinfinetcnt>100000000))
//        if(timeout_f == 1)//||(response_fcnt >100000))
        {   
            response_fcnt = 100000;  
            printf("rpy:-%s\r\n",rx_buffer); 
            // Find first occurrence of s2 in s1 
//            p = strstr(rx_buffer, "OK");
            if(strstr(rx_buffer, "NO CARRIER:1"))
            {
                u8_atcmd_status = AT_NOCARRIER1;
//                printf("------->\r\n"); 
//                u8_atcmd_status = AT_ERROR;
            }
            else if(strstr(rx_buffer, "NO CARRIER:2"))
            {
                u8_atcmd_status = AT_NOCARRIER2;
//                printf("------->\r\n"); 
//                u8_atcmd_status = AT_ERROR;
            }
            else if(strstr(rx_buffer, "NO CARRIER:3"))
            {
                u8_atcmd_status = AT_NOCARRIER3;
//                printf("------->\r\n"); 
//                u8_atcmd_status = AT_ERROR;
            }
            else if(strstr(rx_buffer, "NO CARRIER:4"))
            {
                u8_atcmd_status = AT_NOCARRIER4;
//                printf("------->\r\n"); 
//                u8_atcmd_status = AT_ERROR;
            }
            else if(strstr(rx_buffer, "NO CARRIER:5"))
            {
                u8_atcmd_status = AT_NOCARRIER5;
//                printf("------->\r\n"); 
//                u8_atcmd_status = AT_ERROR;
            }
            else if(strstr(rx_buffer, "NO CARRIER:6"))
            {
                u8_atcmd_status = AT_NOCARRIER6;
//                printf("------->\r\n"); 
//                u8_atcmd_status = AT_ERROR;
            }
            else if(strstr(rx_buffer, ">"))
            {
                u8_atcmd_status = AT_DATASEND;
//                printf("------->\r\n"); 
//                u8_atcmd_status = AT_ERROR;
            }
            else if (strstr(rx_buffer, "OK")) 
            { 
                u8_atcmd_status = AT_OK;
//                printf("-------Ok\r\n"); 
            }
            else
            {
                u8_atcmd_status = AT_UNKNOWN;
//                printf("-------Error3\r\n"); 
//                u8_atcmd_status = AT_ERROR;
            }
            GPIO_PB30_Clear();//blue led
            break;
        }
//        else if(timedout == 1)
//        {
//            printf("timedout\r\n");
//            u8_atcmd_status = AT_ERROR;
//            printf("%s",rx_buffer); 
//            timedout = 0;
//            timeout_f = 1; 
//            break;
//        }
    }  
    return 1;
}
bool myat_cmd3(char *inbuf,uint32_t respdelay)
{
    extern volatile bool       response_f,exception_f;
    extern volatile uint8_t u8_atcmd_status;
    extern APP_DATA appData;
    
    extern void saveserialNo(uint8_t *data);
    extern void saveIPaddr(uint8_t *data);
    extern void saveAPNaddr(uint8_t *data);
    extern void exflash_erras(void);
    extern void smr_clear(void);
    
    char u8_ltempbuf[100] = {0};
    uint32_t response_fcnt =0;
//    uint8_t u8_lrssi =0,u8_lber =0;
    //char s1[] = "Fun with STL"; 
    //char s2[] = "OK"; 
//    char* p;
    char temp_input[AT_TRANSFER_SIZE];
    uint16_t tx_index = 0;
    uint32_t blinkcnt=0,u32_ledblinkcnt =0,loopinfinetcnt=0;
    memset( ( void* )temp_input, 0, AT_TRANSFER_SIZE );
    while (*inbuf != '\0') 
    {
        temp_input[ tx_index++ ] = *inbuf;
        inbuf++;
    } 
    temp_input[ tx_index++ ] = '\r';
    temp_input[ tx_index++ ] = '\n';
    tx_buffer[ tx_index ] = '\0';
    
    dev_timer_load( respdelay );
    dev_timer_start();
    memset( ( void* )rx_buffer, 0, AT_TRANSFER_SIZE );
    dev_adapter_reset ();
    timeout_f = false;
    response_f = false;
    printf("tx:%s\r\n",temp_input);
    DRV_USART_WriteBufferAdd(appData.usartHandle, temp_input,tx_index,&appData.bufferHandle);
    while(DRV_USART_BufferStatusGet(appData.bufferHandle) != DRV_USART_BUFFER_EVENT_COMPLETE)
    {
        loopinfinetcnt++;
        if(response_f == 1)
        {
            response_fcnt++; 
        }
        if((timeout_f == 1)||(response_fcnt >500000)||(loopinfinetcnt>100000000))
        {   
            response_fcnt = 500000;
            printf("rpy:-%s\r\n",rx_buffer);
            memset( ( void* )u8_ltempbuf, 0, 100 );
//            memcpy(u8_ltempbuf,rx_buffer,100);
            // Find first occurrence of s2 in s1 
//            p = strstr(rx_buffer, "OK");
            
//            printf("u8_ltempbuf:-%s\r\n",u8_ltempbuf);
            if (strstr(rx_buffer, "&1234")) 
            { 
                uint8_t u8_strlenbuf = 0;
                u8_atcmd_status = AT_OK;
                for(uint8_t i= 0;(i<strlen(rx_buffer)&&(i<100));i++)
//                for(uint8_t i= 0;i<30;i++)
                {
                    if(rx_buffer[i] == '&')
                    {
                        
                        for(uint8_t j= 0;((rx_buffer[i] != '*')&&(i<strlen(rx_buffer))&&(j < 200));j++)
                        {
                            u8_ltempbuf[j] = rx_buffer[i++];
                            
                            u8_strlenbuf++;
                        }
                        break;
                    }
                }
//                pt1= strtok (u8_ltempbuf,"+");
//                 
//                strcpy ( u8_lbuf, pt1 ) ;
                
//                printf("u8_ltempbuf Rec.SMS:-%s,%d\r\n",u8_ltempbuf,u8_strlenbuf);
                
                memset(passwordbuf, 0x00, sizeof(passwordbuf));
                memset(paratypebuf, 0x00, sizeof(paratypebuf));
                memset(ipaddrbuf, 0x00, sizeof(ipaddrbuf));
                memset(apnbuf, 0x00, sizeof(apnbuf));
                memset(slnobuf, 0x00, sizeof(slnobuf));
                
                temp_ptr1= strtok (u8_ltempbuf,",*");


                strcpy ( passwordbuf, temp_ptr1 ) ;
//                printf("passwordbuf:%s\r\n",passwordbuf);
                if(strcmp ( temp_ptr1, "&1234" ) == 0)
                {
                    
//                    printf("password Ok\r\n"); 
                    temp_ptr1 = strtok (NULL, ",*");
                    strcpy ( paratypebuf, temp_ptr1 ) ;
//                    printf ("paratypebuf:%s,temp_ptr1:%s\n",paratypebuf,temp_ptr1);
                    if(strcmp ( temp_ptr1, "IP" ) == 0)
                    {
//                        printf ("paratypebuf is IP \n");
                        temp_ptr1 = strtok (NULL, ",*");
                        strcpy ( ipaddrbuf, temp_ptr1 ) ;
                        if(ipaddrbuf[0] == ' ')
                        {
                            printf ("Invalid ip!\n");
                        }
                        else
                        {
                            printf ("IP:%s\n",ipaddrbuf);
                            saveIPaddr((uint8_t *)ipaddrbuf);
                        }
                    }
                    else if(strcmp ( temp_ptr1, "APN" ) == 0)
                    {
//                        printf ("paratypebuf is IP \n");
                        temp_ptr1 = strtok (NULL, ",*");
                        strcpy ( apnbuf, temp_ptr1 ) ;
                        if(apnbuf[0] == ' ')
                        {
                            printf ("Invalid APN!\n");
                        }
                        else
                        {
                            printf ("APN:%s\n",apnbuf);
                            saveAPNaddr((uint8_t *)apnbuf);
                        }
                    }
                    else if(strcmp ( temp_ptr1, "SL" ) == 0)
                    {
//                        printf ("paratypebuf is IP \n");
                        temp_ptr1 = strtok (NULL, ",*");
                        strcpy ( slnobuf, temp_ptr1 ) ;
                        if(slnobuf[0] == ' ')
                        {
                            printf ("Invalid SL.No!\n");
                        }
                        else
                        {
                            printf ("SL.No:%s\n",slnobuf);
                            saveserialNo((uint8_t *)slnobuf);
                        }
                    }
                    else if(strcmp ( temp_ptr1, "SMR" ) == 0)
                    {
//                        printf ("paratypebuf is IP \n");
                        temp_ptr1 = strtok (NULL, ",*");
                        strcpy ( slnobuf, temp_ptr1 ) ;
                        if(slnobuf[0] == ' ')
                        {
                            printf ("Invalid SMR CLEAR!\n");
                        }
                        else if(slnobuf[0] == '0')
                        {
                            smr_clear();
                            printf ("SMR CLEARED.\n");
                        }
                    }
                    else if(strcmp ( temp_ptr1, "MEM" ) == 0)
                    {
//                        printf ("paratypebuf is IP \n");
                        temp_ptr1 = strtok (NULL, ",*");
                        strcpy ( slnobuf, temp_ptr1 ) ;
                        if(slnobuf[0] == ' ')
                        {
                            printf ("Invalid MEM CLEAR!\n");
                        }
                        else if(slnobuf[0] == '0')
                        {
                            exflash_erras();
                            printf ("MEM CLEARED.\n");
                            
                        }
                    }
                    else
                    {
                        printf ("paratypebuf is fail! \n");
                    }
                }
                else
                {
                    printf("password Fail!\r\n"); 
                }
                for(blinkcnt = 0;blinkcnt<50;)
                {
                    u32_ledblinkcnt++;
                    if(u32_ledblinkcnt > 300000)
                    {
                        blinkcnt++;
                        u32_ledblinkcnt = 0;
//                            GPIO_PB30_Set();//blue led
                        POWER_KEY_Set();//red led
                    }
                    else if(u32_ledblinkcnt > 200000)
                    {
//                            GPIO_PB30_Clear();//blue led
                        POWER_KEY_Clear();//red led
                    }
                    else
                    {
//                            GPIO_PB30_Set();//blue led
                        POWER_KEY_Set();//red led
                    }
                }
                u8_atcmd_status = AT_UNKNOWN;   
            }
            else if (strstr(rx_buffer, "OK")) 
            { 
                u8_atcmd_status = AT_OK;
//                printf("-------Ok\r\n"); 
                u8_datasendEN=0;
//                GPIO_PB30_Clear();//blue led
//                POWER_KEY_Clear();//red led
            }
            else
            {
                u8_atcmd_status = AT_UNKNOWN;
//                printf("-------Error3\r\n"); 
                u8_datasendEN = 0;
//                GPIO_PB30_Clear();//blue led
//                POWER_KEY_Clear();//red led
//                u8_atcmd_status = AT_ERROR;
            }
            POWER_KEY_Clear();//red led
            break;
        }
//        else if(timedout == 1)
//        {
//            printf("timedout\r\n");
//            u8_atcmd_status = AT_ERROR;
//            printf("%s",rx_buffer); 
//            timedout = 0;
//            timeout_f = 1; 
//            break;
//        }
    }  
    return 1;
}
bool myatSIstaus_cmd(char *inbuf,uint32_t respdelay,uint8_t *connId,uint16_t *sent,uint16_t *received,uint16_t *buff_in,uint16_t *ack_waiting)
{
    extern volatile bool       response_f,exception_f;
    extern volatile uint8_t u8_atcmd_status;
    extern APP_DATA appData;
    char u8_ltempbuf[100] = {0};
    
//    uint8_t u8_lrssi =0,u8_lber =0;
    //char s1[] = "Fun with STL"; 
    //char s2[] = "OK"; 
//    char* p;
    char temp_input[AT_TRANSFER_SIZE];
    uint16_t tx_index = 0;//,u16_ledblinkcnt=0;
    uint32_t response_fcnt=0,loopinfinetcnt=0;
    memset( ( void* )temp_input, 0, AT_TRANSFER_SIZE );
    while (*inbuf != '\0') 
    {
        temp_input[ tx_index++ ] = *inbuf;
        inbuf++;
    } 
    temp_input[ tx_index++ ] = '\r';
    temp_input[ tx_index++ ] = '\n';
    tx_buffer[ tx_index ] = '\0';
//    at_parse( temp_input, &temp_cb, &temp_timer );//
//    dev_timer_load( temp_timer );
//    while( cue_f ) 
//        at_process();
//
//    while( !dev_tx( *( temp_input++ ) ) );
//
//    dev_adapter_reset();
//    dev_timer_start();
    
    dev_timer_load( respdelay );
    dev_timer_start();
    memset( ( void* )rx_buffer, 0, AT_TRANSFER_SIZE );
    dev_adapter_reset ();
    timeout_f = false;
    response_f = false;
    printf("tx:%s\r\n",temp_input);
    DRV_USART_WriteBufferAdd(appData.usartHandle, temp_input,tx_index,&appData.bufferHandle);
    while(DRV_USART_BufferStatusGet(appData.bufferHandle) != DRV_USART_BUFFER_EVENT_COMPLETE)
    {
        loopinfinetcnt=0;
        if(response_f == 1)
        {
            response_fcnt++; 
        }
        if((timeout_f == 1)||(response_fcnt >100000)||(loopinfinetcnt>100000000))
        {   
            response_fcnt = 100000;
            printf("rpy:-%s\r\n",rx_buffer);
            strcpy ( u8_ltempbuf, rx_buffer ) ;
            char connIdbuf[10] = {0},sentbuf[10] = {0},receivedbuf[10] = {0},buff_inbuf[10] = {0},ack_waitingbuf[10] = {0};
            uint8_t len=0;
            uint16_t pow10[6] = {0,1,10,100,1000,10000};
            uint16_t u16_temp = 0;
            temp_ptr1= strtok (u8_ltempbuf,",*");
            strcpy ( connIdbuf, temp_ptr1 ) ;
//            printf("connIdbuf:%s\r\n",connIdbuf);
            if(strstr(rx_buffer, "NO CARRIER"))
            {
                u8_atcmd_status = AT_NOCARRIER;
//                printf("------->\r\n"); 
//                u8_atcmd_status = AT_ERROR;
            }
            else //if(1)//((strcmp ( connIdbuf, "#SI: 1" ) == 0)||(strcmp ( connIdbuf, "#SI: 2" ) == 0)||(strcmp ( connIdbuf, "#SI: 3" ) == 0)||(strcmp ( connIdbuf, "#SI: 4" ) == 0)||(strcmp ( connIdbuf, "#SI: 5" ) == 0)||(strcmp ( connIdbuf, "#SI: 6" ) == 0))
            {
                if(strcmp ( connIdbuf, "#SI: 1" ) == 0)
                    *connId = 1;
                else if(strcmp ( connIdbuf, "#SI: 2" ) == 0)
                    *connId = 2;
                else if(strcmp ( connIdbuf, "#SI: 3" ) == 0)
                    *connId = 3;
                else if(strcmp ( connIdbuf, "#SI: 4" ) == 0)
                    *connId = 4;
                else if(strcmp ( connIdbuf, "#SI: 5" ) == 0)
                    *connId = 5;
                else if(strcmp ( connIdbuf, "#SI: 6" ) == 0)
                    *connId = 6;
                
                temp_ptr1 = strtok (NULL, ",*");//1234
                strcpy ( sentbuf, temp_ptr1 ) ;
                len = strlen(sentbuf);
                u16_temp = 0;
                for(uint8_t i= 0;i<len;i++)
                {
                    u16_temp = u16_temp + ((sentbuf[i] - 0x30)*pow10[len - i]);
                }
                *sent = u16_temp;
//                printf("sentbuf:%s,len=%d,sent=%d\r\n",sentbuf,len,*sent);
                
                temp_ptr1 = strtok (NULL, ",*");//1234
                strcpy ( receivedbuf, temp_ptr1 ) ;
                len = strlen(receivedbuf);
                u16_temp = 0;
                for(uint8_t i= 0;i<len;i++)
                {
                    u16_temp = u16_temp + ((receivedbuf[i] - 0x30)*pow10[len - i]);
                }
                *received = u16_temp;
//                printf("receivedbuf:%s,len=%d,socketinfobuf=%d\r\n",receivedbuf,len,*received);
                
                temp_ptr1 = strtok (NULL, ",*");//1234
                strcpy ( buff_inbuf, temp_ptr1 ) ;
                len = strlen(buff_inbuf);
                u16_temp = 0;
                for(uint8_t i= 0;i<len;i++)
                {
                    u16_temp = u16_temp + ((buff_inbuf[i] - 0x30)*pow10[len - i]);
                }
                *buff_in = u16_temp;
//                printf("buff_inbuf:%s,len=%d,buff_in=%d\r\n",buff_inbuf,len,*buff_in);
                
                temp_ptr1 = strtok (NULL, "\r\n,*");//1234
                strcpy ( ack_waitingbuf, temp_ptr1 ) ;
                len = strlen(ack_waitingbuf);
                u16_temp = 0;
                for(uint8_t i= 0;i<len;i++)
                {
                    u16_temp = u16_temp + ((ack_waitingbuf[i] - 0x30)*pow10[len - i]);
                }
                *ack_waiting = u16_temp;
//                printf("ack_waitingbuf:%s,len=%d,ack_waiting=%d\r\n",ack_waitingbuf,len,*ack_waiting);

                u8_atcmd_status = AT_OK;   
            }
//            else
//            {
//                u8_atcmd_status = AT_UNKNOWN;
//                printf("-------Error3\r\n"); 
//                u8_datasendEN = 0;
//                GPIO_PB30_Clear();//blue led
////                u8_atcmd_status = AT_ERROR;
//            }
            break;
        }
//        else if(timedout == 1)
//        {
//            printf("timedout\r\n");
//            u8_atcmd_status = AT_ERROR;
//            printf("%s",rx_buffer); 
//            timedout = 0;
//            timeout_f = 1; 
//            break;
//        }
    }  
    return 1;
}
void at_cmd_addition
(
                char *input
)
{
    char* temp_input = input;
    dev_timer_start();
    while( !exception_f )
        at_process();

    dev_timer_stop();

    while( !dev_tx( *( temp_input++ ) ) );

    dev_adapter_reset();
    dev_timer_restart();
}

void at_cmd_save
(
                char *cmd,
        uint32_t timeout,
        at_cmd_cb getter,
        at_cmd_cb setter,
        at_cmd_cb tester,
        at_cmd_cb executer
)
{
    if ( !setter )
        setter = cb_default;

    if( !getter )
        getter = cb_default;

    if( !tester )
        tester = cb_default;

    if( !executer )
        executer = cb_default;

    if( !timeout )
        timeout = AT_DEFAULT_TIMEOUT;

    at_parser_store( cmd, timeout, getter, setter, tester, executer );
}

void at_process
(
                void
)
{
    //response_f = true;
    if( response_f )
    {
        dev_hal_cts_ctl( false );
        dev_timer_stop();
        at_parse( rx_buffer, &cb, &temp_timer );
        cb( rx_buffer );
        dev_adapter_reset();

        timeout_f = false;
        exception_f = false;
        response_f = false;
        cue_f = false;
    }

    if( timeout_f )
    {
        dev_hal_cts_ctl( false );
        dev_timer_stop();
        at_parse( rx_buffer, &cb, &temp_timer );
        cb( rx_buffer );
        dev_adapter_reset();

        timeout_f = false;
        exception_f = false;
        response_f = true;
        cue_f = false;
    }
}

/*************** END OF FUNCTIONS *********************************************/
