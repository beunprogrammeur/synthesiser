#pragma once
#include "ioscillator.h"

namespace BOSSCorp::Synthesis::Oscillators
{

class SawToothOscillator : public IOscillator
{
protected:
    virtual float next();
};

} // end BOSSCorp::Synthesis::Oscillators