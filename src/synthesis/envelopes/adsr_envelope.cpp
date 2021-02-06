#include "adsr_envelope.h"

namespace BOSSCorp::Synthesis::Envelopes
{

float ADSREnvelope::next()
{
    auto t = time();
    float output = 0;

    if(t < _configuration.attack)
    {
        output = 1.0 / _configuration.attack * t;
    }
    else if(t < _configuration.attack + _configuration.decay)
    {
        t -= _configuration.attack;
        output = 1.0 - ((1.0 - _configuration.sustain) / _configuration.decay * t);
    } 
    else if(!_released)
    {
        output = _configuration.sustain;
    }
    else
    {
        t -= _releaseTimestamp;
        output = _configuration.sustain - (_configuration.sustain / _configuration.release * t);    

        if(output < 0) 
        {
            output = 0;
            finish();
        }
    }
    
    return output;    
}

} // end BOSSCorp::Synthesis::Envelopes
