#include "sawtooth_oscillator.h"
#include <cmath>
namespace BOSSCorp::Synthesis::Oscillators
{

float SawToothOscillator::next()
{
    auto t = time();
    // TODO: apply phase shift in IOscillator automatically (in time()?)
    float duration = (1.0 / _frequency);
    float remainder= fmod(t, duration);
    return (1.0 / duration * remainder) -0.5;
}

} // end BOSSCorp::Synthesis::Oscillators
