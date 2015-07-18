#ifndef DIAL_H
#define DIAL_H
#include "DistrhoUI.hpp"

//#include "ImageAboutWindow.hpp"
//#include "ImageButton.hpp"
//#include "ImageKnob.hpp"
//#include "ImageSlider.hpp"

class Dial: public NanoWidget
{
public:
    Dial(DGL::Window &parent);
protected:
    void onNanoDisplay();
};


#endif // DIAL_H
