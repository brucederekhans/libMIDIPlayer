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
	double deltaTime;
	double triggerTime;
	unsigned char lastCommand;
};
//---------------------------------------------------------------------------
unsigned int readVLQFromMIDITrackHeader(QMIDITrackHeader * pMIDITrackHeader);
unsigned char readByteFromMIDITrackHeader(QMIDITrackHeader * pMIDITrackHeader);
//---------------------------------------------------------------------------
#endif