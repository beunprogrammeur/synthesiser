#include <gtest/gtest.h>
#include "synthesis/oscillators/pwm_oscillator.h"

#include "fft.h"

using namespace BOSSCorp::Synthesis::Oscillators;
using namespace Configurations;

class PWMOscillatorTestFixture : public ::testing::Test
{
protected:
    PWMOscillator* oscillator;
    PWMConfiguration * configuration;
    IOscillator* ioscillator;
    virtual void SetUp()
    {
        configuration = new PWMConfiguration;
        oscillator    = new PWMOscillator(*configuration);
        ioscillator   = oscillator;

        configuration->dutyCycle = 0.5;
        oscillator->configure(100);
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


TEST_F(PWMOscillatorTestFixture, PLOT)
{
    configuration->dutyCycle = 0.5;

    autoplot("pwm-50%", *oscillator);
    
    oscillator->reset();
    configuration->dutyCycle = 0.75;
    autoplot("pwm-75%", *oscillator);

    oscillator->reset();
    configuration->dutyCycle = 0.25;
    autoplot("pwm-25%", *oscillator);
}

TEST_F(PWMOscillatorTestFixture, ConfirmFrequency)
{
    configuration->dutyCycle = 0.5;

    int frequencies[] {20, 440, 3000};
    int size = sizeof(frequencies) / sizeof(frequencies[0]);

    doGlobalFrequencyTest(*oscillator, frequencies, size, 5);
}

TEST_F(PWMOscillatorTestFixture, DutyCycleTest)
{
    configuration->dutyCycle = 0.5;

    int upSamples = 0;

    float deltaT = 0.001;
    for(int i = 0; i < 1000; i++)
    {
        float sample = ioscillator->next(deltaT);
        upSamples += sample > 0;
    }

    ASSERT_GE(upSamples, 490);
    ASSERT_LT(upSamples, 510);
}

TEST_F(PWMOscillatorTestFixture, AmplitudeTest)
{
    configuration->dutyCycle = 0.5;
    
    float max = 0;
    float min = 0;

    float deltaT = 0.001;
    for(int i = 0; i < 1000; i++)
    {
        float sample = ioscillator->next(deltaT);
        max = std::max(max, sample);
        min = std::min(min, sample);
    }

    ASSERT_EQ(max, configuration->amplitude / 2);
    ASSERT_EQ(min, -configuration->amplitude / 2);
}