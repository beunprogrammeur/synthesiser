#pragma once
#include "imidi_sink.h"
#include "synthesis/synthesizers/isynthesizer.h"

namespace BOSSCorp::Midi
{
class SynthesizerMidiSink : public IMidiSink
{
private:
    BOSSCorp::Synthesis::Synthesizers::ISynthesizer& _synth;

    void noteOn(MidiEvent& event);
    void noteOff(MidiEvent& event);
    void volume(MidiEvent& event);
    void pitchBend(MidiEvent& event);
    void effect1(MidiEvent& event);
    void effect2(MidiEvent& event);
    void lowPassFilter(MidiEvent& event);
    void highPassFilter(MidiEvent& event);
    void attack(MidiEvent& event);
    void decay(MidiEvent& event);
    void sustain(MidiEvent& event);
    void release(MidiEvent& event);

    void monoMode(MidiEvent& event);
    void polyMode(MidiEvent& event);
    void allNotesOff(MidiEvent& event);
    void reset(MidiEvent& event);

    void controlChange(MidiEvent& event);

    float toFloat(uint8_t data2, float min, float max) const;
    float toFloat(uint16_t data, float min, float max) const;
public:
    SynthesizerMidiSink(Channel channel, BOSSCorp::Synthesis::Synthesizers::ISynthesizer& synth) : IMidiSink(channel), _synth(synth) { }
    virtual void receive(MidiEvent& event);
};
}