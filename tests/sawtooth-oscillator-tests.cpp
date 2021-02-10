#include<gtest/gtest.h>

#include "synthesis/oscillators/sawtooth_oscillator.h"
#include "fft.h"

TEST(SawtoothOscillatorTests, PLOT)
{
    using namespace BOSSCorp::Synthesis::Oscillators;
    Configurations::SawtoothConfiguration config;
    SawToothOscillator oscillator(config);
    autoplot("sawtooth", oscillator);
}

TEST(SawtoothOscillatorTests, ConfirmFrequency)
{
    using namespace BOSSCorp::Synthesis::Oscillators;
    Configurations::SawtoothConfiguration config;
    SawToothOscillator oscillator(config);

    int frequencies[] {20, 440, 3000};
    int size = sizeof(frequencies) / sizeof(frequencies[0]);

    doGlobalFrequencyTest(oscillator, frequencies, size, 5);
}