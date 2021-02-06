#pragma once
#include "midi_event.h"

namespace BOSSCorp::Midi
{

class IMidiSink {
public:
    virtual void receive(const MidiEvent& event) = 0;
};

} //  BOSSCorp::Midi