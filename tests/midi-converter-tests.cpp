#include <gtest/gtest.h>
#include "midi/converter.h"
#include <cmath>

using namespace BOSSCorp::Midi;

struct value
{
	float freq;
	BOSSCorp::Midi::Note note;
	int octave;
	int pitch;
	float bend;

	static value fromPitch(float f, int p, float b = 0.0f)        { return value {.freq = f, .note = BOSSCorp::Midi::Note::A, .octave = 0, .pitch = p, .bend = b}; }
	static value fromNote(float f, Note n, int o, float b = 0.0f) { return value {.freq = f, .note = n, .octave = o, .bend = b}; }
};

TEST(MidiConverter, ConvertNoteToFrequency)
{
	// https://nl.wikipedia.org/wiki/Musical_Instrument_Digital_Interface

	
	value values[] {
		value::fromNote(440,    Note::A, 4),
		value::fromNote(27.5,   Note::A, 0),
		value::fromNote(261.63, Note::C, 4),
		value::fromNote(3520,   Note::A, 7),
		value::fromNote(1174.7, Note::D, 6),	
	};
	
	for(auto row : values)
	{
		float actual   = std::floor(Converter::toFrequency(row.note, row.octave));
		float expected = std::floor(row.freq);

		EXPECT_EQ(expected, actual);
	}
}

TEST(MidiConverter, ConvertPitchToFrequency)
{
	using namespace BOSSCorp::Midi;

	value values[] {
		value::fromPitch(27.5,   21),  // A0
		value::fromPitch(4186,   108), // C8
		value::fromPitch(440,    69),  // A4
		value::fromPitch(261.63, 60),  // C4
		value::fromPitch(174.61, 53),  // F3
	};

	for(auto row : values)
	{
		float actual   = std::floor(Converter::toFrequency(row.pitch));
		float expected = std::floor(row.freq);

		EXPECT_EQ(expected, actual);
	}
}

TEST(MidiConverter, ConvertPitchWithBending)
{
	using namespace BOSSCorp::Midi;
		value values[] {
		value::fromPitch(27.5,   21),  // A0
		value::fromPitch(4186,   108), // C8
		value::fromPitch(440,    69),  // A4
		value::fromPitch(261.63, 60),  // C4
		value::fromPitch(174.61, 53),  // F3
	};

	for(auto row : values)
	{
		float actual   = std::floor(Converter::toFrequency(row.pitch, row.bend));
		float expected = std::floor(row.freq);

		EXPECT_EQ(expected, actual);
	}
}

TEST(MidiConverter, ConvertNoteWithBending)
{
	using namespace BOSSCorp::Midi;
	value values[] {
		value::fromNote(440,    Note::B, 4, -2.0f),
		value::fromNote(27.5,   Note::A, 0,  0.0f),
		value::fromNote(261.63, Note::B, 3,  1.0f),
		value::fromNote(3520,   Note::C, 8, -3.0f),
		value::fromNote(1174.7, Note::C, 6,  2.0f),	
	};

	for(auto row : values)
	{
		float actual   = std::floor(Converter::toFrequency(row.note, row.octave, row.bend));
		float expected = std::floor(row.freq);

		EXPECT_EQ(expected, actual);
	}
}
