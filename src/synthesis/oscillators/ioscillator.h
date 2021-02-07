#pragma once

#include "../isteppable.h"

namespace BOSSCorp::Synthesis::Oscillators
{

    class IOscillator : public ISteppable
    {
        private:
        float _shiftTime = 0;
        protected:
        float _frequency;
        float _amplitude;
        

        public:
        virtual void configure(float frequency, float amplitude = 1, float phaseShift = 0) { _frequency = frequency; _amplitude = amplitude, _shiftTime = (1.0 / frequency * phaseShift); }
        virtual void reset() { setTime(_shiftTime); }
        float frequency() const { return _frequency; }
    };

}