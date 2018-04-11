//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "BitListClass.h"
#include <cstring>
//---------------------------------------------------------------------------
BitListClass::BitListClass(int NewDataSize, const char *NewBitMask)
{
	DataSize = NewDataSize;
	BitCount = NewDataSize * 8;

	BitMask = new unsigned char[DataSize];
	std::memcpy(BitMask, NewBitMask, DataSize);

	BitData = new unsigned char[DataSize];
	std::memset(BitData, 0, DataSize);

	UndoBitData = new unsigned char[DataSize];
	std::memset(UndoBitData, 0, DataSize);

	RedoBitData = new unsigned char[DataSize];
	std::memset(RedoBitData, 0, DataSize);
}
//---------------------------------------------------------------------------
void BitListClass::Copy(const BitListClass &Source)
{
	DataSize = Source.DataSize;
	BitCount = Source.BitCount;

	BitMask = new unsigned char[DataSize];
	std::memcpy(BitMask, Source.BitMask, DataSize);

	BitData = new unsigned char[DataSize];
	std::memcpy(BitData, Source.BitData, DataSize);

	UndoBitData = new unsigned char[DataSize];
	std::memcpy(UndoBitData, Source.UndoBitData, DataSize);

	RedoBitData = new unsigned char[DataSize];
	std::memcpy(RedoBitData, Source.RedoBitData, DataSize);
}
//---------------------------------------------------------------------------
void BitListClass::Delete()
{
	delete[] BitMask;
	delete[] BitData;
	delete[] UndoBitData;
	delete[] RedoBitData;
}
//---------------------------------------------------------------------------
BitListClass::BitListClass(const BitListClass &Source)
{
	Copy(Source);
}
//---------------------------------------------------------------------------
BitListClass &BitListClass::operator=(const BitListClass &Source)
{
	Delete();
	Copy(Source);
	return *this;
}
//---------------------------------------------------------------------------
BitListClass::~BitListClass()
{
	Delete();
}
//---------------------------------------------------------------------------
bool BitListClass::AllPossible()
{
	int Index;

	for (Index = 0; Index < DataSize; Index++)
		if (BitData[Index] != BitMask[Index])
			return true;

	return false;
}
//---------------------------------------------------------------------------
bool BitListClass::All()
{
	std::memcpy(BitData, BitMask, DataSize);
	return true;
}
//---------------------------------------------------------------------------
bool BitListClass::NonePossible()
{
	int Index;

	for (Index = 0; Index < DataSize; Index++)
		if (BitData[Index] != 0)
			return true;

	return false;
}
//---------------------------------------------------------------------------
bool BitListClass::None()
{
	std::memset(BitData, 0, DataSize);
	return true;
}
//---------------------------------------------------------------------------
bool BitListClass::UpdateUndo()
{
	std::memcpy(UndoBitData, BitData, DataSize);
	std::memcpy(RedoBitData, BitData, DataSize);
	return true;
}
//---------------------------------------------------------------------------
bool BitListClass::UndoPossible()
{
	if (std::memcmp(BitData, UndoBitData, DataSize) == 0)
		return false;

	return true;
}
//---------------------------------------------------------------------------
bool BitListClass::Undo()
{
	std::memcpy(RedoBitData, BitData, DataSize);
	std::memcpy(BitData, UndoBitData, DataSize);
	return true;
}
//---------------------------------------------------------------------------
bool BitListClass::RedoPossible()
{
	if (std::memcmp(BitData, RedoBitData, DataSize) == 0)
		return false;

	return true;
}
//---------------------------------------------------------------------------
bool BitListClass::Redo()
{
	std::memcpy(UndoBitData, BitData, DataSize);
	std::memcpy(BitData, RedoBitData, DataSize);
	return true;
}
//---------------------------------------------------------------------------
