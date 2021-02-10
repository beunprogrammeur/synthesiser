#include <gtest/gtest.h>
#include "synthesis/oscillators/pwm_oscillator.h"

#include "fft.h"

TEST(SawtoothOscillatorTests, PLOT)
{
    using namespace BOSSCorp::Synthesis::Oscillators;
    Configurations::PWMConfiguration config;
    config.dutyCycle = 0.5;

    PWMOscillator oscillator(config);

    autoplot("pwm-50%", oscillator);
    
    oscillator.reset();
    config.dutyCycle = 0.75;
    autoplot("pwm-75%", oscillator);

    oscillator.reset();
    config.dutyCycle = 0.25;
    autoplot("pwm-25%", oscillator);
}

TEST(SawtoothOscillatorTests, ConfirmFrequency)
{
    using namespace BOSSCorp::Synthesis::Oscillators;
    Configurations::PWMConfiguration config;
    config.dutyCycle = 0.5;
    PWMOscillator oscillator(config);

    int frequencies[] {20, 440, 3000};
    int size = sizeof(frequencies) / sizeof(frequencies[0]);

    doGlobalFrequencyTest(oscillator, frequencies, size, 5);
}