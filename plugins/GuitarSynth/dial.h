#ifndef DIAL_H
#define DIAL_H
#include "DistrhoUI.hpp"

//#include "ImageAboutWindow.hpp"
//#include "ImageButton.hpp"
//#include "ImageKnob.hpp"
//#include "ImageSlider.hpp"
USE_NAMESPACE_DISTRHO
USE_NAMESPACE_DGL
class Dial: public UIWidget
{
public:
    Dial(Window* parent);
protected:
    void onNanoDisplay();
};

#endif // DIAL_H
