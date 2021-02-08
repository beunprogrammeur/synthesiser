#pragma once
#include "../isteppable.h"
#include "../envelopes/ienvelope.h"

namespace BOSSCorp::Synthesis::SoundSources
{

class ISoundSource : public ISteppable
{
private:
    float _lastDeltaTime;
protected:
    Envelopes::IEnvelope& _envelope;
    float deltaTime() const { return _lastDeltaTime; }
public:
    ISoundSource(Envelopes::IEnvelope& envelope) : _envelope(envelope) { }
    virtual float next(float deltaTime) { _lastDeltaTime = deltaTime; return ISteppable::next(deltaTime); }
    virtual void reset() { _envelope.reset(); ISteppable::reset(); }
};

} // end BOSSCorp::Synthesis::SoundSources