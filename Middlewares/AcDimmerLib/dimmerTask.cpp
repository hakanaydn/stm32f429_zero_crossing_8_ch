/**
******************************************************************************
* @file         dimmerTask.c
* @authors      Hakan AYDIN
* @date         01-FEB-2019
* @version      V0.0.1
* @copyright    Copyright (c) 2019 
* @brief        Bu dosya GUI üzerinden 8 adet lambayi kontrol etmesi icin hazirlandi
******************************************************************************
*/

/*****************************************************************************/
/* INCLUDES */
/*****************************************************************************/
#include "dimmerTask.hpp"
#include "dimmerlib.h" 
#include "dimmerFlash.h" 

#include "string.h"
#include "dimmerlib.h" 
#include "stdbool.h"

#include <touchgfx/hal/CONSOL.hpp>

/*****************************************************************************/
/* GLOBALS 																																	 */
/*****************************************************************************/
using namespace touchgfx;

/*****************************************************************************/
/* EXTERN																																		 */
/*****************************************************************************/
extern Ts_AcDimLight_t AcDimLight[DIMMER_LAMP_COUNT];
extern SemaphoreHandle_t SemaphoreUpdateDimmer;
extern SemaphoreHandle_t SemaphorExitDimmer;
extern void DimmerOccur(void);

/*****************************************************************************/
/* STATIC 																																	 */
/*****************************************************************************/
static void AcDimmerLearnTask(void* params);
static void AcDimmerWriteFlash(void* params);
static void ZeroCrossingDedectorInt(void);
static void DimmerTimerInt(void);

static volatile bool 	  	ZCD_Flag		=	false;
static volatile uint8_t 	LampCnt   	= 0;

char kelime[50];

xSemaphoreHandle xFlashMutex;

void DIMMERTASK::DimmerBegin()
{
		xTaskCreate(AcDimmerLearnTask, "AcDimmerLearnTask",
                configGUITASKSTKSIZE,
                NULL,
                configGUITASKPRIORITY,
                NULL);
	
//		xTaskCreate(AcDimmerWriteFlash, "AcDimmerWriteFlash",
//							configGUITASKSTKSIZE,
//							NULL,
//							configGUITASKPRIORITY,
//							NULL);
//	
		Dimmer_Init();
	
	  /* Create the Semaphore for synchronization between hw & softirq */
    vSemaphoreCreateBinary(SemaphoreUpdateDimmer);	
		/* Create the Semaphore for synchronization between hw & softirq */
    vSemaphoreCreateBinary(SemaphorExitDimmer);	
		/* Create the Mutex for accessing the console */
    //xFlashMutex = xSemaphoreCreateMutex();
}

static void AcDimmerWriteFlash(void* params){
	
	while(1) {
			 /* Block until the semaphore is given */
       xSemaphoreTake(SemaphorExitDimmer, portMAX_DELAY);
				  
			//xSemaphoreTake(xFlashMutex, portMAX_DELAY);
			 if(SendFlashData() == HAL_OK){
				CONSOL::transmit((char*)"KAYDEDILDI\r\n",strlen("KAYDEDILDI\r\n"));
			 }else{
				CONSOL::transmit((char*)"PROBLEM\r\n",strlen("KAYDEDILDI\r\n"));
			 }
			//xSemaphoreGive(xFlashMutex);

		}
}

/**
  * @brief  Configures ....
  * @param  None
  * @retval None
  */
void AcDimmerLearnTask(void* params){
		
  uint8_t index = 0;
	
	while(1) {
			 /* Block until the semaphore is given */
       xSemaphoreTake(SemaphoreUpdateDimmer, portMAX_DELAY);
						
				for(index = 0 ; index < DIMMER_LAMP_COUNT ; index++)
				{
					if(AcDimLight[index].flag ==true && AcDimLight[index].DimLightState.Mode == ON) 
					{
						AcDimLight[index].TriacOffTime = map(100-AcDimLight[index].DimLightState.Val, LAMP_MIN_LUKS_RATIO, LAMP_MAX_LUKS_RATIO, LAMP_MIN_LUKS_VALUE, LAMP_MAX_LUKS_VALUE);
						AcDimLight[index].TriacOffTime = AcDimLight[index].TriacOffTime;
						break;
					}
					else if(AcDimLight[index].flag ==true && AcDimLight[index].DimLightState.Mode == OFF){
						AcDimLight[index].TriacOffTime =950;
						AcDimLight[index].TriacOffTime = AcDimLight[index].TriacOffTime;
						break;		
					}
				}		
				//SendFlashData();
		}
}
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) 
{
		if(GPIO_Pin == AC_Int_Pin){
			HAL_NVIC_DisableIRQ(EXTI15_10_IRQn);
			ZeroCrossingDedectorInt();	
			HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
		}
}

void ZeroCrossingDedectorInt()
{
		uint8_t index = 0;
    LampCnt = 0;
    
    for(index=0; index<DIMMER_LAMP_COUNT; index++)
    {
      AcDimLight[index].LampOnFlag = false; 
			pDimmerGPIOState[index](false);
    }  
    ZCD_Flag = true; 
}

extern void DimmerOccur(void){
	DimmerTimerInt();
}

void DimmerTimerInt()
{
	uint8_t index = 0;
		
  if(ZCD_Flag == true)                     
  {
			for(index = 0; index < DIMMER_LAMP_COUNT; index++) 
			{
				if(AcDimLight[index].TriacNowTime >= AcDimLight[index].TriacOffTime && AcDimLight[index].LampState == false )       
				{
					if(AcDimLight[index].DimLightState.Mode == ON && AcDimLight[index].DimLightState.Val != 0 ) 
					{
							pDimmerGPIOState[index](true);
							AcDimLight[index].LampOnFlag   = true;  

					}
					else if(AcDimLight[index].DimLightState.Mode == OFF ||  AcDimLight[index].DimLightState.Val == 0  )
					{
							pDimmerGPIOState[index](false);
							AcDimLight[index].LampOnFlag   = true;  
					}
					
					AcDimLight[index].TriacNowTime = 0;  
					
					LampCnt++;
					
					if(LampCnt == DIMMER_LAMP_COUNT)
					{    
						ZCD_Flag = false;     
					}
				}
				else if(AcDimLight[index].LampState == true)
				{
						pDimmerGPIOState[index](false);
				}					
				else if(AcDimLight[index].LampOnFlag == false)
				{
					AcDimLight[index].TriacNowTime++;                     
				}          
		 }
  }
}
/*****************************************************************************/
/* END OF FILE */
/*****************************************************************************/
