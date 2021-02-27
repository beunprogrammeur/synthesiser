#include <gtest/gtest.h>

#include "midi/enums.h"


#include "synthesis/sound_sources/poly_sound_source.h"
#include "synthesis/envelopes/adsr_envelope.h"
#include "synthesis/oscillators/oscillators.h"

#include "wav.h"
#include <functional>

TEST(PolySoundSourceTest, GenerateWaveFiles)
{
    using namespace BOSSCorp::Synthesis;
    using namespace BOSSCorp::Synthesis::Oscillators;
    Envelopes::ADSRConfiguration                configuration;
    Envelopes::ADSREnvelope                     envelope(configuration);
    
    Configurations::PWMConfiguration            pwmConfig;
    Configurations::NoiseConfiguration          noiseConfig;
    Configurations::TriangleConfiguration       triangleConfig;
    Configurations::SawtoothConfiguration       sawtoothConfig;
    Configurations::ReverseSawoothConfiguration rsawtoothConfig;
    Configurations::SineConfiguration           sineConfig;


    Oscillators::SineOscillator            sineOscillator(sineConfig);
    Oscillators::SawToothOscillator        sawtoothOscillator(sawtoothConfig);
    Oscillators::ReverseSawToothOscillator rsawtoothOscillator(rsawtoothConfig);
    Oscillators::PWMOscillator             pwmOscillator(pwmConfig);
    Oscillators::TriangleOscillator        triangleOscillator(triangleConfig);
    Oscillators::NoiseOscillator           noiseOscillator(noiseConfig);

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
        pack.oscillator.frequency(frequency);
        soundSource.reset();
        
        createWavFile(source, pack.name, [&](){envelope.release();});
    }

    soundSource.clear();
    soundSource.add(sineOscillator);

    Oscillators::SineOscillator            sineOscillator2(sineConfig);
    Oscillators::SineOscillator            sineOscillator3(sineConfig);

    sineOscillator.configure(BOSSCorp::Midi::Note::A, 0);
    sineOscillator2.configure(BOSSCorp::Midi::Note::A, 0);
    sineOscillator3.configure(BOSSCorp::Midi::Note::A, 0);

    sineOscillator2.frequency(500);
    sineOscillator3.frequency(700);

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
    explicit MockOscillator(const BOSSCorp::Synthesis::Oscillators::Configurations::IOscillatorConfiguration& config) : IOscillator(config) {}
};

TEST(PolySoundSourceTest, ActuallyOutputsData)
{
    using namespace BOSSCorp::Synthesis;
    Envelopes::ADSRConfiguration                          configuration;
    Envelopes::ADSREnvelope                               envelope(configuration);
    Oscillators::Configurations::IOscillatorConfiguration config;
    MockOscillator                                        oscillator(config);

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

TEST(PolySoundSourceTest, configuresOscillators)
{
    using namespace BOSSCorp::Synthesis::Oscillators;
    using namespace BOSSCorp::Synthesis::SoundSources;
    using namespace BOSSCorp::Synthesis::Envelopes;

    class MockOscillatorConfiguration : public Configurations::IOscillatorConfiguration
    {

    };

    class MockOscillator : public IOscillator
    {
    protected:
        virtual float next() { return 0; }
    public:
        MockOscillator(const MockOscillatorConfiguration& config) : IOscillator(config) {}
    };

    MockOscillatorConfiguration oscconfig;
    MockOscillator oscillator(oscconfig);

    ADSRConfiguration adsrconfig;
    ADSREnvelope envelope(adsrconfig);


    PolySoundSource source(envelope);
    source.add(oscillator);

    auto note = BOSSCorp::Midi::Note::C;
    auto octave = 4;
    auto amplitude = 1;

    source.configure(note, octave, amplitude);
    ASSERT_EQ(oscillator.frequency(), BOSSCorp::Midi::Converter::toFrequency(note, octave));
}
