﻿//---------------------------------------------------------------------------

#ifndef TMIDIPlayingThreadH
#define TMIDIPlayingThreadH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include "TMIDI.h"
#include "TMIDITrackHeader.h"
//---------------------------------------------------------------------------
class TMIDIPlayingThread : public TThread
{
public:
	__fastcall TMIDIPlayingThread(char * pFilename, unsigned char AVolumePercentage, bool CreateSuspended);
	__fastcall ~TMIDIPlayingThread();
protected:
	void __fastcall Execute();
private:
	char filename[MAX_PATH];
	unsigned char volumePercentage;
	unsigned long long selectedOuputDeviceIndex;
	bool isSelectedOuputDeviceValid;
	bool isTrackHeadersValid;
};
//---------------------------------------------------------------------------
#define HI_NYBBLE(byte) (((byte) & 0xF0) >> 4)
#define LO_NYBBLE(byte) ((byte) & 0x0F)
//---------------------------------------------------------------------------
#endif