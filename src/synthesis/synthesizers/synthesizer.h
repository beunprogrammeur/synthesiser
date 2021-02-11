#pragma once
#include "isynthesizer.h"
#include "../sound_sources/isound_source.h"
#include <vector>

#include "../envelopes/adsr_configuration.h"
#include "../oscillators/configurations/configurations.h"

namespace BOSSCorp::Synthesis::Synthesizers
{

class Synthesizer : public ISynthesizer
{
private:
    std::vector<SoundSources::ISoundSource*> _soundSources {};
    
    Envelopes::ADSRConfiguration                             _adsrConfig;

    Oscillators::Configurations::PWMConfiguration            _pwmConfig;
    Oscillators::Configurations::SawtoothConfiguration       _sawtoothConfig;
    Oscillators::Configurations::ReverseSawoothConfiguration _reverseSawtoothConfig;
    Oscillators::Configurations::TriangleConfiguration       _triangleConfig;
    Oscillators::Configurations::SineConfiguration           _sineConfig;
    Oscillators::Configurations::NoiseConfiguration          _noiseConfig;    

    const int _maxPolyphony;

    void cleanOldSources();

    float next(float deltaT);
public:
    const int MaxAttackSeconds  = 3;
    const int MaxDecaySeconds   = 3;
    const int MaxReleaseSeconds = 3;

    Synthesizer(int maxPolyphony);
    ~Synthesizer();
    virtual void process(Buffer& buffer);


    // velocity 0 = silence, 1 = bottom out.
    virtual void noteOn(Midi::Note note, int8_t octave, float velocity);
    virtual void noteOff(Midi::Note note, int8_t octave, float velocity);
    virtual void attack(float value);
    virtual void decay(float value);
    virtual void sustain(float value);
    virtual void release(float value);

    virtual void reset();
};

} // end BOSSCorp::Synthesis::Synthesizers