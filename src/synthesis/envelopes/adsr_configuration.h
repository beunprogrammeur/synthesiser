#pragma once

namespace BOSSCorp::Synthesis::Envelopes
{

struct ADSRConfiguration
{
    float attack;  // time in ms
    float decay;   // time in ms
    float sustain; // amplitude in 0.0-1.0
    float release; // time in ms
};

} // end BOSSCorp::Synthesis::Envelopes