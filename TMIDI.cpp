﻿//---------------------------------------------------------------------------

#pragma hdrstop

#include "TMIDI.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
const char MThd[5] = "MThd";
//---------------------------------------------------------------------------
unsigned long long readUShortFromMIDIFile(unsigned short * pDst, FILE * pMIDIFile)
{
	unsigned char hiByte = static_cast<unsigned char>(fgetc(pMIDIFile));
	unsigned char loByte = static_cast<unsigned char>(fgetc(pMIDIFile));
	(*pDst) = static_cast<unsigned short>(MAKEWORD(loByte, hiByte));
	return 2;
}
//---------------------------------------------------------------------------
unsigned int readUIntFromMIDIFile(FILE * pMIDIFile)
{
	unsigned short hi2Bytes, lo2Bytes;
	readUShortFromMIDIFile(&hi2Bytes, pMIDIFile);
	readUShortFromMIDIFile(&lo2Bytes, pMIDIFile);
	return static_cast<unsigned int>((hi2Bytes << 16) + lo2Bytes);
}
//---------------------------------------------------------------------------