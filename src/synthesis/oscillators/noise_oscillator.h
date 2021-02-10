#pragma once
#include "ioscillator.h"
#include "configurations/noise_configuration.h"
namespace BOSSCorp::Synthesis::Oscillators
{

class NoiseOscillator : public IOscillator
{
protected:
    virtual float next();
public:
    NoiseOscillator(const Configurations::NoiseConfiguration& config) : IOscillator(config) { }
};

} // end BOSSCorp::Synthesis::Oscillators