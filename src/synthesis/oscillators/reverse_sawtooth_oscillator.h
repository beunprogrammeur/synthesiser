#pragma once
#include "sawtooth_oscillator.h"
#include "configurations/reverse_sawtooth_configuration.h"
namespace BOSSCorp::Synthesis::Oscillators
{

class ReverseSawToothOscillator : public SawToothOscillator
{
protected:
    virtual float next();
public:
    ReverseSawToothOscillator(const Configurations::ReverseSawoothConfiguration& config) : SawToothOscillator::SawToothOscillator(config) { }
};

} // end BOSSCorp::Synthesis::Oscillators