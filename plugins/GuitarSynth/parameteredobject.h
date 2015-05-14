#ifndef PARAMETEREDOBJECT_H
#define PARAMETEREDOBJECT_H

#include <parameterwithref.h>
#include <vector>
using namespace std;

class ParameteredObject
{
private:
    vector<ParameterWithRef> mParameters;
protected:
    string mName;
    string mShortName;
    string mType;
public:
    ParameteredObject(string name, string shortname, string type);
    void addParameter(ParameterWithRef parameter);
    void addParameter(float& par,uint32_t hints,string name,string symbol,string unit, ParameterRanges ranges,ParameterFunctionCallback actio=ParameterFunctionCallback());
    vector<ParameterWithRef> getParameters();
};

#endif // PARAMETEREDOBJECT_H
