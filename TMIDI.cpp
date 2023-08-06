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
unsigned int readUIntFromMIDIFile(FILE * pMIDIFile)
{
	unsigned short hi2Bytes = readUShortFromMIDIFile(pMIDIFile);
	unsigned short lo2Bytes = readUShortFromMIDIFile(pMIDIFile);
	return static_cast<unsigned int>((hi2Bytes << 16) + lo2Bytes);
}
//---------------------------------------------------------------------------