#ifndef SCREENDIMMER_VIEW_HPP
#define SCREENDIMMER_VIEW_HPP

#include <gui_generated/screendimmer_screen/ScreenDimmerViewBase.hpp>
#include <gui/screendimmer_screen/ScreenDimmerPresenter.hpp>

class ScreenDimmerView : public ScreenDimmerViewBase
{
public:
    ScreenDimmerView();
    virtual ~ScreenDimmerView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // SCREENDIMMER_VIEW_HPP
