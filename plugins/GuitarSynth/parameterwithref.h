#ifndef PARAMETERWITHREF_H
#define PARAMETERWITHREF_H
#include <DistrhoPlugin.hpp>
using namespace DISTRHO;
class ParameterWithRef: public Parameter
{
private:
    float& mParameter;
protected:
    virtual void preChange();
    virtual void postChange();
public:
    ParameterWithRef(float& par,uint32_t hints,String name,String symbol,String unit, ParameterRanges ranges);
    void setParameter(float val);
    float getParameter();
};

#endif // PARAMETERWITHREF_H
