#include <gtest/gtest.h>
#include "midi/converter.h"
#include <cmath>
#include <iostream>
#include <string>
TEST(MIDIConverter, ConvertNoteToFrequency)
{
	// https://nl.wikipedia.org/wiki/Musical_Instrument_Digital_Interface

	using namespace BOSSCorp::MIDI;

	using value = std::tuple<float, Note, int>; // expected freq. , note, octave
	value values[] {
		value(440,    Note::A, 4),
		value(27.5,   Note::A, 0),
		value(261.63, Note::C, 4),
		value(3520,   Note::A, 7),
		value(1174.7, Note::D, 6),	
	};

	for(auto row : values)
	{
		float actual   = std::floor(Converter::toFrequency(std::get<1>(row), std::get<2>(row)));
		float expected = std::floor(std::get<0>(row));

		EXPECT_EQ(expected, actual);
	}
}

TEST(MIDIConverter, ConvertPitchToFrequency)
{
	using namespace BOSSCorp::MIDI;
	using value = std::tuple<float, uint8_t>; // expected freq. , midi pitch
	value values[] {
		value(27.5,   21),  // A0
		value(4186,   108), // C8
		value(440,    69),  // A4
		value(261.63, 60),  // C4
		value(174.61, 53),  // F3
	};

	for(auto row : values)
	{
		float actual   = std::floor(Converter::toFrequency(std::get<1>(row))); 
		float expected = std::floor(std::get<0>(row));

		EXPECT_EQ(expected, actual);
	}
}
