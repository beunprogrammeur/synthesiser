#pragma once
#include "ioscillator.h"
#include "configurations/sawtooth_configuration.h"
namespace BOSSCorp::Synthesis::Oscillators
{

class SawToothOscillator : public IOscillator
{
protected:
    virtual float next();

    // for derived types like reverse sawtooth
    SawToothOscillator(const Configurations::IOscillatorConfiguration& config) : IOscillator(config) {}
public:
    SawToothOscillator(const Configurations::SawtoothConfiguration& config) : IOscillator::IOscillator(config) { }
};

} // end BOSSCorp::Synthesis::Oscillators