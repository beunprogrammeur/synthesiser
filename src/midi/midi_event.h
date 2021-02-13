#pragma once
#include <stdint.h>
#include "enums.h"
namespace BOSSCorp::Midi
{

struct MidiEvent 
{
private:
    const Status _status;
    const uint8_t _data1;
    const uint8_t _data2;
public:
    MidiEvent(Status status, uint8_t data1, uint8_t data2) : _status(status), _data1(data1), _data2(data2) { }
    Status  status() const { return _status; }
    uint8_t data1()  const { return _data1;  }
    uint8_t data2()  const { return _data2;  }
};

} // end BOSSCorp::Midi