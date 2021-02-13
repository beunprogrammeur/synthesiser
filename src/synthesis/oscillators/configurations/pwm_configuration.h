#pragma once
#include "ioscillator_configuration.h"

namespace BOSSCorp::Synthesis::Oscillators::Configurations
{

struct PWMConfiguration : IOscillatorConfiguration
{
    float dutyCycle = 0.5f;
};

} // end BOSSCorp::Synthesis::Oscillators::Configurations