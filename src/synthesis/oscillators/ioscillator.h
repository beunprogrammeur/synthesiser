#pragma once

#include "../isteppable.h"

namespace BOSSCorp::Synthesis::Oscillators
{

    class IOscillator : public ISteppable
    {
        protected:
        float _frequency;
        float _amplitude;
        float _phaseShift;

        public:
        void configure(float frequency, float amplitude = 1, float phaseShift = 0) { _frequency = frequency; _amplitude = amplitude, _phaseShift = phaseShift; }
    };

}