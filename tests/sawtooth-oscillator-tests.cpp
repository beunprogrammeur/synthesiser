#include<gtest/gtest.h>

#include "synthesis/oscillators/sawtooth_oscillator.h"
#include "fft.h"

TEST(SawtoothOscillatorTests, PLOT)
{
    BOSSCorp::Synthesis::Oscillators::SawToothOscillator oscillator;
    autoplot("sawtooth", oscillator);
}

TEST(SawtoothOscillatorTests, ConfirmFrequency)
{
    BOSSCorp::Synthesis::Oscillators::SawToothOscillator oscillator;
    int frequencies[] {20, 440, 3000};
    int size = sizeof(frequencies) / sizeof(frequencies[0]);

    doGlobalFrequencyTest(oscillator, frequencies, size, 5);
}