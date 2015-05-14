#ifndef GUITARSYNTHDSPPLUGIN_H
#define GUITARSYNTHDSPPLUGIN_H

#include <gsengine.h>
using namespace DISTRHO;
class GuitarSynthDSPPlugin: public Plugin
{
public:
    GuitarSynthDSPPlugin();
    ~GuitarSynthDSPPlugin();
    // -------------------------------------------------------------------
    // Information

    const char* getLabel() const noexcept override
    {
        return "GuitarSynth";
    }

    const char* getMaker() const noexcept override
    {
        return "Gerald Mwangi";
    }

    const char* getLicense() const noexcept override
    {
        return "GPL";
    }

    uint32_t getVersion() const noexcept override
    {
        return 0x1000;
    }

    int64_t getUniqueId() const noexcept override
    {
        return d_cconst('G', 'S', 'G', 'M');
    }

    // -------------------------------------------------------------------
    // Init

    void initParameter(uint32_t index, Parameter& parameter) override;
//    void initProgramName(uint32_t index, string& programName) override;

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
private:
    GSEngine* mInstance;

    // -------------------------------------------------------------------
};

#endif // GUITARSYNTHDSPPLUGIN_H
