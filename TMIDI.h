#ifndef TMIDIH
#define TMIDIH
//---------------------------------------------------------------------------
#include <stdio.h>
#include <windows.h>
#include <mmsystem.h>
//---------------------------------------------------------------------------
struct TMIDI{
	unsigned short countTracks;
	unsigned short countTicks;
	unsigned int tempo;
	double tickLength;
	unsigned char channels[16][128];
	double currentTime;
};
//---------------------------------------------------------------------------
namespace MIDI{
	extern const char MThd[5];
	extern const char MTrk[5];
}
//---------------------------------------------------------------------------
#define HI_NYBBLE(byte) (((byte) & 0xF0) >> 4)
#define LO_NYBBLE(byte) ((byte) & 0x0F)
#define MAKEBYTE(loNybble, hiNybble) (((hiNybble) << 4) | (loNybble))
//---------------------------------------------------------------------------
unsigned long long readUShortFromMIDIFile(unsigned short * pDst, FILE * pMIDIFile);
unsigned long long readUIntFromMIDIFile(unsigned int * pDst, FILE * pMIDIFile);
double getHighResolutionTime();
void setNoteOnOff(unsigned char isOn, unsigned char note, unsigned char velocity, unsigned char velocityPercentage, unsigned char channelIndex, TMIDI * pMIDI, HMIDIOUT * pHMIDIOut);
void setAllNotesOff(TMIDI * pMIDI, HMIDIOUT * pHMIDIOut);
//---------------------------------------------------------------------------
#endif