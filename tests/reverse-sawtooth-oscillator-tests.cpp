#include<gtest/gtest.h>

#include "synthesis/oscillators/reverse_sawtooth_oscillator.h"
#include "fft.h"
#include "amplitudetest.h"

using namespace BOSSCorp::Synthesis::Oscillators;
using namespace Configurations;

class ReverseSawtoothOscillatorTestFixture : public ::testing::Test
{
protected:
    ReverseSawToothOscillator*     oscillator;
    ReverseSawoothConfiguration * configuration;
    IOscillator* ioscillator;
    virtual void SetUp()
    {
        configuration = new ReverseSawoothConfiguration;
        oscillator    = new ReverseSawToothOscillator(*configuration);
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


TEST_F(ReverseSawtoothOscillatorTestFixture, PLOT)
{
    using namespace BOSSCorp::Synthesis::Oscillators;
    Configurations::ReverseSawoothConfiguration config;
    ReverseSawToothOscillator oscillator(config);
    autoplot("reverse-sawtooth", oscillator);
}

TEST_F(ReverseSawtoothOscillatorTestFixture, ConfirmFrequency)
{
    using namespace BOSSCorp::Synthesis::Oscillators;
    Configurations::ReverseSawoothConfiguration config;
    ReverseSawToothOscillator oscillator(config);
    
    int frequencies[] {20, 440, 3000};
    int size = sizeof(frequencies) / sizeof(frequencies[0]);

    doGlobalFrequencyTest(oscillator, frequencies, size, 5);
}

TEST_F(ReverseSawtoothOscillatorTestFixture, AmplitudeTest)
{
    oscillator->configure(20);
    configuration->amplitude = 1.0f;
    amplitudeTest(*oscillator, 1.0f);

    configuration->amplitude = 0.5f;
    amplitudeTest(*oscillator, 0.5f);

    ioscillator->configure(20, 0.5f);
    amplitudeTest(*oscillator, 0.25f);
}