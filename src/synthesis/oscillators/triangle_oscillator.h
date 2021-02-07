#pragma once
#include "sawtooth_oscillator.h"

namespace BOSSCorp::Synthesis::Oscillators
{

class TriangleOscillator : public SawToothOscillator
{
private:
    float polarity = 1;
    float previous = 0;
protected:
    virtual float next();
    virtual void configure(float frequency, float amplitude = 1, float phaseShift = 0);
};

} // end BOSSCorp::Synthesis::Oscillators