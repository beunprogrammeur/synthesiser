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
    float _waveTime  = 0;
protected:
    const Configurations::IOscillatorConfiguration& _configuration;
    void wavetime(float value) { _waveTime = value; } // is reset when configure is called
public:
    IOscillator(const Configurations::IOscillatorConfiguration& configuration) : _configuration(configuration) { }
    virtual void configure(float frequency, float amplitude = 1, float phaseShift = 0) { _frequency = frequency; _amplitude = amplitude; _waveTime = 1.0f / frequency; _shiftTime = (_waveTime * phaseShift); }
    virtual void reset()    { time(_shiftTime); ISteppable::reset(); }
    float frequency() const { return _frequency; }
    float amplitude() const { return _amplitude * _configuration.amplitude; }
    float wavetime()  const { return _waveTime;  }
};

}
