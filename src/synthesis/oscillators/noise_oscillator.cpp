#include "noise_oscillator.h"
#include <random>
namespace BOSSCorp::Synthesis::Oscillators
{
float NoiseOscillator::next()
{
    constexpr float max =  0.5;
    constexpr float min = -0.5;

    return ((float(std::rand()) / float(RAND_MAX)) * (max - min)) + min;
}
} // end BOSSCorp::Synthesis::Oscillators
