#ifndef PARAMETERWITHREF_H
#define PARAMETERWITHREF_H
#include <parameterfunctioncallback.h>
#include <DistrhoPlugin.hpp>
#include <string>
using namespace std;
using namespace DISTRHO;
class ParameterWithRef: public Parameter
{
private:
    float& mParameter;
    ParameterFunctionCallback& mCallback;
public:
    ParameterWithRef(float& par,uint32_t hints,string name,string symbol,string unit, ParameterRanges ranges,ParameterFunctionCallback action=ParameterFunctionCallback());
    void setParameter(float val);
    float getParameter();
};

#endif // PARAMETERWITHREF_H
