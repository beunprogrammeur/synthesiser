#pragma once
#include <stdint.h>

namespace BOSSCorp::MIDI 
{

enum class Note : uint8_t 
{
	A      = 0,
	ASharp = 1,
	BFlat  = 1,
	B      = 2,
	CFlat  = 2,
	BSharp = 3,
	C      = 3,
	CSharp = 4,
	DFlat  = 4,
	D      = 5,
	DSharp = 6,
	EFlat  = 6,
	E      = 7,
	FFlat  = 7,
	ESharp = 8,
	F      = 8,
	FSharp = 9,
	GFlat  = 9,
	G      = 10,
	GSharp = 11,
};

} // BOSSCorp::MIDI end