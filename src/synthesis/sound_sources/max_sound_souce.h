#pragma once
#include "poly_sound_source.h"
#include "../envelopes/adsr_envelope.h"
#include "../oscillators/configurations/configurations.h"
#include "../oscillators/oscillators.h"

namespace BOSSCorp::Synthesis::SoundSources
{

class MaxSoundSource : public PolySoundSource
{
private:
    Envelopes::ADSREnvelope                _envelope;

    Oscillators::PWMOscillator             _pwmOscillator;
    Oscillators::SawToothOscillator        _sawtoothOscillator;
    Oscillators::ReverseSawToothOscillator _revereSawtoothOscillator;
    Oscillators::TriangleOscillator        _triangleOscillator;
    Oscillators::SineOscillator            _sineOscillator;
    Oscillators::NoiseOscillator           _noiseOscillator;
public:
    MaxSoundSource(Envelopes::ADSRConfiguration& adsrConfig, 
        const Oscillators::Configurations::PWMConfiguration& pwmConfig,
        const Oscillators::Configurations::SawtoothConfiguration& sawtoothConfig,
        const Oscillators::Configurations::ReverseSawoothConfiguration& rsawtoothConfig,
        const Oscillators::Configurations::TriangleConfiguration& triangleConfig,
        const Oscillators::Configurations::SineConfiguration& sineConfig,
        const Oscillators::Configurations::NoiseConfiguration& noiseConfig);
    void release() { _envelope.release(); }
    
};

} // end BOSSCorp::Synthesis::SoundSources