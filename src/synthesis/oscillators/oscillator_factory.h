#pragma once
#include "ioscillator.h"
#include "pwm_configuration.h"

#include <stdint.h>

namespace BOSSCorp::Synthesis::Oscillators
{

enum class Waveform : uint32_t
{
    Sine,
    Noise,
    Triangle,
    PWM,
    SawTooth,
    ReverseSawTooth,
};

class OscillatorFactory
{
private:
    Waveform _waveform;
    PWMConfiguration _pwmConfiguration;

    IOscillator getOscillator();
    IOscillator getOscillator(float frequency, float amplitude, float phaseShift);
};

} // end BOSSCorp::Synthesis::Oscillators