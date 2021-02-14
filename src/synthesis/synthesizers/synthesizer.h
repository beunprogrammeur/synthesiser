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
protected:
    std::vector<SoundSources::ISoundSource*> _soundSources { };
    
    Envelopes::ADSRConfiguration                             _adsrConfig;

    Oscillators::Configurations::PWMConfiguration            _pwmConfig;
    Oscillators::Configurations::SawtoothConfiguration       _sawtoothConfig;
    Oscillators::Configurations::ReverseSawoothConfiguration _reverseSawtoothConfig;
    Oscillators::Configurations::TriangleConfiguration       _triangleConfig;
    Oscillators::Configurations::SineConfiguration           _sineConfig;
    Oscillators::Configurations::NoiseConfiguration          _noiseConfig;    

    float _volume=0;

    const int _maxPolyphony;

    void cleanOldSources();

    float next(float deltaT);

    virtual SoundSources::ISoundSource* getNewSoundSource();
public:
    const int MaxAttackSeconds  = 3;
    const int MaxDecaySeconds   = 3;
    const int MaxReleaseSeconds = 3;

    Synthesizer(int maxPolyphony);
    ~Synthesizer();
    virtual void process(Buffer& buffer);

    virtual void init();
    // velocity 0 = silence, 1 = bottom out.
    virtual void noteOn(Midi::Note note, int8_t octave, float velocity);
    virtual void noteOff(Midi::Note note, int8_t octave, float velocity);
    virtual void attack(float value);
    virtual void decay(float value);
    virtual void sustain(float value);
    virtual void release(float value);

    virtual float volume() { return _volume;             }
    virtual void  volume(float value) { _volume = value; }

    virtual void reset();

    virtual void allNotesOff();

    // 1 is the next note, -1 the previous note.
    virtual void pitchBend(float value);

    // 0 = clean, 1 = full application
    virtual void effect1(float value);
    virtual void effect2(float value);

    // 0 = no filter, 1 = max filter
    virtual void lowPassFilter(float value);
    virtual void highPassFilter(float value);

    virtual void monoMode();
    virtual void polyMode();


    virtual void pwmOscillatorVolume(float volume)             { _pwmConfig.amplitude = volume;             }
    virtual void pwmOscillatorDutyCycle(float dutyCycle)       { _pwmConfig.dutyCycle = dutyCycle;          }
    virtual void sineOscillatorVolume(float volume)            { _sineConfig.amplitude = volume;            }
    virtual void sawtoothOscillatorVolume(float volume)        { _sawtoothConfig.amplitude = volume;        }
    virtual void reverseSawtoothOscillatorVolume(float volume) { _reverseSawtoothConfig.amplitude = volume; }
    virtual void triangleOscillatorVolume(float volume)        { _triangleConfig.amplitude = volume;        }
    virtual void noiseOscillatorVolume(float volume)           { _noiseConfig.amplitude = volume;           }
};

}// end BOSSCorp::Synthesis::Synthesizers
