#include "guitarsynthdspplugin.h"
#include <DistrhoPlugin.hpp>
Plugin* DISTRHO::createPlugin()
{
    return new GuitarSynthDSPPlugin();
}
GuitarSynthDSPPlugin::GuitarSynthDSPPlugin():
    Plugin(10,1,0)
{
}

void GuitarSynthDSPPlugin::initParameter(uint32_t index, Parameter &parameter)
{

}

//void GuitarSynthDSPPlugin::initProgramName(uint32_t index, String &programName)
//{

//}

float GuitarSynthDSPPlugin::getParameterValue(uint32_t index) const
{

}

void GuitarSynthDSPPlugin::setParameterValue(uint32_t index, float value)
{

}

//void GuitarSynthDSPPlugin::loadProgram(uint32_t index)
//{

//}

void GuitarSynthDSPPlugin::activate()
{

}

void GuitarSynthDSPPlugin::deactivate()
{

}

void GuitarSynthDSPPlugin::run(const float **inputs, float **outputs, uint32_t frames)
{

}
