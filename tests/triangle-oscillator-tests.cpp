#include<gtest/gtest.h>

#include "synthesis/oscillators/triangle_oscillator.h"
#include "fft.h"

TEST(TriangleOscillatorTests, PLOT)
{
    BOSSCorp::Synthesis::Oscillators::TriangleOscillator oscillator;
    autoplot("triangle", oscillator);    
}


TEST(TriangleOscillatorTests, ConfirmFrequency)
{
    BOSSCorp::Synthesis::Oscillators::TriangleOscillator oscillator;
    int frequencies[] {20, 440, 3000};
    int size = sizeof(frequencies) / sizeof(frequencies[0]);

    doGlobalFrequencyTest(oscillator, frequencies, size, 5);
}