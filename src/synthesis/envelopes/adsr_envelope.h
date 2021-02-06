#pragma once
#include "ienvelope.h"

namespace BOSSCorp::Synthesis::Envelopes
{

class ADSREnvelope : public IEnvelope
{
public:
    float attack;
    float decay;
    float sustain;
    float release;
};

} // end BOSSCorp::Synthesis::Envelopes