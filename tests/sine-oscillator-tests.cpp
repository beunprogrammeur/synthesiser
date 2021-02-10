#include <gtest/gtest.h>
#include "synthesis/oscillators/sine_oscillator.h"
#include "fft.h"

TEST(SineOscillatorTests, PLOT)
{
    using namespace BOSSCorp::Synthesis::Oscillators;
    Configurations::SineConfiguration config;
    SineOscillator oscillator(config);
    autoplot("sine", oscillator);
}

TEST(SineOscillatorTests, ConfirmFrequency)
{
    using namespace BOSSCorp::Synthesis::Oscillators;
    Configurations::SineConfiguration config;
    SineOscillator oscillator(config);

    int frequencies[] {20, 440, 3000};
    int size = sizeof(frequencies) / sizeof(frequencies[0]);

    doGlobalFrequencyTest(oscillator, frequencies, size, 5);
}