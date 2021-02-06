#pragma once

namespace BOSSCorp::Synthesis
{
class ISteppable
{
private:
    float _time;
protected:
    virtual void next() = 0;
    float time() const         { return _time;               }
public:
    void next(float deltaTime) { _time += deltaTime; next(); }
    virtual void reset()       { _time  = 0;                 }
};
}