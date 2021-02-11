#include "sawtooth_oscillator.h"
#include <cmath>
namespace BOSSCorp::Synthesis::Oscillators
{

float SawToothOscillator::next()
{
    auto t = time();
    float duration = (1.0 / frequency());
    float remainder= fmod(t, duration);
    return (config().amplitude / duration * remainder) - (config().amplitude / 2);
}

} // end BOSSCorp::Synthesis::Oscillators
