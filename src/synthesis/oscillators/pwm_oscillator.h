#pragma once
#include "ioscillator.h"

namespace BOSSCorp::Synthesis::Oscillators
{

class PWMOscillator : public IOscillator
{
public:
    void process();
};


} // end BOSSCorp::Synthesis
