#include<gtest/gtest.h>

#include "synthesis/oscillators/reverse_sawtooth_oscillator.h"
#include "fft.h"

TEST(SawtoothOscillatorTests, PLOT)
{
    using namespace BOSSCorp::Synthesis::Oscillators;
    Configurations::ReverseSawoothConfiguration config;
    ReverseSawToothOscillator oscillator(config);
    autoplot("reverse-sawtooth", oscillator);
}

TEST(SawtoothOscillatorTests, ConfirmFrequency)
{
    using namespace BOSSCorp::Synthesis::Oscillators;
    Configurations::ReverseSawoothConfiguration config;
    ReverseSawToothOscillator oscillator(config);
    
    int frequencies[] {20, 440, 3000};
    int size = sizeof(frequencies) / sizeof(frequencies[0]);

    doGlobalFrequencyTest(oscillator, frequencies, size, 5);
}