﻿#ifndef TMIDITrackHeaderH
#define TMIDITrackHeaderH
//---------------------------------------------------------------------------
#include <windows.h>
//---------------------------------------------------------------------------
struct TMIDITrackHeader{
	unsigned char isEnabled;
	unsigned int length;
	unsigned char * data;
	unsigned char * pData;
	double tickDuration;
	double triggerTime;
	unsigned char lastCommand;
};
//---------------------------------------------------------------------------
#endif