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


TEST(SineOscillatorTests, ConfirmAmplitude)
{
    using namespace BOSSCorp::Synthesis::Oscillators;
    Configurations::SineConfiguration config;
    SineOscillator oscillator(config);
    IOscillator& osc = oscillator;

    config.amplitude = 1;
    config.pitchBend = 0;
    oscillator.configure(20); // 20 hz
    
    float max = 0;
    float min = 0;

    int steps = 1000;
    float deltaTime = 1.0 / steps; // 1 second

    for(int i = 0; i < steps; i++)
    {
        float value = osc.next(deltaTime);
        min = std::min(min, value);
        max = std::max(max, value);
    }

    float precision = 0.005;
    ASSERT_GE(max, (config.amplitude / 2) - precision);
    ASSERT_LE(max, (config.amplitude / 2) + precision);

    ASSERT_GE(min, -(config.amplitude / 2) - precision);
    ASSERT_LE(min, -(config.amplitude / 2) + precision);


}