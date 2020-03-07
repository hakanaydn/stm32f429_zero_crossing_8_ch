#ifndef SCREENDIMMER_PRESENTER_HPP
#define SCREENDIMMER_PRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class ScreenDimmerView;

class ScreenDimmerPresenter : public Presenter, public ModelListener
{
public:
    ScreenDimmerPresenter(ScreenDimmerView& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual ~ScreenDimmerPresenter() {};

private:
    ScreenDimmerPresenter();

    ScreenDimmerView& view;
};


#endif // SCREENDIMMER_PRESENTER_HPP
