#include "parameterwithref.h"





ParameterWithRef::ParameterWithRef(float &par, uint32_t hints, string name, string symbol, string unit, ParameterRanges ranges, ParameterFunctionCallback action):
    mParameter(par),mCallback(action)
{
    Parameter::hints=hints;
    Parameter::name=name.c_str()+'\0';
    Parameter::symbol=symbol.c_str()+'\0';
    Parameter::ranges=ranges;
    Parameter::unit=unit.c_str()+'\0';
}

void ParameterWithRef::setParameter(float val)
{
    mCallback.preChange();
    mParameter=val;
    mCallback.postChange();
}

float ParameterWithRef::getParameter()
{
    return mParameter;
}
