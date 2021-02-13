#include "triangle_oscillator.h"
#include <cmath>
namespace BOSSCorp::Synthesis::Oscillators
{

float TriangleOscillator::next()
{
    float t  = time();
    float wt = wavetime();

    if(t > wt)
    {
        t -= wt;
        time(t);
    }

    float a = amplitude();

    float step = a / wt * t * 2.0f -a;

    if(std::abs(step - previous) > 0.5f * a) polarity = -polarity;
    previous = step;

    return step * polarity;
}

void TriangleOscillator::configure(float frequency, float amplitude, float phaseShift)
{
    // doubling the frequency here is needed because next() halves the frequency as a sideeffect of using SawToothOscillator's next()
    IOscillator::configure(frequency * 2, amplitude, phaseShift);
}

} // end BOSSCorp::Synthesis::Oscillators
