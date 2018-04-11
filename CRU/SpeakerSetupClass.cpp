//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "SpeakerSetupClass.h"
#include <cstring>
//---------------------------------------------------------------------------
SpeakerSetupClass::SpeakerSetupClass() : BitListClass(3, "\xFF\x07\x00")
{
	BitData[0] = true;
	UndoBitData[0] = true;
	RedoBitData[0] = true;
}
//---------------------------------------------------------------------------
bool SpeakerSetupClass::Read(const unsigned char *Data, int MaxSize)
{
	int Type;
	int Size;
	int Index;

	if (!Data)
		return false;

	if (MaxSize < DataSize + 1)
		return false;

	Type = Data[0] >> 5;
	Size = Data[0] & 31;

	if (Type != 4)
		return false;

	if (Size < DataSize)
		return false;

	for (Index = 0; Index < DataSize; Index++)
		BitData[Index] = Data[Index + 1] & BitMask[Index];

	UpdateUndo();
	return true;
}
//---------------------------------------------------------------------------
bool SpeakerSetupClass::Write(unsigned char *Data, int MaxSize)
{
	if (!Data)
		return false;

	if (MaxSize < DataSize + 1)
		return false;

	std::memset(Data, 0, MaxSize);
	Data[0] = 4 << 5;
	Data[0] |= DataSize;
	std::memcpy(&Data[1], BitData, DataSize);
	return true;
}
//---------------------------------------------------------------------------
bool SpeakerSetupClass::Get(int Index)
{
	if (Index < 0 || Index >= BitCount)
		return false;

	return BitData[Index / 8] & (1 << Index % 8);
}
//---------------------------------------------------------------------------
bool SpeakerSetupClass::Set(int Index, bool Enabled)
{
	if (Index < 0 || Index >= BitCount)
		return false;

	if (Enabled)
		BitData[Index / 8] |= 1 << Index % 8;
	else
		BitData[Index / 8] &= ~(1 << Index % 8);

	return true;
}
//---------------------------------------------------------------------------
bool SpeakerSetupClass::Set20Possible()
{
	if (std::memcmp(BitData, "\x01\x00\x00", 3) == 0)
		return false;

	return true;
}
//---------------------------------------------------------------------------
bool SpeakerSetupClass::Set20()
{
	std::memcpy(BitData, "\x01\x00\x00", 3);
	return true;
}
//---------------------------------------------------------------------------
bool SpeakerSetupClass::Set51Possible()
{
	if (std::memcmp(BitData, "\x0F\x00\x00", 3) == 0)
		return false;

	return true;
}
//---------------------------------------------------------------------------
bool SpeakerSetupClass::Set51()
{
	std::memcpy(BitData, "\x0F\x00\x00", 3);
	return true;
}
//---------------------------------------------------------------------------
bool SpeakerSetupClass::Set71Possible()
{
	if (std::memcmp(BitData, "\x4F\x00\x00", 3) == 0)
		return false;

	return true;
}
//---------------------------------------------------------------------------
bool SpeakerSetupClass::Set71()
{
	std::memcpy(BitData, "\x4F\x00\x00", 3);
	return true;
}
//---------------------------------------------------------------------------
