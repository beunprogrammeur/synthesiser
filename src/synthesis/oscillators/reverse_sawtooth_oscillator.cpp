#include "reverse_sawtooth_oscillator.h"
namespace BOSSCorp::Synthesis::Oscillators
{

float ReverseSawToothOscillator::next()
{
    return -SawToothOscillator::next();
}

} // end BOSSCorp::Synthesis::Oscillators
