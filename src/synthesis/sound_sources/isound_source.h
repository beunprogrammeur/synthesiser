#pragma once
#include "../isteppable.h"
#include "../envelopes/ienvelope.h"

namespace BOSSCorp::Synthesis::SoundSources
{

class ISoundSource : public ISteppable
{
private:
    Envelopes::IEnvelope& _envelope;
};

} // end BOSSCorp::Synthesis::SoundSources