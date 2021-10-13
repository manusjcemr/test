/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.78.1
        Device            :  PIC18F26K22
        Driver Version    :  2.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "mcc_generated_files/mcc.h"

/*
                         Main application
 */
#define SET_KEY         1
#define SET_LONG_KEY    2
#define UP_KEY          3
#define UP_LONG_KEY     4
#define DOWN_KEY        5
#define DOWN_LONG_KEY   6
#define DEFAULT_KEY     16

void myTimer1ISR(void);

unsigned char Key_Scan(void);
void Key_Service(void);
uint8_t uchr_PresentKey =0,uchr_PreviousKey = 0,uchr_DebounceCnt=0;
unsigned char uchr_restmode,uchr_dly,uchr_Curser,uchr_valuemodified;
unsigned int uint_updatEN,uint_resetcnt;
unsigned char uchr_Curser,uchr_mincurser,uchr_maxcurser;
unsigned int uint_data[4];
uint16_t u16_SETtemp,u16_SETtime,u16_displyfirstcnt=0;
uint8_t u8_loadON = 0,u8_loadONfirst = 0,u8_ledvalue=0,u8_led1=0,u8_led2=0,u8_led3=0;
volatile uint16_t u16_timesec =0;
void ctrl_task(void);
void int2arr (unsigned int uint_intdata);
unsigned char uchr_blinkdigit0,uchr_blinkdigit1,uchr_blinkdigit2,uchr_blinkdigit3;
enum menus{
    MAIN_MENU,
    off_MENU,
    PB_MENU,
    IB_MENU,
    PLM_MENU,
    HYS_MENU,
    CG1_MENU,
    CG2_MENU,
    COF_MENU,
    MDE_MENU,
    
    SET_TEMP_MENU,
    SET_TIME_MENU,
    
};
char menu;
uint16_t u16_off=0,u16_pb=0,u16_ib=0,u16_plm=0,u16_hys=0,u16_cg1=0,u16_cg2=0,u16_cof=0,u16_mde=0;


uint16_t u16_Temp=0,u16_Temp1 =0,u16_Temp2 =0,u16_offset,u16_gain1,u16_gain2;


float flt_Temp,flt_Temp1,flt_Temp2,flt_offset,flt_gain1,flt_gain2;



uint16_t u16_Tempvalue =0,uint_count=0,uint_count2 = 0,u8_sw_microEN=0;
uint8_t u8_calisetEN =0;
volatile uint8_t u8_powerduty = 0;
//PID variables
float PID_error = 0;
float previous_error = 0;
float elapsedTime, Time, timePrev;
float PID_value = 0;
//PID constants
float kp = 30;   float ki= 0.0005;//0.00025;   float kd = 15;
float PID_p = 0;    float PID_i = 0;    float PID_d = 0;

uint8_t u8_digit[4] ={0};
void write_2bytedata(unsigned char addr, unsigned int data);

float low_pass_filter(float x);
void display7seg(unsigned char data);
void display7seg2(unsigned char data);
void sev_display1(char DD0,char DD1,char DD2,char DD3);
//void Int_7segdisplay1(unsigned int value,char decimal);
//void Sring_7segdisplay1(char char3,char char2,char char1,char char0);
void sev_display2(char DD0,char DD1,char DD2,char DD3);
//void Int_7segdisplay2(unsigned int value,char decimal);
//void Sring_7segdisplay2(char char3,char char2,char char1,char char0);
enum dis7seg{
    LINE1 =1,
    LINE2        
};
void Int_7segdisplay(char line,unsigned int value,char decimal);
void Sring_7segdisplay(char line,char char3,char char2,char char1,char char0);

unsigned char uchr_blinkdigit0,uchr_blinkdigit1,uchr_blinkdigit2,uchr_blinkdigit3;

unsigned char uchr_LED1,uchr_LED2;
uint16_t convertedValue;
uint16_t uint_adccnt;
float flt_adcavg1,flt_adcavg2,flt_adc1,flt_adc2;
double lowPassExponential(double input, double average, double factor);
//------ Function to Return mask for common anode 7-seg. display
//7SEG FORMAT : DB G F E D C B A    C-E
//        bit : 7  6 5 4 3 2 1 0    D-C
//           P  0  0 0 1 0 0 0 0    E-D
//        a
//       ---
//     f| g |b
//       ---
//     e|   |c
//       --- .db
//        d 
//------ Function to Return mask for common anode 7-seg. display
unsigned short mask(unsigned short num) {
 switch (num) {
 case 0 : return 0x3F;//0
 case 1 : return 0x06;//1
 case 2 : return 0x5B;//2
 case 3 : return 0x4F;//3
 case 4 : return 0x66;//4
 case 5 : return 0x6D;//5
 case 6 : return 0x7D;//6
 case 7 : return 0x07;//7
 case 8 : return 0x7F;//8
 case 9 : return 0x6F;//9
 
 case 10 : return 0x00;//" "
 case ' ' : return 0x00;//" "
 
 case 'S' : return 0x6D;//" "
 case 'E' : return 0x79;//" "
 case 't' : return 0x78;//" "
 case 'A' : return 0x77;
 case 'u' : return 0x1C;
 case '-' : return 0x40;
 case 'N' : return 0x37;
 case 'n' : return 0x54;
 case 'M' : return 0x15;
 case 'R' : return 0x31;
 case 'd' : return 0x5E;
 case 'L' : return 0x38;
 case 'Y' : return 0x6E;
 case 'G' : return 0x3D;
 case 'F' : return 0x71;
 case 'C' : return 0x39; 
 case 'P' : return 0x73; 
 case 'b' : return 0x7C; 
 case 'H' : return 0x76; 
 case 'i' : return 0x10;  
 
 } //case end
}
void main(void)
{
    __delay_ms(1);
    // Initialize the device
    SYSTEM_Initialize();
    
    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global and Peripheral Interrupts
    SSR1_SetLow();
    u8_led1 = 0;
    SSR2_SetLow();
    u8_led2 = 0;
    __delay_ms(100);
    __delay_ms(100);
    //clear memory data if there is any value there at first time
//    for(int i =0;i<8;i++)
//    {
//        if((unsigned int)DATAEE_ReadByte(i) > 100)
//            DATAEE_WriteByte(i,0);
//    }   
    // restore eeprom data to corresponding variables
//    u16_off=0,u16_pb=0,u16_plm=0,u16_hys=0,u16_cg1=0,u16_cg2=0,u16_cof=0,u16_mde=0
            
    u16_SETtemp = (unsigned int)((DATAEE_ReadByte(1)*100) + DATAEE_ReadByte(0));
    if(u16_SETtemp > 999)
        u16_SETtemp = 250;
    u16_SETtime = (unsigned int)((DATAEE_ReadByte(3)*100) + DATAEE_ReadByte(2));
    if(u16_SETtime > 999)
        u16_SETtime = 20;
    u16_off = (unsigned int)((DATAEE_ReadByte(5)*100) + DATAEE_ReadByte(4));
    if(u16_off > 999)
        u16_off = 0;
    u16_pb = (unsigned int)((DATAEE_ReadByte(7)*100) + DATAEE_ReadByte(6));
    if(u16_pb > 999)
        u16_pb = 15;
    u16_ib = (unsigned int)((DATAEE_ReadByte(9)*100) + DATAEE_ReadByte(8));
    if(u16_ib > 999)
        u16_ib = 60;
    u16_plm = (unsigned int)((DATAEE_ReadByte(11)*100) + DATAEE_ReadByte(10));
    if(u16_plm > 999)
        u16_plm = 50;
    u16_hys = (unsigned int)((DATAEE_ReadByte(13)*100) + DATAEE_ReadByte(12));
    if(u16_hys > 999)
        u16_hys = 10;
    u16_cg1 = (unsigned int)((DATAEE_ReadByte(15)*100) + DATAEE_ReadByte(14));
    if(u16_cg1 > 999)
        u16_cg1 = 3;
    u16_cg2 = (unsigned int)((DATAEE_ReadByte(17)*100) + DATAEE_ReadByte(16));
    if(u16_cg2 > 999)
        u16_cg2 = 665;//670
    u16_cof = (unsigned int)((DATAEE_ReadByte(19)*100) + DATAEE_ReadByte(18));
    if(u16_cof > 999)
        u16_cof = 134;
    u16_mde = (unsigned int)((DATAEE_ReadByte(21)*100) + DATAEE_ReadByte(20));
    if(u16_mde > 999)
        u16_mde = 0;
    
//    u16_cg1 = 3;
//    u16_cg2=880;
//    u16_cof = 128;
//    u16_SETtemp = 50;
//    u16_pb = 10;
//    u16_plm = 50;
    
//    u16_gain1 = ((DATAEE_ReadByte(5)*100) + DATAEE_ReadByte(4));
//    if(u16_gain1 > 999)
//        u16_gain1 = 388;
//    
//    u16_offset = ((DATAEE_ReadByte(7)*100) + DATAEE_ReadByte(6));
//    if(u16_offset > 999)
//        u16_offset = 128;
    
    
    
    
//    u16_gain1 = 500;
//    u16_offset = 130;
    
    TMR1_SetInterruptHandler (myTimer1ISR);
        // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();
    kp = (1.0*u16_plm)/u16_pb;//ex:20 = 100/20=5
    ki = u16_ib;
    ki = 1.0/(ki*10.0);
    flt_gain1 = u16_cg1*100.0 + (u16_cg2 * 0.1) ;//u16_gain1;
    flt_gain1 = flt_gain1 * 0.001;
    flt_offset = (float)u16_cof;
    while (1)
    {
        // Add your application code
        if(TMR0_HasOverflowOccured() == true)//10msec 
        {   
            // Clearing IF flag
            INTCONbits.TMR0IF = 0;
            TMR0_ReadTimer();
            /********************/
            if(u8_calisetEN == 0)
            {
                if(SW_CFG_GetValue()== 0)//(RA2 == 0) // manual reset 
                {
                    uint_count++; // debounce count
                    if(uint_count > 200)// debounce count
                    {
                        uint_count = 0;
                        u8_calisetEN =1;
                        menu = off_MENU;
                    } 
                }
                else// auto reset
                {
                    uint_count = 0;
                }
            }
            if(SW_MICRO_GetValue()==0)
            {
                uint_count2++; // debounce count
                if(uint_count2 > 50)// debounce count
                {
                    uint_count2 = 0;
                    u8_sw_microEN=1;
                } 
            }
            else// auto reset
            {
                uint_count2 = 0;
                u8_sw_microEN=0;
            }
            
            
            Key_Service();
            if(uchr_DebounceCnt > 0)
            {
                uchr_DebounceCnt--;
                if(!uchr_DebounceCnt)
                {
                    if(uchr_PresentKey == SET_KEY)
                    {
                        if(u8_calisetEN == 0)
                        {
                            if(menu == MAIN_MENU)
                               menu = SET_TEMP_MENU;
                            else if(menu == SET_TEMP_MENU)
                                menu = SET_TIME_MENU;
                            else
                                menu = MAIN_MENU;
                        }
                        else
                        {
                            menu++;
                            if(menu > 11)
                            {
                                menu = 0;
                                u8_calisetEN =0;
                            }
                        }
                        uint_updatEN = 1500;
                        u16_displyfirstcnt=0;
                        
                    }
                    else if(uchr_PresentKey == UP_KEY)
                    {
                        uchr_PreviousKey = DEFAULT_KEY;
                        uchr_valuemodified = 1;
                        uint_updatEN = 5000;
                        switch(menu)
                        {
                            case MAIN_MENU:
                            {
                                break;
                            }
                            case off_MENU:
                            {
                                u16_off++;
                                if(u16_off >100)
                                    u16_off = 100;
                                break;
                            }
                            case PB_MENU:
                            {
                                u16_pb++;
                                if(u16_pb >100)
                                    u16_pb = 100;
                                break;
                            }
                            case IB_MENU:
                            {
                                u16_ib++;
                                if(u16_ib >999)
                                    u16_ib = 999;
                                break;
                            }
                            case PLM_MENU:
                            {
                                u16_plm++;
                                if(u16_plm >100)
                                    u16_plm = 100;
                                break;
                            }
                            case HYS_MENU:
                            {
                                u16_hys++;
                                if(u16_hys >999)
                                    u16_hys = 999;
                                break;
                            }
                            case CG1_MENU:
                            {
                                u16_cg1++;
                                if(u16_cg1 >10)
                                    u16_cg1 = 10;
                                break;
                            }
                            case CG2_MENU:
                            {
                                u16_cg2++;
                                if(u16_cg2 >999)
                                    u16_cg2 = 999;
                                break;
                            }
                            case COF_MENU:
                            {
                                u16_cof++;
                                if(u16_cof >999)
                                    u16_cof = 999;
                                break;
                            }
                            case MDE_MENU:
                            {
                                u16_mde++;
                                if(u16_mde >1)
                                    u16_mde = 0;
                                break;
                            }
                            case SET_TEMP_MENU:
                            {
                                u16_SETtemp++;
                                if(u16_SETtemp >999)
                                    u16_SETtemp = 999;
                                break;
                            }
                            case SET_TIME_MENU:
                            {
                                u16_SETtime++;
                                if(u16_SETtime > 999)
                                    u16_SETtime = 999;
                                break;
                            }
                        }
                    }
                    else if(uchr_PresentKey == DOWN_KEY)
                    {
                        uchr_PreviousKey = DEFAULT_KEY;
                        uchr_valuemodified = 1;
                        uint_updatEN = 5000;
                        switch(menu)
                        {
                            case MAIN_MENU:
                            {
                                break;
                            }
                            case off_MENU:
                            {
                                if(u16_off <=0)
                                    u16_off = 1;
                                u16_off--;
                                break;
                            }
                            case PB_MENU:
                            {
                                if(u16_pb <=0)
                                    u16_pb = 1;
                                u16_pb--;
                                break;
                            }
                            case IB_MENU:
                            {
                                if(u16_ib <=0)
                                    u16_ib = 1;
                                u16_ib--;
                                break;
                            }
                            case PLM_MENU:
                            {
                                if(u16_plm <=0)
                                    u16_plm = 1;
                                u16_plm--;
                                break;
                            }
                            case HYS_MENU:
                            {
                                if(u16_hys <=0)
                                    u16_hys = 1;
                                u16_hys--;
                                break;
                            }
                            case CG1_MENU:
                            {
                                if(u16_cg1 <=0)
                                    u16_cg1 = 1;
                                u16_cg1--;
                                break;
                            }
                            case CG2_MENU:
                            {
                                if(u16_cg2 <=0)
                                    u16_cg2 = 1;
                                u16_cg2--;
                                break;
                            }
                            case COF_MENU:
                            {
                                if(u16_cof <=0)
                                    u16_cof = 1;
                                u16_cof--;
                                break;
                            }
                            case MDE_MENU:
                            {
                                if(u16_mde <=0)
                                    u16_mde = 1;
                                u16_mde--;
                                break;
                            }
                            case SET_TEMP_MENU:
                            {
                                if(u16_SETtemp <=0)
                                    u16_SETtemp = 1;
                                u16_SETtemp--;
                                break;
                            }
                            case SET_TIME_MENU:
                            {
                                
                                if(u16_SETtime <=0)
                                    u16_SETtime = 1;
                                u16_SETtime--;
                                break;
                            }
                        }
                    }
                }
            }
            

        }
        if(TMR3_HasOverflowOccured() == true)//10msec 
        {
            // Clearing IF flag.
            PIR2bits.TMR3IF = 0;
            TMR3_ReadTimer();
            
            uint_adccnt++;

            flt_adcavg1 = flt_adcavg1 + ADC_GetConversion(channel_AN2);//low_pass_filter((float)ADC_GetConversion(channel_AN2));//tc
            flt_adcavg2 = flt_adcavg2 + ADC_GetConversion(channel_AN1);//lm35
            if(uint_adccnt >= 10)
            {
                flt_adc1 = flt_adcavg1/uint_adccnt;
                flt_adc1 = flt_adc1*1.0/1024.0;
//                flt_adc1 = low_pass_filter(flt_adc1);
                flt_adc1 = flt_adc1 * 1000.0;
                
                //388
                //u16_cg1 = 3,u16_cg2=880
//                u16_cg1 = 3;
//                u16_cg2=880;
//                flt_gain1 = u16_cg1*100.0 + (u16_cg2 * 0.1) ;//u16_gain1;
//                flt_gain1 = flt_gain1 * 0.001;
//                flt_offset = (float)u16_cof;
//                flt_Temp1 = (u16_Temp1 - flt_offset)*flt_gain1;
//                flt_gain1 = u16_cg1*100.0 + (u16_cg2 * 0.1) ;//u16_gain1;
//                flt_gain1 = flt_gain1 * 0.001;
//                flt_offset = (float)u16_cof;
                flt_Temp1 = (flt_adc1 - flt_offset)*flt_gain1;
                
                
                /*********lm35******/
                flt_adc2 = flt_adcavg2/uint_adccnt;
                flt_adc2 = flt_adc2*1.0/1024.0;
//                flt_adc2 = flt_adc2 * 1000.0;
                flt_Temp2 = flt_adc2 * 100.0;
                flt_Temp2 = flt_Temp2*0.848;
                /*******************/

//                flt_Temp = flt_Temp1 + u16_Temp2;

                
                uint_adccnt = 0;
                flt_adcavg1 = 0;
                flt_adcavg2 = 0;
            }
            flt_Temp = low_pass_filter(flt_Temp1 + flt_Temp2);

        /************OPERATIONS1***********/
            //            Int_7segdisplay(LINE2,flt_rpm,2);
            
//            kp = (1.0*u16_plm)/u16_pb;//ex:20 = 100/20=5
//            ki = u16_ib;
//            ki = 1.0/(ki*10.0);
//            uchr_LED2 = 1;
             
//            u8_powerduty = 99;
            
            // end added by Mike
            PID_error = 0.5 + (float)u16_SETtemp - flt_Temp;        //Calculate the pid ERROR

            if(PID_error > (u16_pb))                              //integral constant will only affect errors below 30ºC             
            {PID_i = 0;}

            if(PID_i < 0)                              //integral constant will only affect errors below 30ºC             
            {PID_i = 0;}
            
            if(PID_i >u16_plm)                              //integral constant will only affect errors below 30ºC             
            {PID_i = u16_plm;}
            
//            if((PID_error > 0.5)||(PID_error < - 1.0))
            {
                PID_p = kp * PID_error;  //                       //Calculate the P value
                PID_i = PID_i + (ki * PID_error);               //Calculate the I value

    //            timePrev = Time;                    // the previous time is stored before the actual time read
    //            Time = millis();                    // actual time read
    //            elapsedTime = (Time - timePrev) / 1000;   
    //            PID_d = kd*((PID_error - previous_error)/elapsedTime);  //Calculate the D value
                PID_value = PID_p + PID_i + PID_d;                      //Calculate total PID value
                PID_value = PID_value * (u16_plm * 0.01); 
            }
            //We define firing delay range between 0 and 7400. Read above why 7400!!!!!!!
            if(PID_value < 0) // initial it was <
            {      PID_value = 0;       }
            if(PID_value > u16_plm) // initial it was >
            {      PID_value = u16_plm;    }
            previous_error = PID_error; //Remember to store the previous error.
            
            u8_powerduty = PID_value;//99;
    /*********************************/
            if(flt_Temp > (u16_SETtemp - u16_hys))
            {
//                if(SW_MICRO_GetValue()==0)
                if(u8_sw_microEN==1)
                {
                    if((u8_loadON == 0)&&(u8_loadONfirst == 0))
                    {
                        SSR2_SetHigh();
                        u8_led2 = 1;
                        u8_loadON = 1;
                        u8_loadONfirst = 1;
                        u16_timesec = u16_SETtime;
                    }
                }
                else
                {
                    u8_loadONfirst = 0;
                }
            } 
        }
        ctrl_task ();    
    }       
    
}
void ctrl_task (void)
{
    static uint16_t valueshiftcnt=0;
    
   switch(menu)
   {
       case MAIN_MENU:
       {
           
//           valueshiftcnt++;
//           if(valueshiftcnt > 500)
//           {
////               Int_7segdisplay(LINE2,PID_i,0);
//                u16_Tempvalue = PID_i;//u16_Temp2 + flt_Temp1;
//                u8_digit[0] = u16_Tempvalue/100;
//                u8_digit[1] = u16_Tempvalue%100;
//                u8_digit[1] = u8_digit[1]/10;
//                u8_digit[2] = u16_Tempvalue%10;
//
//    //            Int_7segdisplay(LINE2,(u16_Temp1%10000),0);
//                Sring_7segdisplay(LINE2,u8_digit[0],u8_digit[1],u8_digit[2],' ');
//               if(valueshiftcnt > 1000)
//                    valueshiftcnt=0;
//           }
//           else
           {
               if(u8_loadON == 0)
               {
                    u16_Tempvalue = flt_Temp;//u16_Temp2 + flt_Temp1;
                    u8_digit[0] = u16_Tempvalue/100;
                    u8_digit[1] = u16_Tempvalue%100;
                    u8_digit[1] = u8_digit[1]/10;
                    u8_digit[2] = u16_Tempvalue%10;

        //            Int_7segdisplay(LINE2,(u16_Temp1%10000),0);
                    Sring_7segdisplay(LINE2,u8_digit[0],u8_digit[1],u8_digit[2],' ');
               }
               else
               {
                    u16_Tempvalue = u16_timesec;//u16_Temp2 - flt_Temp1;
                    u8_digit[0] = u16_Tempvalue/100;
                    u8_digit[1] = u16_Tempvalue%100;
                    u8_digit[1] = u8_digit[1]/10;
                    u8_digit[2] = u16_Tempvalue%10;

                    Sring_7segdisplay(LINE2,u8_digit[0],u8_digit[1],u8_digit[2],'-');
//                    Sring_7segdisplay(LINE2,u8_digit[0],u8_digit[1],u8_digit[2],u8_ledvalue);
               }
            }
           break;
       }
       case off_MENU:
       {
            if(u16_displyfirstcnt<=300)
            {
                u16_displyfirstcnt++;
                Sring_7segdisplay(LINE2,0,'F','F',' ');
                uint_updatEN = 5000;
            }
            else
            {
                u8_digit[0] = u16_off/100;
                u8_digit[1] = u16_off%100;
                u8_digit[1] = u8_digit[1]/10;
                u8_digit[2] = u16_off%10;
    //            Int_7segdisplay(LINE2,(u16_Temp1%10000),0);
                Sring_7segdisplay(LINE2,u8_digit[0],u8_digit[1],u8_digit[2],' ');
            }
           break;
       }
       case PB_MENU:
       {
            if(u16_displyfirstcnt<=300)
            {
                u16_displyfirstcnt++;
                Sring_7segdisplay(LINE2,'P','b',' ',' ');
                uint_updatEN = 5000;
            }
            else
            {
                u8_digit[0] = u16_pb/100;
                u8_digit[1] = u16_pb%100;
                u8_digit[1] = u8_digit[1]/10;
                u8_digit[2] = u16_pb%10;
    //            Int_7segdisplay(LINE2,(u16_Temp1%10000),0);
                Sring_7segdisplay(LINE2,u8_digit[0],u8_digit[1],u8_digit[2],' ');
            }
           break;
       }
       case IB_MENU:
       {
            if(u16_displyfirstcnt<=300)
            {
                u16_displyfirstcnt++;
                Sring_7segdisplay(LINE2,'i','b',' ',' ');
                uint_updatEN = 5000;
            }
            else
            {
                u8_digit[0] = u16_ib/100;
                u8_digit[1] = u16_ib%100;
                u8_digit[1] = u8_digit[1]/10;
                u8_digit[2] = u16_ib%10;
    //            Int_7segdisplay(LINE2,(u16_Temp1%10000),0);
                Sring_7segdisplay(LINE2,u8_digit[0],u8_digit[1],u8_digit[2],' ');
            }
           break;
       }
       case PLM_MENU:
       {
            if(u16_displyfirstcnt<=300)
            {
                u16_displyfirstcnt++;
                Sring_7segdisplay(LINE2,'P','L','M',' ');
                uint_updatEN = 5000;
            }
            else
            {
                u8_digit[0] = u16_plm/100;
                u8_digit[1] = u16_plm%100;
                u8_digit[1] = u8_digit[1]/10;
                u8_digit[2] = u16_plm%10;
    //            Int_7segdisplay(LINE2,(u16_Temp1%10000),0);
                Sring_7segdisplay(LINE2,u8_digit[0],u8_digit[1],u8_digit[2],' ');
            }
           break;
       }
       case HYS_MENU:
       {
            if(u16_displyfirstcnt<=300)
            {
                u16_displyfirstcnt++;
                Sring_7segdisplay(LINE2,'H','Y','S',' ');
                uint_updatEN = 5000;
            }
            else
            {
                u8_digit[0] = u16_hys/100;
                u8_digit[1] = u16_hys%100;
                u8_digit[1] = u8_digit[1]/10;
                u8_digit[2] = u16_hys%10;
    //            Int_7segdisplay(LINE2,(u16_Temp1%10000),0);
                Sring_7segdisplay(LINE2,u8_digit[0],u8_digit[1],u8_digit[2],' ');
            }
           break;
       }
       case CG1_MENU:
       {
            if(u16_displyfirstcnt<=300)
            {
                u16_displyfirstcnt++;
                Sring_7segdisplay(LINE2,'C','G',1,' ');
                uint_updatEN = 5000;
            }
            else
            {
                u8_digit[0] = u16_cg1/100;
                u8_digit[1] = u16_cg1%100;
                u8_digit[1] = u8_digit[1]/10;
                u8_digit[2] = u16_cg1%10;
    //            Int_7segdisplay(LINE2,(u16_Temp1%10000),0);
                Sring_7segdisplay(LINE2,u8_digit[0],u8_digit[1],u8_digit[2],' ');
            }
           break;
       }
       case CG2_MENU:
       {
            if(u16_displyfirstcnt<=300)
            {
                u16_displyfirstcnt++;
                Sring_7segdisplay(LINE2,'C','G',2,' ');
                uint_updatEN = 5000;
            }
            else
            {
                u8_digit[0] = u16_cg2/100;
                u8_digit[1] = u16_cg2%100;
                u8_digit[1] = u8_digit[1]/10;
                u8_digit[2] = u16_cg2%10;
    //            Int_7segdisplay(LINE2,(u16_Temp1%10000),0);
                Sring_7segdisplay(LINE2,u8_digit[0],u8_digit[1],u8_digit[2],' ');
            }
           break;
       }
       case COF_MENU:
       {
            if(u16_displyfirstcnt<=300)
            {
                u16_displyfirstcnt++;
                Sring_7segdisplay(LINE2,'C',0,'F',' ');
                uint_updatEN = 5000;
            }
            else
            {
                u8_digit[0] = u16_cof/100;
                u8_digit[1] = u16_cof%100;
                u8_digit[1] = u8_digit[1]/10;
                u8_digit[2] = u16_cof%10;
    //            Int_7segdisplay(LINE2,(u16_Temp1%10000),0);
                Sring_7segdisplay(LINE2,u8_digit[0],u8_digit[1],u8_digit[2],' ');
            }
           break;
       }
       case MDE_MENU:
       {
            if(u16_displyfirstcnt<=300)
            {
                u16_displyfirstcnt++;
                Sring_7segdisplay(LINE2,'M',0,'d',' ');
                uint_updatEN = 5000;
            }
            else
            {
                u8_digit[0] = u16_mde/100;
                u8_digit[1] = u16_mde%100;
                u8_digit[1] = u8_digit[1]/10;
                u8_digit[2] = u16_mde%10;
    //            Int_7segdisplay(LINE2,(u16_Temp1%10000),0);
                Sring_7segdisplay(LINE2,u8_digit[0],u8_digit[1],u8_digit[2],' ');
            }
           break;
       }
       case SET_TEMP_MENU:
       {
            if(u16_displyfirstcnt<=300)
            {
                u16_displyfirstcnt++;
                Sring_7segdisplay(LINE2,'S',' ',1,' ');
                uint_updatEN = 5000;
            }
            else
            {
                u8_digit[0] = u16_SETtemp/100;
                u8_digit[1] = u16_SETtemp%100;
                u8_digit[1] = u8_digit[1]/10;
                u8_digit[2] = u16_SETtemp%10;
    //            Int_7segdisplay(LINE2,(u16_Temp1%10000),0);
                Sring_7segdisplay(LINE2,u8_digit[0],u8_digit[1],u8_digit[2],' ');
            }
           break;
       }
       case SET_TIME_MENU:
       {
           if(u16_displyfirstcnt<=300)
            {
                u16_displyfirstcnt++;
                Sring_7segdisplay(LINE2,'S',' ',2,' ');
                uint_updatEN = 5000;
            }
            else
            {
                u8_digit[0] = u16_SETtime/100;
                u8_digit[1] = u16_SETtime%100;
                u8_digit[1] = u8_digit[1]/10;
                u8_digit[2] = u16_SETtime%10;
    //            Int_7segdisplay(LINE2,(u16_Temp1%10000),0);
                Sring_7segdisplay(LINE2,u8_digit[0],u8_digit[1],u8_digit[2],' ');
            }
           break;
       }
       
       default:
       break;
   }
   //values are save in EEPROM only if value change and after 5sec
    if(uint_updatEN)
    {
        uint_updatEN--;
        if(uint_updatEN == 0)
        {
            menu = MAIN_MENU;
//            uchr_displayfirst =0;
            if(uchr_valuemodified == 1)
            {
                uchr_valuemodified = 0;
                /*******SET temp********/
                write_2bytedata(0, u16_SETtemp);
                /*******SET time*******/
                write_2bytedata(2, u16_SETtime);
                /*********u16_off********/
                write_2bytedata(4, u16_off);
                /*********u16_pb********/
                write_2bytedata(6, u16_pb);
                /*********u16_ib********/
                write_2bytedata(8, u16_ib);
                /*********u16_plm********/
                write_2bytedata(10, u16_plm);
                /*********u16_hys********/
                write_2bytedata(12, u16_hys);
                /*********u16_cg1********/
                write_2bytedata(14, u16_cg1);
                /*********u16_cg2********/
                write_2bytedata(16, u16_cg2);
                /*********u16_cof********/
                write_2bytedata(18, u16_cof);
                /*********u16_mde********/
                write_2bytedata(20, u16_mde);
                
               /*****************************/
                kp = (1.0*u16_plm)/u16_pb;//ex:20 = 100/20=5
                ki = u16_ib;
                ki = 1.0/(ki*10.0);
                flt_gain1 = u16_cg1*100.0 + (u16_cg2 * 0.1) ;//u16_gain1;
                flt_gain1 = flt_gain1 * 0.001;
                flt_offset = (float)u16_cof;
            }
        }
    }
}
void myTimer1ISR(void)//timer1 over flow
{
    static uint8_t timecycle = 0,timemili=0;
    if(u8_loadON == 1)
    {
        timemili++;
        if(timemili >= 200)
        {
            timemili = 0;
            if(u16_timesec <= 0)
                u16_timesec = 1;
            u16_timesec--;
            if(u16_timesec == 0)
            {
                SSR2_SetLow();
                u8_led2 = 0;
                u8_loadON = 0;
            }
        }
    }
    //u8_powerduty = 90;
    timecycle++;
    if(timecycle >= 100)
    {
        timecycle = 0;
    }
    if(timecycle >= u8_powerduty )
    {
        uchr_LED2 = 0;
        SSR1_SetLow();
        u8_led1 = 0;
    }
    else
    {
        uchr_LED2 = 1;
        SSR1_SetHigh();
        u8_led1 = 1;
    }
}

void int2arr (unsigned int uint_intdata)
{
    uint_data[0] = uint_intdata/1000;
    uint_data[1] = uint_intdata%1000;
    uint_data[1] = uint_data[1]/100;
    uint_data[2] = uint_intdata%100;
    uint_data[2] = uint_data[2]/10;
    uint_data[3] = uint_intdata%10;
}
void write_2bytedata(unsigned char addr, unsigned int data)
{
    unsigned char uchr_dataL;
    unsigned char uchr_dataH;
    uchr_dataL = data%100;
    uchr_dataH = data/100;
    
    DATAEE_WriteByte(addr,uchr_dataL);
    DATAEE_WriteByte(addr+1,uchr_dataH);
}
float low_pass_filter(float x)
{
//    float LPF_Beta = 0.01 ;// 0<ß<1
//    static float result =0;
//    // Function that brings Fresh Data into RawData
//    result = result - (LPF_Beta * (result - x));
//    return result;
/**************metode2*********************/
//   static float samples[20];
//   float K1 = 0.1,K2=0.9;
//   static int i = 0;
//   static float total = 0; 
//   static float pastvalue = 0; 
//   
//   
//   samples[0] = (x*K1)+(pastvalue*K2);
//   pastvalue = x;
//   for(i= 0; i < 10;i++)
//   {
//     samples[i+1] = (samples[i]*K1)+(samples[i+1]*K2);   
//   }
//   return samples[i];
///**************methode3*********************/
//   static float samples[201];
//   static int i = 0, j = 0;
//   static double total = 0;
//   
//   /* Update the moving average */ 
//   total += (x - samples[i]);
//   samples[i] = x;
//
//   /* Update the index */
//   i = (i==199 ? 0 : i+1);
//
//   return (total/200.0);
// /*********METHOD4************/  
    static int j = 0;
    int RawData;
    float LPF_Beta = 0.05 ; // 0<ß<1
    static float result =0;
    // Function that brings Fresh Data into RawData
    result = result - (LPF_Beta * (result - lowPassExponential(x,10,0.9)));
    if(j<500)
    {
        j++;
        return x;
    }
    return result; 
}
double lowPassExponential(double input, double average, double factor)
{
    /*Exponential Filter
    The last filter is a recursive filter. A recursive filter is just one that calculates a new, smoothed value (yn) by
    using the last smoothed value (yn ? 1) and a new measurement (xn):
    yn = w × xn + (1 ? w) × yn ? 1
    The amount of smoothing is controlled by a weighting parameter (w). The weight is a value between 0% and 100%. 
    When the weight is high (say 90%), the filter doesn?t smooth the measurements very much but responds quickly
    to changes. If the weight is low (say 10%), the filter smooths the measurements a lot but doesn?t respond 
    very quickly to changes*/
    static double oldvalue = 0;
    double Result;
    float weighting = 0.01;

//  yn = w × xn + (1 ? w) × yn ? 1
    Result = weighting * input + (1 - weighting) * oldvalue;
    oldvalue = Result;
    return Result;
}
void Int_7segdisplay(char line,unsigned int value,char decimal)
{
    unsigned short DD0, DD1, DD2, DD3;
    char DD1dec = 0,DD2dec = 0,DD3dec = 0,AllDigitEN = 0;
    
    static unsigned int uint_blinkcnt = 0;
    char chr_blinkstate0 = 0xFF,chr_blinkstate1=0xFF,chr_blinkstate2=0xFF,chr_blinkstate3=0xFF;
    if(line == 1)
    {    
        uint_blinkcnt++;
        if(uint_blinkcnt > 200)
        {
            uint_blinkcnt = 0;
        }
        else if(uint_blinkcnt > 150)
        {
            if(uchr_blinkdigit0)
                chr_blinkstate0 = 0;
            if(uchr_blinkdigit1)
                chr_blinkstate1 = 0;
            if(uchr_blinkdigit2)
                chr_blinkstate2 = 0;
            if(uchr_blinkdigit3)
                chr_blinkstate3 = 0;
        }
        else
        {
            chr_blinkstate0 = 0xFF;
            chr_blinkstate1 = 0xFF;
            chr_blinkstate2 = 0xFF;
            chr_blinkstate3 = 0xFF;
        }
    }
    
    DD0 = value%10;  // Extract Ones Digit
    DD0 = mask(DD0) & chr_blinkstate0;
    switch(decimal)
    {
        case 1:DD1dec = 0x80;
            break;
        case 2:DD2dec = 0x80;
            break;
        case 3:DD3dec = 0x80;
            break;
        case 4:AllDigitEN = 1;
            break;    
        default:
            break;
    }
    if(((value > 9)||(DD1dec)||(DD2dec)||(DD3dec))||(AllDigitEN))
    {
        DD1 = (value/10)%10; // Extract Tens Digit        
        DD1 = (mask(DD1) & chr_blinkstate1)|DD1dec;
    }
    else
    {
       DD1 = mask(10); 
    }
    
    if(((value > 99)||(DD2dec)||(DD3dec))||(AllDigitEN))
    {
        DD2 = (value/100)%10; // Extract Hundreds Digit
        DD2 = (mask(DD2) & chr_blinkstate2)|DD2dec;
    }
    else
    {
       DD2 = mask(10); 
    }
    if(((value > 999)||(DD3dec))||(AllDigitEN))
    {
        DD3 = (value/1000);  // Extract Thousands Digit
        DD3 = (mask(DD3) & chr_blinkstate3)|DD3dec;
    }
    else
    {
        DD3 = mask(10);
    }
    if(line == 1)
        sev_display1(DD0,DD1,DD2,DD3);
    else if(line == 2)
        sev_display2(DD0,DD1,DD2,DD3);
}
void Sring_7segdisplay(char line,char char3,char char2,char char1,char char0)
{
    static unsigned int uint_blinkcnt = 0;
    if(line == 1)
    {
        uint_blinkcnt++;
        if(uint_blinkcnt > 200)
        {
            uint_blinkcnt = 0;
        }
        else if(uint_blinkcnt > 150)
        {
            sev_display1(mask(10),mask(10),mask(10),mask(10));
        }
        else
        {
            sev_display1(mask(char0),mask(char1),mask(char2),mask(char3));
        }
    }    
    else if(line == 2)
        sev_display2(mask(char0),mask(char1),mask(char2),mask(char3));        
}
void sev_display1(char DD0,char DD1,char DD2,char DD3)
{
    A_SEG_SetLow();B_SEG_SetLow();C_SEG_SetLow();D_SEG_SetLow();
    E_SEG_SetLow();F_SEG_SetLow();G_SEG_SetLow();DB_SEG_SetLow();
    
    //1st row 1000's digit
    DIGIT1_SetHigh();      // Enable Digit Three 
    DIGIT2_SetLow();      // Enable Digit Two 
    DIGIT3_SetHigh();      // Enable Digit Two 
    display7seg2(DD3);
    __delay_us(600);
    A_SEG_SetLow();B_SEG_SetLow();C_SEG_SetLow();D_SEG_SetLow();
    E_SEG_SetLow();F_SEG_SetLow();G_SEG_SetLow();DB_SEG_SetLow();
    //1st row 100's digit
    DIGIT1_SetLow();      // Enable Digit Three 
    DIGIT2_SetHigh();      // Enable Digit Two 
    DIGIT3_SetLow();      // Enable Digit Two 
    display7seg(DD2);
    __delay_us(600);
    A_SEG_SetLow();B_SEG_SetLow();C_SEG_SetLow();D_SEG_SetLow();
    E_SEG_SetLow();F_SEG_SetLow();G_SEG_SetLow();DB_SEG_SetLow();
    //1st row 10's digit
    DIGIT1_SetLow();      // Enable Digit Three 
    DIGIT2_SetLow();      // Enable Digit Two 
    DIGIT3_SetHigh();      // Enable Digit Two 
    display7seg2(DD1);   
    __delay_us(600);
    A_SEG_SetLow();B_SEG_SetLow();C_SEG_SetLow();D_SEG_SetLow();
    E_SEG_SetLow();F_SEG_SetLow();G_SEG_SetLow();DB_SEG_SetLow();
    
    //1st row 1's digit
    DIGIT1_SetLow();      // Enable Digit Three 
    DIGIT2_SetLow();      // Enable Digit Two 
    DIGIT3_SetLow();      // Enable Digit Two 
    display7seg(DD0);
    if(uchr_LED1 == 1)
        DB_SEG_SetHigh();     
    
    __delay_us(600);
    A_SEG_SetLow();B_SEG_SetLow();C_SEG_SetLow();D_SEG_SetLow();
    E_SEG_SetLow();F_SEG_SetLow();G_SEG_SetLow();DB_SEG_SetLow();
}
void sev_display2(char DD0,char DD1,char DD2,char DD3)
{
    A_SEG_SetLow();B_SEG_SetLow();C_SEG_SetLow();D_SEG_SetLow();
    E_SEG_SetLow();F_SEG_SetLow();G_SEG_SetLow();DB_SEG_SetLow();
    
    //1st row 1000's digit
    DIGIT1_SetHigh();      // Enable Digit Three 
    DIGIT2_SetHigh();      // Enable Digit Two 
    DIGIT3_SetHigh();      // Enable Digit Two 
    display7seg(DD3);
    __delay_us(600);
    A_SEG_SetLow();B_SEG_SetLow();C_SEG_SetLow();D_SEG_SetLow();
    E_SEG_SetLow();F_SEG_SetLow();G_SEG_SetLow();DB_SEG_SetLow();
    //1st row 100's digit
    DIGIT1_SetHigh();      // Enable Digit Three 
    DIGIT2_SetHigh();      // Enable Digit Two 
    DIGIT3_SetLow();      // Enable Digit Two 
    display7seg(DD2);
    __delay_us(600);
    A_SEG_SetLow();B_SEG_SetLow();C_SEG_SetLow();D_SEG_SetLow();
    E_SEG_SetLow();F_SEG_SetLow();G_SEG_SetLow();DB_SEG_SetLow();
    //1st row 10's digit
    DIGIT1_SetHigh();      // Enable Digit Three 
    DIGIT2_SetLow();      // Enable Digit Two 
    DIGIT3_SetLow();      // Enable Digit Two 
    display7seg(DD1);
    __delay_us(600);
    A_SEG_SetLow();B_SEG_SetLow();C_SEG_SetLow();D_SEG_SetLow();
    E_SEG_SetLow();F_SEG_SetLow();G_SEG_SetLow();DB_SEG_SetLow();
    //1st row 1's digit
    DIGIT1_SetLow();      // Enable Digit Three 
    DIGIT2_SetHigh();      // Enable Digit Two 
    DIGIT3_SetHigh();      // Enable Digit Two 
    display7seg(DD0);
    if(uchr_LED2 == 1)
        DB_SEG_SetHigh();
    if(u8_led1==1)
    {
        A_SEG_SetHigh();
    }
    if(u8_led2==1)
    {
        B_SEG_SetHigh();
    }
    if(u8_led3==1)
    {
        C_SEG_SetHigh();
    }
    __delay_us(600);
    A_SEG_SetLow();B_SEG_SetLow();C_SEG_SetLow();D_SEG_SetLow();
    E_SEG_SetLow();F_SEG_SetLow();G_SEG_SetLow();DB_SEG_SetLow();
}

void display7seg(unsigned char data)
{
    unsigned char mask = 0x80;                //Initialize to write and read bit 7
    
    if (data & mask)
      DB_SEG_SetHigh();
    else
      DB_SEG_SetLow();
    mask = mask >> 1;   //Shift mask so that next bit is written and read from SPI lines
    
    if (data & mask)
      G_SEG_SetHigh();
    else
      G_SEG_SetLow();
    mask = mask >> 1;   //Shift mask so that next bit is written and read from SPI lines
    
    if (data & mask)
      F_SEG_SetHigh();
    else
      F_SEG_SetLow();
    mask = mask >> 1;   //Shift mask so that next bit is written and read from SPI lines
    
    if (data & mask)
      E_SEG_SetHigh();
    else
      E_SEG_SetLow();
    mask = mask >> 1;   //Shift mask so that next bit is written and read from SPI lines
    
    if (data & mask)
      D_SEG_SetHigh();
    else
      D_SEG_SetLow();
    mask = mask >> 1;   //Shift mask so that next bit is written and read from SPI lines
    
    if (data & mask)
      C_SEG_SetHigh();
    else
      C_SEG_SetLow();
    mask = mask >> 1;   //Shift mask so that next bit is written and read from SPI lines
    
    if (data & mask)
      B_SEG_SetHigh();
    else
      B_SEG_SetLow();
    mask = mask >> 1;   //Shift mask so that next bit is written and read from SPI lines
    
    if (data & mask)
      A_SEG_SetHigh();
    else
      A_SEG_SetLow();
    mask = mask >> 1;   //Shift mask so that next bit is written and read from SPI lines
}
void display7seg2(unsigned char data)
{
    unsigned char mask = 0x80;                //Initialize to write and read bit 7
    
    if (data & mask)
      B_SEG_SetHigh();
    else
      B_SEG_SetLow();
    mask = mask >> 1;   //Shift mask so that next bit is written and read from SPI lines
    
    if (data & mask)
      E_SEG_SetHigh();
    else
      E_SEG_SetLow();
    mask = mask >> 1;   //Shift mask so that next bit is written and read from SPI lines
    
    if (data & mask)
      D_SEG_SetHigh();
    else
      D_SEG_SetLow();
    mask = mask >> 1;   //Shift mask so that next bit is written and read from SPI lines
    
    if (data & mask)
      G_SEG_SetHigh();
    else
      G_SEG_SetLow();
    mask = mask >> 1;   //Shift mask so that next bit is written and read from SPI lines
    
    if (data & mask)
      F_SEG_SetHigh();
    else
      F_SEG_SetLow();
    mask = mask >> 1;   //Shift mask so that next bit is written and read from SPI lines
    
    if (data & mask)
      A_SEG_SetHigh();
    else
      A_SEG_SetLow();
    mask = mask >> 1;   //Shift mask so that next bit is written and read from SPI lines
    
    if (data & mask)
      DB_SEG_SetHigh();
    else
      DB_SEG_SetLow();
    mask = mask >> 1;   //Shift mask so that next bit is written and read from SPI lines
    
    if (data & mask)
      C_SEG_SetHigh();
    else
      C_SEG_SetLow();
    mask = mask >> 1;   //Shift mask so that next bit is written and read from SPI lines
}
void pcbled(void)
{
    DB_SEG_SetHigh();
    DIGIT1_SetLow();      // Enable Digit Three 
    DIGIT2_SetHigh();      // Enable Digit Two 
    DIGIT3_SetHigh();      // Enable Digit Two
    __delay_us(600);
    DB_SEG_SetHigh();
    DIGIT1_SetLow();      // Enable Digit Three 
    DIGIT2_SetLow();      // Enable Digit Two 
    DIGIT3_SetLow();      // Enable Digit Two
    __delay_us(600);
    DB_SEG_SetHigh();
}

void Key_Service(void)
{  
    static uint8_t fastincrcnt=0;
    uchr_PresentKey = Key_Scan();
    if(uchr_PreviousKey != uchr_PresentKey)
    {  
        uchr_PreviousKey = uchr_PresentKey;
        if(uchr_PresentKey ==SET_KEY)
            uchr_DebounceCnt = 100;	
        else
        {
            if(fastincrcnt <= 10)
            {
                fastincrcnt++;
                uchr_DebounceCnt = 50;	
            }
            else if(fastincrcnt <= 100)
            {
                fastincrcnt++;
                uchr_DebounceCnt = 10;	
            }
            else
            {
                uchr_DebounceCnt = 2;	
            }
            
        }

//        if(uchr_PresentKey == DEFAULT_KEY)  
//        {
//            uchr_DebounceCnt = 0;  
//            fastincrcnt =0;
//        }
    }
    if(uchr_PresentKey == DEFAULT_KEY)  
    {
        uchr_DebounceCnt = 0;  
        fastincrcnt =0;
    }
}
unsigned char Key_Scan(void)
{

    if(SW_SET_GetValue()==0)
    {
        return SET_KEY;
    }
    else if(SW_UP_GetValue()==0)
    {
        return UP_KEY;
    }
    else if(SW_DOWN_GetValue()==0)
    {
        return DOWN_KEY;
    }
    else
        return DEFAULT_KEY;
}

/**
 End of File
*/