#pragma once
#include "ioscillator.h"
#include "configurations/triangle_configuration.h"
namespace BOSSCorp::Synthesis::Oscillators
{

class TriangleOscillator : public IOscillator
{
private:
    float polarity = 1;
    float previous = 0;

    const Configurations::TriangleConfiguration& config() const { return static_cast<const Configurations::TriangleConfiguration&>(_configuration); }

protected:
    virtual float next();
    virtual void frequency(float value) { IOscillator::frequency(value * 2.0f); }
public:
    explicit TriangleOscillator(const Configurations::TriangleConfiguration& config) : IOscillator(config) {}
};

} // end BOSSCorp::Synthesis::Oscillators