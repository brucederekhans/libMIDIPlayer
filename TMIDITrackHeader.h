#ifndef TMIDITRACKHEADERH
#define TMIDITRACKHEADERH
//---------------------------------------------------------------------------
#include <windows.h>
//---------------------------------------------------------------------------
struct TMIDITrackHeader{
	unsigned int length;
	unsigned char * data;
	unsigned char * pData;
};
//---------------------------------------------------------------------------
#endif