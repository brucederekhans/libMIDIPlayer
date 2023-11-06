//---------------------------------------------------------------------------

#ifndef TMIDIPlayingThreadH
#define TMIDIPlayingThreadH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <algorithm>
#include "TMIDI.h"
#include "TMIDITrackHeader.h"
//---------------------------------------------------------------------------
namespace TMIDI{
	class TMIDIPlayingThread : public TThread
	{
	public:
		__fastcall TMIDIPlayingThread(const wchar_t * pFilename, unsigned char AVolumePercentage, unsigned char AIsLoop, TNotifyEvent AOnTerminate);
		__fastcall ~TMIDIPlayingThread();
		unsigned char __fastcall getIsLoop();
		void __fastcall setIsLoop(unsigned char AIsLoop);
		unsigned char __fastcall getIsPaused();
		void __fastcall setIsPaused(unsigned char AIsPaused);
		unsigned char __fastcall getIsStopRequested();
		void __fastcall setIsStopRequested(unsigned char AIsStopRequested);
		unsigned char __fastcall getVolumePercentage();
		void __fastcall setVolumePercentage(unsigned char AVolumePercentage);
		unsigned long long __fastcall getSelectedOuputDeviceIndex();
	protected:
		void __fastcall Execute();
	private:
		wchar_t filename[MAX_PATH];
		unsigned char isLoop;
		unsigned char isPaused;
		unsigned char isStopRequested;
		unsigned char volumePercentage;
		unsigned long long selectedOuputDeviceIndex;
		bool isSelectedOuputDeviceValid;
	};
}
//---------------------------------------------------------------------------
#endif