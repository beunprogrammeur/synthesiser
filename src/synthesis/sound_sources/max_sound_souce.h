#pragma once
#include "poly_sound_source.h"
#include "../envelopes/adsr_configuration.h"
#include "../oscillators/oscillator_configuration.h"
#include "../oscillators/pwm_configuration.h"
#include "../oscillators/sine_oscillator.h"
#include "../oscillators/sawtooth_oscillator.h"
#include "../oscillators/reverse_sawtooth_oscillator.h"
#include "../oscillators/triangle_oscillator.h"
#include "../oscillators/pwm_oscillator.h"
#include "../oscillators/noise_oscillator.h"
namespace BOSSCorp::Synthesis::SoundSources
{

class MaxSoundSource : public PolySoundSource
{
private:
    
public:
    MaxSoundSource(Envelopes::ADSRConfiguration& adsrConfig, const Oscillators::OscillatorConfiguration& oscConfig, const Oscillators::PWMConfiguration& pwmConfig);
    
};

} // end BOSSCorp::Synthesis::SoundSources