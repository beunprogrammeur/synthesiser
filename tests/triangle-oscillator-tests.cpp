#include<gtest/gtest.h>

#include "synthesis/oscillators/triangle_oscillator.h"
#include "fft.h"

TEST(TriangleOscillatorTests, PLOT)
{
    using namespace BOSSCorp::Synthesis::Oscillators;
    Configurations::TriangleConfiguration config;
    TriangleOscillator oscillator(config);
    autoplot("triangle", oscillator);    
}


TEST(TriangleOscillatorTests, ConfirmFrequency)
{
    using namespace BOSSCorp::Synthesis::Oscillators;
    Configurations::TriangleConfiguration config;
    TriangleOscillator oscillator(config);

    int frequencies[] {20, 440, 3000};
    int size = sizeof(frequencies) / sizeof(frequencies[0]);

    doGlobalFrequencyTest(oscillator, frequencies, size, 5);
}