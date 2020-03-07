/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/screendimmer_screen/ScreenDimmerViewBase.hpp>
#include "BitmapDatabase.hpp"
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/Color.hpp>

ScreenDimmerViewBase::ScreenDimmerViewBase() :
    buttonCallback(this, &ScreenDimmerViewBase::buttonCallbackHandler),
    sliderValueChangedCallback(this, &ScreenDimmerViewBase::sliderValueChangedCallbackHandler)
{
    image.setXY(0, 0);
    image.setBitmap(Bitmap(BITMAP_BACKGROUND_ID));

    buttonWithExit.setXY(43, 254);
    buttonWithExit.setBitmaps(Bitmap(BITMAP_BLUE_BUTTONS_ROUND_EDGE_SMALL_ID), Bitmap(BITMAP_BLUE_BUTTONS_ROUND_EDGE_SMALL_PRESSED_ID));
    buttonWithExit.setLabelText(TypedText(T_SINGLEUSEID3));
    buttonWithExit.setLabelColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    buttonWithExit.setLabelColorPressed(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    buttonWithExit.setAction(buttonCallback);

    toggleButton1.setXY(64, 10);
    toggleButton1.setBitmaps(Bitmap(BITMAP_BLUE_TOGGLEBARS_TOGGLE_ROUND_LARGE_BUTTON_OFF_ID), Bitmap(BITMAP_BLUE_TOGGLEBARS_TOGGLE_ROUND_LARGE_BUTTON_ON_ID));
    toggleButton1.setAction(buttonCallback);

    slider1.setXY(9, 58);
    slider1.setBitmaps(Bitmap(BITMAP_BLUE_SLIDER_VERTICAL_SMALL_SLIDER3_VERTICAL_ROUND_FILL_ID), Bitmap(BITMAP_BLUE_SLIDER_VERTICAL_SMALL_SLIDER3_VERTICAL_ROUND_BACK_ID), Bitmap(BITMAP_SLIDER_KNOB_SHAPE_ID));
    slider1.setupVerticalSlider(7, 3, 0, 0, 154);
    slider1.setValueRange(0, 100);
    slider1.setValue(0);
    slider1.setNewValueCallback(sliderValueChangedCallback);

    textProgress1.setXY(78, 143);
    textProgress1.setProgressIndicatorPosition(0, 0, 84, 34);
    textProgress1.setRange(0, 100);
    textProgress1.setColor(touchgfx::Color::getColorFrom24BitRGB(0, 0, 0));
    textProgress1.setNumberOfDecimals(0);
    textProgress1.setTypedText(TypedText(T_SINGLEUSEID4));
    textProgress1.setValue(60);

    textArea1.setXY(71, 105);
    textArea1.setColor(touchgfx::Color::getColorFrom24BitRGB(0, 0, 0));
    textArea1.setLinespacing(0);
    textArea1.setTypedText(TypedText(T_SINGLEUSEID5));

    add(image);
    add(buttonWithExit);
    add(toggleButton1);
    add(slider1);
    add(textProgress1);
    add(textArea1);
}

void ScreenDimmerViewBase::setupScreen()
{

}

void ScreenDimmerViewBase::buttonCallbackHandler(const touchgfx::AbstractButton& src)
{
    if (&src == &buttonWithExit)
    {
        //Interaction1
        //When buttonWithExit clicked change screen to Main
        //Go to Main with screen transition towards East
        application().gotoMainScreenSlideTransitionEast();

        //Interaction2
        //When buttonWithExit clicked call virtual function
        //Call fButExitClicked
        fButExitClicked();
    }
    else if (&src == &toggleButton1)
    {
        //Interaction4
        //When toggleButton1 clicked call virtual function
        //Call fchangeButOnOff
        fchangeButOnOff();
    }
}

void ScreenDimmerViewBase::sliderValueChangedCallbackHandler(const touchgfx::Slider& src, int value)
{
    if (&src == &slider1)
    {
        //Interaction3
        //When slider1 value changed call virtual function
        //Call fchangeSliderDimmer
        fchangeSliderDimmer(value);
    }
}
