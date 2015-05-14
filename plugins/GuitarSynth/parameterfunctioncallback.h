#ifndef PARAMETERFUNCTIONCALLBACK_H
#define PARAMETERFUNCTIONCALLBACK_H
class ParameteredObject;
class ParameterFunctionCallback
{
    friend class ParameterWithRef;
protected:
    ParameteredObject* mObject;
    virtual void preChange()
    {

    };
    virtual void postChange()
    {
    };
public:
    ParameterFunctionCallback(ParameteredObject* object=0)
    {
        mObject=object;
    };


};

#endif // PARAMETERFUNCTIONCALLBACK_H
