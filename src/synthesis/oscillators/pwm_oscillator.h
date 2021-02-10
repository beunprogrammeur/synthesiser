#pragma once
#include "ioscillator.h"
#include "configurations/pwm_configuration.h"
namespace BOSSCorp::Synthesis::Oscillators
{

class PWMOscillator : public IOscillator
{
protected:
    virtual float next();
    const Configurations::PWMConfiguration& config() const { return reinterpret_cast<const Configurations::PWMConfiguration&>(_configuration); }
public:
    PWMOscillator(const Configurations::PWMConfiguration& oscConfiguration); 
};


} // end BOSSCorp::Synthesis
