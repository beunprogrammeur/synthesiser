#pragma once
#include "imidi_sink.h"
#include "synthesis/synthesizers/isynthesizer.h"

namespace BOSSCorp::Midi
{
class SynthesizerMidiSink : public IMidiSink
{
private:
    BOSSCorp::Synthesis::Synthesizers::ISynthesizer& _synth;

    void noteOn(const MidiEvent& event);
    void noteOff(const MidiEvent& event);
    void volume(const MidiEvent& event);
    void pitchBend(const MidiEvent& event);
    void effect1(const MidiEvent& event);
    void effect2(const MidiEvent& event);
    void lowPassFilter(const MidiEvent& event);
    void highPassFilter(const MidiEvent& event);
    void attack(const MidiEvent& event);
    void decay(const MidiEvent& event);
    void sustain(const MidiEvent& event);
    void release(const MidiEvent& event);

    void monoMode(const MidiEvent& event);
    void polyMode(const MidiEvent& event);
    void allNotesOff(const MidiEvent& event);
    void reset(const MidiEvent& event);

    void controlChange(const MidiEvent& event);

    float map(uint8_t data2, float min, float max) const;
    float map2(uint16_t data, float min, float max) const;
public:
    SynthesizerMidiSink(Channel channel, BOSSCorp::Synthesis::Synthesizers::ISynthesizer& synth) : IMidiSink(channel), _synth(synth) { }
    virtual void receive(const MidiEvent& event);
};
}