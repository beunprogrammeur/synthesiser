#include "synthesizer_midi_sink.h"
#include "midi_event.h"
#include "enums.h"
#include "converter.h"

namespace BOSSCorp::Midi
{

void SynthesizerMidiSink::receive(MidiEvent& event)
{
    if(!IMidiSink::meantForMe(event)) return;

    // Channel voice messages
    switch(Converter::stripChannel(event.status()))
    {
        case Status::NoteOn:          noteOn(event);        return;
        case Status::NoteOff:         noteOff(event);       return;
        case Status::ControlChange:   controlChange(event); return;
        case Status::PitchBendChange: pitchBend(event);     return;
    }

    // System real-time messages
    switch(event.status())
    {
        case Status::Reset: reset(event); return;
    }
}

void SynthesizerMidiSink::controlChange(MidiEvent& event) 
{
    CC cc = static_cast<CC>(event.data1());

    switch(cc)
    {
        case CC::Volume: volume(event);                          return;
        case CC::EffectControl1: effect1(event);                 return;
        case CC::EffectControl2: effect2(event);                 return;
        case CC::SoundReleaseTime: release(event);               return;
        case CC::SoundAttackTime: attack(event);                 return;
        case CC::LowPassFilterFrequency: lowPassFilter(event);   return;
        case CC::SoundDecayTime: decay(event);                   return;
        case CC::HighPassFilterFrequency: highPassFilter(event); return;
        
        case CC::AllNotesOff: allNotesOff(event); return;
        case CC::OmniModeOff: omniMode(false);    return;
        case CC::OmniModeOn: omniMode(true);      return;
        case CC::MonoMode: monoMode(event);       return;
        case CC::PolyMode: polyMode(event);       return;
    }
}

float SynthesizerMidiSink::toFloat(uint8_t data2, float min, float max) const
{
    constexpr int maxdata2 = 127;
    constexpr int mindata2 = 0;

    if (data2 == maxdata2) return max; 
    if (data2 == mindata2) return min;
    return (max - min) / maxdata2 * data2;
}

float SynthesizerMidiSink::toFloat(uint16_t data, float min, float max) const
{
    constexpr int maxdata     = 0x7fff;
    constexpr int centervalue = 0x4000;
    constexpr int mindata     = 0x0000;

    if (data == centervalue) return (max - min) / 2.0;
    if (data == maxdata) return max;
    if (data == mindata) return min;

    return (max - min) / maxdata * data;
}

void SynthesizerMidiSink::noteOn(MidiEvent& event) 
{
    Note note;
    int8_t octave;
    Converter::toNote(event.data1(),note, octave);

    _synth.noteOn(note, octave, toFloat(event.data2(), 0.0, 1.0));
}

void SynthesizerMidiSink::noteOff(MidiEvent& event) 
{
    Note note;
    int8_t octave;
    Converter::toNote(event.data1(),note, octave);

    _synth.noteOff(note, octave, toFloat(event.data2(), 0.0, 1.0));
}

void SynthesizerMidiSink::volume(MidiEvent& event) 
{
    _synth.volume(toFloat(event.data2(), 0.0, 1.0));
}

void SynthesizerMidiSink::pitchBend(MidiEvent& event) 
{
    uint16_t value = (event.data2() << 7) | (event.data1() & 0x7f);
    _synth.pitchBend(toFloat(value,-1.0, 1.0));
}

void SynthesizerMidiSink::effect1(MidiEvent& event) 
{
    _synth.effect1(toFloat(event.data2(), 0.0, 1.0));
}

void SynthesizerMidiSink::effect2(MidiEvent& event) 
{
    _synth.effect2(toFloat(event.data2(), 0.0, 1.0));
}

void SynthesizerMidiSink::lowPassFilter(MidiEvent& event) 
{
    _synth.lowPassFilter(toFloat(event.data2(), 0.0, 1.0));
}

void SynthesizerMidiSink::highPassFilter(MidiEvent& event) 
{
    _synth.highPassFilter(toFloat(event.data2(), 0.0, 1.0));
}

void SynthesizerMidiSink::attack(MidiEvent& event) 
{
    _synth.attack(toFloat(event.data2(), 0.0, 1.0));
}

void SynthesizerMidiSink::decay(MidiEvent& event) 
{
    _synth.decay(toFloat(event.data2(), 0.0, 1.0));
}

void SynthesizerMidiSink::sustain(MidiEvent& event) 
{
    _synth.sustain(toFloat(event.data2(), 0.0, 1.0));
}

void SynthesizerMidiSink::release(MidiEvent& event) 
{
    _synth.release(toFloat(event.data2(), 0.0, 1.0));
}

void SynthesizerMidiSink::monoMode(MidiEvent& event) 
{
    _synth.monoMode();
}

void SynthesizerMidiSink::polyMode(MidiEvent& event) 
{
    _synth.polyMode();
}

void SynthesizerMidiSink::reset(MidiEvent& event)
{
    _synth.reset();
}

void SynthesizerMidiSink::allNotesOff(MidiEvent& event) 
{
    _synth.allNotesOff();
}
} // end  BOSSCorp::Midi