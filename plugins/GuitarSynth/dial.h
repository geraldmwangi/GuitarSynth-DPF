#ifndef DIAL_H
#define DIAL_H
#include "DistrhoUI.hpp"
#include "NanoVG.hpp"
//#include "ImageAboutWindow.hpp"
//#include "ImageButton.hpp"
//#include "ImageKnob.hpp"
//#include "ImageSlider.hpp"
START_NAMESPACE_DGL
class Dial: public NanoWidget
{
public:
    Dial(NanoWidget *parent);
protected:
    void onNanoDisplay();
};
END_NAMESPACE_DGL

#endif // DIAL_H
