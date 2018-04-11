//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "EstablishedResolutionListClass.h"
#include <cstring>
//---------------------------------------------------------------------------
EstablishedResolutionListClass::EstablishedResolutionListClass() : BitListClass(3, "\x2F\xCF\x00")
{
}
//---------------------------------------------------------------------------
bool EstablishedResolutionListClass::Read(const unsigned char *Data, int MaxSize)
{
	int Index;

	if (!Data)
		return false;

	if (MaxSize < DataSize)
		return false;

	for (Index = 0; Index < DataSize; Index++)
		BitData[Index] = Data[Index] & BitMask[Index];

	return true;
}
//---------------------------------------------------------------------------
bool EstablishedResolutionListClass::Write(unsigned char *Data, int MaxSize)
{
	if (!Data)
		return false;

	if (MaxSize < DataSize)
		return false;

	std::memcpy(Data, BitData, DataSize);
	return true;
}
//---------------------------------------------------------------------------
bool EstablishedResolutionListClass::Get(int Index)
{
	if (Index < 0 || Index >= BitCount)
		return false;

	return BitData[Index / 8] & (128 >> Index % 8);
}
//---------------------------------------------------------------------------
bool EstablishedResolutionListClass::Set(int Index, bool Enabled)
{
	if (Index < 0 || Index >= BitCount)
		return false;

	if (Enabled)
		BitData[Index / 8] |= 128 >> Index % 8;
	else
		BitData[Index / 8] &= ~(128 >> Index % 8);

	return true;
}
//---------------------------------------------------------------------------
