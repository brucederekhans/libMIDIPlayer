﻿#ifndef TMIDIH
#define TMIDIH
//---------------------------------------------------------------------------
#include <stdio.h>
#include <windows.h>
#include <mmsystem.h>
//---------------------------------------------------------------------------
namespace TMIDI{
	struct TMIDI{
		unsigned short countTracks;
		unsigned short countTicks;
		unsigned int tempo;
		double tickLength;
		double currentTime;
	};
//---------------------------------------------------------------------------
	extern const char MThd[5];
	extern const char MTrk[5];
//---------------------------------------------------------------------------
	unsigned long long readUShortFromMIDIFile(unsigned short * pDst, FILE * pMIDIFile);
	unsigned long long readUIntFromMIDIFile(unsigned int * pDst, FILE * pMIDIFile);
	double getHighResolutionTime();
	void setNoteOnOff(unsigned char isOn, unsigned char note, unsigned char velocity, unsigned char velocityPercentage, unsigned char channelIndex, HMIDIOUT * pHMIDIOut);
	void setAllNotesOff(HMIDIOUT * pHMIDIOut);
}
//---------------------------------------------------------------------------
#define HI_NYBBLE(byte) (((byte) & 0xF0) >> 4)
#define LO_NYBBLE(byte) ((byte) & 0x0F)
#define MAKEBYTE(loNybble, hiNybble) (((hiNybble) << 4) | (loNybble))
//---------------------------------------------------------------------------
#endif