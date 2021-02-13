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
}

Synthesizer::~Synthesizer()
{
    for(auto* source : _soundSources)
    {
    	delete source;
    }
    _soundSources.clear();
}

void Synthesizer::init()
{
    for(int i=0; i< _maxPolyphony; i++)
    {
        _soundSources.emplace_back(getNewSoundSource());
    }

    reset();
}

void Synthesizer::allNotesOff()
{
	for(auto* source : _soundSources)
	{
		source->reset();
		source->ignore(true);
	}
}

void Synthesizer::reset()
{
    allNotesOff();

    _volume = 0.25f;

    _adsrConfig.attack  = 0.5;
    _adsrConfig.decay   = 0.3;
    _adsrConfig.sustain = 0.8;
    _adsrConfig.release = 2;

    _sineConfig.amplitude = 0.5;
    _sineConfig.pitchBend = 0;

    _sawtoothConfig.amplitude = 1.0;
    _sawtoothConfig.pitchBend = 0;

    _reverseSawtoothConfig.amplitude = 0;
    _reverseSawtoothConfig.pitchBend = 0;

    _triangleConfig.amplitude = 0;
    _triangleConfig.pitchBend = 0;

    _pwmConfig.amplitude = 0.5;
    _pwmConfig.dutyCycle = 0.5;
    _pwmConfig.pitchBend = 0;

    _noiseConfig.amplitude = 0;
    _noiseConfig.pitchBend = 0;
}

void Synthesizer::cleanOldSources()
{
	for(auto* source : _soundSources)
	{
		if(source->finished())
		{
			source->ignore(true);
		}
	}
}

void Synthesizer::process(Buffer& buffer)
{
    cleanOldSources();


    float deltatime = 1.0f / buffer.sampleRate();
    int numSamples = buffer.size();

    int16_t* data = buffer.data();

    int maxdata = std::numeric_limits<int16_t>::max();

    for(int i = 0; i < numSamples; i++)
    {
        data[i] = next(deltatime) * maxdata * 2.0f * _volume;
    }
}

float Synthesizer::next(float deltaT)
{
    float output  = 0.0f;
    for(auto* source : _soundSources)
    {
        if(!source->ignore())
        {
        	output += source->next(deltaT);
        }
    }

    return output;
}

    // velocity 0 = silence, 1 = bottom out.
void Synthesizer::noteOn(Midi::Note note, int8_t octave, float velocity) 
{
	for(auto* source : _soundSources)
	{
		if(!source->ignore() && source->note() == note && source->octave() == octave)
		{
			return; // somehow, this note is already pressed.
		}
	}

	for(auto* source : _soundSources)
	{
		if(source->ignore())
		{
			source->reset();
			source->configure(note, octave, velocity);
			return;
		}
	}
}

SoundSources::ISoundSource* Synthesizer::getNewSoundSource()
{
	return new SoundSources::MaxSoundSource(_adsrConfig, _pwmConfig, _sawtoothConfig, _reverseSawtoothConfig, _triangleConfig, _sineConfig, _noiseConfig);
}

void Synthesizer::noteOff(Midi::Note note, int8_t octave, float velocity) 
{
	for(auto* source : _soundSources)
	{
		if(source->note() == note && source->octave() == octave)
		{
			source->release();
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



















