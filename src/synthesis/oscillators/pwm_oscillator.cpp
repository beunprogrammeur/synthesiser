#include "pwm_oscillator.h"
#include <cmath>
namespace BOSSCorp::Synthesis::Oscillators
{

PWMOscillator::PWMOscillator(const Configurations::PWMConfiguration& config)
    : IOscillator::IOscillator(config)
{
}

float PWMOscillator::next()
{
    float t  = time();
    float wt = wavetime();
    float highTime = wt * config().dutyCycle;

    if(t > wt)
    {
        t -= wt;
        time(t);
    }

    float a = amplitude(); // a wave of a(1) would be -0.5 to 0.5

    if(t > highTime) return -a;
    else             return  a;
}

} // end namespace BOSSCorp::Synthesis::Oscillators