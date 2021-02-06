#pragma once
#include "../buffer.h"
namespace BOSSCorp::Synthesis::Synthesizers
{

class ISynthesizer {
public:
    virtual void process(Buffer& buffer) = 0;
};

} // end BOSSCorp::Synthesis::Synthesizers