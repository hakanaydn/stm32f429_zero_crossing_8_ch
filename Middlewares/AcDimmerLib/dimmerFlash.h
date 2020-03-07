/**
******************************************************************************
* @file         dimmerFlash.h
* @authors      Hakan AYDIN
* @date         18-Feb-2019
* @version      V0.0.1
* @copyright    Copyright (c) 2019 
* @brief        dimmerFlash Header File.
******************************************************************************
*/
#ifndef DIMMER_FLASH_H_
#define DIMMER_FLASH_H_

/*****************************************************************************/
/*                               INCLUDES                                    */
/*****************************************************************************/
#include "stm32f4xx.h"
#include "stdbool.h"
#include "stm32f429i_discovery.h"
#include "dimmerlib.h" 

/*****************************************************************************/
/*                              DEFINITIONS                                  */
/*****************************************************************************/
/* Error Codes */
#define DIMMER_FLASH_OK      					 (uint32_t)HAL_OK
#define DIMMER_FLASH_ERROR   					 (uint32_t)HAL_ERROR
#define DIMMER_FLASH_BUSY    					 (uint32_t)HAL_BUSY
#define DIMMER_FLASH_TIMEOUT 					 (uint32_t)HAL_TIMEOUT

/* Sector Page Size */
#define DIMMER_PAGE_SIZE               (uint32_t)0x20000  	 /* Page size = 128KByte */

/* Device working voltage range [2.7V to 3.6V]*/
#define DIMMER_VOLTAGE_RANGE           (uint8_t)VOLTAGE_RANGE_3

/*Start address in Flash */
#define DIMMER_EEPROM_START_ADDRESS  ((uint32_t)0x081C0000) /*From Sector 22*/																															
 
 /* Base page 0 and 1 adress */
#define DIMMER_PAGE0_BASE_ADDRESS    ((uint32_t)(DIMMER_EEPROM_START_ADDRESS + 0x0000))
#define DIMMER_PAGE0_END_ADDRESS     ((uint32_t)(DIMMER_EEPROM_START_ADDRESS + (DIMMER_PAGE_SIZE - 1)))
 
#define DIMMER_PAGE1_BASE_ADDRESS    ((uint32_t)(DIMMER_EEPROM_START_ADDRESS + 0x20000))
#define DIMMER_PAGE1_END_ADDRESS     ((uint32_t)(DIMMER_EEPROM_START_ADDRESS + (2 * DIMMER_PAGE_SIZE - 1)))
 
#define DIMMER_PAGE0                 ((uint16_t)0x0000)
#define DIMMER_PAGE1                 ((uint16_t)0x0001)  

 

/*****************************************************************************/
/*                       STRUCTURE/ENUM DEFINITIONS                          */
/*****************************************************************************/

/*****************************************************************************/
/*                            EXTERN DECLERATIONS                            */
/*****************************************************************************/

/*****************************************************************************/
/*                       PUBLIC FUNCTION DECLERATIONS                        */
/*****************************************************************************/
void DimmerLockFlash(void);
void DimmerUnlockFlash(void);
bool DimmerWriteFlash(uint32_t FlashDestinationBaseAddr, Ts_AcDimLight_t *pSource);
bool EraseFlashSectors();

#endif                                                                                    /*DIMMER_FLASH_H_ */
/*****************************************************************************/
/*                                END OF FILE		                         */
/*****************************************************************************/