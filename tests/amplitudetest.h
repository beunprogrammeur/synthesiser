#pragma once
#include "synthesis/oscillators/ioscillator.h"
#include <algorithm>
#include <gtest/gtest.h>

void amplitudeTest(BOSSCorp::Synthesis::Oscillators::IOscillator& oscillator, float amplitude, float range = 0.05)
{
    float max = 0;
    float min = 0;

    int samples = 1000;
    float deltaT = 1.0f / samples;

    for(int i = 0; i < samples; i++)
    {
        float sample = oscillator.next(deltaT);
        max = std::max(max, sample);
        min = std::min(min, sample);
    }

    ASSERT_LT(max, amplitude + range);
    ASSERT_GE(max, amplitude - range);

    ASSERT_LT(min, -amplitude + range);
    ASSERT_GE(min, -amplitude - range);
}