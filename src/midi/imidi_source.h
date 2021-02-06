#pragma once
#include "../pattern/observer.h"
#include "imidi_sink.h"

namespace BOSSCorp::Midi
{

class IMidiSource {
private:
    BOSSCorp::Pattern::Observer<IMidiSource&, const MidiEvent&> _event;

protected:
    void send(const MidiEvent& event) { _event.raise(*this, event); }

public:
    void subscribe(IMidiSink& sink)   { _event.subscribe([&sink](auto& sender, auto& event) { sink.receive(event); }); }
};

} //  BOSSCorp::Midi