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
}; 

} // end BOSSCorp::Synthesis::Envelopes