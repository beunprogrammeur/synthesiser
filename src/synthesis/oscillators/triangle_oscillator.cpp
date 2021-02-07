#include "triangle_oscillator.h"
#include <cmath>
namespace BOSSCorp::Synthesis::Oscillators
{

float TriangleOscillator::next()
{
    float value = SawToothOscillator::next();
    
    if(std::abs(value - previous) > 0.5)
    {
        polarity = -polarity;
    }    

    previous = value;
    return value * polarity;
}

void TriangleOscillator::configure(float frequency, float amplitude, float phaseShift)
{
    // doubling the frequency here is needed because next() halves the frequency as a sideeffect of using SawToothOscillator's next()
    IOscillator::configure(frequency*2.0, amplitude, phaseShift);
}

} // end BOSSCorp::Synthesis::Oscillators
