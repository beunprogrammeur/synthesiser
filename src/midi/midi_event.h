#pragma once
#include <stdint.h>

namespace BOSSCorp::Midi
{

struct MidiEvent 
{
public:
    uint8_t status;
    uint8_t data1;
    uint8_t data2;
};

} // end BOSSCorp::Midi