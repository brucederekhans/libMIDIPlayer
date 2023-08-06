//---------------------------------------------------------------------------

#pragma hdrstop

#include "TMIDI.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
const char MThd[5] = "MThd";
//---------------------------------------------------------------------------
unsigned short readUShortFromMIDIFile(FILE * pMIDIFile)
{
	unsigned char hiByte = static_cast<unsigned char>(fgetc(pMIDIFile));
	unsigned char loByte = static_cast<unsigned char>(fgetc(pMIDIFile));
	return static_cast<unsigned short>(MAKEWORD(loByte, hiByte));
}
//---------------------------------------------------------------------------