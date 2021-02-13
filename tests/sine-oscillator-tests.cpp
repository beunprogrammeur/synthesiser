#include <gtest/gtest.h>
#include "synthesis/oscillators/sine_oscillator.h"
#include "fft.h"
#include "amplitudetest.h"

using namespace BOSSCorp::Synthesis::Oscillators;
using namespace Configurations;

class SineOscillatorTestFixture : public ::testing::Test
{
protected:
    SineOscillator*     oscillator;
    SineConfiguration * configuration;
    IOscillator* ioscillator;
    virtual void SetUp()
    {
        configuration = new SineConfiguration;
        oscillator    = new SineOscillator(*configuration);
        ioscillator   = oscillator;

        ioscillator->configure(100);
    }

    virtual void TearDown()
    {
        delete oscillator;
        delete configuration;
        oscillator    = nullptr;
        configuration = nullptr;
        ioscillator   = nullptr;
    }
};

TEST_F(SineOscillatorTestFixture, PLOT)
{
    autoplot("sine", *oscillator);
}

TEST_F(SineOscillatorTestFixture, ConfirmFrequency)
{
    int frequencies[] {20, 440, 3000};
    int size = sizeof(frequencies) / sizeof(frequencies[0]);

    doGlobalFrequencyTest(*oscillator, frequencies, size, 5);
}


TEST_F(SineOscillatorTestFixture, AmplitudeTest)
{
    oscillator->configure(20);
    configuration->amplitude = 1.0f;
    amplitudeTest(*oscillator, 1.0f);

    configuration->amplitude = 0.5f;
    amplitudeTest(*oscillator, 0.5f);

    ioscillator->configure(20, 0.5f);
    amplitudeTest(*oscillator, 0.25f);
}