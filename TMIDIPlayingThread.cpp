//---------------------------------------------------------------------------

#include <System.hpp>
#pragma hdrstop

#include "TMIDIPlayingThread.h"
#pragma package(smart_init)

//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(&UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall TMIDIPlayingThread::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------
__fastcall TMIDIPlayingThread::TMIDIPlayingThread(char * pFilename, unsigned char AVolumePercentage, bool CreateSuspended)
	: TThread(CreateSuspended),
	volumePercentage(AVolumePercentage),
	selectedOuputDeviceIndex(0),
	isSelectedOuputDeviceValid(false),
	isTrackHeadersValid(false)
{
	strcpy(this->filename, pFilename);
	unsigned long long i, countMIDIOutDevices = midiOutGetNumDevs();
	for(i = 0; i < countMIDIOutDevices; i++)
	{
		MIDIOUTCAPS midiOutCaps;
		if(midiOutGetDevCaps(i, &midiOutCaps, sizeof(MIDIOUTCAPS)) == MMSYSERR_NOERROR)
		{
			this->selectedOuputDeviceIndex = i;
			this->isSelectedOuputDeviceValid = true;
			break;
		}
	}
}
//---------------------------------------------------------------------------
__fastcall TMIDIPlayingThread::~TMIDIPlayingThread()
{
	//
}
//---------------------------------------------------------------------------
void __fastcall TMIDIPlayingThread::Execute()
{
	//---- Place thread code here ----
	if(this->isSelectedOuputDeviceValid)
	{
		FILE * pMIDIFile;
		fopen_s(&pMIDIFile, this->filename, "rb");
		if(pMIDIFile != nullptr)
		{
			TMIDI midi;
			memset(&midi, 0, sizeof(TMIDI));
			TMIDITrackHeader * midiTrackHeaders;
			try
			{
				unsigned char t4Bytes[4];
				if(fread(t4Bytes, 1, 4, pMIDIFile) != 4)
				{
					throw -1;
				}

				if(memcmp(t4Bytes, MThd, 4))
				{
					throw -2;
				}

				if(fseek(pMIDIFile, 6, SEEK_CUR) != 0)
				{
					throw -3;
				}

				if(readUShortFromMIDIFile(&midi.countTracks, pMIDIFile) != 2)
				{
					throw -4;
				}

				if(readUShortFromMIDIFile(&midi.countTicks, pMIDIFile) != 2)
				{
					throw -5;
				}

				midiTrackHeaders = new TMIDITrackHeader[midi.countTracks];
				try
				{
					unsigned short iTrack = 0;
					while(!feof(pMIDIFile))
					{
						unsigned char t4Bytes[4];
						if(fread(t4Bytes, 1, 4, pMIDIFile) == 4)
						{
							if(memcmp(t4Bytes, MTrk, 4))
							{
								throw -6;
							}

							midiTrackHeaders[iTrack].isEnabled = 1;
							midiTrackHeaders[iTrack].isReadOnce = 0;

							if(readUIntFromMIDIFile(midiTrackHeaders[iTrack].length, pMIDIFile) != 4)
							{
								throw -7;
							}

							midiTrackHeaders[iTrack].data = new unsigned char[midiTrackHeaders[iTrack].length];

							if(fread(midiTrackHeaders[iTrack].data, 1, midiTrackHeaders[iTrack].length, pMIDIFile) != midiTrackHeaders[iTrack].length)
							{
								throw -8;
							}

							midiTrackHeaders[iTrack].pData = midiTrackHeaders[iTrack].data;
							midiTrackHeaders[iTrack].deltaTime = 0;
							midiTrackHeaders[iTrack].triggerTime = 0;
							midiTrackHeaders[iTrack].lastCommand = 0;

							iTrack++;
						}
					}
					this->isTrackHeadersValid = true;
					midi.countTracks = iTrack;
				}
				catch(int errCode)
				{
					delete []midiTrackHeaders;
				}

				fclose(pMIDIFile);

				HMIDIOUT hMIDIOut;
				if(midiOutOpen(&hMIDIOut, static_cast<unsigned int>(this->selectedOuputDeviceIndex), 0, 0, 0) == MMSYSERR_NOERROR)
				{
					midi.isPlaying = 1;
					midi.tempo = 1000;
					midi.tickLength = midi.tempo * 1.0 / midi.countTicks;

					midi.currentTime = getHighResolutionTime();

					double tCurrentTime;
					while(!midi.isStopRequested)
					{
						tCurrentTime = getHighResolutionTime();
						double nextTriggerTime = tCurrentTime + 1000;
						unsigned char isAnyTrackEnabled = 0;
						unsigned short iTrack;
						for(iTrack = 0; iTrack < midi.countTracks; iTrack++)
						{
							if(midiTrackHeaders[iTrack].isEnabled)
							{
								isAnyTrackEnabled = 1;
								if(midiTrackHeaders[iTrack].pData < (midiTrackHeaders[iTrack].data + midiTrackHeaders[iTrack].length))
								{
									if(midiTrackHeaders[iTrack].isReadOnce)
									{
										midiTrackHeaders[iTrack].isReadOnce = 0;
										midiTrackHeaders[iTrack].deltaTime = readVLQFromMIDITrackHeader(&midiTrackHeaders[iTrack]) * midi.tickLength;
										midiTrackHeaders[iTrack].triggerTime = tCurrentTime + midiTrackHeaders[iTrack].deltaTime;
									}

									while(tCurrentTime >= midiTrackHeaders[iTrack].triggerTime)
									{
										midi.currentTime = tCurrentTime;

										unsigned char command = readByteFromMIDITrackHeader(&midiTrackHeaders[iTrack]);
										if(command < 128)
										{
											midiTrackHeaders[iTrack].pData--;
											command = midiTrackHeaders[iTrack].lastCommand;
										}
										else
										{
											midiTrackHeaders[iTrack].lastCommand = command;
										}

										if(command == 0xFF)
										{
											command = readByteFromMIDITrackHeader(&midiTrackHeaders[iTrack]);
											unsigned int tLength = readVLQFromMIDITrackHeader(&midiTrackHeaders[iTrack]);
											if(tLength <= (midiTrackHeaders[iTrack].pData - midiTrackHeaders[iTrack].data + midiTrackHeaders[iTrack].length))
											{
												if(command == 0x0)
												{
													midiTrackHeaders[iTrack].pData += 2;
												}
												else if(command <= 0x07)
												{
													midiTrackHeaders[iTrack].pData += tLength;
												}
												else if(command == 0x20)
												{
													midiTrackHeaders[iTrack].pData++;
												}
												else if(command == 0x21)
												{
													midiTrackHeaders[iTrack].pData++;
												}
												else if(command == 0x2F)
												{
													midiTrackHeaders[iTrack].isEnabled = 0;
												}
												else if(command == 0x51)
												{
													unsigned char t3Bytes[3];
													memcpy(t3Bytes, midiTrackHeaders[iTrack].pData, 3);
													midiTrackHeaders[iTrack].pData += 3;
													double newTempo = ((t3Bytes[0] << 16) + (t3Bytes[1] << 8) + t3Bytes[2]) / 1000;
													double orgTickLength = midi.tickLength;
													midi.tickLength = newTempo / midi.countTicks;

													unsigned short jTrack;
													for(jTrack = 0; jTrack < midi.countTracks; jTrack++)
													{
														if(midiTrackHeaders[jTrack].isEnabled)
														{
															midiTrackHeaders[jTrack].deltaTime = (midiTrackHeaders[jTrack].triggerTime - midi.currentTime) / orgTickLength * midi.tickLength;
															midiTrackHeaders[jTrack].triggerTime = midi.currentTime + midiTrackHeaders[jTrack].deltaTime;
														}
													}
												}
												else if(command == 0x54)
												{
													midiTrackHeaders[iTrack].pData += 5;
												}
												else if(command == 0x58)
												{
													midiTrackHeaders[iTrack].pData += 4;
												}
												else if(command == 0x59)
												{
													midiTrackHeaders[iTrack].pData += 2;
												}
												else if(command == 0x7F)
												{
													midiTrackHeaders[iTrack].pData += tLength;
												}
												else
												{
													midiTrackHeaders[iTrack].pData += tLength;
												}
											}
										}
										else
										{
											unsigned char hiNybble = HI_NYBBLE(command);
											unsigned char loNybble = LO_NYBBLE(command);
											if(hiNybble == 0x08)
											{
												unsigned char key = readByteFromMIDITrackHeader(midiTrackHeaders[iTrack]);
												unsigned char velocity = readByteFromMIDITrackHeader(midiTrackHeaders[iTrack]);
												setNoteOnOff(0, key, velocity, this->volumePercentage, loNybble, &midi, &hMIDIOut);
											}
											else if(hiNybble == 0x09)
											{
												unsigned char key = readByteFromMIDITrackHeader(midiTrackHeaders[iTrack]);
												unsigned char velocity = readByteFromMIDITrackHeader(midiTrackHeaders[iTrack]);
												setNoteOnOff(1, key, velocity, this->volumePercentage, loNybble, &midi, &hMIDIOut);
											}
											else if(hiNybble == 0x0A)
											{
												unsigned char key = readByteFromMIDITrackHeader(midiTrackHeaders[iTrack]);
												unsigned char touch = readByteFromMIDITrackHeader(midiTrackHeaders[iTrack]);
												midiOutShortMsg(hMIDIOut, static_cast<DWORD>(MAKELONG(MAKEWORD(command, key), MAKEWORD(touch, 0))));
											}
										}
									}
								}
								else
								{
									midiTrackHeaders[iTrack].isEnabled = 0;
								}
							}
						}
					}
				}
			}
			catch(int errCode)
			{
				fclose(pMIDIFile);
			}
		}
	}
}
//---------------------------------------------------------------------------