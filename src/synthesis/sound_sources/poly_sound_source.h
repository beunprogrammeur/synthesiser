#pragma once
#include <vector>
#include "isound_source.h"
#include "../oscillators/ioscillator.h"
#include "../../midi/converter.h"

namespace BOSSCorp::Synthesis::SoundSources
{

class PolySoundSource : public ISoundSource
{
private:
    std::vector<Synthesis::Oscillators::IOscillator*> _oscillators;
protected:
    virtual float next();
public:
    PolySoundSource(Envelopes::IEnvelope& envelope) : ISoundSource(envelope) {}
    void add(Synthesis::Oscillators::IOscillator& oscillator) { _oscillators.emplace_back(&oscillator); oscillator.configure(Midi::Converter::toFrequency(note(), octave())); }
    void clear() { _oscillators.clear(); }
    virtual void reset() { for(auto* osc : _oscillators) { osc->reset(); } ISoundSource::reset(); }
    virtual void configure(Midi::Note note, int8_t octave, float amplitude);
};

} // end BOSSCorp::Synthesis::SoundSources
