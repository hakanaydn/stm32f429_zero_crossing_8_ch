/**
******************************************************************************
* @file         dimmerlib.h
* @authors      Hakan AYDIN
* @date         01-FEB-2019
* @version      V0.0.1
* @copyright    Copyright (c) 2019 
* @brief        Bu dosya GUI üzerinden 8 adet lambayi kontrol etmesi icin hazirlandi.
								Her 10ms'de bir TIM13 tarafindan kesme  uretilmektedir. Zero crossing
								sayesinde ise sinus dalgasinin her sifir pozisyonu algilanarak, dalga 
								uzerinde istenen orana (%0 - %100 arasinda) lamba parlakligi ayarlanmaktadir. 	
******************************************************************************
*/
#ifndef DIMMERLIB_H_
#define DIMMERLIB_H_

/*****************************************************************************/
/* INCLUDES                                                                  */
/*****************************************************************************/
#include "stm32f4xx.h"
#include "stdbool.h"
#include "stm32f429i_discovery.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

/*****************************************************************************/
/* STRUCTURE/ENUM DEFINITIONS                                                */
/*****************************************************************************/
typedef enum {OFF = 0x0, ON = 0x01} TE_Mode_t;

typedef struct _DimLightState{
			TE_Mode_t  		 Mode;								  /* LAMBA MOD */
			uint8_t     	 Val;								  	/* YUZDELIK OLARAK LAMBA DEGERI 0-100 */
}DimLightState_t;

typedef struct _AcDimLight {
			uint8_t    		 		ID;									/* LAMBA ID'SI */
			DimLightState_t		DimLightState;			
			uint8_t     			PrevVal;						/* BIR ONCEKI DEGER */
			uint16_t     		  TriacOffTime;				/* TRIYAK KAC uS Off OLARAK KALACAK */
			uint16_t				  TriacNowTime;				/* TRIYAK SIMDKI ZAMANI */
			bool 					 		flag;								/* LCD EKRAN GUNCELLEME FLAG'I */
			bool 						  LampState;				  /* LAMBA ON - OFF DURUMU*/
			bool 					 		LampOnFlag;					/* LCD EKRAN GUNCELLEME FLAG'I */
}Ts_AcDimLight_t;

/*****************************************************************************/
/* DEFINITIONS                                                               */
/*****************************************************************************/
#define DIMMER_LAMP_MAX_VAL    100
#define DIMMER_LAMP_MIN_VAL    0 	  
#define DIMMER_LAMP_COUNT   	 8 	
#define LAMP_MAX_LUKS_VALUE    950
#define LAMP_MIN_LUKS_VALUE    150
#define LAMP_MAX_LUKS_RATIO    100
#define LAMP_MIN_LUKS_RATIO    0


													/*ID, Mode, Val, PrevVal, TriacOffTime, TriacOffTime,  Flag, LampState, LampOnFlag,*/    
#define INIT_DIMMER_LAMP_1   0,  OFF, 	0,       0,		    	 950,	      	   0, false,     false,      false,            
#define INIT_DIMMER_LAMP_2   1,  OFF, 	0,       0,		    	 950,	       	   0, false,     false,      false,          
#define INIT_DIMMER_LAMP_3   2,  OFF, 	0,       0,		    	 950,	      	   0, false,     false,      false,          
#define INIT_DIMMER_LAMP_4   3,  OFF, 	0,       0,		    	 950,	      	   0, false,     false,      false,          
#define INIT_DIMMER_LAMP_5   4,  OFF, 	0,       0,	    		 950,     		   0, false,     false,      false,          
#define INIT_DIMMER_LAMP_6   5,  OFF, 	0,       0,		    	 950,	      	   0, false,     false,      false,          
#define INIT_DIMMER_LAMP_7   6,  OFF, 	0,       0,		    	 950,	      	   0, false,     false,      false,          
#define INIT_DIMMER_LAMP_8   7,  OFF, 	0,       0,		    	 950,	      	   0, false,     false,      false,

#define INIT_DIMMER  {    \
    INIT_DIMMER_LAMP_1    \
    INIT_DIMMER_LAMP_2    \
    INIT_DIMMER_LAMP_3    \
    INIT_DIMMER_LAMP_4    \
    INIT_DIMMER_LAMP_5    \
    INIT_DIMMER_LAMP_6    \
    INIT_DIMMER_LAMP_7    \
    INIT_DIMMER_LAMP_8    \
}

#define LAMP_1_Pin GPIO_PIN_2
#define LAMP_1_GPIO_Port GPIOE

#define LAMP_2_Pin GPIO_PIN_3
#define LAMP_2_GPIO_Port GPIOE

#define LAMP_3_Pin GPIO_PIN_4
#define LAMP_3_GPIO_Port GPIOE

#define LAMP_4_Pin GPIO_PIN_5
#define LAMP_4_GPIO_Port GPIOE

#define LAMP_5_Pin GPIO_PIN_6
#define LAMP_5_GPIO_Port GPIOE

#define LAMP_6_Pin GPIO_PIN_6
#define LAMP_6_GPIO_Port GPIOF

#define LAMP_7_Pin GPIO_PIN_3
#define LAMP_7_GPIO_Port GPIOC

#define LAMP_8_Pin GPIO_PIN_5
#define LAMP_8_GPIO_Port GPIOA

#define AC_Int_Pin GPIO_PIN_13
#define AC_Int_GPIO_Port GPIOC
#define AC_Int_EXTI_IRQn EXTI15_10_IRQn

/*****************************************************************************/
/* VARIABLES                                                                 */
/*****************************************************************************/
typedef void (*const pDimmerFunction)(bool);

/*****************************************************************************/
/* EXTERN GLOBALS                                                            */
/*****************************************************************************/
extern Ts_AcDimLight_t AcDimLight[DIMMER_LAMP_COUNT];
extern SemaphoreHandle_t SemaphoreUpdateDimmer;
extern SemaphoreHandle_t SemaphorExitDimmer;
extern TIM_HandleTypeDef htim13;

/*****************************************************************************/
/* FUNCTION DECLERATIONS																										 */
/*****************************************************************************/
void Dimmer_Init(void) ;
void Dimmer_GPIO_Init(void) ;
void Dimmer_TIMER_Init(void);
void DimmerOccur(void);

void pLamp1State(bool val);
void pLamp2State(bool val);
void pLamp3State(bool val);
void pLamp4State(bool val);
void pLamp5State(bool val);
void pLamp6State(bool val);
void pLamp7State(bool val);
void pLamp8State(bool val);

bool SendFlashData(void);
uint16_t map(uint8_t x, uint8_t in_min, uint8_t in_max, uint16_t out_min, uint16_t out_max);
/*****************************************************************************/
/* STRUCTS																																	 */
/*****************************************************************************/
extern pDimmerFunction pDimmerGPIOState[];
#endif                                                                                                                  /* DIMMERLIB_H_ */
/*****************************************************************************/
/* END OF FILE */
/*****************************************************************************/