#ifndef GUITARSYNTHDSPPLUGIN_H
#define GUITARSYNTHDSPPLUGIN_H
#include <DistrhoPlugin.hpp>
using namespace DISTRHO;
class GuitarSynthDSPPlugin: public Plugin
{
public:
    GuitarSynthDSPPlugin();
    // -------------------------------------------------------------------
    // Information

    const char* getLabel() const noexcept override
    {
        return "3BandEQ";
    }

    const char* getMaker() const noexcept override
    {
        return "DISTRHO";
    }

    const char* getLicense() const noexcept override
    {
        return "LGPL";
    }

    uint32_t getVersion() const noexcept override
    {
        return 0x1000;
    }

    int64_t getUniqueId() const noexcept override
    {
        return d_cconst('D', '3', 'E', 'Q');
    }

    // -------------------------------------------------------------------
    // Init

    void initParameter(uint32_t index, Parameter& parameter) override;
//    void initProgramName(uint32_t index, String& programName) override;

    // -------------------------------------------------------------------
    // Internal data

    float getParameterValue(uint32_t index) const override;
    void  setParameterValue(uint32_t index, float value) override;
//    void  loadProgram(uint32_t index) override;

    // -------------------------------------------------------------------
    // Process

    void activate() override;
    void deactivate() override;
    void run(const float** inputs, float** outputs, uint32_t frames) override;

    // -------------------------------------------------------------------
};

#endif // GUITARSYNTHDSPPLUGIN_H
