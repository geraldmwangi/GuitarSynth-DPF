#include "parameterwithref.h"





void ParameterWithRef::preChange()
{

}

void ParameterWithRef::postChange()
{

}

ParameterWithRef::ParameterWithRef(float &par, uint32_t hints, string name, string symbol, string unit, ParameterRanges ranges):
    mParameter(par)
{
    Parameter::hints=hints;
    Parameter::name=name.c_str()+'\0';
    Parameter::symbol=symbol.c_str()+'\0';
    Parameter::ranges=ranges;
    Parameter::unit=unit.c_str()+'\0';
}

ParameterWithRef::~ParameterWithRef()
{
//    if(mCallback)
//        delete mCallback;
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
