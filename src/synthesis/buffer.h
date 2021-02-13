#pragma once
#include <stdint.h>


namespace BOSSCorp::Synthesis
{
// optional: make this Buffer<T> and have the synth use T too.
class Buffer
{
private:
    int16_t * _buffer;
    uint16_t   _size;
    uint32_t   _sampleRate;
    bool _isOwner = false;
public:
     Buffer() = delete;
     Buffer(const Buffer& buffer) = delete;
     Buffer(uint16_t size, uint32_t sampleRate) : _buffer(new int16_t[size]),_size(size), _sampleRate(sampleRate), _isOwner(true) { }
     Buffer(uint16_t size, uint32_t sampleRate, int16_t* datasource) : _buffer(datasource), _size(size), _sampleRate(sampleRate), _isOwner(false) { }
    ~Buffer()             { if(_isOwner) delete _buffer; }
    int16_t* data()       { return _buffer;              }
    uint32_t size()       { return _size;                }
    uint32_t sampleRate() { return _sampleRate;          }

    // operators
    int16_t  operator[](const uint16_t index) const { return _buffer[index]; }
};

} // end BOSSCorp::Synthesis