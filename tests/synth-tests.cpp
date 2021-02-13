#include <gtest/gtest.h>
#include "synthesis/synthesizers/synthesizer.h"
#include "synthesis/buffer.h"
#include "midi/enums.h"
#include <functional>
#include "sound_maker/sound_maker.hpp"
#include "fft.h"

using namespace BOSSCorp;

TEST(SynthesizerTests, GenerateC4Chordreturn)
{
    int bufferSize = 512;
    int sampleRate = 44100;
    Synthesis::Synthesizers::Synthesizer synth(10);
    Synthesis::Buffer buffer(bufferSize, sampleRate);
    synth.attack(0.3);
    synth.decay(0.1);
    synth.sustain(0.8);
    synth.release(0.4);

    int secondsToRecord = 6;
    int loops = sampleRate * secondsToRecord / bufferSize + 1;

    float time = 0;
    float lastTime = 0;
    float deltaTime = 1.0 / sampleRate;
    float amplitude = 1.0;

    struct pack
    {
        int8_t octave;
        Midi::Note note;
        std::function<bool(float, float)> conditionOn;
        std::function<bool(float, float)> conditionOff;
    };

    pack activities[] {
        pack{
            .octave = 4,
            .note = Midi::Note::C,
            .conditionOn  = [](float time, float prev) { return prev < 1 && time > 1; },
            .conditionOff = [](float time, float prev) { return prev < 4 && time > 4; },
        },
        pack{
            .octave = 4,
            .note = Midi::Note::E,
            .conditionOn  = [](float time, float prev) { return prev < 2 && time > 2; },
            .conditionOff = [](float time, float prev) { return prev < 4 && time > 4; },
        },
        pack{
            .octave = 4,
            .note = Midi::Note::G,
            .conditionOn  = [](float time, float prev) { return prev < 3 && time > 3; },
            .conditionOff = [](float time, float prev) { return prev < 4 && time > 4; },
        },
    };

    std::vector<float> steps;

    SoundMaker smaker("synth-c4.wav");
    for(int l = 0; l < loops; l++)
    {
        time += deltaTime * bufferSize;

        for(auto& activity : activities)
        {
            if(activity.conditionOn(time, lastTime))
            {
                synth.noteOn(activity.note, activity.octave, amplitude);
            }
            if(activity.conditionOff(time, lastTime))
            {
                synth.noteOff(activity.note, activity.octave, amplitude);
            }
        }

        synth.process(buffer);        
        lastTime = time;

        auto data = buffer.data();
        for(int i= 0; i < buffer.size(); i++)
        {
            steps.emplace_back(data[i]);
            smaker.add_sample(data[i], data[i]);
        }
    }
    dataplot("synth-c4", steps);
    smaker.done();
}