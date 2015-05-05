#include "parameterwithref.h"

void ParameterWithRef::preChange()
{

}

void ParameterWithRef::postChange()
{

}

ParameterWithRef::ParameterWithRef(float& par, uint32_t hints, String name, String symbol, String unit, ParameterRanges ranges):
    mParameter(par)
{
    Parameter::hints=hints;
    Parameter::name=name;
    Parameter::symbol=symbol;
    Parameter::ranges=ranges;
    Parameter::unit=unit;
}

void ParameterWithRef::setParameter(float val)
{
    preChange();
    mParameter=val;
    postChange();
}

float ParameterWithRef::getParameter()
{
    return mParameter;
}
