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
	__fastcall TMIDIPlayingThread(bool CreateSuspended);
	__fastcall ~TMIDIPlayingThread();
protected:
	void __fastcall Execute();
};
//---------------------------------------------------------------------------
#endif