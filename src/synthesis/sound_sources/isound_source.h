#pragma once
#include "../isteppable.h"
#include "../envelopes/ienvelope.h"
#include "../../midi/enums.h"
#include <stdint.h>

namespace BOSSCorp::Synthesis::SoundSources
{

class ISoundSource : public ISteppable
{
private:
    float _lastDeltaTime;
    int8_t _octave;
    Midi::Note _note;
    float _amplitude;
    bool _ignore;
protected:
    Envelopes::IEnvelope& _envelope;
    float deltaTime() const { return _lastDeltaTime; }
public:
    ISoundSource(Envelopes::IEnvelope& envelope) : _lastDeltaTime(0), _octave(0), _note(Midi::Note::A), _amplitude(0), _envelope(envelope) { }
    virtual float next(float deltaTime) { _lastDeltaTime = deltaTime; return ISteppable::next(deltaTime); }
    virtual void reset() { _envelope.reset(); ISteppable::reset(); ignore(false);}
    virtual void configure(Midi::Note note, int8_t octave, float amplitude) { _note = note; _octave = octave; _amplitude = amplitude; }
    virtual bool finished() { return _envelope.finished(); }
    int8_t octave() const { return _octave; } 
    Midi::Note note() const { return _note; }
    bool ignore() const { return _ignore; }
    void ignore(bool value) { _ignore = value; } // to not use this source. for instance when no key is pressed.
    virtual void release() {}
};

} // end BOSSCorp::Synthesis::SoundSources
