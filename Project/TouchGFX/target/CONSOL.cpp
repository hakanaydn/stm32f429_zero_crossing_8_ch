#include <touchgfx/hal/CONSOL.hpp>

#include "stm32f429i_discovery.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "string.h"

using namespace touchgfx;

UART_HandleTypeDef huart1;
GPIO_InitTypeDef GPIO_InitStruct;

xSemaphoreHandle xConsoleMutex;

#define TX_Pin GPIO_PIN_9
#define TX_GPIO_Port GPIOA
#define RX_Pin GPIO_PIN_10
#define RX_GPIO_Port GPIOA

void CONSOL::init()
{
    __HAL_RCC_USART1_CLK_ENABLE();
	
		/**USART1 GPIO Configuration    
		PA9     ------> USART1_TX
		PA10     ------> USART1_RX 
		*/
		GPIO_InitStruct.Pin = TX_Pin|RX_Pin;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

		huart1.Instance = USART1;
		huart1.Init.BaudRate = 115200;
		huart1.Init.WordLength = UART_WORDLENGTH_8B;
		huart1.Init.StopBits = UART_STOPBITS_1;
		huart1.Init.Parity = UART_PARITY_NONE;
		huart1.Init.Mode = UART_MODE_TX_RX;
		huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
		huart1.Init.OverSampling = UART_OVERSAMPLING_16;
		HAL_UART_Init(&huart1);	
		
		/* Create the Mutex for accessing the console */
    xConsoleMutex = xSemaphoreCreateMutex();
}

void CONSOL::transmit(char* data,int len)
{
	
	  xSemaphoreTake(xConsoleMutex, portMAX_DELAY);
		HAL_UART_Transmit(&huart1,(uint8_t*)data,strlen(data),50);	
		xSemaphoreGive(xConsoleMutex);
}