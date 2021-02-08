#include "pwm_oscillator.h"
#include <cmath>
namespace BOSSCorp::Synthesis::Oscillators
{

PWMOscillator::PWMOscillator(const PWMConfiguration& pwmConfiguration)
    : _configuration(pwmConfiguration)
{
}

float PWMOscillator::next()
{
    float wavetime = 1.0 / frequency();
    float output = 0.5;

    if(fmod(time(), wavetime) > _configuration.dutyCycle * wavetime)
    {
        output = -output;
    }

    return output;
}

} // end namespace BOSSCorp::Synthesis::Oscillators