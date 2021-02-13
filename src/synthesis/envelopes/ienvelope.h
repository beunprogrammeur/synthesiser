#pragma once

#include "../isteppable.h"

namespace BOSSCorp::Synthesis::Envelopes
{

class IEnvelope : public ISteppable
{
private:
    bool _finished = false;
protected:
    void finish() { _finished = true; }
public:
    bool finished() const { return _finished; }
    virtual void reset() { ISteppable::reset(); _finished = false; }
}; 

} // end BOSSCorp::Synthesis::Envelopes
