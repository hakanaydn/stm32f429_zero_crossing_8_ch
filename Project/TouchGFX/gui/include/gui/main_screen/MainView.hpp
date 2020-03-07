#ifndef MAIN_VIEW_HPP
#define MAIN_VIEW_HPP

#include <gui_generated/main_screen/MainViewBase.hpp>
#include <gui/main_screen/MainPresenter.hpp>
#include <gui/common/ParticleEffect.hpp>
#include <gui/common/ScrollingWheels/ParticlesScrollingWheel.hpp>
#include <touchgfx/mixins/FadeAnimator.hpp>

class MainView : public MainViewBase
{
public:
    MainView();
    virtual ~MainView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
			
		virtual void fButOkClicked();


protected:

    ParticleEffect particleEffect;
    int numberOfParticles;

    FadeAnimator<ParticlesScrollingWheel> particlesScrollingWheel;

    virtual void gotoMenuSelected();

};

#endif // MAIN_VIEW_HPP
