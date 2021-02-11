#include "max_sound_souce.h"

namespace BOSSCorp::Synthesis::SoundSources
{

MaxSoundSource::MaxSoundSource(Envelopes::ADSRConfiguration& adsrConfig, 
    const Oscillators::Configurations::PWMConfiguration& pwmConfig,
    const Oscillators::Configurations::SawtoothConfiguration& sawtoothConfig,
    const Oscillators::Configurations::ReverseSawoothConfiguration& rsawtoothConfig,
    const Oscillators::Configurations::TriangleConfiguration& triangleConfig,
    const Oscillators::Configurations::SineConfiguration& sineConfig,
    const Oscillators::Configurations::NoiseConfiguration& noiseConfig)
        : _envelope(adsrConfig),
        _pwmOscillator(pwmConfig),
        _sawtoothOscillator(sawtoothConfig),
        _revereSawtoothOscillator(rsawtoothConfig),
        _triangleOscillator(triangleConfig),
        _sineOscillator(sineConfig),
        _noiseOscillator(noiseConfig),
        PolySoundSource(_envelope)
    {
        add(_pwmOscillator);
        add(_sawtoothOscillator);
        add(_revereSawtoothOscillator);
        add(_triangleOscillator);
        add(_sineOscillator);
        add(_noiseOscillator);
    }


} // end BOSSCorp::Synthesis::SoundSources