#ifndef GUITARSYNTHGUIPLUGIN_H
#define GUITARSYNTHGUIPLUGIN_H
#include "DistrhoUI.hpp"
#include <dial.h>
//#include "ImageAboutWindow.hpp"
//#include "ImageButton.hpp"
//#include "ImageKnob.hpp"
//#include "ImageSlider.hpp"
START_NAMESPACE_DISTRHO
class GuitarSynthGuiPlugin: public UI
{
public:
    GuitarSynthGuiPlugin();
    ~GuitarSynthGuiPlugin();
protected:
    virtual void parameterChanged(uint32_t index, float value);
    virtual void programLoaded(uint32_t index);
    virtual void stateChanged(const char* key, const char* value);
    virtual void onNanoDisplay();
private:
    DGL::Dial* m_dial;
    DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GuitarSynthGuiPlugin)

};
END_NAMESPACE_DISTRHO

#endif // GUITARSYNTHGUIPLUGIN_H
