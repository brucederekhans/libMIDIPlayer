#ifndef TMIDITRACKHEADERH
#define TMIDITRACKHEADERH
//---------------------------------------------------------------------------
#include <windows.h>
//---------------------------------------------------------------------------
struct TMIDITrackHeader{
	unsigned char isEnabled;
	unsigned int length;
	unsigned char * data;
	unsigned char * pData;
	double triggerTime;
};
//---------------------------------------------------------------------------
#endif