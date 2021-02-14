#pragma once
#include "../buffer.h"
#include "../../midi/enums.h"

namespace BOSSCorp::Synthesis::Synthesizers
{

class ISynthesizer {
public:
    virtual void process(Buffer& buffer) = 0;

	virtual void init() {}

    // Resets to cold boot
    virtual void reset() {}

    // velocity 0 = silence, 1 = bottom out.
    virtual void noteOn(Midi::Note note, int8_t octave, float velocity) {}
    virtual void noteOff(Midi::Note note, int8_t octave, float velocity) {}

    // 0 = silence, 1 = max volume
    virtual float volume() { return 0; }
    virtual void  volume(float value)  {}

    // 1 is the next note, -1 the previous note.
    virtual void pitchBend(float value)  { }

    // 0 = clean, 1 = full application
    virtual void effect1(float value) {}
    virtual void effect2(float value) {}

    // 0 = no filter, 1 = max filter
    virtual void lowPassFilter(float value)  {}
    virtual void highPassFilter(float value) {}

    // ADSR envelope
    // 0 = immediate, 1 = as long as the synth allows
    virtual void  attack(float time)  {}
    virtual float attack() const  { return 0; }
    virtual void  decay(float time)   {}
    virtual float decay() const   { return 0; }
    virtual void  release(float time) {}
    virtual float release() const { return 0; }

    // 0 = silence, 1 = max volume
    virtual void  sustain(float amplitude) {}
    virtual float sustain() const { return 0; }

    virtual void monoMode() {}
    virtual void polyMode() {}

    virtual void allNotesOff() {}
};

} // end BOSSCorp::Synthesis::Synthesizers
