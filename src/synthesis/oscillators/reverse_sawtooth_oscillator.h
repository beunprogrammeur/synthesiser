#pragma once
#include "sawtooth_oscillator.h"

namespace BOSSCorp::Synthesis::Oscillators
{

class ReverseSawToothOscillator : public SawToothOscillator
{
protected:
    virtual float next();
};

} // end BOSSCorp::Synthesis::Oscillators