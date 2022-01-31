// Include EXT Flash Header File
#include "ext_flash.h"
// Supported Flash Devices
static const extFlashInfo_t flashInfo[] =
{
	{
		.manuID = MF_ADESTO,		// Adesto
		.devID = 0x01,				// Device ID
		.deviceSize = 0x100000		// 1Mbyte (8Mbit)
	},
	{
		.manuID = 0x0,
		.devID = 0x0,
		.deviceSize = 0x0
	}
};

//// Flash Information
static const extFlashInfo_t *pFlashInfo = NULL;
static uint8_t infoBuf[2];
static uint8_t rxBuff[FLASH_PROGRAM_PAGE_SIZE + FLASH_MAX_COMMAND_SIZE];

void EXTFLASH_init()
{
	// Get the IO Descriptor
//	spi_m_async_get_io_descriptor(&SERIALFLASH, &extflash_io);
//	
//	// Register the Callback Function
//	spi_m_async_register_callback(&SERIALFLASH, SPI_M_ASYNC_CB_XFER, (FUNC_PTR)SPI_EXTFLASH_complete_cb);
//	
//	// Enable Asynchronous SPI
//	spi_m_async_enable(&SERIALFLASH);
    
        //EEPROM_HOLD_Set();
    FLASH_WP_Set();
//    FLASH_WP_Clear();
    FLASH_CS_Set();
}

/**
 * Method for Transmitting to EXTFLASH via SPI.
 *
 * @param uint8_t *wbuf					Write buffer.
 * @param uint8_t *rbuf					Read buffer.
 * @param uint16_t length				Length of bytes to transfer.
 *
 * @return bool
 */
//static bool EXTFLASH_transfer(const uint8_t *wbuf, uint8_t *rbuf, const uint16_t length)
//{
//	// Set the Initial Return Value
//	bool returnVal = false;	
//	// Enable SPI
//	//spi_select_slave(&spi_master_instance, &slave, true);
//	FLASH_CS_Clear();
//	// Perform ASYNC Transfer (send and receive)
//	//spi_transceive_buffer_job(&spi_master_instance, &wbuf[0], &rbuf[0], length);
//	returnVal = SERCOM0_SPI_WriteRead(&wbuf[0], length, &rbuf[0], length);
//	// Wait until transfer completes...
//	//while (!transrev_complete_spi_master) {
//	/////* Wait for write and read complete */
//	//}
//	//transrev_complete_spi_master = false;
//	
//	// Set the Return Value
//	//returnVal = true;
//	
//	// Disable SPI
//	//spi_select_slave(&spi_master_instance, &slave, false);
//    FLASH_CS_Set();
//	// Return the Function
//	return returnVal;
//}

/**
 * Reads the flash information (manufacturer and device ID) from the device.
 *
 * @return bool
 */
static bool EXTFLASH_readInfo(void)
{
	// Create the Command Message
	 uint8_t wbuf[] = { FLASH_CMD_MDID, 0x00, 0x00, 0x00 };
	bool returnVal = false;
	
	// Send the Command
//	if (EXTFLASH_transfer(wbuf, rxBuff, 4))
    if (SERCOM0_SPI_WriteRead(wbuf, 4, rxBuff, 4))
	{
		// Copy Vendor and Device Data into the Info Buffer
		infoBuf[0] = rxBuff[1];
		infoBuf[1] = rxBuff[3];
		
		// Return True
		returnVal = true;
	}
	
	// Return the Function
	return returnVal;
}

/**
 * Verify that the flash component is valid.
 *
 * @return bool
 */
static bool _extFlashVerifyPart(void)
{
	// Check that we can read the info in
	if (!EXTFLASH_readInfo())
	{
		return false;
	}
	
	// Point pFlashInfo to FlashInfo Array
	pFlashInfo = flashInfo;
	
	// Loop and Compare
	while(pFlashInfo->deviceSize > 0)
	{
		if (infoBuf[0] == pFlashInfo->manuID && infoBuf[1] == pFlashInfo->devID)
		{
			break;
		}
		pFlashInfo++;
	}
	
	// Return whether we found a matching device
	return (pFlashInfo->deviceSize > 0);
}

/**
 * Read the status register of the flash device.
 *
 * @param uint8_t *buf						Read buffer.
 *
 * @return bool
 */
static bool EXTFLASH_readStatus(uint8_t *buf)
{
	// Build the Command for Reading Flash Status
	 uint8_t wbuf[3] = { FLASH_CMD_READ_STATUS, 0x00, 0x00 };
	
	// Set Initial Return Value
	bool returnVal = false;
	
	// Send the Command get the Response
	if(SERCOM0_SPI_WriteRead(wbuf, 3, rxBuff, 3))//if (EXTFLASH_transfer(wbuf, rxBuff, 3))
	{
		// Copy the Data into the Receive Buffer
		buf[0] = rxBuff[1];
		returnVal = true;
	}
	
	// Return the Function
	return returnVal;
}

/**
 * Wait for the previous erase / program operation to complete.
 *
 * @return int								0 on success, < 0 on failure
 */
static int EXTFLASH_waitReady(void)
{
	// Return Value
	int returnValue;
	
	for (;;)
	{
		uint8_t buf;
		returnValue = EXTFLASH_readStatus(&buf);
		
		// Check if Status Register Bit Busy
		if (!(buf & FLASH_STATUS_BIT_BUSY))
		{
			// Now Ready
			break;
		}
	}
	returnValue = 0;
	return 	returnValue;
;
}

/**
 * Enable writing on the flash device.
 *
 * @return int								0 on success, < 0 on failure
 */
static int EXTFLASH_writeEnable(void)
{
	// Command for Enabling Write Operations
	 uint8_t wbuf[] = { FLASH_CMD_WRITE_ENABLE };
	int returnValue = -3;
	
	// Send the Command over SPI
//	if (EXTFLASH_transfer(wbuf, rxBuff, 1))
    if(SERCOM0_SPI_WriteRead(wbuf, 1, rxBuff, 1))
	{
		// Set our Return Value to Zero
		returnValue = 0;
	}
	
	// Return
	return returnValue;
}

/**
 * Configures the flash device for user.
 *
 * @return bool
 */
bool EXTFLASH_open(void)
{
	// Return Value (default to FALSE)
	bool returnValue = false;
	
	// Buffer for the Status Register
	uint8_t buf[1];
	
	// Verify the manufacturer and device ID
	if (_extFlashVerifyPart())
	{
		// Read the Status Register
		returnValue = EXTFLASH_readStatus(buf);
	}
	
	// Return
	return returnValue;
}

/**
 * Send a read request using 24-bit addressing.
 *
 * @param size_t offset		The byte offset in flash to begin reading from.
 * @param size_t length		The number of bytes to read.
 * @param uint8_t *buf		The buffer where data is stored. Must be at least {length} bytes in size.
 *
 * @return bool
 */
bool EXTFLASH_read(size_t offset, size_t length, uint8_t *buf)
{
	// Write Buffer for Command
	uint8_t wbuf[4];
	
	// Return Value (default to FALSE)
	bool returnValue = false;
	
	// Wait until previous command completes
	int ret = EXTFLASH_waitReady();
	
	if (ret)
	{
		return false;
	}
	
	// SPI is driven with low frequency (1Mhz), so not necessary to use fast read.
	wbuf[0] = FLASH_CMD_READ;
	wbuf[1] = (offset >> 16) & 0xFF;
	wbuf[2] = (offset >> 8) & 0xFF;
	wbuf[3] = offset & 0xFF;
	
	// Send the Read Command and Get the Response
//	if (EXTFLASH_transfer(wbuf, rxBuff, length + 4))
    if(SERCOM0_SPI_WriteRead(wbuf, length + 4, rxBuff, length + 4))
	{
		// Copy the data over
		memcpy(&buf[0], &rxBuff[4], length);
		
		// Set the Return Value
		returnValue = true;
	}
	
	// Return the Function
	return returnValue;
}

/**
 * Send a write request using 24-bit addressing.
 *
 * @param size_t offset		The byte offset in flash to begin writing to.
 * @param size_t length		The number of bytes to write.
 * @param uint8_t *buf		The buffer where data to be written is stored. Must be at least {length} bytes in size.
 *
 * @return bool
 */
bool EXTFLASH_write(size_t offset, size_t length, uint8_t *buf)
{
	// Write Buffer for Command
	uint8_t wbuf[4];
	
	// Status of SPI async
	//struct spi_m_async_status p_stat;
	
	// Begin Write Loop
	while (length > 0)
	{
		// Wait until the previous operation is completed.
		int ret = EXTFLASH_waitReady();
		
		// If the device isn't ready, return false
		if (ret)
		{
			return false;
		}
		
		// Enable Writing on the Flash Device
		ret = EXTFLASH_writeEnable();
		
		// If the device isn't ready, return false
		if (ret)
		{
			return false;
		}
		
		// Interim length per instruction
		size_t ilen;
		
		// Work out the Instruction Length
		ilen = FLASH_PROGRAM_PAGE_SIZE - (offset % FLASH_PROGRAM_PAGE_SIZE);
		
		// Bound Checking
		if (length < ilen)
		{
			ilen = length;
		}
		
		// Create Command and 24 bit address
		wbuf[0] = FLASH_CMD_PROGRAM;
		wbuf[1] = (offset >> 16) & 0xFF;
		wbuf[2] = (offset >> 8) & 0xFF;
		wbuf[3] = offset & 0xFF;
		
		// Set Counters
		offset += ilen;
		length -= ilen;
		
		// Start the Combined Write Sequence
		//port_pin_set_output_level(SERIALFLASH_CS, 0);
		//! [select_slave]
		//spi_select_slave(&spi_master_instance, &slave, true);
        FLASH_CS_Clear();
		
		// First, write the page program command
		//if (spi_m_async_transfer(&SERIALFLASH, wbuf, rxBuff, 4) == ERR_NONE)
		//if (spi_transceive_buffer_job(&spi_master_instance, wbuf, rxBuff,4) == ERR_NONE)
        if ( SERCOM0_SPI_WriteRead(wbuf, 4, rxBuff, 4) ==ERR_NONE)
		{
			//// Wait until transfer completes
			//while (spi_m_async_get_status(&SERIALFLASH, &p_stat) == ERR_BUSY)
			//{
				//// Delay and Re-Check
				//delay_us(10);
			//}
			//! [wait]
			//while (!transrev_complete_spi_master) {
			/////* Wait for write and read complete */
			//}
			//transrev_complete_spi_master = false;
		}
		else
		{
			// Failure
			//gpio_set_pin_level(SERIALFLASH_CS, 1);
			//! [deselect_slave]
			//spi_select_slave(&spi_master_instance, &slave, false);
            FLASH_CS_Set();
			// Return FALSE
			return false;
		}
		
		// Now write out the page of data
		//if (spi_m_async_transfer(&SERIALFLASH, buf, rxBuff, ilen) == ERR_NONE)
//		if (spi_transceive_buffer_job(&spi_master_instance,  buf, rxBuff, ilen) == ERR_NONE)
        if (SERCOM0_SPI_WriteRead(buf, ilen, rxBuff, ilen) == ERR_NONE)    
		{
			//// Wait until transfer completes
			//while (spi_m_async_get_status(&SERIALFLASH, &p_stat) == ERR_BUSY)
			//{
				//// Delay and Re-Check
				//delay_us(10);
			//}
			//! [wait]
//			while (!transrev_complete_spi_master) {
//				/////* Wait for write and read complete */
//			}
//			transrev_complete_spi_master = false;
		}
		else
		{
			// Failure
			//port_pin_set_output_level(SERIALFLASH_CS, 1);
			//! [deselect_slave]
//			spi_select_slave(&spi_master_instance, &slave, false);
            FLASH_CS_Set();
			// Return FALSE
			return false;
		}
		
		// Complete the combined write sequence
		//port_pin_set_output_level(SERIALFLASH_CS, 1);
		//! [deselect_slave]
//		spi_select_slave(&spi_master_instance, &slave, false);
        FLASH_CS_Set();
		// Increment the Buffer
		buf += ilen;
	}
	
	// Return TRUE
	return true;
}

/**
 * Send an erase request using 24-bit addressing.
 *
 * @param size_t offset				The byte offset in flash to begin erasing from.
 * @param size_t length				The number of bytes to erase.
 *
 * @return bool
 */
bool EXTFLASH_erase(size_t offset, size_t length)
{
	// Write Buffer for Command
	uint8_t wbuf[4];
	size_t i, numsectors;
	
	// Set the Erase Command
	wbuf[0] = FLASH_CMD_SECTOR_ERASE;
	
	// Set the Offsets
	size_t endoffset = offset + length - 1;
	offset = (offset / FLASH_ERASE_SECTOR_SIZE) * FLASH_ERASE_SECTOR_SIZE;
	numsectors = (endoffset - offset + FLASH_ERASE_SECTOR_SIZE - 1) / FLASH_ERASE_SECTOR_SIZE;
	
	// Loop through each sector to erase
	for (i = 0; i < numsectors; i++)
	{
		// Wait until the previous operation is complete
		int ret = EXTFLASH_waitReady();
		
		// If not complete, return FALSE
		if (ret)
		{
			return false;
		}
		
		// Enable writing on the device
		ret = EXTFLASH_writeEnable();
		
		// If not complete, return FALSE
		if (ret)
		{
			return false;
		}
		
		// 24 bit sector address
		wbuf[1] = (offset >> 16) & 0xFF;
		wbuf[2] = (offset >> 8) & 0xFF;
		wbuf[3] = offset & 0xFF;
		
		// Send the Erase Command and Get the Response
//		if (EXTFLASH_transfer(wbuf, rxBuff, 4)) 
        if(SERCOM0_SPI_WriteRead(wbuf, 4, rxBuff, 4))
        {}
	}
	
	// Return TRUE
	return true;
}

//new
uint8_t SPI2_Exchange8bit( uint8_t data )
{
	//uint8_t receiveData[4];
	//
	////SPI2_Exchange(&data, &receiveData);
	////EXTFLASH_transfer(&data, &receiveData, 1);
	//spi_m_async_transfer(&SERIALFLASH, data, receiveData, 1);
	//return (receiveData);
	
	// Command for Enabling Write Operations
	 uint8_t wbuf[] = { data };
//	int returnValue = -3;
	// Struct for the SPI Status
	//struct spi_m_async_status p_stat;
	
	
	// Send the Command over SPI
	//spi_m_async_transfer(&SERIALFLASH, &wbuf[0], &rxBuff[0], 1);
//	spi_transceive_buffer_job(&spi_master_instance, &wbuf[0], &rxBuff[0], 1);
	SERCOM0_SPI_WriteRead(&wbuf[0], 1, &rxBuff[0], 1);
            
	//// Wait until transfer completes...
	//while (spi_m_async_get_status(&SERIALFLASH, &p_stat) == ERR_BUSY)
	//{
		//// Delay a bit before checking again
		//delay_us(10);
	//}
	//! [wait]
//	while (!transrev_complete_spi_master) {
//	/////* wait for write and read complete */
//	}
//	transrev_complete_spi_master = false;
	return (rxBuff[0]);
}
/************************************************************************/
/* PROCEDURE: Read_Status_Register					*/
/*									*/
/* This procedure reads the status register and returns the byte.	*/
/************************************************************************/
unsigned char SPI_Read_Status_Register()
{
	unsigned char byte = 0;
	//port_pin_set_output_level(SERIALFLASH_CS, 0);//CE_SetLow();			/* enable device */
	//! [select_slave]
//	spi_select_slave(&spi_master_instance, &slave, true);
	FLASH_CS_Clear();
	SPI2_Exchange8bit(0x05);		/* send RDSR command */
	byte = SPI2_Exchange8bit(0xFF);		/* receive byte */
	//port_pin_set_output_level(SERIALFLASH_CS, 1);//CE_SetHigh();			/* disable device */
	//! [deselect_slave]
//	spi_select_slave(&spi_master_instance, &slave, false);
    FLASH_CS_Set();
	return byte;
}

/************************************************************************/
/* PROCEDURE: Read_Configuration_Register				*/
/*									*/
/* This procedure reads the configuration register and returns the byte.*/
/************************************************************************/
unsigned char SPI_Read_Configuration_Register()
{
	unsigned char byte = 0;
	//port_pin_set_output_level(SERIALFLASH_CS, 0);//CE_SetLow();			/* enable device */
	//! [select_slave]
//	spi_select_slave(&spi_master_instance, &slave, true);
    FLASH_CS_Clear();
	SPI2_Exchange8bit(0x35);		/* send RDSR command */
	byte = SPI2_Exchange8bit(0xFF);		/* receive byte */
	//port_pin_set_output_level(SERIALFLASH_CS, 1);//CE_SetHigh();			/* disable device */
	//! [deselect_slave]
//	spi_select_slave(&spi_master_instance, &slave, false);
    FLASH_CS_Set();
	return byte;
}



/************************************************************************/
/* PROCEDURE: WREN							*/
/*									*/
/* This procedure enables the Write Enable Latch.               	*/
/************************************************************************/


void SPI_WREN()
{
	//port_pin_set_output_level(SERIALFLASH_CS, 0);//CE_SetLow();			/* enable device */
	//! [select_slave]
//	spi_select_slave(&spi_master_instance, &slave, true);
    FLASH_CS_Clear();
	SPI2_Exchange8bit(0x06);		/* send WREN command */
	//port_pin_set_output_level(SERIALFLASH_CS, 1);//CE_SetHigh();			/* disable device */
	//! [deselect_slave]
//	spi_select_slave(&spi_master_instance, &slave, false);
    FLASH_CS_Set();
}

/************************************************************************/
/* PROCEDURE: WRDI							*/
/*									*/
/* This procedure disables the Write Enable Latch.			*/
/************************************************************************/

void SPI_WRDI()
{
	//port_pin_set_output_level(SERIALFLASH_CS, 0);//CE_SetLow();			/* enable device */
	//! [select_slave]
//	spi_select_slave(&spi_master_instance, &slave, true);
    FLASH_CS_Clear();
	SPI2_Exchange8bit(0x04);		/* send WRDI command */
	//port_pin_set_output_level(SERIALFLASH_CS, 1);//CE_SetHigh();			/* disable device */
	//! [deselect_slave]
//	spi_select_slave(&spi_master_instance, &slave, false);
    FLASH_CS_Set();
}


/************************************************************************/
/* PROCEDURE: QuadJ_ID							*/
/*									*/
/* This procedure Reads the manufacturer's ID, device Type and device ID.  It will 	*/
/* use AFh as the command to read the ID.                               */
/* Returns:								*/
/*	ID1(Manufacture's ID = BFh, Device Type =26h , Device ID = 02h)	*/
/*									*/
/************************************************************************/

void SPI_Jedec_ID_Read(char *Manufacturer_Id, char *Device_Type, char *Device_Id)

{	
//	// Create the Command Message
//	const uint8_t wbuf[] = { FLASH_CMD_MDID, 0x00, 0x00, 0x00 };
//	bool returnVal = false;
//	
//	// Send the Command
//	if (EXTFLASH_transfer(wbuf, rxBuff, 4))
//	{
//		// Copy Vendor and Device Data into the Info Buffer
//		*Manufacturer_Id = rxBuff[1];
//		*Device_Type = rxBuff[2];
//		*Device_Id = rxBuff[3];
//	}	
	// Create the Command Message
//	char wbuf[] = { FLASH_CMD_MDID, 0x00, 0x00, 0x00 };
	FLASH_CS_Clear();
    
	// Send the Command
/*	if(SERCOM0_SPI_WriteRead(wbuf, 4, rxBuff, 4))//if (EXTFLASH_transfer(wbuf, rxBuff, 4))
    //SERCOM0_SPI_WriteRead(flashtxData, 4, flashrxData, (4 + FLASH_DATA_LEN));
	{
		// Copy Vendor and Device Data into the Info Buffer
		*Manufacturer_Id = rxBuff[1];
		*Device_Type = rxBuff[2];
		*Device_Id = rxBuff[3];
//        printf("%d,%d,%d,%d,%d,%d,%d,%d",flashrxData[0],flashrxData[1],flashrxData[2],flashrxData[3],flashrxData[4],flashrxData[5],flashrxData[6],flashrxData[7]);
	}*/
    
//    SERCOM0_SPI_WriteRead(wbuf, 1, rxBuff, 1);
//    SERCOM0_SPI_WriteRead(0, 1, rxBuff, 1);
//    *Manufacturer_Id = rxBuff[0];
//    SERCOM0_SPI_WriteRead(0, 1, rxBuff, 1);
//    *Device_Type = rxBuff[0];
//    SERCOM0_SPI_WriteRead(0, 1, rxBuff, 1);
//    *Device_Id = rxBuff[0];
    
//    SPI2_Exchange8bit(0x02);
    *Manufacturer_Id = SPI2_Exchange8bit(FLASH_CMD_MDID);
    *Manufacturer_Id =SPI2_Exchange8bit(0);
    *Device_Type =SPI2_Exchange8bit(0);
    *Device_Id =SPI2_Exchange8bit(0);

    FLASH_CS_Set();
}



/************************************************************************/
/* PROCEDURE:	Read							*/
/*									*/
/* This procedure reads one address of the device.  It will return the 	*/
/* byte read in variable byte.						*/
/* Input:								*/
/*		Dst:	Destination Address 000000H - 7FFFFFH		*/
/************************************************************************/
unsigned char SPI_Read(unsigned long Dst)
{
	unsigned char byte = 0;

	//port_pin_set_output_level(SERIALFLASH_CS, 0);//CE_SetLow();                                /* enable device */
	//! [select_slave]
//	spi_select_slave(&spi_master_instance, &slave, true);
    FLASH_CS_Clear();
	SPI2_Exchange8bit(0x03);                        /* read command */
	SPI2_Exchange8bit(((Dst & 0xFFFFFF) >> 16));	/* send 3 address bytes */
	SPI2_Exchange8bit(((Dst & 0xFFFF) >> 8));
	SPI2_Exchange8bit(Dst & 0xFF);
	byte = SPI2_Exchange8bit(0xFF);
	//port_pin_set_output_level(SERIALFLASH_CS, 1);//CE_SetHigh();                              /* disable device */
	//! [deselect_slave]
//	spi_select_slave(&spi_master_instance, &slave, false);
    FLASH_CS_Set();
	return byte;                            /* return one byte read */
}


/************************************************************************/
/* PROCEDURE:	Read_Cont						*/
/*									*/
/* This procedure reads multiple addresses of the device and stores	*/
/* data into 256 byte buffer. Maximum number of bytes read is limited 256 bytes*/
/*									*/
/* Input:								*/
/*		Dst:		Destination Address 000000H - 7FFFFFH	*/
/*      	no_bytes	Number of bytes to read	(max = 256)	*/
/************************************************************************/
void SPI_Read_Cont(unsigned long Dst,unsigned long no_bytes, unsigned int *read_data)
{
	unsigned long i = 0;
	//port_pin_set_output_level(SERIALFLASH_CS, 0);//CE_SetLow();				/* enable device */
	//! [select_slave]
//	spi_select_slave(&spi_master_instance, &slave, true);
    FLASH_CS_Clear();
	SPI2_Exchange8bit(0x03); 			/* read command */
	SPI2_Exchange8bit(((Dst & 0xFFFFFF) >> 16)); 	/* send 3 address bytes */
	SPI2_Exchange8bit(((Dst & 0xFFFF) >> 8));
	SPI2_Exchange8bit(Dst & 0xFF);
	for (i = 0; i < no_bytes; i++)		/* read until no_bytes is reached */
	{
		*read_data = SPI2_Exchange8bit(0xFF);	/* receive byte and store at address 80H - FFH */
		read_data++;
	}
	//port_pin_set_output_level(SERIALFLASH_CS, 1);//CE_SetHigh();				/* disable device */
	//! [deselect_slave]
//	spi_select_slave(&spi_master_instance, &slave, false);
    FLASH_CS_Set();

}

/************************************************************************/
/* PROCEDURE:	HighSpeed_Read						*/
/*									*/
/* This procedure reads one address of the device.  It will return the 	*/
/* byte read in variable byte.						*/
/* Input:								*/
/*		Dst:	Destination Address 000000H - 7FFFFFH		*/
/************************************************************************/
unsigned char SPI_HighSpeed_Read(unsigned long Dst)
{
	unsigned char byte = 0;

	//port_pin_set_output_level(SERIALFLASH_CS, 0);//CE_SetLow();                               /* enable device */
	//! [select_slave]
//	spi_select_slave(&spi_master_instance, &slave, true);
    FLASH_CS_Clear();
	SPI2_Exchange8bit(0x0B);                        /* read command */
	SPI2_Exchange8bit(((Dst & 0xFFFFFF) >> 16));	/* send 3 address bytes */
	SPI2_Exchange8bit(((Dst & 0xFFFF) >> 8));
	SPI2_Exchange8bit(Dst & 0xFF);
	SPI2_Exchange8bit(0xFF);                        /*dummy byte*/
	byte = SPI2_Exchange8bit(0xFF);
	//port_pin_set_output_level(SERIALFLASH_CS, 1);//CE_SetHigh();                              /* disable device */
	//! [deselect_slave]
//	spi_select_slave(&spi_master_instance, &slave, false);
    FLASH_CS_Set();
	return byte;                            /* return one byte read */
}

/************************************************************************/
/* PROCEDURE:	HighSpeed_Read_Cont					*/
/*									*/
/* This procedure reads multiple addresses of the device and stores	*/
/* data into 256 byte buffer. Maximum number of bytes read is limited to 256 bytes*/
/*									*/
/* Input:								*/
/*		Dst:		Destination Address 000000H - 7FFFFFH	*/
/*      	no_bytes	Number of bytes to read	(max = 256)	*/
/************************************************************************/
void SPI_HighSpeed_Read_Cont(unsigned long Dst,unsigned long no_bytes, uint8_t *read_data)
{
	unsigned long i = 0;
	//port_pin_set_output_level(SERIALFLASH_CS, 0);//CE_SetLow();				/* enable device */
	//! [select_slave]
//	spi_select_slave(&spi_master_instance, &slave, true);
    FLASH_CS_Clear();
	SPI2_Exchange8bit(0x0B); 			/* read command */
	SPI2_Exchange8bit(((Dst & 0xFFFFFF) >> 16)); 	/* send 3 address bytes */
	SPI2_Exchange8bit(((Dst & 0xFFFF) >> 8));
	SPI2_Exchange8bit(Dst & 0xFF);
	SPI2_Exchange8bit(0xFF);			/*dummy byte*/
	for (i = 0; i < no_bytes; i++)		/* read until no_bytes is reached */
	{
		*read_data = SPI2_Exchange8bit(0xFF);	/* receive byte and store at address 80H - FFH */
		read_data++;
	}
	//port_pin_set_output_level(SERIALFLASH_CS, 1);//CE_SetHigh();				/* disable device */
	//! [deselect_slave]
//	spi_select_slave(&spi_master_instance, &slave, false);
    FLASH_CS_Set();
}




/************************************************************************/
/* PROCEDURE:	Page_Program						*/
/*									*/
/* This procedure does page programming.  The destination               */
/* address should be provided.                                  	*/
/* The data array of 256 bytes contains the data to be programmed.      */
/* Since the size of the data array is 256 bytes rather than 256 bytes, this page program*/
/* procedure programs only 256 bytes                                    */
/* Assumption:  Address being programmed is already erased and is NOT	*/
/*		block protected.					*/
/* Input:								*/
/*		Dst:		Destination Address 000000H - 7FFFFFH	*/
/*		data_256[256] containing 256 bytes of data will be programmed using this function */
/************************************************************************/

void SPI_Page_Program(unsigned long Dst, char *Prog_data)
{
	unsigned int i;
	i=0;

	//gpio_set_pin_level(SERIALFLASH_CS, 0);//CE_SetLow();				/* enable device */
	//! [select_slave]
//	spi_select_slave(&spi_master_instance, &slave, true);
	FLASH_CS_Clear();
	SPI2_Exchange8bit(0x02); 			/* send Byte Program command */
	SPI2_Exchange8bit(((Dst & 0xFFFFFF) >> 16));	/* send 3 address bytes */
	SPI2_Exchange8bit(((Dst & 0xFFFF) >> 8));
	SPI2_Exchange8bit(Dst & 0xFF);
	for (i=0;i<256;i++)
	{	SPI2_Exchange8bit(*Prog_data);		/* send byte to be programmed */
		Prog_data++;
	}
	//gpio_set_pin_level(SERIALFLASH_CS, 1);//CE_SetHigh();				/* disable device */
	//! [deselect_slave]
//	spi_select_slave(&spi_master_instance, &slave, false);
    FLASH_CS_Set();
}
void SPI_byte_Program(unsigned long Dst, uint8_t *Prog_data, uint16_t size)
{
	unsigned int i;
	i=0;

	//gpio_set_pin_level(SERIALFLASH_CS, 0);//CE_SetLow();				/* enable device */
	//! [select_slave]
//	spi_select_slave(&spi_master_instance, &slave, true);
    FLASH_CS_Clear();
	
	SPI2_Exchange8bit(0x02); 			/* send Byte Program command */
	SPI2_Exchange8bit(((Dst & 0xFFFFFF) >> 16));	/* send 3 address bytes */
	SPI2_Exchange8bit(((Dst & 0xFFFF) >> 8));
	SPI2_Exchange8bit(Dst & 0xFF);
	for (i=0;i<size;i++)
	{	SPI2_Exchange8bit(*Prog_data);		/* send byte to be programmed */
		Prog_data++;
	}
	//gpio_set_pin_level(SERIALFLASH_CS, 1);//CE_SetHigh();				/* disable device */
	//! [deselect_slave]
//	spi_select_slave(&spi_master_instance, &slave, false);
    FLASH_CS_Set();
}


/************************************************************************/
/* PROCEDURE: Chip_Erase						*/
/*									*/
/* This procedure erases the entire Chip.				*/
/************************************************************************/

void SPI_Chip_Erase()
{
	//gpio_set_pin_level(SERIALFLASH_CS, 0);//CE_SetLow();				/* enable device */
	//! [select_slave]
//	spi_select_slave(&spi_master_instance, &slave, true);
    FLASH_CS_Clear();
	SPI2_Exchange8bit(0xC7);			/* send Chip Erase command (C7h) */
	//gpio_set_pin_level(SERIALFLASH_CS, 1);//CE_SetHigh();				/* disable device */
	//! [deselect_slave]
//	spi_select_slave(&spi_master_instance, &slave, false);
    FLASH_CS_Set();
}

/************************************************************************/
/* PROCEDURE: Sector_Erase						*/
/*									*/
/* This procedure Sector Erases the Chip.				*/
/* Input:								*/
/*		Dst:		Destination Address 000000H - 7FFFFFH	*/
/************************************************************************/


void SPI_Sector_Erase(unsigned long Dst)
{


	//gpio_set_pin_level(SERIALFLASH_CS, 0);//CE_SetLow();				/* enable device */
	//! [select_slave]
//	spi_select_slave(&spi_master_instance, &slave, true);
    FLASH_CS_Clear();
	SPI2_Exchange8bit(0x20);			/* send Sector Erase command */
	SPI2_Exchange8bit(((Dst & 0xFFFFFF) >> 16)); 	/* send 3 address bytes */
	SPI2_Exchange8bit(((Dst & 0xFFFF) >> 8));
	SPI2_Exchange8bit(Dst & 0xFF);
	//gpio_set_pin_level(SERIALFLASH_CS, 1);//CE_SetHigh();				/* disable device */
	//! [deselect_slave]
//	spi_select_slave(&spi_master_instance, &slave, false);
    FLASH_CS_Set();
}

/************************************************************************/
/* PROCEDURE: Block_Erase						*/
/*									*/
/* This procedure Block Erases 8Kbyte, 32 KByte or 64 KByte of the Chip.*/
/*									*/
/* Input:								*/
/*		Dst:		Destination Address 000000H - 7FFFFFH	*/
/************************************************************************/

void SPI_Block_Erase(unsigned long Dst)
{
	//gpio_set_pin_level(SERIALFLASH_CS, 0);//CE_SetLow();				/* enable device */
	//! [select_slave]
//	spi_select_slave(&spi_master_instance, &slave, true);
    FLASH_CS_Clear();
	SPI2_Exchange8bit(0xD8);			/* send Block Erase command */
	SPI2_Exchange8bit(((Dst & 0xFFFFFF) >> 16)); 	/* send 3 address bytes */
	SPI2_Exchange8bit(((Dst & 0xFFFF) >> 8));
	SPI2_Exchange8bit(Dst & 0xFF);
	//gpio_set_pin_level(SERIALFLASH_CS, 1);//CE_SetHigh();				/* disable device */
	//! [deselect_slave]
//	spi_select_slave(&spi_master_instance, &slave, false);
    FLASH_CS_Set();
}


/************************************************************************/
/* PROCEDURE: NoOp                                              	*/
/*									*/
/* No operation is performed.                                           */
/************************************************************************/

void SPI_NoOp()
{
	//gpio_set_pin_level(SERIALFLASH_CS, 0);//CE_SetLow();				/* enable device */
	//! [select_slave]
//	spi_select_slave(&spi_master_instance, &slave, true);
    FLASH_CS_Clear();
	SPI2_Exchange8bit(0x00);
	//gpio_set_pin_level(SERIALFLASH_CS, 1);//CE_SetHigh();				/* disable device */
	//! [deselect_slave]
//	spi_select_slave(&spi_master_instance, &slave, false);
    FLASH_CS_Set();
}



/************************************************************************/
/* PROCEDURE: ResetEn                                                   */
/*									*/
/* This procedure Enables acceptance of the RST (Reset) operation.	*/
/************************************************************************/

void SPI_ResetEn()
{
	//gpio_set_pin_level(SERIALFLASH_CS, 0);//CE_SetLow();				/* enable device */
	//! [select_slave]
//	spi_select_slave(&spi_master_instance, &slave, true);
    FLASH_CS_Clear();
	SPI2_Exchange8bit(0x66);
	//gpio_set_pin_level(SERIALFLASH_CS, 1);//CE_SetHigh();				/* disable device */
	//! [deselect_slave]
//	spi_select_slave(&spi_master_instance, &slave, false);
    FLASH_CS_Set();
}




/************************************************************************/
/* PROCEDURE: Reset                                     		*/
/*									*/
/* This procedure resets the device in to normal operating Ready mode.	*/
/*									*/
/************************************************************************/


void SPI_Reset()
{
	//gpio_set_pin_level(SERIALFLASH_CS, 0);//CE_SetLow();				/* enable device */
	//! [select_slave]
//	spi_select_slave(&spi_master_instance, &slave, true);
    FLASH_CS_Clear();
	SPI2_Exchange8bit(0x99);
	//gpio_set_pin_level(SERIALFLASH_CS, 1);//CE_SetHigh();				/* disable device */
	//! [deselect_slave]
//	spi_select_slave(&spi_master_instance, &slave, false);
    FLASH_CS_Set();
}



/************************************************************************/
/* PROCEDURE: Write_Suspend						*/
/*									*/
/* This procedure suspends Program/Erase operation.			*/
/************************************************************************/

void SPI_Write_Suspend()
{
	//gpio_set_pin_level(SERIALFLASH_CS, 0);//CE_SetLow();				/* enable device */
	//! [select_slave]
//	spi_select_slave(&spi_master_instance, &slave, true);
    FLASH_CS_Clear();
	SPI2_Exchange8bit(0xb0);
	//gpio_set_pin_level(SERIALFLASH_CS, 1);//CE_SetHigh();				/* disable device */
	//! [deselect_slave]
//	spi_select_slave(&spi_master_instance, &slave, false);
    FLASH_CS_Set();
}



/************************************************************************/
/* PROCEDURE: Write_Resume						*/
/*									*/
/* This procedure resumes Program/Erase operation.			*/
/************************************************************************/

void SPI_Write_Resume()
{
	//gpio_set_pin_level(SERIALFLASH_CS, 0);//CE_SetLow();				/* enable device */
	//! [select_slave]
//	spi_select_slave(&spi_master_instance, &slave, true);
    FLASH_CS_Clear();
	SPI2_Exchange8bit(0x30);
	//gpio_set_pin_level(SERIALFLASH_CS, 1);//CE_SetHigh();				/* disable device */
	//! [deselect_slave]
//	spi_select_slave(&spi_master_instance, &slave, false);
    FLASH_CS_Set();
}



/************************************************************************/
/* PROCEDURE: Write_Status_Register					*/
/*									*/
/* This procedure resumes Program/Erase operation.			*/
/************************************************************************/

void SPI_Write_Status_Register(unsigned int data1, unsigned char datalen)
{	  //For data1 - top 8 bits are status reg bits , lower 8 bits are configuration reg bits
	//gpio_set_pin_level(SERIALFLASH_CS, 0);//CE_SetLow();				/* enable device */
	//! [select_slave]
//	spi_select_slave(&spi_master_instance, &slave, true);
    FLASH_CS_Clear();
	SPI2_Exchange8bit(0x01);
	SPI2_Exchange8bit((data1>>8)&0xff);
	if (datalen==2)
	{
		SPI2_Exchange8bit((data1)&0xff);
	}

	//gpio_set_pin_level(SERIALFLASH_CS, 1);//CE_SetHigh();				/* disable device */
	//! [deselect_slave]
//	spi_select_slave(&spi_master_instance, &slave, false);
    FLASH_CS_Set();
}


/************************************************************************/
/* PROCEDURE:	ReadSID	(Read Security ID)				*/
/*									*/
/* This procedure reads the security ID					*/
/************************************************************************/


void SPI_ReadSID(unsigned char *security_ID, unsigned long Dst, unsigned long security_length)
{

	unsigned long i;
	i=0;
	if (security_length>2048)
	{ security_length=2048;}

	//gpio_set_pin_level(SERIALFLASH_CS, 0);//CE_SetLow();			/* enable device */
	//! [select_slave]
//	spi_select_slave(&spi_master_instance, &slave, true);
    FLASH_CS_Clear();
	SPI2_Exchange8bit(0x88);
	SPI2_Exchange8bit((Dst>>8) & 0xFF);
	SPI2_Exchange8bit(Dst & 0xFF);
	SPI2_Exchange8bit(Dst & 0xFF);  //dummy

	for (i=0;i<security_length;i++)
	{
		*security_ID = SPI2_Exchange8bit(0xFF);
		security_ID++;
	}
	//gpio_set_pin_level(SERIALFLASH_CS, 1);//CE_SetHigh();				/* disable device */
	//! [deselect_slave]
//	spi_select_slave(&spi_master_instance, &slave, false);
    FLASH_CS_Set();
}



/************************************************************************/
/* PROCEDURE:	ProgSID	(Program Security ID)                           */
/*									*/
/* This procedure programs the security ID				*/
/*									*/
/************************************************************************/

void SPI_ProgSID(unsigned char *security_ID, unsigned long Dst, unsigned long security_length)
{
	unsigned long i;

	i=0;

	if (security_length>256)
	{ security_length=256;}

	//gpio_set_pin_level(SERIALFLASH_CS, 0);//CE_SetLow();			/* enable device */
	//! [select_slave]
//	spi_select_slave(&spi_master_instance, &slave, true);
    FLASH_CS_Clear();
	SPI2_Exchange8bit(0xa5);
	SPI2_Exchange8bit((Dst>>8) & 0xFF);
	SPI2_Exchange8bit(Dst & 0xFF);


	for (i=0;i<security_length;i++)
	{
		SPI2_Exchange8bit(*security_ID);
		security_ID++;
	}


	//gpio_set_pin_level(SERIALFLASH_CS, 1);//CE_SetHigh();				/* disable device */
	//! [deselect_slave]
//	spi_select_slave(&spi_master_instance, &slave, false);
    FLASH_CS_Set();
}




/************************************************************************/
/* PROCEDURE:	LockSID							*/
/*									*/
/* This procedure Locks the security ID setting				*/
/*									*/
/************************************************************************/

void SPI_LockSID()
{

	//gpio_set_pin_level(SERIALFLASH_CS, 0);//CE_SetLow();			/* enable device */
	//! [select_slave]
//	spi_select_slave(&spi_master_instance, &slave, true);
    FLASH_CS_Clear();
	SPI2_Exchange8bit(0x85);
	//gpio_set_pin_level(SERIALFLASH_CS, 1);//CE_SetHigh();				/* disable device */
	//! [deselect_slave]
//	spi_select_slave(&spi_master_instance, &slave, false);
    FLASH_CS_Set();
}




/************************************************************************/
/* PROCEDURE:	ReadBlockProtection			  		*/
/*									*/
/* This procedure reads block protection register			*/
/*									*/
/************************************************************************/

void SPI_ReadBlockProtection(unsigned int *block_protection_data)
{
	
	unsigned char i;
	i=0;

	//gpio_set_pin_level(SERIALFLASH_CS, 0);//CE_SetLow();			/* enable device */
	//! [select_slave]
//	spi_select_slave(&spi_master_instance, &slave, true);
    FLASH_CS_Clear();
	SPI2_Exchange8bit(0x72);

	for (i=18;i>0;i--)
	{	*block_protection_data = SPI2_Exchange8bit(0xFF);
		block_protection_data++;
	}
	//gpio_set_pin_level(SERIALFLASH_CS, 1);//CE_SetHigh();				/* disable device */
	//! [deselect_slave]
//	spi_select_slave(&spi_master_instance, &slave, false);
    FLASH_CS_Set();
}



/************************************************************************/
/* PROCEDURE:	WriteBlockProtection					*/
/*									*/
/* This procedure writes to block protection register			*/
/*									*/
/************************************************************************/


void SPI_WriteBlockProtection(unsigned int *block_protection_data)
{

	unsigned char i;
	i=0;

	//gpio_set_pin_level(SERIALFLASH_CS, 0);//CE_SetLow();			/* enable device */
	//! [select_slave]
//	spi_select_slave(&spi_master_instance, &slave, true);
    FLASH_CS_Clear();
	SPI2_Exchange8bit(0x42); 		/* read command */

	for (i=18;i>0;i--)
	{
		SPI2_Exchange8bit(*block_protection_data);
		block_protection_data++;
	}
	//gpio_set_pin_level(SERIALFLASH_CS, 1);//CE_SetHigh();				/* disable device */
	//! [deselect_slave]
//	spi_select_slave(&spi_master_instance, &slave, false);
    FLASH_CS_Set();
}
/************************************************************************/
/* PROCEDURE:	Global Block Protection Unlock				*/
/*									*/
/* This procedure clears all block protection				*/
/************************************************************************/
void SPI_Global_Block_Protection_Unlock()
{

	//gpio_set_pin_level(SERIALFLASH_CS, 0);//CE_SetLow();			/* enable device */
	//! [select_slave]
//	spi_select_slave(&spi_master_instance, &slave, true);
    FLASH_CS_Clear();
	SPI2_Exchange8bit(0x98); 		/* read command */
	//gpio_set_pin_level(SERIALFLASH_CS, 1);//CE_SetHigh();				/* disable device */
	//! [deselect_slave]
//	spi_select_slave(&spi_master_instance, &slave, false);
    FLASH_CS_Set();
}


/************************************************************************/
/* PROCEDURE:	LockBlockProtection					*/
/*									*/
/* This procedure locks the block protection register			*/
/************************************************************************/


void SPI_LockBlockProtection()
{

	//gpio_set_pin_level(SERIALFLASH_CS, 0);//CE_SetLow();			/* enable device */
	//! [select_slave]
//	spi_select_slave(&spi_master_instance, &slave, true);
    FLASH_CS_Clear();
	SPI2_Exchange8bit(0x8d); 		/* read command */
	//gpio_set_pin_level(SERIALFLASH_CS, 1);//CE_SetHigh();				/* disable device */
	//! [deselect_slave]
//	spi_select_slave(&spi_master_instance, &slave, false);
    FLASH_CS_Set();
}





/************************************************************************/
/* PROCEDURE:	Non Volatile Write Lock Protection			*/
/*									*/
/* This procedure writes to block protection register			*/
/*									*/
/************************************************************************/

void SPI_NonVolWriteLockProtection(unsigned int *block_protection_data)
{

	unsigned char i;
	i=0;

	//gpio_set_pin_level(SERIALFLASH_CS, 0);//CE_SetLow();			/* enable device */
	//! [select_slave]
//	spi_select_slave(&spi_master_instance, &slave, true);
    FLASH_CS_Clear();
	SPI2_Exchange8bit(0xE8); 		/* read command */

	for (i=18;i>0;i--)
	{
		SPI2_Exchange8bit(*block_protection_data);
		block_protection_data++;
	}
	//gpio_set_pin_level(SERIALFLASH_CS, 1);//CE_SetHigh();				/* disable device */
	//! [deselect_slave]
//	spi_select_slave(&spi_master_instance, &slave, false);
    FLASH_CS_Set();
}


/************************************************************************/
/* PROCEDURE: Wait_Busy							*/
/*									*/
/* This procedure waits until device is no longer busy (can be used by	*/
/* Byte-Program, Page-Program, Sector-Erase, Block-Erase and Chip-Erase).*/
/************************************************************************/



void SPI_Wait_Busy()
{
	while ((SPI_Read_Status_Register()& 0x80) == 0x80)	// waste time until not busy
	SPI_Read_Status_Register();
}

/************************************************************************/
/* PROCEDURE:	SPI_SFDP_Read						*/
/*									*/
/* This procedure reads SFDP Table.					*/
/*									*/
/************************************************************************/
unsigned char SPI_SFDP_Read(unsigned long Dst)
{
	unsigned char byte = 0;

	//gpio_set_pin_level(SERIALFLASH_CS, 0);//CE_SetLow();                               /* enable device */
	//! [select_slave]
//	spi_select_slave(&spi_master_instance, &slave, true);
    FLASH_CS_Clear();
	SPI2_Exchange8bit(0x5A);                        /* read command */
	SPI2_Exchange8bit(((Dst & 0xFFFFFF) >> 16));	/* send 3 address bytes */
	SPI2_Exchange8bit(((Dst & 0xFFFF) >> 8));
	SPI2_Exchange8bit(Dst & 0xFF);
	SPI2_Exchange8bit(0xFF);                	/*dummy byte*/
	byte = SPI2_Exchange8bit(0xFF);
	//gpio_set_pin_level(SERIALFLASH_CS, 1);//CE_SetHigh();				/* disable device */
	//! [deselect_slave]
//	spi_select_slave(&spi_master_instance, &slave, false);
    FLASH_CS_Set();
	return byte;                     	/* return one byte read */
}

