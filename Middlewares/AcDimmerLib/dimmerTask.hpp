
#ifndef DIMMERTASK_HPP
#define DIMMERTASK_HPP

#include "stm32f4xx.h"

extern "C" {
	#include "dimmerlib.h"	
}

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#define configGUITASKPRIORITY               ( tskIDLE_PRIORITY + 1 )
#define configGUITASKSTKSIZE                ( 1024 )

namespace touchgfx
{
	class DIMMERTASK
	{
	public:
		
			static void DimmerBegin();
			static void DimmerTimerOccour();

	}; 
} // namespace touchgfx

#endif // DIMMERTASK_HPP
