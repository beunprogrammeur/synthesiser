#pragma once
#include "synthesis/sound_sources/isound_source.h"
#include <fstream>
#include <limits>
#include <string>
#include "fft.h"
#include "sound_maker/sound_maker.hpp"

void createWavFile(BOSSCorp::Synthesis::SoundSources::ISoundSource& soundSource, std::string filename, std::function<void()> whatToDoAt2Seconds)
{
    SoundMaker smaker(filename + ".wav");

    std::vector<float> points;
    int samplerate = 44100;
    int numsamples = samplerate * 3; // 3 seconds
    float deltatime = 1.0 / samplerate;

    int invokeFunctionAt = samplerate * 2;

    for (int i = 0; i < numsamples; ++i) 
    {
        if(i == invokeFunctionAt) whatToDoAt2Seconds();
        float point = soundSource.next(deltatime);
        constexpr auto max = std::numeric_limits<int16_t>::max();
        int sample = point * max;

        smaker.add_sample(sample, sample);
        points.emplace_back(point);
    }
    smaker.done();
    dataplot(filename, points);
}