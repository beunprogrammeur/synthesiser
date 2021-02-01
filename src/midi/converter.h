#pragma once
#include "note.h"

namespace BOSSCorp::MIDI
{

class Converter {
public:
    static float toFrequency(Note note, int8_t octave);
    static float toFrequency(int8_t midiPitch);

private:
    static void getNote(int midiPitch, Note& note, int8_t& octave);
    
};


} // end BOSSCorp::MIDI