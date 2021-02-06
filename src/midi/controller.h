#pragma once
#include "icontroller.h"
#include "imidi_source.h"
#include "midi_event.h"

namespace BOSSCorp::Midi 
{
class Controller : public IController
{
public:


private:


    void midiReceived(const MidiEvent& event);
};

} // end BOSSCorp::Midi 