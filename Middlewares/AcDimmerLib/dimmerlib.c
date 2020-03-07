/**
******************************************************************************
* @file         dimmerlib.c
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
#include "dimmerlib.h" 
#include "stdio.h"
#include "string.h"
#include "stm32f429i_discovery.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "dimmerFlash.h"

/*****************************************************************************/
/* GLOBALS */
/*****************************************************************************/
Ts_AcDimLight_t 	AcDimLight[DIMMER_LAMP_COUNT]=INIT_DIMMER;
SemaphoreHandle_t SemaphoreUpdateDimmer;
SemaphoreHandle_t SemaphorExitDimmer;
TIM_HandleTypeDef htim13;

pDimmerFunction pDimmerGPIOState[]=
{
	(pDimmerFunction)pLamp1State,
	(pDimmerFunction)pLamp2State,
	(pDimmerFunction)pLamp3State,
	(pDimmerFunction)pLamp4State,
	(pDimmerFunction)pLamp5State,
	(pDimmerFunction)pLamp6State,
	(pDimmerFunction)pLamp7State,
	(pDimmerFunction)pLamp8State
};

/*****************************************************************************/
/* FUNCTIONS */
/*****************************************************************************/
void Dimmer_Init (void)
{	
	Dimmer_GPIO_Init();
	
	Dimmer_TIMER_Init();
		
	HAL_TIM_Base_Start_IT(&htim13);
}

uint16_t map(uint8_t x, uint8_t in_min, uint8_t in_max, uint16_t out_min, uint16_t out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void Dimmer_TIMER_Init(void)
{
  /* Peripheral clock enable */
	__HAL_RCC_TIM13_CLK_ENABLE();
	
	/* TIM13 interrupt Init */
  htim13.Instance = TIM13;
  htim13.Init.Prescaler = 44;
  htim13.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim13.Init.Period = 9;
  htim13.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  HAL_TIM_Base_Init(&htim13);
  
	HAL_NVIC_SetPriority(TIM8_UP_TIM13_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(TIM8_UP_TIM13_IRQn);
}

void Dimmer_GPIO_Init(void) 
{
	GPIO_InitTypeDef GPIO_InitStruct;

	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOE_CLK_ENABLE();
	__HAL_RCC_GPIOF_CLK_ENABLE();

	/*Configure GPIO pins : LAMP_1_Pin LAMP_2_Pin LAMP_3_Pin LAMP_4_Pin LAMP_5_Pin */
	GPIO_InitStruct.Pin = LAMP_1_Pin|LAMP_2_Pin|LAMP_3_Pin|LAMP_4_Pin |LAMP_5_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

	/*Configure GPIO pin : LAMP_6_Pin */
	GPIO_InitStruct.Pin = LAMP_6_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(LAMP_6_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pins : LAMP_8_Pin */
	GPIO_InitStruct.Pin = LAMP_8_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/*Configure GPIO pin : AC_Int_Pin */
	GPIO_InitStruct.Pin = AC_Int_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(AC_Int_GPIO_Port, &GPIO_InitStruct);
	
	/*EXTI interrupt init */
	HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
}

bool SendFlashData(){
	
	uint32_t res;
	res = DimmerWriteFlash(DIMMER_PAGE0_BASE_ADDRESS, AcDimLight);
	return (res);
}

void EXTI15_10_IRQHandler(void)
{
  HAL_GPIO_EXTI_IRQHandler(AC_Int_Pin);
}

void TIM8_UP_TIM13_IRQHandler(void)
{
  HAL_TIM_IRQHandler(&htim13);
}

void pLamp1State(bool val){
	if(val == true){
		HAL_GPIO_WritePin(LAMP_1_GPIO_Port, LAMP_1_Pin, GPIO_PIN_SET);
	}else if(val  == false){
		HAL_GPIO_WritePin(LAMP_1_GPIO_Port, LAMP_1_Pin, GPIO_PIN_RESET);
	}	
}

void pLamp2State(bool val){
	if(val == true){
		HAL_GPIO_WritePin(LAMP_2_GPIO_Port, LAMP_2_Pin, GPIO_PIN_SET);
	}else if(val  == false){
		HAL_GPIO_WritePin(LAMP_2_GPIO_Port, LAMP_2_Pin, GPIO_PIN_RESET);
	}	
}

void pLamp3State(bool val){
	if(val == true){
		HAL_GPIO_WritePin(LAMP_3_GPIO_Port, LAMP_3_Pin, GPIO_PIN_SET);
	}else if(val  == false){
		HAL_GPIO_WritePin(LAMP_3_GPIO_Port, LAMP_3_Pin, GPIO_PIN_RESET);
	}	
}

void pLamp4State(bool val){
	if(val == true){
		HAL_GPIO_WritePin(LAMP_4_GPIO_Port, LAMP_4_Pin, GPIO_PIN_SET);
	}else if(val  == false){
		HAL_GPIO_WritePin(LAMP_4_GPIO_Port, LAMP_4_Pin, GPIO_PIN_RESET);
	}	
}

void pLamp5State(bool val){
	if(val == true){
		HAL_GPIO_WritePin(LAMP_5_GPIO_Port, LAMP_5_Pin, GPIO_PIN_SET);
	}else if(val  == false){
		HAL_GPIO_WritePin(LAMP_5_GPIO_Port, LAMP_5_Pin, GPIO_PIN_RESET);
	}	
}

void pLamp6State(bool val){
	if(val == true){
		HAL_GPIO_WritePin(LAMP_6_GPIO_Port, LAMP_6_Pin, GPIO_PIN_SET);
	}else if(val  == false){
		HAL_GPIO_WritePin(LAMP_6_GPIO_Port, LAMP_6_Pin, GPIO_PIN_RESET);
	}	
}

void pLamp7State(bool val){
	if(val == true){
		HAL_GPIO_WritePin(LAMP_7_GPIO_Port, LAMP_7_Pin, GPIO_PIN_SET);
	}else if(val  == false){
		HAL_GPIO_WritePin(LAMP_7_GPIO_Port, LAMP_7_Pin, GPIO_PIN_RESET);
	}	
}
void pLamp8State(bool val){
	if(val == true){
		HAL_GPIO_WritePin(LAMP_8_GPIO_Port, LAMP_8_Pin, GPIO_PIN_SET);
	}else if(val  == false){
		HAL_GPIO_WritePin(LAMP_8_GPIO_Port, LAMP_8_Pin, GPIO_PIN_RESET);
	}	
}

/*****************************************************************************/
/* END OF FILE */
/*****************************************************************************/