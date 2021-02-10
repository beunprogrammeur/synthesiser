#pragma once

#include "../isteppable.h"
#include "configurations/ioscillator_configuration.h"

namespace BOSSCorp::Synthesis::Oscillators
{

class IOscillator : public ISteppable
{
private:
    float _frequency = 0;
    float _amplitude = 0;
    float _shiftTime = 0;
protected:
    const Configurations::IOscillatorConfiguration& _configuration;

public:
    IOscillator(const Configurations::IOscillatorConfiguration& configuration) : _configuration(configuration) { }
    virtual void configure(float frequency, float amplitude = 1, float phaseShift = 0) { _frequency = frequency; _amplitude = amplitude, _shiftTime = (1.0 / frequency * phaseShift); }
    virtual void reset()    { setTime(_shiftTime); }
    float frequency() const { return _frequency; }
};

}