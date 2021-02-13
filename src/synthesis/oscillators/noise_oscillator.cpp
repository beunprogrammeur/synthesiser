#include "noise_oscillator.h"
#include <random>
namespace BOSSCorp::Synthesis::Oscillators
{
float NoiseOscillator::next()
{
    float  a = amplitude();
    float  r = ((float) std::rand() / RAND_MAX) * 2.0f - 1.0f;
    return a * r;
}
} // end BOSSCorp::Synthesis::Oscillators
