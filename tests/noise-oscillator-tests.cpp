#include <gtest/gtest.h>
#include "synthesis/oscillators/noise_oscillator.h"

#include "fft.h"

using namespace BOSSCorp::Synthesis::Oscillators;
using namespace Configurations;

class NoiseOscillatorTestFixture : public ::testing::Test
{
protected:
    NoiseOscillator* oscillator;
    NoiseConfiguration * configuration;
    IOscillator* ioscillator;
    virtual void SetUp()
    {
        configuration = new NoiseConfiguration;
        oscillator    = new NoiseOscillator(*configuration);
        ioscillator   = oscillator;

        oscillator->frequency(100);
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

TEST_F(NoiseOscillatorTestFixture, PLOT)
{
    autoplot("noise", *oscillator);    
}