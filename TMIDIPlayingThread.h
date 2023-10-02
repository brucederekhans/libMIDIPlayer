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
	void __fastcall setIsPaused(unsigned char AIsPaused);
protected:
	void __fastcall Execute();
private:
	char filename[MAX_PATH];
	unsigned char isPaused;
	unsigned char isStopRequested;
	unsigned char volumePercentage;
	unsigned long long selectedOuputDeviceIndex;
	bool isSelectedOuputDeviceValid;
};
//---------------------------------------------------------------------------
#endif