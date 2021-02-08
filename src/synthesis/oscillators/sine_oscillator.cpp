#include "sine_oscillator.h"
#include <math.h>
namespace BOSSCorp::Synthesis::Oscillators
{

float SineOscillator::next()
{
    constexpr float pi2 = M_PI * 2;

    return sin(pi2 * frequency() * time()) * 0.5; // amplitude range from -0.5 to +0.5
}


} // end BOSSCorp::Synthesis::Oscillators