#include "guitarsynthguiplugin.h"
START_NAMESPACE_DISTRHO
GuitarSynthGuiPlugin::GuitarSynthGuiPlugin(): UI(512,512)
{
    show();
    m_dial=new Dial(this->getParentWindow());
    m_dial->show();
}

GuitarSynthGuiPlugin::~GuitarSynthGuiPlugin()
{
    delete m_dial;
}

void GuitarSynthGuiPlugin::parameterChanged(uint32_t index, float value)
{

}

void GuitarSynthGuiPlugin::programLoaded(uint32_t index)
{

}

void GuitarSynthGuiPlugin::stateChanged(const char *key, const char *value)
{

}

void GuitarSynthGuiPlugin::onNanoDisplay()
{


    m_dial->show();

}

UI* createUI()
{
    return new GuitarSynthGuiPlugin();
}

END_NAMESPACE_DISTRHO
