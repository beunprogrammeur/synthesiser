#include <gtest/gtest.h>
#include "synthesis/oscillators/sine_oscillator.h"
#include "fft.h"

TEST(SineOscillatorTests, PLOT)
{
    BOSSCorp::Synthesis::Oscillators::SineOscillator oscillator;
    autoplot("sine", oscillator);
}

TEST(SineOscillatorTests, ConfirmFrequency)
{
    BOSSCorp::Synthesis::Oscillators::SineOscillator oscillator;
    int frequencies[] {20, 440, 3000};
    int size = sizeof(frequencies) / sizeof(frequencies[0]);

    doGlobalFrequencyTest(oscillator, frequencies, size, 5);
}