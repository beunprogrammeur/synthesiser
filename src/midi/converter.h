#pragma once
#include "enums.h"

namespace BOSSCorp::Midi
{

class Converter {
public:
    static float   toFrequency(Note note, int8_t octave, float bend = 0);
    static float   toFrequency(int8_t midiPitch, float bend = 0);
    static Channel toChannel(Status status);
    static Status  stripChannel(Status status);
    static void    toNote(int midiPitch, Note& note, int8_t& octave);

    
};


} // end BOSSCorp::MIDI