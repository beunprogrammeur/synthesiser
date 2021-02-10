#pragma once
#include "ioscillator.h"
#include "configurations/sine_configuration.h"
namespace BOSSCorp::Synthesis::Oscillators
{

class SineOscillator : public IOscillator
{
protected:
    virtual float next();

public:
    SineOscillator(const Configurations::SineConfiguration& configuration) : IOscillator::IOscillator(configuration) {}
};

} // end BOSSCorp::Synthesis::Oscillators