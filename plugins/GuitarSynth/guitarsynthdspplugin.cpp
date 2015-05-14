#include "guitarsynthdspplugin.h"
#include <DistrhoPlugin.hpp>
#include "sinussynth.h"
#include "squaresynth.h"
#include "gausssynth.h"
#include "sawsynth.h"
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
}

GuitarSynthDSPPlugin::~GuitarSynthDSPPlugin()
{
    if(mInstance)
        delete mInstance;
}

void GuitarSynthDSPPlugin::initParameter(uint32_t index, Parameter &parameter)
{
    parameter.hints=kParameterIsAutomable;
    switch(index)
    {
    case 0:

        parameter.name="Sinus Gain";
        parameter.ranges=ParameterRanges(0.1,0,1);
        parameter.symbol="SinGa";

        break;
    case 1:

        parameter.name="Sinus Phase";
        parameter.ranges=ParameterRanges(0.1,-1,1);
        parameter.symbol="SinPh";

        break;
    case 2:

        parameter.name="Sinus Transpose";
        parameter.ranges=ParameterRanges(0.1,-1,1);
        parameter.symbol="SinTr";

        break;
    case 3:

        parameter.name="Saw Gain";
        parameter.ranges=ParameterRanges(0.1,0,1);
        parameter.symbol="SawGa";

        break;
    case 4:

        parameter.name="Saw Phase";
        parameter.ranges=ParameterRanges(0.1,-1,1);
        parameter.symbol="SawPh";

        break;
    case 5:

        parameter.name="Saw Transpose";
        parameter.ranges=ParameterRanges(0.1,-1,1);
        parameter.symbol="SawTr";

        break;
    case 6:

        parameter.name="Gauss Gain";
        parameter.ranges=ParameterRanges(0.1,0,1);
        parameter.symbol="GaussGa";

        break;
    case 7:

        parameter.name="Gauss Phase";
        parameter.ranges=ParameterRanges(0.1,-1,1);
        parameter.symbol="GaussPh";

        break;
    case 8:

        parameter.name="Gauss Transpose";
        parameter.ranges=ParameterRanges(0.1,-1,1);
        parameter.symbol="GaussTr";

        break;
    case 9:

        parameter.name="Gauss Standard Deviation";
        parameter.ranges=ParameterRanges(0.5,0.1,10);
        parameter.symbol="GaussStDev";

        break;
    case 10:

        parameter.name="Square Gain";
        parameter.ranges=ParameterRanges(0.1,0,1);
        parameter.symbol="SquareGa";

        break;
    case 11:

        parameter.name="Square Phase";
        parameter.ranges=ParameterRanges(0.1,-1,1);
        parameter.symbol="SquarePh";

        break;
    case 12:

        parameter.name="Square Transpose";
        parameter.ranges=ParameterRanges(0.1,-1,1);
        parameter.symbol="SquareTr";

        break;
    case 13:

        parameter.name="Square Rounding Radius";
        parameter.ranges=ParameterRanges(0.1,0,1);
        parameter.symbol="SquareRoundRad";

        break;
    case 14:
        parameter.name="Input Threshold";
        parameter.ranges=ParameterRanges(0.1,0,1);
        parameter.symbol="InputThresh";
        break;


    }

}

//void GuitarSynthDSPPlugin::initProgramName(uint32_t index, string &programName)
//{

//}

float GuitarSynthDSPPlugin::getParameterValue(uint32_t index) const
{
    float res=0;
    SynthBase* synth;
    GaussSynth* gauss;
    SquareSynth* square;
    switch(index)
    {
    case 0:

//        parameter.name="Sinus Gain";
//        parameter.ranges=ParameterRanges(0.1,0,1);
//        parameter.symbol="SinGa";
         synth=mInstance->mSynths[0];
         res=synth->ampl;
         break;
    case 1:

//        parameter.name="Sinus Phase";
//        parameter.ranges=ParameterRanges(0.1,-1,1);
//        parameter.symbol="SinPh";
        synth=mInstance->mSynths[0];
        res=synth->phase;
        break;
    case 2:

//        parameter.name="Sinus Transpose";
//        parameter.ranges=ParameterRanges(0.1,-1,1);
//        parameter.symbol="SinTr";
        synth=mInstance->mSynths[0];
        res=synth->transposefactor;
        break;
    case 3:

//        parameter.name="Saw Gain";
//        parameter.ranges=ParameterRanges(0.1,0,1);
//        parameter.symbol="SawGa";
        synth=mInstance->mSynths[1];
        res=synth->ampl;

        break;
    case 4:

//        parameter.name="Saw Phase";
//        parameter.ranges=ParameterRanges(0.1,-1,1);
//        parameter.symbol="SawPh";
        synth=mInstance->mSynths[1];
        res=synth->phase;
        break;
    case 5:

//        parameter.name="Saw Transpose";
//        parameter.ranges=ParameterRanges(0.1,-1,1);
//        parameter.symbol="SawTr";
        synth=mInstance->mSynths[1];
        res=synth->transposefactor;
        break;
    case 6:

//        parameter.name="Gauss Gain";
//        parameter.ranges=ParameterRanges(0.1,0,1);
//        parameter.symbol="GaussGa";
        synth=mInstance->mSynths[2];
        res=synth->ampl;

        break;
    case 7:

//        parameter.name="Gauss Phase";
//        parameter.ranges=ParameterRanges(0.1,-1,1);
//        parameter.symbol="GaussPh";
        synth=mInstance->mSynths[2];
        res=synth->phase;

        break;
    case 8:

//        parameter.name="Gauss Transpose";
//        parameter.ranges=ParameterRanges(0.1,-1,1);
//        parameter.symbol="GaussTr";
        synth=mInstance->mSynths[2];
        res=synth->transposefactor;

        break;
    case 9:

//        parameter.name="Gauss Standard Deviation";
//        parameter.ranges=ParameterRanges(0.1,0.1,1);
//        parameter.symbol="GaussStDev";
        synth=mInstance->mSynths[2];
        gauss=dynamic_cast<GaussSynth*>(synth);
        res=gauss->sdfactor;

        break;
    case 10:

//        parameter.name="Square Gain";
//        parameter.ranges=ParameterRanges(0.1,0,1);
//        parameter.symbol="SquareGa";
        synth=mInstance->mSynths[3];
        res=synth->ampl;
        break;
    case 11:

//        parameter.name="Square Phase";
//        parameter.ranges=ParameterRanges(0.1,-1,1);
//        parameter.symbol="SquarePh";
        synth=mInstance->mSynths[3];
        res=synth->phase;
        break;
    case 12:

//        parameter.name="Square Transpose";
//        parameter.ranges=ParameterRanges(0.1,-1,1);
//        parameter.symbol="SquareTr";
        synth=mInstance->mSynths[3];
        square=dynamic_cast<SquareSynth*>(synth);
        res=square->transposefactor;

        break;
    case 13:

//        parameter.name="Square Rounding Radius";
//        parameter.ranges=ParameterRanges(0.1,0,1);
//        parameter.symbol="SquareRoundRad";
        synth=mInstance->mSynths[3];
        square=dynamic_cast<SquareSynth*>(synth);
        res=square->radius;
        break;
    case 14:
//        parameter.name="Input Threshold";
//        parameter.ranges=ParameterRanges(0.1,0,1);
//        parameter.symbol="InputThresh";
        res=mInstance->mInputThreshold;
        break;


    }
    return res;
}

void GuitarSynthDSPPlugin::setParameterValue(uint32_t index, float value)
{
    SynthBase* synth;
    GaussSynth* gauss;
    SquareSynth* square;
    switch(index)
    {
    case 0:

//        parameter.name="Sinus Gain";
//        parameter.ranges=ParameterRanges(0.1,0,1);
//        parameter.symbol="SinGa";
         synth=mInstance->mSynths[0];
         synth->ampl=value;
         break;
    case 1:

//        parameter.name="Sinus Phase";
//        parameter.ranges=ParameterRanges(0.1,-1,1);
//        parameter.symbol="SinPh";
        synth=mInstance->mSynths[0];
        synth->phase=value;
        break;
    case 2:

//        parameter.name="Sinus Transpose";
//        parameter.ranges=ParameterRanges(0.1,-1,1);
//        parameter.symbol="SinTr";
        synth=mInstance->mSynths[0];
        synth->transposefactor=value;
        break;
    case 3:

//        parameter.name="Saw Gain";
//        parameter.ranges=ParameterRanges(0.1,0,1);
//        parameter.symbol="SawGa";
        synth=mInstance->mSynths[1];
        synth->ampl=value;

        break;
    case 4:

//        parameter.name="Saw Phase";
//        parameter.ranges=ParameterRanges(0.1,-1,1);
//        parameter.symbol="SawPh";
        synth=mInstance->mSynths[1];
        synth->phase=value;
        break;
    case 5:

//        parameter.name="Saw Transpose";
//        parameter.ranges=ParameterRanges(0.1,-1,1);
//        parameter.symbol="SawTr";
        synth=mInstance->mSynths[1];
        synth->transposefactor=value;
        break;
    case 6:

//        parameter.name="Gauss Gain";
//        parameter.ranges=ParameterRanges(0.1,0,1);
//        parameter.symbol="GaussGa";
        synth=mInstance->mSynths[2];
        synth->ampl=value;

        break;
    case 7:

//        parameter.name="Gauss Phase";
//        parameter.ranges=ParameterRanges(0.1,-1,1);
//        parameter.symbol="GaussPh";
        synth=mInstance->mSynths[2];
        synth->phase=value;

        break;
    case 8:

//        parameter.name="Gauss Transpose";
//        parameter.ranges=ParameterRanges(0.1,-1,1);
//        parameter.symbol="GaussTr";
        synth=mInstance->mSynths[2];
        synth->transposefactor=value;

        break;
    case 9:

//        parameter.name="Gauss Standard Deviation";
//        parameter.ranges=ParameterRanges(0.1,0.1,1);
//        parameter.symbol="GaussStDev";
        synth=mInstance->mSynths[2];
        gauss=dynamic_cast<GaussSynth*>(synth);
        gauss->sdfactor=value;


        break;
    case 10:

//        parameter.name="Square Gain";
//        parameter.ranges=ParameterRanges(0.1,0,1);
//        parameter.symbol="SquareGa";
        synth=mInstance->mSynths[3];
        synth->ampl=value;
        break;
    case 11:

//        parameter.name="Square Phase";
//        parameter.ranges=ParameterRanges(0.1,-1,1);
//        parameter.symbol="SquarePh";
        synth=mInstance->mSynths[3];
        synth->phase=value;
        break;
    case 12:

//        parameter.name="Square Transpose";
//        parameter.ranges=ParameterRanges(0.1,-1,1);
//        parameter.symbol="SquareTr";
        synth=mInstance->mSynths[3];
        synth->transposefactor=value;


        break;
    case 13:

//        parameter.name="Square Rounding Radius";
//        parameter.ranges=ParameterRanges(0.1,0,1);
//        parameter.symbol="SquareRoundRad";
        synth=mInstance->mSynths[3];
        square=dynamic_cast<SquareSynth*>(synth);
        square->radius=value;

        break;
    case 14:
//        parameter.name="Input Threshold";
//        parameter.ranges=ParameterRanges(0.1,0,1);
//        parameter.symbol="InputThresh";
        mInstance->mInputThreshold=value;
        break;

        break;



    }

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
