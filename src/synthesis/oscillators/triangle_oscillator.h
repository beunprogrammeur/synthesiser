#pragma once
#include "sawtooth_oscillator.h"
#include "configurations/triangle_configuration.h"
namespace BOSSCorp::Synthesis::Oscillators
{

class TriangleOscillator : public SawToothOscillator
{
private:
    float polarity = 1;
    float previous = 0;

    const Configurations::TriangleConfiguration& config() const { return static_cast<const Configurations::TriangleConfiguration&>(_configuration); }

protected:
    virtual float next();
    virtual void configure(float frequency, float amplitude = 1, float phaseShift = 0);
public:
    explicit TriangleOscillator(const Configurations::TriangleConfiguration& config) : SawToothOscillator(config) {}
};

} // end BOSSCorp::Synthesis::Oscillators