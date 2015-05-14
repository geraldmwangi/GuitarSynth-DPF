#include "parameteredobject.h"

ParameteredObject::ParameteredObject(string name, string shortname, string type)
{
    mName=name;
    mType=type;
    mShortName=shortname;
}

void ParameteredObject::addParameter(ParameterWithRef parameter)
{
    mParameters.push_back(parameter);
}

void ParameteredObject::addParameter(float &par, uint32_t hints, string name, string symbol, string unit, ParameterRanges ranges, ParameterFunctionCallback action)
{
    addParameter(ParameterWithRef(par,hints,name,symbol,unit,ranges,action));
}

vector<ParameterWithRef> ParameteredObject::getParameters()
{
    return mParameters;
}
