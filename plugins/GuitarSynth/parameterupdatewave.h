#ifndef PARAMETERUPDATEWAVE_H
#define PARAMETERUPDATEWAVE_H
#include <parameterwithref.h>
class SynthBase;
class ParameterUpdateWave:public ParameterWithRef
{
    SynthBase* mSynth;
protected:
    virtual void postChange();

public:
    ParameterUpdateWave(SynthBase* synth,float &par, uint32_t hints, string name, string symbol, string unit, ParameterRanges ranges);
};

#endif // PARAMETERUPDATEWAVE_H
