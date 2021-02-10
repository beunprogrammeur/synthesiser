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
    float wavetime = 1.0 / frequency();
    float output = 0.5;

    if(fmod(time(), wavetime) > config().dutyCycle * wavetime)
    {
        output = -output;
    }

    return output;
}

} // end namespace BOSSCorp::Synthesis::Oscillators