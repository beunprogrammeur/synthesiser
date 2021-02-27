#pragma once

#include "../isteppable.h"
#include "configurations/ioscillator_configuration.h"
#include "../../midi/converter.h"

namespace BOSSCorp::Synthesis::Oscillators
{

class IOscillator : public ISteppable
{
private:
    float _frequency     = 0.0f;
    float _amplitude     = 0.0f;
    float _shiftTime     = 0.0f;
    float _waveTime      = 0.0f;
    float _oldPitchBend  = 0.0f;
    float _oldPhaseShift = 0.0f;
    Midi::Note _note     = Midi::Note::A;
    int8_t     _octave   = 0;

    void updateInternals(bool force = false)
    {
        if(force || _configuration.pitchBend != _oldPitchBend)
        {
            frequency(Midi::Converter::toFrequency(_note, _octave, _configuration.pitchBend));
            
            _waveTime     = 1.0f / _frequency;
            _oldPitchBend = _configuration.pitchBend;
        }

        if(force || _configuration.phaseShift != _oldPhaseShift)
        {
            _shiftTime     = _waveTime * _configuration.phaseShift;
            _oldPhaseShift = _configuration.phaseShift;
        }
    }
protected:
    const Configurations::IOscillatorConfiguration& _configuration;
    void wavetime(float value) { _waveTime = value; } // is reset when configure is called
public:
    IOscillator(const Configurations::IOscillatorConfiguration& configuration) : _configuration(configuration) { }
    virtual void configure(Midi::Note note, int8_t octave, float amplitude = 1) { _note = note; _octave = octave;  _amplitude = amplitude; updateInternals(true); }
    virtual void reset()    { time(_shiftTime); ISteppable::reset(); }
    float frequency() const { return _frequency; }
    virtual void frequency(float value) { _frequency = value; _waveTime = 1.0f / value; } // overriden by triangle oscillator to double the frequency, also for testing
    float amplitude() const { return _amplitude * _configuration.amplitude; }
    float wavetime()  const { return _waveTime;  }
    virtual float next(float deltaTime) { updateInternals(); return ISteppable::next(deltaTime); }
};

}
