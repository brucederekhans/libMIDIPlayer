#ifndef TMIDIH
#define TMIDIH
//---------------------------------------------------------------------------
#include <windows.h>
#include <mmsystem.h>
//---------------------------------------------------------------------------
struct TMIDI{
	unsigned char isPlaying;
	unsigned char isPaused;
	unsigned char isStopRequested;
	unsigned short countTracks;
	unsigned short countTicks;
	unsigned int tempo;
	double tickLength;
	unsigned char channels[16][128];
	double currentTime;
};
//---------------------------------------------------------------------------
extern const char MThd[5];
//---------------------------------------------------------------------------
unsigned short readUShortFromMIDIFile(FILE * pMIDIFile);
unsigned int readUIntFromMIDIFile(FILE * pMIDIFile);
//---------------------------------------------------------------------------
#endif