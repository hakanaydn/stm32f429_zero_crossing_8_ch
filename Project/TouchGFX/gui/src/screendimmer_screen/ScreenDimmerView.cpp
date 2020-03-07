#include <gui/screendimmer_screen/ScreenDimmerView.hpp>
#include "BitmapDatabase.hpp"

#include "stdio.h"
#include "string.h"
#include "dimmerlib.h" 

extern Ts_AcDimLight_t AcDimLight[DIMMER_LAMP_COUNT];
extern SemaphoreHandle_t SemaphoreUpdateDimmer;
extern SemaphoreHandle_t SemaphorExitDimmer;
static int LampId = 0 ; 

ScreenDimmerView::ScreenDimmerView()
{

}

void ScreenDimmerView::setupScreen()
{
    ScreenDimmerViewBase::setupScreen();
	
	  for(int i = 0 ; i < DIMMER_LAMP_COUNT ; i++){
				if(AcDimLight[i].flag == true){
					LampId = 	i ;
					break;
				}
		 }	
		
    slider1.setValue(AcDimLight[LampId].DimLightState.Val);
		 
		if(AcDimLight[LampId].DimLightState.Mode == OFF){
			
			  toggleButton1.setXY(64, 10);
				toggleButton1.setBitmaps(Bitmap(BITMAP_BLUE_TOGGLEBARS_TOGGLE_ROUND_LARGE_BUTTON_OFF_ID), Bitmap(BITMAP_BLUE_TOGGLEBARS_TOGGLE_ROUND_LARGE_BUTTON_ON_ID));
				toggleButton1.setAction(buttonCallback);

				textProgress1.setValue(0);
				slider1.setValue(0);
			
		}else if(AcDimLight[LampId].DimLightState.Mode == ON){
				
				toggleButton1.setXY(64, 10);
				toggleButton1.setBitmaps(Bitmap(BITMAP_BLUE_TOGGLEBARS_TOGGLE_ROUND_LARGE_BUTTON_ON_ID), Bitmap(BITMAP_BLUE_TOGGLEBARS_TOGGLE_ROUND_LARGE_BUTTON_OFF_ID));
				toggleButton1.setAction(buttonCallback);
			
				textProgress1.setValue(AcDimLight[LampId].DimLightState.Val);
				slider1.setValue(AcDimLight[LampId].DimLightState.Val);		
		}
}

void ScreenDimmerView::tearDownScreen()
{
    ScreenDimmerViewBase::tearDownScreen();
		static signed portBASE_TYPE xHigherPriorityTaskWoken;
	  /* Give the semaphore */
		xSemaphoreGiveFromISR(SemaphoreUpdateDimmer, &xHigherPriorityTaskWoken);
}

void ScreenDimmerViewBase::fButExitClicked()
{
		static signed portBASE_TYPE xHigherPriorityTaskWoken;
		AcDimLight[LampId].flag = false;
	  /* Give the semaphore */
		xSemaphoreGiveFromISR(SemaphoreUpdateDimmer, &xHigherPriorityTaskWoken);
}

void ScreenDimmerViewBase::fchangeSliderDimmer(int value)
{
	    static signed portBASE_TYPE xHigherPriorityTaskWoken;

			if(	AcDimLight[LampId].DimLightState.Mode == ON /*&& AcDimLight[LampId].PrevVal != value*/){
				
				   AcDimLight[LampId].PrevVal =AcDimLight[LampId].DimLightState.Val ;
					 AcDimLight[LampId].DimLightState.Val=value;
					 textProgress1.setValue(value);
					
					 /* Give the semaphore */
					 xSemaphoreGiveFromISR(SemaphoreUpdateDimmer, &xHigherPriorityTaskWoken);
			}
}

void ScreenDimmerViewBase::fchangeButOnOff()
{
		static signed portBASE_TYPE xHigherPriorityTaskWoken;

		if(AcDimLight[LampId].DimLightState.Mode == OFF){
			
			  toggleButton1.setXY(64, 10);
				toggleButton1.setBitmaps(Bitmap(BITMAP_BLUE_TOGGLEBARS_TOGGLE_ROUND_LARGE_BUTTON_ON_ID), Bitmap(BITMAP_BLUE_TOGGLEBARS_TOGGLE_ROUND_LARGE_BUTTON_OFF_ID));
				toggleButton1.setAction(buttonCallback);
				
				AcDimLight[LampId].DimLightState.Mode = ON;
			
				textProgress1.setValue(AcDimLight[LampId].DimLightState.Val);
				slider1.setValue(AcDimLight[LampId].DimLightState.Val);	
	
		}else if(AcDimLight[LampId].DimLightState.Mode == ON){
				
				toggleButton1.setXY(64, 10);
				toggleButton1.setBitmaps(Bitmap(BITMAP_BLUE_TOGGLEBARS_TOGGLE_ROUND_LARGE_BUTTON_OFF_ID), Bitmap(BITMAP_BLUE_TOGGLEBARS_TOGGLE_ROUND_LARGE_BUTTON_ON_ID));
				toggleButton1.setAction(buttonCallback);
				
				AcDimLight[LampId].DimLightState.Mode = OFF;
			
				textProgress1.setValue(0);
				slider1.setValue(0);	
		}
		
		/* Give the semaphore */
		xSemaphoreGiveFromISR(SemaphoreUpdateDimmer, &xHigherPriorityTaskWoken);
}

