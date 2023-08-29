//---------------------------------------------------------------------------

#pragma hdrstop

#include "TMIDITrackHeader.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
unsigned int readVLQFromMIDITrackHeader(QMIDITrackHeader * pMIDITrackHeader)
{
	unsigned char * p = pMIDITrackHeader->pData;
	unsigned int vlq = *p;
	p++;

	if(vlq & 0x80)
	{
		vlq &= 0x7f;

		unsigned char nextByte;
		do
		{
			nextByte = *p;
			p++;
			vlq = (vlq << 7) + (nextByte & 0x7f);
		}while(nextByte & 0x80);
	}

	pMIDITrackHeader->pData = p;
	return vlq;
}
//---------------------------------------------------------------------------
unsigned char readByteFromMIDITrackHeader(QMIDITrackHeader * pMIDITrackHeader)
{
	unsigned char data = *(pMIDITrackHeader->pData);
	pMIDITrackHeader->pData++;
	return data;
}
//---------------------------------------------------------------------------
