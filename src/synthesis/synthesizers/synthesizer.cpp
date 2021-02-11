#include "synthesizer.h"
#include <limits>
#include <algorithm>

#include "../sound_sources/max_sound_souce.h"

namespace BOSSCorp::Synthesis::Synthesizers
{
Synthesizer::Synthesizer(int maxPolyphony)
    : _soundSources()
    , _adsrConfig()
    , _pwmConfig()
    , _sawtoothConfig()
    , _reverseSawtoothConfig()
    , _triangleConfig()
    , _sineConfig()
    , _noiseConfig()
    , _maxPolyphony(maxPolyphony)
{
    for(int i=0; i< maxPolyphony; i++)
    {
        _soundSources.emplace_back(nullptr);
    }

    reset();
}
Synthesizer::~Synthesizer()
{
    for(int i = 0; i < _maxPolyphony; i++)
    {
        _soundSources[i] != nullptr;
        delete _soundSources[i];
        _soundSources[i] = nullptr;
    }
}

void Synthesizer::reset()
{
    allNotesOff();

    // TODO: make proper default variables
    _adsrConfig.attack  = 0;
    _adsrConfig.decay   = 0;
    _adsrConfig.sustain = 0.8;
    _adsrConfig.release = 0;

    _sineConfig.amplitude = 0.5;
    _sineConfig.pitchBend = 0;

    _sawtoothConfig.amplitude = 0;
    _sawtoothConfig.pitchBend = 0;

    _reverseSawtoothConfig.amplitude = 0;
    _reverseSawtoothConfig.pitchBend = 0;

    _triangleConfig.amplitude = 0;
    _triangleConfig.pitchBend = 0;

    _pwmConfig.amplitude = 0.0;
    _pwmConfig.dutyCycle = 0.5;
    _pwmConfig.pitchBend = 0;

    _noiseConfig.amplitude = 0;
    _noiseConfig.pitchBend = 0;
}



void Synthesizer::cleanOldSources()
{
    for(int i = 0; i < _maxPolyphony; i++)
    {
        auto* source = _soundSources[i];
        if(source == nullptr) continue;
        if(source->finished())
        {
            delete source;
            _soundSources[i] = nullptr;
        }
    }
}

void Synthesizer::process(Buffer& buffer)
{
    cleanOldSources();


    float deltatime = 1.0 / buffer.sampleRate();
    int numSamples = buffer.size();

    int16_t* data = buffer.data();

    int mindata = std::numeric_limits<int16_t>::min();
    int maxdata = std::numeric_limits<int16_t>::max();
    int deltaSize = maxdata - mindata;

    for(int i = 0; i < numSamples; i++)
    {
        data[i] = mindata + (deltaSize * next(deltatime));
    }
}

float Synthesizer::next(float deltaT)
{
    int polyphony = 0;
    float output = 0;
    for(auto* source : _soundSources)
    {
        if(source == nullptr) continue;
        output += source->next(deltaT);
        polyphony++;
    }

    if(polyphony == 0) return 0.0;
    return output / polyphony;
}

    // velocity 0 = silence, 1 = bottom out.
void Synthesizer::noteOn(Midi::Note note, int8_t octave, float velocity) 
{
    int addIndex = -1;
    for(int i = 0; i < _maxPolyphony; i++)
    {
        if(_soundSources[i] == nullptr)
        {
            addIndex = i;
            continue;
        }

        if(_soundSources[i]->note() == note && _soundSources[i]->octave() == octave)
        {
            return;
        }
    }

    if(addIndex > -1)
    {
        auto* source = new SoundSources::MaxSoundSource(_adsrConfig, _pwmConfig, _sawtoothConfig, _reverseSawtoothConfig, _triangleConfig, _sineConfig, _noiseConfig);
        source->configure(note, octave, velocity);
        _soundSources[addIndex] = source;
    }    
}

void Synthesizer::noteOff(Midi::Note note, int8_t octave, float velocity) 
{
    for(int i = 0; i < _maxPolyphony; i++)
    {
        auto* source = _soundSources[i];

        if(source != nullptr && source->note() == note && source->octave() == octave)
        {
            source->finished();
            return;
        }
    }
}

void Synthesizer::attack(float value)
{
    _adsrConfig.attack = MaxAttackSeconds * value;
}

void Synthesizer::decay(float value)
{
    _adsrConfig.decay = MaxDecaySeconds * value;
}

void Synthesizer::sustain(float value)
{
    _adsrConfig.sustain = value;
}

void Synthesizer::release(float value)
{
    _adsrConfig.release = MaxReleaseSeconds * value;
}



} // end BOSSCorp::Synthesis::Synthesizers



















