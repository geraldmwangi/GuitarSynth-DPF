#include "parameterupdatewave.h"
#include <synthbase.h>



void ParameterUpdateWave::postChange()
{
    mSynth->InitSynth();
}

ParameterUpdateWave::ParameterUpdateWave(SynthBase *synth, float &par, uint32_t hints, string name, string symbol, string unit, ParameterRanges ranges):
    ParameterWithRef(par,hints,name,symbol,unit,ranges)
{
    mSynth=synth;
}
