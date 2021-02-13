#include <gtest/gtest.h>
#include "midi/synthesizer_midi_sink.h"
#include "midi/imidi_source.h"
#include "midi/midi_event.h"
#include "synthesis/buffer.h"

using namespace BOSSCorp;
using namespace BOSSCorp::Midi;

class MockSynth : public Synthesis::Synthesizers::ISynthesizer
{
public:
    bool processCalled;
    bool resetCalled;
    Midi::Note noteOnNote;
    int8_t noteOnOctave;
    float noteOnVelocity;
    Midi::Note noteOffNote;
    int8_t noteOffOctave;
    float noteOffVelocity;
    float volumeValue;
    float pitchBendValue;
    float effect1Value;
    float effect2Value;
    float lowPassFilterValue;
    float highPassFilterValue;
    float attackValue;
    float decayvalue;
    float releaseValue;
    float sustainValue;
    bool monoModeCalled;
    bool polyModeCalled;
    bool allNotesOffCalled;

    virtual void process(Synthesis::Buffer &buffer) { processCalled = true; }
    // Resets to cold boot
    virtual void reset() { resetCalled = true; }
    // velocity 0 = silence, 1 = bottom out.
    virtual void noteOn(Midi::Note note, int8_t octave, float velocity)
    {
        noteOnNote = note, noteOnOctave = octave;
        noteOnVelocity = velocity;
    }
    virtual void noteOff(Midi::Note note, int8_t octave, float velocity)
    {
        noteOffNote = note;
        noteOffOctave = octave;
        noteOffVelocity = velocity;
    }
    // 0 = silence, 1 = max volume
    virtual float volume() { return volumeValue; }
    virtual void volume(float value) { volumeValue = value; }
    // 1 is the next note, -1 the previous note.
    virtual void pitchBend(float value) { pitchBendValue = value; }
    // 0 = clean, 1 = full application
    virtual void effect1(float value) { effect1Value = value; }
    virtual void effect2(float value) { effect2Value = value; }
    // 0 = no filter, 1 = max filter
    virtual void lowPassFilter(float value) { lowPassFilterValue = value; }
    virtual void highPassFilter(float value) { highPassFilterValue = value; }
    // ADSR envelope
    // 0 = immediate, 1 = as long as the synth allows
    virtual void attack(float time) { attackValue = time; }
    virtual float attack() const { return attackValue; }
    virtual void decay(float time) { decayvalue = time; }
    virtual float decay() const { return decayvalue; }
    virtual void release(float time) { releaseValue = time; }
    virtual float release() const { return releaseValue; }
    // 0 = silence, 1 = max volume
    virtual void sustain(float amplitude) { sustainValue = amplitude; }
    virtual float sustain() const { return sustainValue; }
    virtual void monoMode() { monoModeCalled = true; }
    virtual void polyMode() { polyModeCalled = true; }
    virtual void allNotesOff() { allNotesOffCalled = true; }
};

class SynthMidiSinkTestFixture : public ::testing::Test
{
protected:
    Midi::Channel              channel;
    MockSynth*                 synth;
    Midi::IMidiSource*         source;
    Midi::SynthesizerMidiSink* sink;
    
    virtual void SetUp()
    {
        channel = Midi::Channel::Channel4;
        synth   = new MockSynth;
        sink    = new Midi::SynthesizerMidiSink(channel, *synth);
        source  = new Midi::IMidiSource;

        source->subscribe(*sink);
    }

    virtual void TearDown()
    {
        delete synth;
        delete sink;
        delete source;
        synth  = nullptr;
        sink   = nullptr;
        source = nullptr;
    }

    Midi::Status addChannel(Midi::Status status)
    {
        return static_cast<Midi::Status>(static_cast<uint8_t>(status) | static_cast<uint8_t>(channel));
    }

    float map(int value, float min, float max)
    {
        constexpr int maxdata = 127;
        constexpr int mindata = 0;

        if (value >= maxdata) return max; 
        if (value <= mindata) return min;
        return (max - min) / maxdata * value; 
    }

    float map2(int data, float min, float max) const
    {
        constexpr int maxdata     = 0x3fff;
        constexpr int centerdata = maxdata/2;
        constexpr int mindata     = 0x0000;

        if (data == centerdata) return (max - min) / 2.0;
        if (data >= maxdata)    return  max;
        if (data <= mindata)    return  min;

        return (max - min) / maxdata * data;
    }

    MidiEvent ccevent(CC cc, uint8_t value)
    {
        return MidiEvent(addChannel(Status::ControlChange), static_cast<uint8_t>(cc), value);
    }
};

TEST_F(SynthMidiSinkTestFixture, wrongChannelIgnored)
{
    // TODO: also test omnimode here

}


TEST_F(SynthMidiSinkTestFixture, noteOnCalled)
{
    constexpr int NOTEC4 = 60;
    auto event = Midi::MidiEvent(addChannel(Midi::Status::NoteOn), NOTEC4,12);
    source->send(event);

    ASSERT_EQ(Note::C,       synth->noteOnNote);
    ASSERT_EQ(4,             synth->noteOnOctave);
    ASSERT_EQ(map(12, 0, 1), synth->noteOnVelocity);
}

TEST_F(SynthMidiSinkTestFixture, noteOffCalled)
{
    constexpr int NOTEA5 = 81;
    auto event = Midi::MidiEvent(addChannel(Midi::Status::NoteOff), NOTEA5,11);
    source->send(event);

    ASSERT_EQ(Note::A,       synth->noteOffNote);
    ASSERT_EQ(5,             synth->noteOffOctave);
    ASSERT_EQ(map(11, 0, 1), synth->noteOffVelocity);
}

TEST_F(SynthMidiSinkTestFixture, volumeCalled)
{
    int value = 64;
    auto event = ccevent(CC::Volume, value);
    source->send(event);

    ASSERT_EQ(map(value, 0, 1), synth->volumeValue);
}

TEST_F(SynthMidiSinkTestFixture, pitchBendCalled)
{
    constexpr int value = 0x03fff;
    auto event = Midi::MidiEvent(addChannel(Midi::Status::PitchBendChange), 0x7f,0x7f);
    source->send(event);

    ASSERT_EQ(map2(value, -1, 1), synth->pitchBendValue);
}

TEST_F(SynthMidiSinkTestFixture, effect1Called)
{
    constexpr int value = 64;
    auto event = ccevent(CC::EffectControl1, value);
    source->send(event);

    ASSERT_EQ(map(value, 0, 1), synth->effect1Value);
}

TEST_F(SynthMidiSinkTestFixture, effect2Called)
{
    constexpr int value = 22;
    auto event = ccevent(CC::EffectControl2, value);
    source->send(event);

    ASSERT_EQ(map(value, 0, 1), synth->effect2Value);
}

TEST_F(SynthMidiSinkTestFixture, lowPassFilterCalled)
{
    constexpr int value = 40;
    auto event = ccevent(CC::LowPassFilterFrequency, value);
    source->send(event);

    ASSERT_EQ(map(value, 0, 1), synth->lowPassFilterValue);
}

TEST_F(SynthMidiSinkTestFixture, highPassFilterCalled)
{
    constexpr int value = 40;
    auto event = ccevent(CC::HighPassFilterFrequency, value);
    source->send(event);

    ASSERT_EQ(map(value, 0, 1), synth->highPassFilterValue);
}

TEST_F(SynthMidiSinkTestFixture, attackCalled)
{
    constexpr int value = 40;
    auto event = ccevent(CC::SoundAttackTime, value);
    source->send(event);

    ASSERT_EQ(map(value, 0, 1), synth->attackValue);
}

TEST_F(SynthMidiSinkTestFixture, decayCalled)
{
    constexpr int value = 40;
    auto event = ccevent(CC::SoundDecayTime, value);
    source->send(event);

    ASSERT_EQ(map(value, 0, 1), synth->decayvalue);
}

TEST_F(SynthMidiSinkTestFixture, sustainCalled)
{
    constexpr int value = 40;
    auto event = ccevent(CC::Sustain, value);
    source->send(event);

    ASSERT_EQ(map(value, 0, 1), synth->sustainValue);
}

TEST_F(SynthMidiSinkTestFixture, releaseCalled)
{
    constexpr int value = 40;
    auto event = ccevent(CC::SoundReleaseTime, value);
    source->send(event);

    ASSERT_EQ(map(value, 0, 1), synth->releaseValue);
}


TEST_F(SynthMidiSinkTestFixture, monoModeCalled)
{
    constexpr int value = 40;
    auto event = ccevent(CC::MonoMode, value);
    source->send(event);

    ASSERT_TRUE(synth->monoModeCalled);
}

TEST_F(SynthMidiSinkTestFixture, polyModeCalled)
{
    constexpr int value = 40;
    auto event = ccevent(CC::PolyMode, value);
    source->send(event);

    ASSERT_TRUE(synth->polyModeCalled);
}

TEST_F(SynthMidiSinkTestFixture, allNotesOffCalled)
{
    constexpr int value = 40;
    auto event = ccevent(CC::AllNotesOff, value);
    source->send(event);

    ASSERT_TRUE(synth->allNotesOffCalled);
}

TEST_F(SynthMidiSinkTestFixture, resetCalled)
{
    ASSERT_FALSE(synth->resetCalled);
    auto event = Midi::MidiEvent(Midi::Status::Reset, 0,0);
    source->send(event);

    ASSERT_TRUE(synth->resetCalled);
}