#ifndef TMIDIH
#define TMIDIH
//---------------------------------------------------------------------------
#include <windows.h>
#include <mmsystem.h>
//---------------------------------------------------------------------------
struct TMIDI{
	unsigned char isPlaying;
	unsigned short countTracks;
	unsigned short countTicks;
	unsigned int tempo;
};
//---------------------------------------------------------------------------
#endif