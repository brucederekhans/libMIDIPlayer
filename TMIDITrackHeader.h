#ifndef TMIDITrackHeaderH
#define TMIDITrackHeaderH
//---------------------------------------------------------------------------
#include <windows.h>
//---------------------------------------------------------------------------
struct TMIDITrackHeader{
	unsigned char isEnabled;
	unsigned char isReadOnce;
	unsigned int length;
	unsigned char * data;
	unsigned char * pData;
	double tickDuration;
	double triggerTime;
	unsigned char lastCommand;
};
//---------------------------------------------------------------------------
unsigned int readVLQFromMIDITrackHeader(QMIDITrackHeader * pMIDITrackHeader);
//---------------------------------------------------------------------------
#endif