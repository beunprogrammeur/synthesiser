#pragma once

namespace BOSSCorp::Synthesis
{
class ISteppable
{
private:
    float _time;
   
protected:
    ISteppable() : _time(0.0f)  {               }
    float time() const          { return _time; }
    void time(float time)       { _time = time; }
    virtual float next() = 0;
public:
    virtual float next(float deltaTime) { _time += deltaTime; return next(); }
    virtual void reset()        { _time  = 0;   }
};
}