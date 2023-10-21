#ifndef TMIDITrackHeaderH
#define TMIDITrackHeaderH
//---------------------------------------------------------------------------
#include <windows.h>
//---------------------------------------------------------------------------
namespace TMIDI{
	struct TMIDITrackHeader{
		unsigned char isEnabled;
		unsigned char isReadOnce;
		unsigned int length;
		unsigned char * data;
		unsigned char * pData;
		double deltaTime;
		double triggerTime;
		unsigned char lastCommand;
	};
//---------------------------------------------------------------------------
	unsigned int readVLQFromMIDITrackHeader(TMIDITrackHeader * pMIDITrackHeader);
	unsigned char readByteFromMIDITrackHeader(TMIDITrackHeader * pMIDITrackHeader);
	unsigned short readUShortFromMIDITrackHeader(TMIDITrackHeader * pMIDITrackHeader);
}
//---------------------------------------------------------------------------
#endif