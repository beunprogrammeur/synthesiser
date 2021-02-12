#include "poly_sound_source.h"

namespace BOSSCorp::Synthesis::SoundSources
{

float PolySoundSource::next()
{
    float delta = deltaTime();
    float output = 0;
    for(auto* oscillator : _oscillators)
    {
        output += oscillator->next(delta);
    }

    output /= _oscillators.size();

    return output * _envelope.next(delta);
}

void PolySoundSource::configure(Midi::Note note, int8_t octave, float amplitude)
{
    ISoundSource::configure(note, octave, amplitude);

    float frequency = Midi::Converter::toFrequency(note, octave);

    for(auto* oscillator : _oscillators)
    {
        oscillator->configure(frequency, amplitude);
    }
}

} // end BOSSCorp::Synthesis::SoundSources