#include<gtest/gtest.h>

#include "synthesis/oscillators/reverse_sawtooth_oscillator.h"
#include "fft.h"

TEST(SawtoothOscillatorTests, PLOT)
{
    BOSSCorp::Synthesis::Oscillators::ReverseSawToothOscillator oscillator;
    autoplot("reverse-sawtooth", oscillator);
}

TEST(SawtoothOscillatorTests, ConfirmFrequency)
{
    BOSSCorp::Synthesis::Oscillators::ReverseSawToothOscillator oscillator;
    int frequencies[] {20, 440, 3000};
    int size = sizeof(frequencies) / sizeof(frequencies[0]);

    doGlobalFrequencyTest(oscillator, frequencies, size, 5);
}