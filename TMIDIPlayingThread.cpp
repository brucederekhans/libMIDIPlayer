//---------------------------------------------------------------------------

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
	if(this->isSelectedOuputDeviceValid)
	{
		FILE * pMIDIFile;
		fopen_s(&pMIDIFile, this->filename, "rb");
		if(pMIDIFile != nullptr)
		{
			try
			{
				TMIDI midi;
				memset(&midi, 0, sizeof(TMIDI));
				unsigned char t4Bytes[4];
				if(fread(t4Bytes, 1, 4, pMIDIFile) != 4)
				{
					throw -1;
				}

				if(memcmp(t4Bytes, MThd, 4))
				{
					throw -2;
				}

				if(fseek(pMIDIFile, 6, SEEK_CUR) != 0)
				{
					throw -3;
				}

				if(readUShortFromMIDIFile(&midi.countTracks, pMIDIFile) != 2)
				{
					throw -4;
				}

				if(readUShortFromMIDIFile(&midi.countTicks, pMIDIFile) != 2)
				{
					throw -5;
				}

				fclose(pMIDIFile);
			}
			catch(int errCode)
			{
				fclose(pMIDIFile);
			}
		}
	}
}
//---------------------------------------------------------------------------