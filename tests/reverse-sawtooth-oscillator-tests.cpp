#include<gtest/gtest.h>

#include "synthesis/oscillators/reverse_sawtooth_oscillator.h"
#include "fft.h"
#include "amplitudetest.h"

using namespace BOSSCorp::Synthesis::Oscillators;
using namespace BOSSCorp::Midi;
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

        ioscillator->configure(Note::A, 4);
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
    autoplot("reverse-sawtooth", *oscillator);
}

TEST_F(ReverseSawtoothOscillatorTestFixture, ConfirmFrequency)
{    
    int frequencies[] {20, 440, 3000};
    int size = sizeof(frequencies) / sizeof(frequencies[0]);

    doGlobalFrequencyTest(*oscillator, frequencies, size, 5);
}

TEST_F(ReverseSawtoothOscillatorTestFixture, AmplitudeTest)
{
    oscillator->configure(Note::A, 0);
    configuration->amplitude = 1.0f;
    amplitudeTest(*oscillator, 1.0f);

    configuration->amplitude = 0.5f;
    amplitudeTest(*oscillator, 0.5f);

    ioscillator->configure(Note::A, 0, 0.5f);
    amplitudeTest(*oscillator, 0.25f);
}