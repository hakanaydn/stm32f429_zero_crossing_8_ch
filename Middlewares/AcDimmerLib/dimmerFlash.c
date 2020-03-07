#include "dimmerFlash.h"
#include "dimmerlib.h" 

/*Variable used for Erase procedure*/
static FLASH_EraseInitTypeDef EraseInitStruct;
uint32_t FirstSector = 0, NbOfSectors = 0, Address = 0;
uint32_t flashGetSector(uint32_t Address);
uint32_t SectorError = 0;

/**
 * @brief  Flash memory kitle
 * @param  None
 * @retval None
 */
void LockFlash(void)
{
	HAL_FLASH_Lock();
}

/**
 * @brief  Flash memory kiliti aç
 * @param  None
 * @retval None
 */
void UnlockFlash(void)
{
	HAL_FLASH_Unlock();
}

bool EraseFlashSectors()
{

	/* Get the 1st sector to erase */
	FirstSector = flashGetSector(DIMMER_PAGE0_BASE_ADDRESS);
	/* Get the number of sector to erase from 1st sector*/
	NbOfSectors = flashGetSector(DIMMER_PAGE0_BASE_ADDRESS) - FirstSector + 1;
	
	/* Fill EraseInit structure*/
	EraseInitStruct.TypeErase 		= 	TYPEERASE_SECTORS;
	EraseInitStruct.VoltageRange 	= 	DIMMER_VOLTAGE_RANGE;
	EraseInitStruct.Sector			  = 	FirstSector;
	EraseInitStruct.NbSectors 		= 	NbOfSectors;
	
		
	return HAL_FLASHEx_Erase(&EraseInitStruct, &SectorError);
}

/**
 * @brief  Write datas to flash adress
 * @param  None
 * @retval OK or Error
 */
bool DimmerWriteFlash(uint32_t FlashDestinationBaseAddr, Ts_AcDimLight_t *pSource)
{	
	  uint32_t addr = 0;
	
	  UnlockFlash();
		if (EraseFlashSectors() != HAL_OK)
		{
			 return HAL_ERROR;
		}
		for(uint8_t lampcnt = 0 ; lampcnt < DIMMER_LAMP_COUNT ; lampcnt++)
		{
			if(HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, FlashDestinationBaseAddr + addr, pSource[lampcnt].DimLightState.Mode)!= HAL_OK)
			{
				LockFlash();
				return HAL_ERROR;
			}
			addr += 2;

			if(HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, FlashDestinationBaseAddr + addr, pSource[lampcnt].DimLightState.Val)!= HAL_OK)
			{
				LockFlash();
				return HAL_ERROR;
			}
			addr += 2;
		}
		
		LockFlash();
		return HAL_OK;
}



uint32_t flashGetSector(uint32_t Address)
{
	uint32_t sector = 0;
	
	if((Address < DIMMER_PAGE0_BASE_ADDRESS) && (Address >= DIMMER_PAGE1_BASE_ADDRESS))
	{
		sector = FLASH_SECTOR_22;  
	}
	else 
	{
		sector = FLASH_SECTOR_23;
	}

	return sector;
}


