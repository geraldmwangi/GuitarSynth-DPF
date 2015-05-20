#include "guitarsynthdspplugin.h"
#include <DistrhoPlugin.hpp>
#include "sinussynth.h"
#include "squaresynth.h"
#include "gausssynth.h"
#include "sawsynth.h"
#include <stdlib.h>
Plugin* DISTRHO::createPlugin()
{
    return new GuitarSynthDSPPlugin();
}
GuitarSynthDSPPlugin::GuitarSynthDSPPlugin():
    Plugin(15,0,0)
{
    mInstance=new GSEngine();
    mInstance->addSynth(new SinusSynth);
    mInstance->addSynth(new SawSynth);
    mInstance->addSynth(new GaussSynth);
    mInstance->addSynth(new SquareSynth);
    mParameters=mInstance->getParameters();
    for(int s=0;s<mInstance->mSynths.size();s++)
    {
        vector<ParameterWithRef*> params=mInstance->mSynths[s]->getParameters();
        for(int p=0;p<params.size();p++)
            mParameters.push_back(params[p]);
    }
//    assert(mParameters.size()==15);
}

GuitarSynthDSPPlugin::~GuitarSynthDSPPlugin()
{
    if(mInstance)
        delete mInstance;
}

void GuitarSynthDSPPlugin::initParameter(uint32_t index, Parameter &parameter)
{
    Parameter par=parameter=*mParameters[index];
    parameter.hints=par.hints;
    parameter.name=par.name;
    parameter.ranges=par.ranges;
    parameter.symbol=par.symbol;
    parameter.unit=par.unit;


}

//void GuitarSynthDSPPlugin::initProgramName(uint32_t index, string &programName)
//{

//}

float GuitarSynthDSPPlugin::getParameterValue(uint32_t index) const
{

    ParameterWithRef* par=mParameters[index];
    return par->getParameter();
}

void GuitarSynthDSPPlugin::setParameterValue(uint32_t index, float value)
{
        ParameterWithRef* par=mParameters[index];
        par->setParameter(value);
}

//void GuitarSynthDSPPlugin::loadProgram(uint32_t index)
//{

//}

void GuitarSynthDSPPlugin::activate()
{
    mInstance->InitEngine(getSampleRate(),getBufferSize());
}

void GuitarSynthDSPPlugin::deactivate()
{

}

void GuitarSynthDSPPlugin::run(const float **inputs, float **outputs, uint32_t frames)
{
    mInstance->process(inputs,outputs,frames);

}
