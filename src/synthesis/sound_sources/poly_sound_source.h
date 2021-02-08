#pragma once
#include <vector>
#include "isound_source.h"
#include "../oscillators/ioscillator.h"

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
    void add(Synthesis::Oscillators::IOscillator& oscillator) { _oscillators.emplace_back(&oscillator); }
    void clear() { _oscillators.clear(); }
    virtual void reset() { for(auto* osc : _oscillators) { osc->reset(); } ISoundSource::reset(); }
};

} // end BOSSCorp::Synthesis::SoundSources
