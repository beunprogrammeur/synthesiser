#pragma once
#include "imidi_sink.h"
#include "synthesis/synthesizers/synthesizer.h"

namespace BOSSCorp::Midi
{
class SynthesizerMidiSink : public IMidiSink
{
private:
    static constexpr CC PwmOscillatorVolumeCode             = CC::Controller32;
    static constexpr CC PwmOscillatorDutyCycleCode          = CC::Controller33;
    static constexpr CC SawtoothOscillatorVolumeCode        = CC::Controller34;
    static constexpr CC ReverseSawtoothOscillatorVolumeCode = CC::Controller35;
    static constexpr CC TriangleOscillatorVolumeCode        = CC::Controller36;
    static constexpr CC NoiseOscillatorVolumeCode           = CC::Controller37;
    static constexpr CC SineOscillatorVolumeCode            = CC::Controller38;

    BOSSCorp::Synthesis::Synthesizers::Synthesizer& _synth;

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

    void pwmVolume(const MidiEvent& event);
    void pwmDutyCycle(const MidiEvent& event);
    void sawtoothVolume(const MidiEvent& event);
    void reverseSawtoothVolume(const MidiEvent& event);
    void triangleVolume(const MidiEvent& event);
    void noiseVolume(const MidiEvent& event);
    void sineVolume(const MidiEvent& event);




    float map(uint8_t data2, float min, float max) const;
    float map2(uint16_t data, float min, float max) const;

public:
    SynthesizerMidiSink(Channel channel, BOSSCorp::Synthesis::Synthesizers::Synthesizer& synth) : IMidiSink(channel), _synth(synth) { }
    virtual void receive(const MidiEvent& event);
};
}