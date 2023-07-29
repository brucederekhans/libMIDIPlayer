//---------------------------------------------------------------------------

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
};
//---------------------------------------------------------------------------
#endif