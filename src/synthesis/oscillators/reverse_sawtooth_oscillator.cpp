#include "reverse_sawtooth_oscillator.h"
#include <cmath>

namespace BOSSCorp::Synthesis::Oscillators
{

float ReverseSawToothOscillator::next()
{
    auto t = time();
    float wt = wavetime();

    if(t > wt)
    {
        t -= wt;
        time(t);
    }

    float a = amplitude();
    
    return -((a / wt * t) * 2.0f - a);
}

} // end BOSSCorp::Synthesis::Oscillators
