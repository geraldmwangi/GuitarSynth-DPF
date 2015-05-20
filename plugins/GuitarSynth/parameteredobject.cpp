#include "parameteredobject.h"

ParameteredObject::ParameteredObject(string name, string shortname, string type)
{
    mName=name;
    mType=type;
    mShortName=shortname;
}

ParameteredObject::~ParameteredObject()
{
    for(int p=0;p<mParameters.size();p++)
        delete mParameters[p];
}

void ParameteredObject::addParameter(ParameterWithRef* parameter)
{
    mParameters.push_back(parameter);
}

void ParameteredObject::addParameter(float &par, uint32_t hints, string name, string symbol, string unit, ParameterRanges ranges)
{
    addParameter(new ParameterWithRef(par,hints,name,symbol,unit,ranges));
}

vector<ParameterWithRef *> ParameteredObject::getParameters()
{
    return mParameters;
}
