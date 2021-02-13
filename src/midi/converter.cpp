#include "converter.h"
#include <cmath>
namespace BOSSCorp::Midi 
{

float Converter::toFrequency(Note note, int8_t octave)
{
	constexpr float ratio = 1.059463094359; // pow(2.0, 1.0/12.0);
	constexpr float baseNote = 440;         // note A4
	octave -= 4; // compensate for starting at A4

	uint8_t notenum = static_cast<uint8_t>(note);

	if(notenum > 2) octave -= 1;

	return baseNote * pow(ratio, (notenum + (octave * 12))); 
}

float Converter::toFrequency(int8_t midiPitch)
{
	Note    note   = Note::A;
	int8_t octave = 0;

	toNote(midiPitch, note, octave);
	return toFrequency(note, octave);
}

void Converter::toNote(int midiPitch, Note& note, int8_t& octave)
{
    constexpr int A0 = 21;
	midiPitch  -= A0;

	note   = static_cast<Note>(midiPitch % 12);
    octave = midiPitch / 12;
	if (note > Note::B) octave++;
}

Channel Converter::toChannel(Status status)
{
	return static_cast<Channel>(static_cast<uint8_t>(status) & 0x0f);
}

Status Converter::stripChannel(Status status)
{
	return static_cast<Status>(static_cast<uint8_t>(status) & 0xf0);
}


} // end BOSSCorp::MIDI