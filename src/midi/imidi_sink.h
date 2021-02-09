#pragma once
#include "midi_event.h"
#include "enums.h"
#include "converter.h"

namespace BOSSCorp::Midi
{

class IMidiSink 
{
private:
    Channel _channel  = Channel::Channel1;
    bool    _omniMode = false;

protected:
    bool meantForMe(MidiEvent& event) const 
    {
        if(omniMode()) return true;

        switch(Converter::stripChannel(event.status()))
        {
            case Status::NoteOn:
            case Status::NoteOff:
            case Status::AfterTouch:
            case Status::ControlChange:
            case Status::ProgramChange:
            case Status::ChannelPressure:
            case Status::PitchBendChange:
                return Converter::toChannel(event.status()) == channel();
            default:
                return true;
        }
    }

    void omniMode(bool value) { _omniMode = value; }
public:
    explicit IMidiSink(Channel channel) : _channel(channel), _omniMode(false) {}

    bool    omniMode() const { return _omniMode; }
    Channel channel()  const { return _channel;  }
    virtual void receive(MidiEvent& event) = 0;
};

} //  BOSSCorp::Midi