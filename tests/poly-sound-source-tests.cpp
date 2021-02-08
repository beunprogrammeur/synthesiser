#include <gtest/gtest.h>

#include "synthesis/sound_sources/poly_sound_source.h"
#include "synthesis/envelopes/adsr_envelope.h"
#include "synthesis/oscillators/oscillators.h"

#include "wav.h"
#include <functional>

TEST(PolySoundSourceTest, GenerateWaveFiles)
{
    using namespace BOSSCorp::Synthesis;
    Envelopes::ADSRConfiguration           configuration;
    Envelopes::ADSREnvelope                envelope(configuration);

    Oscillators::PWMConfiguration pwmConfiguration;

    Oscillators::SineOscillator            sineOscillator;
    Oscillators::SawToothOscillator        sawtoothOscillator;
    Oscillators::ReverseSawToothOscillator rsawtoothOscillator;
    Oscillators::PWMOscillator             pwmOscillator(pwmConfiguration);
    Oscillators::TriangleOscillator        triangleOscillator;
    Oscillators::NoiseOscillator           noiseOscillator;

    struct OscillatorPack {
        std::string name;
        Oscillators::IOscillator& oscillator;
    };

    OscillatorPack packs[] {
        {"sine",             sineOscillator     },
        {"sawtooth",         sawtoothOscillator },
        {"reverse-sawtooth", rsawtoothOscillator},
        {"triangle",         triangleOscillator },
        {"pwm",              pwmOscillator      },
        {"noise",            noiseOscillator    },
    };


    configuration.attack  = 1;
    configuration.decay   = 0.3;
    configuration.sustain = 0.8;
    configuration.release = 0.8;




    SoundSources::PolySoundSource soundSource(envelope);
    SoundSources::ISoundSource&   source = soundSource;

    float frequency = 440;
    for(auto& pack : packs)
    {
        soundSource.clear();
        soundSource.add(pack.oscillator);
        pack.oscillator.configure(frequency);
        soundSource.reset();
        
        createWavFile(source, pack.name, [&](){envelope.release();});
    }

    soundSource.clear();
    soundSource.add(sineOscillator);

    Oscillators::SineOscillator            sineOscillator2;
    Oscillators::SineOscillator            sineOscillator3;
    sineOscillator2.configure(500);
    sineOscillator3.configure(700);

    soundSource.add(sineOscillator2);
    soundSource.add(sineOscillator3);
    source.reset();
    createWavFile(source, "sine-440+500+700hz", [&](){envelope.release();});

}


class MockOscillator : public BOSSCorp::Synthesis::Oscillators::IOscillator
{
public:
    float amplitude = 0;
    virtual float next() { return amplitude; }
};

TEST(PolySoundSourceTest, ActuallyOutputsData)
{
    using namespace BOSSCorp::Synthesis;
    Envelopes::ADSRConfiguration configuration;
    Envelopes::ADSREnvelope      envelope(configuration);
    MockOscillator               oscillator;

    oscillator.amplitude  = 0.5;
    configuration.attack  = 0.1;
    configuration.decay   = 0.1;
    configuration.sustain = 0.8;
    configuration.release = 1;

    SoundSources::PolySoundSource soundSource(envelope);
    soundSource.add(oscillator);
    SoundSources::ISoundSource& source = soundSource;

    float deltaTime = 0.001;

    float result = 0;
    result = source.next(deltaTime);
    ASSERT_TRUE(result > 0);
    ASSERT_TRUE(result < 0.5);

    oscillator.amplitude = -0.5;
    result = source.next(deltaTime);
    ASSERT_TRUE(result < 0);
    ASSERT_TRUE(result > -0.5);
}

