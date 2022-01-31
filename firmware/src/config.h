/******************************************************************************
* Title                 :   AT PARSER
* Filename              :   config.h
* Author                :   MSV
* Origin Date           :   10/03/2016
* Notes                 :   None
*******************************************************************************/
/**************************CHANGE LIST ****************************************
*
*    Date    Software Version    Initials   Description
*  10/03/16    XXXXXXXXXXX         MSV      Interface Created.
*  15/02/18        2.0.0           ST       Custom Application 
*  01/01/2020      3.0.0            MK         Custom Application   
*******************************************************************************/
/**************************CONTACT INFORMATION********************************
* ST: syed.thaseemuddin@microchip.com
* MK: mohan.kumar@microchip.com
*/
/**
 * @file config.h
 * @brief AT Parser Configuration
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
#ifndef AT_CONFIG_H
#define AT_CONFIG_H

/******************************************************************************
* Includes
*******************************************************************************/

#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>

/******************************************************************************
* Preprocessor Constants
*******************************************************************************/

/**
 * AT Head */
#define AT_HEAD                                         "AT"
#define AT_HEAD_SIZE                                    2

/**
 * General Error Message */
#define AT_CMS_ERROR                                    "+CMS ERROR:"
#define AT_CMS_ERROR_SIZE                               11

/**
 * Size of AT command. This should represent maximum size of request header */
#define AT_HEADER_SIZE                                  100 //15

/**
 * Size of command storage. This represent number of commands that can be
 * stored to the module and later recognized by the library. */
#define AT_STORAGE_SIZE                                 100 //50

/**
 * This is the maximum amount of characters that can be transfered per one
 * sequence in both directions. */
#define AT_TRANSFER_SIZE                                2024//1024

/**
 * Default timeout in milliseconds for the specific module */
#define AT_DEFAULT_TIMEOUT                              1000 //500

/******************************************************************************
* Typedefs
*******************************************************************************/

typedef enum
{
    AT_NON,
    AT_OK,
    AT_SS1,
    AT_SS2,
    AT_SS3, 
    AT_SS4,
    AT_SS5,
    AT_SS6,        
    AT_ERROR,
    AT_ERROR2,        
    AT_UNKNOWN,
    AT_DATASEND,        
    AT_CONNECT,
    AT_NOCARRIER,
    AT_NOCARRIER1,  
    AT_NOCARRIER2, 
    AT_NOCARRIER3,  
    AT_NOCARRIER4,
    AT_NOCARRIER5,  
    AT_NOCARRIER6,        
    AT_TERMINAT,
    AT_SKIP        
}at_t;


typedef void ( *at_cmd_cb )( char *buffer );

//#define MEM_LEN                     1440//1day //90 //44640//31days
#define MEM_LEN                     44674//180//------------//44674//31days=44640+34=44,674
//#define MEM_LEN                     14400//10day //90 //44640//31days

#define NOOFDATAPERPACKET           6//6
#define NOOFDATAPERPACKET_MEM       6//9//12//6
#define LOGTIME                     1 //MIN
#define MEM_RECNO                   100000

typedef enum
{
    SERVER_1011,//desktop
    SERVER_1012,//mithin laptop 
    SERVER_LT,  //L&T server      
}server;
typedef enum
{
    COMMAND,
    ONLINE       
}mode;
#define SERVERTO         SERVER_1011//SERVER_LT//////
#define SENDIOTMODE      ONLINE//COMMAND//
#define UNITSLNO         1 // 1 FOR L&T
#define CHIP_ERASE       0//1 //

#define LOGDATA_ERASE    0//1 //

#define CAN_SOURCEADRR   17//17//OR 0
#define TESINGMODE       0//1//
#define TELIT_SERVER     0

#define MEMTEST    0

#define CANMONITERMODE    0//1

#endif
/*******************************End of File ***********************************/
