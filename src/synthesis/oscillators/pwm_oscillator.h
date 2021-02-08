#pragma once
#include "ioscillator.h"
#include "pwm_configuration.h"
namespace BOSSCorp::Synthesis::Oscillators
{

class PWMOscillator : public IOscillator
{
private:
    const PWMConfiguration& _configuration;
protected:
    virtual float next();
public:
    explicit PWMOscillator(const PWMConfiguration& pwmConfiguration);    
};


} // end BOSSCorp::Synthesis
