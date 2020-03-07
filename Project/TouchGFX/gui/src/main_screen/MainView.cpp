#include <gui/main_screen/MainView.hpp>
#include <touchgfx/hal/HAL.hpp>

#include <gui_generated/main_screen/MainViewBase.hpp>
#include "BitmapDatabase.hpp"
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/Color.hpp>

#include "dimmerlib.h" 

#include "stdio.h"
#include "stdbool.h"
#include "string.h"
#include <touchgfx/hal/CONSOL.hpp>

extern Ts_AcDimLight_t AcDimLight[DIMMER_LAMP_COUNT];

MainView::MainView()
{
    HAL::getInstance()->setFrameRateCompensation(true);
}

void MainView::setupScreen()
{
    particleEffect.setPosition(0, 0, HAL::DISPLAY_WIDTH, HAL::DISPLAY_HEIGHT);
    particleEffect.setSnapToOrigin(true);
    particleEffect.setNumberOfParticles(180);
    particleEffect.setOrigin(particleEffect.getWidth() / 2, particleEffect.getHeight() / 2);
    particleEffect.setCenter(particleEffect.getWidth() / 2, particleEffect.getHeight() / 2);

    // Insert particleEffect jut on top of the background (z-order)
    container.insert(&background, particleEffect);

    particlesScrollingWheel.setXY(20, 130);
    particlesScrollingWheel.setAlpha(0);
    particlesScrollingWheel.setTouchable(false);
    add(particlesScrollingWheel);

    numberOfParticles = particlesScrollingWheel.setSelectedValue(150);
    particleEffect.setNumberOfParticles(numberOfParticles);
}

void MainView::tearDownScreen()
{
	
}

void MainView::gotoMenuSelected()
{
    if (particlesScrollingWheel.getAlpha() > 0)
    {
        numberOfParticles = particlesScrollingWheel.getSelectedValue();
        particleEffect.setNumberOfParticles(numberOfParticles);

        particleEffect.spawnNewParticles(true);
        particlesScrollingWheel.startFadeAnimation(0, 20);
        particlesScrollingWheel.setTouchable(false);

        headline1.startFadeAnimation(0, 20);
        touchgfxLogo.startMoveAnimation(touchgfxLogo.getX(), (HAL::DISPLAY_HEIGHT - touchgfxLogo.getHeight()) / 2, 20, EasingEquations::cubicEaseInOut, EasingEquations::cubicEaseInOut);

        application().gotoMainScreenSlideTransitionEast();

		}
    else
    {
        particleEffect.spawnNewParticles(false);
        particlesScrollingWheel.startFadeAnimation(255, 20);
        particlesScrollingWheel.setTouchable(true);

        headline1.startFadeAnimation(255, 20);
        touchgfxLogo.startMoveAnimation(touchgfxLogo.getX(), 8, 20, EasingEquations::cubicEaseInOut, EasingEquations::cubicEaseInOut);
		}

}

void MainView::fButOkClicked()
{
		char kelime[10];
		sprintf(kelime,"SECILEN LAMBA : %d\r\n",particlesScrollingWheel.getSelectedValue());
		CONSOL::transmit(kelime,strlen(kelime));
		AcDimLight[particlesScrollingWheel.getSelectedValue()-1].flag  = true;
}

