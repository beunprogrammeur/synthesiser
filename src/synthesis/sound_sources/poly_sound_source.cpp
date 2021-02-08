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

} // end BOSSCorp::Synthesis::SoundSources