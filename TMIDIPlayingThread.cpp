﻿//---------------------------------------------------------------------------

#include <System.hpp>
#pragma hdrstop

#include "TMIDIPlayingThread.h"
#pragma package(smart_init)

//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(&UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall TMIDIPlayingThread::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------
__fastcall TMIDIPlayingThread::TMIDIPlayingThread(char * pFilename, unsigned char AVolumePercentage, bool CreateSuspended)
	: TThread(CreateSuspended),
	volumePercentage(AVolumePercentage),
	selectedOuputDeviceIndex(0),
	isSelectedOuputDeviceValid(false),
	isTrackHeadersValid(false)
{
	strcpy(this->filename, pFilename);
	unsigned long long i, countMIDIOutDevices = midiOutGetNumDevs();
	for(i = 0; i < countMIDIOutDevices; i++)
	{
		MIDIOUTCAPS midiOutCaps;
		if(midiOutGetDevCaps(i, &midiOutCaps, sizeof(MIDIOUTCAPS)) == MMSYSERR_NOERROR)
		{
			this->selectedOuputDeviceIndex = i;
			this->isSelectedOuputDeviceValid = true;
			break;
		}
	}
}
//---------------------------------------------------------------------------
__fastcall TMIDIPlayingThread::~TMIDIPlayingThread()
{
	//
}
//---------------------------------------------------------------------------
void __fastcall TMIDIPlayingThread::Execute()
{
	//---- Place thread code here ----
	memset(&this->midi, 0, sizeof(TMIDI));
}
//---------------------------------------------------------------------------