#pragma once
#include<functional>
#include<vector>

namespace BOSSCorp::Pattern
{

template <typename... Args>
class Observer
{
public:
    typedef std::function<void(Args...)> Callback;
    void subscribe(Callback subscriber) { _subscribers.emplace_back(subscriber);                        }
    void raise(Args... args)            { for(auto& subscriber : _subscribers) { subscriber(args...); } }

private:
    std::vector<Callback> _subscribers;
};

} //BOSSCorp::Pattern