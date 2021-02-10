#include <gtest/gtest.h>
#include "synthesis/oscillators/noise_oscillator.h"

#include "fft.h"

TEST(SawtoothOscillatorTests, PLOT)
{
    using namespace BOSSCorp::Synthesis::Oscillators;
    Configurations::NoiseConfiguration config;
    NoiseOscillator oscillator(config);
    autoplot("noise", oscillator);    
}