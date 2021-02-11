#pragma once
#include "ioscillator.h"
#include "configurations/sine_configuration.h"
namespace BOSSCorp::Synthesis::Oscillators
{

class SineOscillator : public IOscillator
{
private:
    const Configurations::SineConfiguration& config() const { return static_cast<const Configurations::SineConfiguration&>(_configuration); }
protected:
    virtual float next();

public:
    SineOscillator(const Configurations::SineConfiguration& configuration) : IOscillator::IOscillator(configuration) {}
};

} // end BOSSCorp::Synthesis::Oscillators