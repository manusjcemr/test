/*******************************************************************************
  MPLAB Harmony Application Source File

  Company:
    Microchip Technology Inc.

  File Name:
    app2.c

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

#include "app2.h"

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
    This structure should be initialized by the APP2_Initialize function.

    Application strings and buffers are be defined outside this structure.
*/

APP2_DATA app2Data;

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************
volatile char gpsrxChar ,guchr_temp1,guchr_validedata; 
static void _APP2_UART_ReceiveCallback(    DRV_USART_BUFFER_EVENT bufferEvent,
    DRV_USART_BUFFER_HANDLE bufferHandle,
    uintptr_t context);
extern uint8_t new_gpsdataset;
extern uint8_t u8_gerrercode1;
bool ch_gpstimereloadstatuse =0;
char gps_GPRMCdata[560]={0};
float flt_gps_SpeedOverGround=0;
float flt_gps_CourseOverGround=0;
/* TODO:  Add any necessary callback functions.
*/

// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************


/* TODO:  Add any necessary local functions.
*/


// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP2_Initialize ( void )

  Remarks:
    See prototype in app2.h.
 */

void APP2_Initialize ( void )
{
    /* Place the App state machine in its initial state. */
    app2Data.state = APP2_STATE_INIT;



    /* TODO: Initialize your application's state machine and other
     * parameters.
     */
}


/******************************************************************************
  Function:
    void APP2_Tasks ( void )

  Remarks:
    See prototype in app2.h.
 */

void APP2_Tasks ( void )
{

    /* Check the application's current state. */
    switch ( app2Data.state )
    {
        /* Application's initial state. */
        case APP2_STATE_INIT:
        {
//            printf("app2Data.state =APP2_STATE_INIT\r\n");
//            app2Data.usartHandle = DRV_USART_Open(DRV_USART_INDEX_1, DRV_IO_INTENT_READWRITE);
            app2Data.usartHandle = DRV_USART_Open(DRV_USART_INDEX_1,
                         (DRV_IO_INTENT_READWRITE | DRV_IO_INTENT_BLOCKING));
//            if (app2Data.usartHandle != DRV_HANDLE_INVALID)
//            {
//                DRV_USART_BufferEventHandlerSet(app2Data.usartHandle, _APP2_UART_ReceiveCallback, 0);
//                app2Data.state = APP2_STATE_SERVICE_TASKS;
//                printf("app2Data.usartHandle != DRV_HANDLE_INVALID\r\n");
//            }
//            else
//            {
//                app2Data.state = APP2_STATE_ERROR;
//                printf("app2Data.state = APP2_STATE_ERROR\r\n");
//            }
            /* Check the USART driver handler */
            if (app2Data.usartHandle != DRV_HANDLE_INVALID )
            {
                DRV_USART_BufferEventHandlerSet(app2Data.usartHandle,&_APP2_UART_ReceiveCallback,0);
                app2Data.state = APP2_STATE_SERVICE_TASKS;
//                DRV_USART_WriteQueuePurge(app2Data.usartHandle);
//                DRV_USART_ReadQueuePurge(app2Data.usartHandle);
//                printf("app2Data.usartHandle != DRV_HANDLE_INVALID\r\n");
                DRV_USART_ReadBufferAdd(app2Data.usartHandle,(void*)&gpsrxChar,1,&app2Data.bufferHandle);
                app2Data.datavalideStatus = 0;
            }
            else
            {
                printf("app2Data.state = APP2_STATE_ERROR\r\n");
                    // Try again to get handle
            }
            break;
        }

        case APP2_STATE_SERVICE_TASKS:
        {
           /* if(app2Data.datavalideStatus == 1)
            {
                
                //$GPRMC,092139.000,A,1305.2216,N,07733.1789,E,0.45,308.93,250221,,,A*6F
                //$GPRMC,111727.090,V,         , ,          , ,0.00,0.00  ,260221,,,N*
                //$GPRMC,111727.090,V,,,,,0.00,0.00,260221,,,N*
                char tempbuff[200];
                
                memset(tempbuff, 0x00, sizeof(tempbuff));
                strcpy ( tempbuff, app2Data.readBuffer ) ;//strcpy ( tempbuff, "$GPRMC,092139.000,A,1305.2216,N,07733.1789,E,0.45,308.93,250221,,,A*6F" ) ;
//                printf("\r\n GPS = %s\r\n",tempbuff);
                
                pt1= strtok (tempbuff,",*");
                //if(strcmp ( pt1, "$GPRMC" ) == 0)
                {
                    memset(gps_UTCTime, 0x00, sizeof(gps_UTCTime));
					memset(gps_Status, 0x00, sizeof(gps_Status));
					memset(gps_Latitude, 0x00, sizeof(gps_Latitude));
					memset(gps_NSIndicator, 0x00, sizeof(gps_NSIndicator));
					memset(gps_Longitude, 0x00, sizeof(gps_Longitude));
                    memset(gps_EWIndicator, 0x00, sizeof(gps_EWIndicator));
                    memset(gps_SpeedOverGround, 0x00, sizeof(gps_SpeedOverGround));
					memset(gps_CourseOverGround, 0x00, sizeof(gps_CourseOverGround));
					memset(gps_Date, 0x00, sizeof(gps_Date));
                    
                    memset(gps_Latitude_dec, 0x00, sizeof(gps_Latitude_dec));
                    memset(gps_Longitude_dec, 0x00, sizeof(gps_Longitude_dec));
                    
					//
                    pt1 = strtok (NULL, ",*");
                    strcpy ( gps_UTCTime, pt1 ) ;
//					printf("UTCTime:%s\r\n",gps_UTCTime);
                    
					pt1 = strtok (NULL, ",*");
                    if(strcmp ( pt1, "A" ) == 0)
                    {
                        strcpy ( gps_Status, pt1 ) ;
//                        printf ("Status:%s,Data valid\n",gps_Status);

                        pt1 = strtok (NULL, ",*");
                        strcpy ( gps_Latitude, pt1 ) ;
//                        printf ("Latitude:%s\n",gps_Latitude);
                        ///1305.2216
                        float flt_temp,flt_temp1,flt_temp2,flt_temp3;
                        flt_temp1 = ((gps_Latitude[0] - 0x30)*10) + (gps_Latitude[1] - 0x30);
                        flt_temp2 = ((gps_Latitude[2] - 0x30)*10) + (gps_Latitude[3] - 0x30);
                        flt_temp3 = ((gps_Latitude[5] - 0x30)*1000) +((gps_Latitude[6] - 0x30)*100) +((gps_Latitude[7] - 0x30)*10) + (gps_Latitude[8] - 0x30);
                        flt_temp3 = flt_temp3/10000.0;
//                        printf ("flt_temp1:%f,flt_temp2:%f,flt_temp3:%f\n",flt_temp1,flt_temp2,flt_temp3);
                        
                        flt_temp = flt_temp1 + (flt_temp2/60.0) + (flt_temp3/60.0);
                        sprintf(gps_Latitude_dec,"%f",flt_temp);
//                        printf ("Latitude_dec:%s\n",gps_Latitude_dec);
                        ///
                        
                        pt1 = strtok (NULL, ",*");
                        strcpy ( gps_NSIndicator, pt1 ) ;
//                        printf ("N/S Indicator:%s\n",gps_NSIndicator);
                        
                        pt1 = strtok (NULL, ",*");
                        strcpy ( gps_Longitude, pt1 ) ;
//                        printf ("Longitude:%s\n",gps_Longitude);
                        //07733.1789
                        //float flt_temp,flt_temp1,flt_temp2,flt_temp3;
                        flt_temp1 = ((gps_Longitude[0] - 0x30)*100) + ((gps_Longitude[1] - 0x30)*10) + (gps_Longitude[2] - 0x30);
                        flt_temp2 = ((gps_Longitude[3] - 0x30)*10) + (gps_Longitude[4] - 0x30);
                        flt_temp3 = ((gps_Longitude[6] - 0x30)*1000) +((gps_Longitude[7] - 0x30)*100) +((gps_Longitude[8] - 0x30)*10) + (gps_Latitude[9] - 0x30);
                        flt_temp3 = flt_temp3/10000.0;
                        flt_temp = flt_temp1 + (flt_temp2/60.0) + (flt_temp3/60.0);
                        sprintf(gps_Longitude_dec,"%f",flt_temp);
//                        printf ("Longitude_dec:%s\n",gps_Longitude_dec);
                        //
                        
                        pt1 = strtok (NULL, ",*");
                        strcpy ( gps_EWIndicator, pt1 ) ;
//                        printf ("E/W Indicator:%s\n",gps_EWIndicator);
                        
                        pt1 = strtok (NULL, ",*");
                        strcpy ( gps_SpeedOverGround, pt1 ) ;
//                        printf ("Speed Over Ground:%s\n",gps_SpeedOverGround);
                        
                        pt1 = strtok (NULL, ",*");
                        strcpy ( gps_CourseOverGround, pt1 ) ;
//                        printf ("Course Over Ground:%s\n",gps_CourseOverGround);
                        
                        pt1 = strtok (NULL, ",*");
                        strcpy ( gps_Date, pt1 ) ;
//                        printf ("Date:%s\n",gps_Date);
                    }
                    else
                    {
                        strcpy ( gps_Status, pt1 ) ;
//                        printf ("Status:%s,Data not valid\n",gps_Status);
                        //$GPRMC,092139.000,A,1305.2216,N,07733.1789,E,0.45,308.93,250221,,,A*6F
                        //pt1 = strtok (NULL, ",*");
                        strcpy ( gps_Latitude, "0000.0000" ) ;
//                        printf ("Latitude:%s\n",gps_Latitude);
                        
                        //pt1 = strtok (NULL, ",*");
                        strcpy ( gps_NSIndicator, "N" ) ;
//                        printf ("N/S Indicator:%s\n",gps_NSIndicator);
                        
                        //pt1 = strtok (NULL, ",*");
                        strcpy ( gps_Longitude, "00000.0000" ) ;
//                        printf ("Longitude:%s\n",gps_Longitude);
                        
                        //pt1 = strtok (NULL, ",*");
                        strcpy ( gps_EWIndicator, "E" ) ;
//                        printf ("E/W Indicator:%s\n",gps_EWIndicator);
                        
                        pt1 = strtok (NULL, ",*");
                        strcpy ( gps_SpeedOverGround, pt1 ) ;
//                        printf ("Speed Over Ground:%s\n",gps_SpeedOverGround);
                        
                        pt1 = strtok (NULL, ",*");
                        strcpy ( gps_CourseOverGround, pt1 ) ;
//                        printf ("Course Over Ground:%s\n",gps_CourseOverGround);
                        
                        pt1 = strtok (NULL, ",*");
                        strcpy ( gps_Date, pt1 ) ;
//                        printf ("Date:%s\n",gps_Date);
                    }
                }
                app2Data.datavalideStatus = 0;
                new_gpsdataset = 1;
            }*/
            break;
        }

        /* TODO: implement your application state machine.*/
        case APP2_STATE_ERROR:
            break;

        /* The default state should never be executed. */
        default:
        {
            /* TODO: Handle error in application's state machine. */
            break;
        }
    }
}
//void loadgpsdata(void)
bool loadgpsdata(char *ch_gps_UTCTime,char *ch_gps_UTCdate)
{
//    if(app2Data.datavalideStatus == 1)
    {

        //$GPRMC,092139.000,A,1305.2216,N,07733.1789,E,0.45,308.93,250221,,,A*6F
        //$GPRMC,111727.090,V,         , ,          , ,0.00,0.00  ,260221,,,N*
        //$GPRMC,111727.090,V,,,,,0.00,0.00,260221,,,N*
        char tempbuff[200];

        memset(tempbuff, 0x00, sizeof(tempbuff));
        strcpy ( tempbuff, gps_GPRMCdata ) ;//strcpy ( tempbuff, app2Data.readBuffer ) ;//strcpy ( tempbuff, "$GPRMC,092139.000,A,1305.2216,N,07733.1789,E,0.45,308.93,250221,,,A*6F" ) ;
//                printf("\r\n GPS = %s\r\n",tempbuff);

        pt1= strtok (tempbuff,",*");
        //if(strcmp ( pt1, "$GPRMC" ) == 0)
        {
            memset(gps_UTCTime, 0x00, sizeof(gps_UTCTime));
            memset(gps_Status, 0x00, sizeof(gps_Status));
            memset(gps_Latitude, 0x00, sizeof(gps_Latitude));
            memset(gps_NSIndicator, 0x00, sizeof(gps_NSIndicator));
            memset(gps_Longitude, 0x00, sizeof(gps_Longitude));
            memset(gps_EWIndicator, 0x00, sizeof(gps_EWIndicator));
            memset(gps_SpeedOverGround, 0x00, sizeof(gps_SpeedOverGround));
            memset(gps_CourseOverGround, 0x00, sizeof(gps_CourseOverGround));
            memset(gps_Date, 0x00, sizeof(gps_Date));

            memset(gps_Latitude_dec, 0x00, sizeof(gps_Latitude_dec));
            memset(gps_Longitude_dec, 0x00, sizeof(gps_Longitude_dec));

            //
            pt1 = strtok (NULL, ",*");
            strcpy ( gps_UTCTime, pt1 ) ;
            strcpy(ch_gps_UTCTime, pt1); 
//					printf("UTCTime:%s\r\n",gps_UTCTime);

            pt1 = strtok (NULL, ",*");
            if(strcmp ( pt1, "A" ) == 0)
            {
                u8_gerrercode1 = 0;
                if((ch_gps_UTCTime[4]=='0')&&(ch_gps_UTCTime[5]=='0'))
                    ch_gpstimereloadstatuse =1;
                strcpy ( gps_Status, pt1 ) ;
//                        printf ("Status:%s,Data valid\n",gps_Status);

                pt1 = strtok (NULL, ",*");
                strcpy ( gps_Latitude, pt1 ) ;
//                        printf ("Latitude:%s\n",gps_Latitude);
                ///1305.2216
                float flt_temp,flt_temp1,flt_temp2,flt_temp3;
                flt_temp1 = ((gps_Latitude[0] - 0x30)*10) + (gps_Latitude[1] - 0x30);
                flt_temp2 = ((gps_Latitude[2] - 0x30)*10) + (gps_Latitude[3] - 0x30);
                flt_temp3 = ((gps_Latitude[5] - 0x30)*1000) +((gps_Latitude[6] - 0x30)*100) +((gps_Latitude[7] - 0x30)*10) + (gps_Latitude[8] - 0x30);
                flt_temp3 = flt_temp3/10000.0;
//                        printf ("flt_temp1:%f,flt_temp2:%f,flt_temp3:%f\n",flt_temp1,flt_temp2,flt_temp3);

                flt_temp = flt_temp1 + (flt_temp2/60.0) + (flt_temp3/60.0);
                uint16_t flt_temp_int = flt_temp;
                uint16_t flt_temp_flt = flt_temp * 100.0;
                flt_temp_flt = flt_temp_flt % 100;
                sprintf(gps_Latitude_dec,"%d.%d",flt_temp_int,flt_temp_flt);
//                        printf ("Latitude_dec:%s\n",gps_Latitude_dec);
                ///

                pt1 = strtok (NULL, ",*");
                strcpy ( gps_NSIndicator, pt1 ) ;
//                        printf ("N/S Indicator:%s\n",gps_NSIndicator);

                pt1 = strtok (NULL, ",*");
                strcpy ( gps_Longitude, pt1 ) ;
//                        printf ("Longitude:%s\n",gps_Longitude);
                //07733.1789
                //float flt_temp,flt_temp1,flt_temp2,flt_temp3;
                flt_temp1 = ((gps_Longitude[0] - 0x30)*100) + ((gps_Longitude[1] - 0x30)*10) + (gps_Longitude[2] - 0x30);
                flt_temp2 = ((gps_Longitude[3] - 0x30)*10) + (gps_Longitude[4] - 0x30);
                flt_temp3 = ((gps_Longitude[6] - 0x30)*1000) +((gps_Longitude[7] - 0x30)*100) +((gps_Longitude[8] - 0x30)*10) + (gps_Latitude[9] - 0x30);
                flt_temp3 = flt_temp3/10000.0;
                flt_temp = flt_temp1 + (flt_temp2/60.0) + (flt_temp3/60.0);
                
                flt_temp_int = flt_temp;
                flt_temp_flt = flt_temp * 100.0;
                flt_temp_flt = flt_temp_flt % 100;
//                sprintf(gps_Longitude_dec,"%f",flt_temp);
                sprintf(gps_Longitude_dec,"%d.%d",flt_temp_int,flt_temp_flt);
                
//                        printf ("Longitude_dec:%s\n",gps_Longitude_dec);
                //

                pt1 = strtok (NULL, ",*");
                strcpy ( gps_EWIndicator, pt1 ) ;
//                        printf ("E/W Indicator:%s\n",gps_EWIndicator);

                pt1 = strtok (NULL, ",*");
                strcpy ( gps_SpeedOverGround, pt1 ) ;
//                printf ("Speed Over Ground:%s\n",gps_SpeedOverGround);
                
                flt_gps_SpeedOverGround = (float)atof(gps_SpeedOverGround);
//                printf("%f",flt_gps_SpeedOverGround); // here you can use f

//                uint8_t len1 = 0,set_deci=0;
//                uint16_t int2arr[4]={1,10,100,1000};
//                float flt_gps_SpeedOverGround=0;
//                uint16_t u16_gps_SpeedOverGround_int=0,u16_gps_SpeedOverGround_ppoint=0;
//                len1 = strlen(gps_SpeedOverGround);
//                for(uint8_t i=0;i<len1;i++)
//                {
//                    if(gps_SpeedOverGround[i]=='.')
//                        set_deci=1;
//                    if(set_deci==0)
//                        u16_gps_SpeedOverGround_int = u16_gps_SpeedOverGround_int + gps_SpeedOverGround[i];
//                }
                pt1 = strtok (NULL, ",*");
                strcpy ( gps_CourseOverGround, pt1 ) ;
//                printf ("Course Over Ground:%s\n",gps_CourseOverGround);
                flt_gps_CourseOverGround = (float)atof(gps_CourseOverGround);
//                printf("%f",flt_gps_CourseOverGround); // here you can use f
                
                pt1 = strtok (NULL, ",*");
                strcpy ( gps_Date, pt1 ) ;
                strcpy(ch_gps_UTCdate, pt1); 
//                        printf ("Date:%s\n",gps_Date);
            }
            else
            {
                u8_gerrercode1 = 1;
                if(strlen(gps_UTCTime) >= 6)
                {
                    ;
                }
                else
                {
                    strcpy ( gps_UTCTime, "000000" ) ;
                }

                strcpy ( gps_Status, "V") ;
//                        printf ("Status:%s,Data not valid\n",gps_Status);
                //$GPRMC,092139.000,A,1305.2216,N,07733.1789,E,0.45,308.93,250221,,,A*6F
                //pt1 = strtok (NULL, ",*");
                strcpy ( gps_Latitude, "0000.0000" ) ;
//                        printf ("Latitude:%s\n",gps_Latitude);

                //pt1 = strtok (NULL, ",*");
                strcpy ( gps_NSIndicator, "N" ) ;
//                        printf ("N/S Indicator:%s\n",gps_NSIndicator);

                //pt1 = strtok (NULL, ",*");
                strcpy ( gps_Longitude, "00000.0000" ) ;
//                        printf ("Longitude:%s\n",gps_Longitude);

                //pt1 = strtok (NULL, ",*");
                strcpy ( gps_EWIndicator, "E" ) ;
//                        printf ("E/W Indicator:%s\n",gps_EWIndicator);

                pt1 = strtok (NULL, ",*");
                strcpy ( gps_SpeedOverGround, pt1 ) ;
//                printf ("Speed Over Ground:%s\n",gps_SpeedOverGround);
                flt_gps_SpeedOverGround = (float)atof(gps_SpeedOverGround);
//                printf("%f",flt_gps_SpeedOverGround); // here you can use f

                pt1 = strtok (NULL, ",*");
                strcpy ( gps_CourseOverGround, pt1 ) ;
//                printf ("Course Over Ground:%s\n",gps_CourseOverGround);
                flt_gps_CourseOverGround = (float)atof(gps_CourseOverGround);
//                printf("%f",flt_gps_CourseOverGround); // here you can use f

                pt1 = strtok (NULL, ",*");
                if(strlen(pt1) >= 6)
                {
                    strcpy ( gps_Date, pt1 ) ;
                    
                }
                else
                {
                    strcpy ( gps_Date, "000000" ) ;
                }
                strcpy(ch_gps_UTCdate, pt1); 
//                        printf ("Date:%s\n",gps_Date);
            }
        }
        
        app2Data.datavalideStatus = 0;
        new_gpsdataset = 1;
        
        if(ch_gpstimereloadstatuse == 1)//&&(tempgps_UTCTime[4]=='0')&&(tempgps_UTCTime[5]=='0'))
            return 1;
        else
            return 0;
    }
}
bool loadgpstime(char *ch_gps_UTCTime,char *ch_gps_UTCdate)
{
    char tempbuff[200];
    char tempgps_UTCTime[20];
    char tempgps_UTCdate[20];
//    if(app2Data.datavalideStatus == 1)
    {

        //$GPRMC,092139.000,A,1305.2216,N,07733.1789,E,0.45,308.93,250221,,,A*6F
        //$GPRMC,111727.090,V,         , ,          , ,0.00,0.00  ,260221,,,N*
        //$GPRMC,111727.090,V,,,,,0.00,0.00,260221,,,N*
        
        
        memset(tempbuff, 0x00, sizeof(tempbuff));
        strcpy ( tempbuff, app2Data.readBuffer ) ;//strcpy ( tempbuff, "$GPRMC,092139.000,A,1305.2216,N,07733.1789,E,0.45,308.93,250221,,,A*6F" ) ;
//                printf("\r\n GPS = %s\r\n",tempbuff);

        pt1= strtok (tempbuff,",*");
        //if(strcmp ( pt1, "$GPRMC" ) == 0)
        {
            memset(ch_gps_Status, 0x00, sizeof(ch_gps_Status));
            //
            pt1 = strtok (NULL, ",*");
            strcpy ( tempgps_UTCTime, pt1 ) ;
			strcpy(ch_gps_UTCTime, pt1); 		

            pt1 = strtok (NULL, ",*");
            if(strcmp ( pt1, "A" ) == 0)
            {
                ch_gpstimereloadstatuse =1;
                u8_gerrercode1 = 0;
            }
            else
            {
                u8_gerrercode1 = 1;
            }
            pt1 = strtok (NULL, ",*");
//                strcpy ( gps_Latitude, pt1 ) ;

                pt1 = strtok (NULL, ",*");
//                strcpy ( gps_NSIndicator, pt1 ) ;
//                        printf ("N/S Indicator:%s\n",gps_NSIndicator);

                pt1 = strtok (NULL, ",*");
//                strcpy ( gps_Longitude, pt1 ) ;

                
//                        printf ("Longitude_dec:%s\n",gps_Longitude_dec);
                //

                pt1 = strtok (NULL, ",*");
//                strcpy ( gps_EWIndicator, pt1 ) ;
//                        printf ("E/W Indicator:%s\n",gps_EWIndicator);

                pt1 = strtok (NULL, ",*");
//                strcpy ( gps_SpeedOverGround, pt1 ) ;
//                        printf ("Speed Over Ground:%s\n",gps_SpeedOverGround);

                pt1 = strtok (NULL, ",*");
//                strcpy ( gps_CourseOverGround, pt1 ) ;
//                        printf ("Course Over Ground:%s\n",gps_CourseOverGround);

                pt1 = strtok (NULL, ",*");
                strcpy ( tempgps_UTCdate, pt1 ) ;
                strcpy(ch_gps_UTCdate, pt1); 
        }
    }
    
    app2Data.datavalideStatus = 0;
//    printf("UTCTime:%s,ch_gpstimereloadstatuse:%d\r\n",tempgps_UTCTime,ch_gpstimereloadstatuse);
    if(ch_gpstimereloadstatuse == 1)//&&(tempgps_UTCTime[4]=='0')&&(tempgps_UTCTime[5]=='0'))
        return 1;
    else
        return 0;
}
static void _APP2_UART_ReceiveCallback(    DRV_USART_BUFFER_EVENT bufferEvent,
    DRV_USART_BUFFER_HANDLE bufferHandle,
    uintptr_t context)
{
//    printf("rec:$\r\n");
    DRV_USART_ReadBufferAdd(app2Data.usartHandle,(void*)&gpsrxChar,1,&app2Data.bufferHandle);
    if(app2Data.datavalideStatus == 0)
    {
        if (gpsrxChar == '$') 
        {
            //guchr_temp1 = 0;
            app2Data.readBufferCount = 0;
            memset(app2Data.readBuffer,0,sizeof(app2Data.readBuffer));
            app2Data.readBuffer[0] = '$';
        }
        else if (app2Data.readBuffer[0] == '$') 
        {
//            printf("rec:$\r\n");
            app2Data.readBufferCount++;
            app2Data.readBuffer[app2Data.readBufferCount] = gpsrxChar;
            if (app2Data.readBuffer[app2Data.readBufferCount] == '*') 
            {
                //$GPRMC,092139.000,A,1305.2216,N,07733.1789,E,0.45,308.93,250221,,,A*6F
                if((app2Data.readBuffer[1] == 'G')&&(app2Data.readBuffer[2] == 'P')&&(app2Data.readBuffer[3] == 'R')&&(app2Data.readBuffer[4] == 'M')&&(app2Data.readBuffer[5] == 'C'))
                {
                    app2Data.readBuffer[app2Data.readBufferCount+1] = '\0';
                   // guchr_validedata = 1;
                    app2Data.datavalideStatus = true;
                    memset(gps_GPRMCdata, 0x00, sizeof(gps_GPRMCdata));
                    strcpy ( gps_GPRMCdata, app2Data.readBuffer ) ;
                    app2Data.readBufferCount = 0;
                }
                else
                {
                    app2Data.datavalideStatus = false;
                    app2Data.readBufferCount = 0;
                    app2Data.readBuffer[0] = '\0';
                }
            }
            else if (app2Data.readBufferCount > APP2_USART_READ_BUFFER_SIZE) 
            {
                app2Data.datavalideStatus = false;
                app2Data.readBufferCount = 0;
                app2Data.readBuffer[0] = '\0';
            }
        }
    }
}

/*******************************************************************************
 End of File
 */
