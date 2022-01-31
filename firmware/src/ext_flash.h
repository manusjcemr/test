#ifndef EXT_FLASH_H_
#define EXT_FLASH_H_

// Include STD C Libraries
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include "configuration.h"
#include "definitions.h"                // SYS function prototypes
// Include Files for Driver Initialisation
//#include "driver_init.h"
#include "string.h"
//! [setup]
//! [buf_length]
#define BUF_LENGTH 20
//! [buf_length]
//! [slave_select_pin]
#define SLAVE_SELECT_PIN CONF_MASTER_SS_PIN
//! [slave_select_pin]
//! [buffer]
//static uint8_t wr_buffer[BUF_LENGTH] = {
//	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09,
//	0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13
//};
//static uint8_t rd_buffer[BUF_LENGTH];
//! [buffer]

//! [var]
//! [setup]

void configure_spi_master_callbacks(void);
void configure_spi_master(void);





// Instruction Codes
#define FLASH_CMD_MDID				0x9F	// Manufacturer Device ID
#define FLASH_CMD_READ_STATUS		0x05	// Read Status Register
#define FLASH_CMD_PROGRAM			0x02	// Page Program
#define FLASH_CMD_READ				0x03	// Read Data
#define FLASH_CMD_WRITE_ENABLE		0x06	// Write Enable
#define FLASH_CMD_SECTOR_ERASE		0x20	// Sector Erase

// Bitmask of the Status Register
#define FLASH_STATUS_BIT_BUSY		0x1		// Busy Bit of Status Register

// Part Specific Constants
#define FLASH_PROGRAM_PAGE_SIZE		0x100	// 256 bytes
#define FLASH_ERASE_SECTOR_SIZE		0x1000	// 4096 bytes
#define FLASH_MAX_COMMAND_SIZE		0x5		// Allow 5 bytes for a command

// Manufacturer DID
#define MF_ADESTO					0x1F

// Structure for the Memory Device
typedef struct
{
	uint32_t deviceSize;
	uint8_t manuID;
	uint8_t devID;
} extFlashInfo_t;

// IO Descriptor for EXTFLASH SPI Comms
//struct io_descriptor *extflash_io;

//// Flash Information
//static const extFlashInfo_t *pFlashInfo = NULL;
//
//static uint8_t infoBuf[2];
//static uint8_t rxBuff[FLASH_PROGRAM_PAGE_SIZE + FLASH_MAX_COMMAND_SIZE];

// Function for Initialising SPI on ExtFlash
void EXTFLASH_init(void);

// ExtFlash Methods
extern void EXTFLASH_setup(void);
extern bool EXTFLASH_open(void);
extern bool EXTFLASH_read(size_t offset, size_t length, uint8_t *buf);
extern bool EXTFLASH_write(size_t offset, size_t length, uint8_t *buf);
extern bool EXTFLASH_erase(size_t offset, size_t length);

//new

unsigned char SPI_Read_Status_Register();
unsigned char SPI_Read_Configuration_Register();
void SPI_WREN();
void SPI_WRDI();
//void SPI_Jedec_ID_Read(int *Manufacturer_Id, int *Device_Type, int *Device_Id);
void SPI_Jedec_ID_Read(char *Manufacturer_Id, char *Device_Type, char *Device_Id);
unsigned char SPI_Read(unsigned long Dst);
void SPI_Read_Cont(unsigned long Dst,unsigned long no_bytes, unsigned int *read_data);
unsigned char SPI_HighSpeed_Read(unsigned long Dst);
void SPI_HighSpeed_Read_Cont(unsigned long Dst,unsigned long no_bytes, uint8_t *read_data);
void SPI_Page_Program(unsigned long Dst, char *Prog_data);
void SPI_byte_Program(unsigned long Dst, uint8_t *Prog_data, uint16_t size);
void SPI_Chip_Erase();
void SPI_Sector_Erase(unsigned long Dst);
void SPI_Block_Erase(unsigned long Dst);
void SPI_NoOp();
void SPI_ResetEn();
void SPI_Reset();
void SPI_Write_Suspend();
void SPI_Write_Resume();
void SPI_Write_Status_Register(unsigned int data1, unsigned char datalen);
void SPI_ReadSID(unsigned char *security_ID, unsigned long Dst, unsigned long security_length);
void SPI_ProgSID(unsigned char *security_ID, unsigned long Dst, unsigned long security_length);
void SPI_LockSID();
void SPI_ReadBlockProtection(unsigned int *block_protection_data);
void SPI_WriteBlockProtection(unsigned int *block_protection_data);
void SPI_Global_Block_Protection_Unlock();
void SPI_LockBlockProtection();
void SPI_NonVolWriteLockProtection(unsigned int *block_protection_data);
void SPI_Wait_Busy();
unsigned char SPI_SFDP_Read(unsigned long Dst);

uint8_t SPI2_Exchange8bit( uint8_t data );

#define ERR_NONE 0
#define ERR_INVALID_DATA -1
#define ERR_NO_CHANGE -2
#define ERR_ABORTED -3
#define ERR_BUSY -4
#define ERR_SUSPEND -5
#define ERR_IO -6
#define ERR_REQ_FLUSHED -7
#define ERR_TIMEOUT -8
#define ERR_BAD_DATA -9
#define ERR_NOT_FOUND -10
#define ERR_UNSUPPORTED_DEV -11
#define ERR_NO_MEMORY -12
#define ERR_INVALID_ARG -13
#define ERR_BAD_ADDRESS -14
#define ERR_BAD_FORMAT -15
#define ERR_BAD_FRQ -16
#define ERR_DENIED -17
#define ERR_ALREADY_INITIALIZED -18
#define ERR_OVERFLOW -19
#define ERR_NOT_INITIALIZED -20
#define ERR_SAMPLERATE_UNAVAILABLE -21
#define ERR_RESOLUTION_UNAVAILABLE -22
#define ERR_BAUDRATE_UNAVAILABLE -23
#define ERR_PACKET_COLLISION -24
#define ERR_PROTOCOL -25
#define ERR_PIN_MUX_INVALID -26
#define ERR_UNSUPPORTED_OP -27
#define ERR_NO_RESOURCE -28
#define ERR_NOT_READY -29
#define ERR_FAILURE -30
#define ERR_WRONG_LENGTH -31


#endif