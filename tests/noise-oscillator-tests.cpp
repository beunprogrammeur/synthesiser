#include <gtest/gtest.h>
#include "synthesis/oscillators/noise_oscillator.h"

#include "fft.h"

TEST(SawtoothOscillatorTests, PLOT)
{
    BOSSCorp::Synthesis::Oscillators::NoiseOscillator oscillator;
    autoplot("noise", oscillator);    
}