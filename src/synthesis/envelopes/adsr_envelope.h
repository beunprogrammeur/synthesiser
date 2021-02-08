#pragma once
#include "ienvelope.h"
#include "adsr_configuration.h"
namespace BOSSCorp::Synthesis::Envelopes
{

class ADSREnvelope : public IEnvelope
{
private:
    ADSRConfiguration& _configuration;
    bool  _released;
    float _releaseTimestamp;

protected:
    virtual float next();
public:
    explicit ADSREnvelope(ADSRConfiguration& configuration) : _configuration(configuration), _releaseTimestamp(0){ }
    void release() { _released = true; _releaseTimestamp = time(); }
    virtual void reset() {_released = false; _releaseTimestamp = 0; IEnvelope::reset(); }
};

} // end BOSSCorp::Synthesis::Envelopes