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

    return output * _envelope.next(delta);
}

void PolySoundSource::configure(Midi::Note note, int8_t octave, float amplitude)
{
    ISoundSource::configure(note, octave, amplitude);

    for(auto* oscillator : _oscillators)
    {
        oscillator->configure(note, octave, amplitude);
    }
}

} // end BOSSCorp::Synthesis::SoundSources