//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "AudioFormatListClass.h"
#include "AudioFormatClass.h"
#include <cstring>
//---------------------------------------------------------------------------
AudioFormatListClass::AudioFormatListClass(int Slots) : ListClass(Slots, 3)
{
}
//---------------------------------------------------------------------------
bool AudioFormatListClass::Read(const unsigned char *Data, int MaxSize)
{
	int Type;
	int Size;
	int Slots;
	int Slot;
	AudioFormatClass AudioFormat;

	if (!Data)
		return false;

	Type = Data[0] >> 5;
	Size = Data[0] & 31;

	if (Type != 1)
		return false;

	DeleteAll();

	if (!SetMaxSize(MaxSize - 1))
		return false;

	Slots = Size / SlotSize;

	for (Slot = 0; Slot < Slots && SlotCount < MaxSlotCount; Slot++)
	{
		if (!AudioFormat.Read(&Data[Slot * SlotSize + 1], SlotSize))
			continue;

		if (!AudioFormat.Write(&SlotData[SlotCount * SlotSize], SlotSize))
			continue;

		SlotCount++;
	}

	UpdateSize();
	UpdateUndo();
	return true;
}
//---------------------------------------------------------------------------
bool AudioFormatListClass::Write(unsigned char *Data, int MaxSize)
{
	if (!Data)
		return false;

	if (MaxSize < DataSize + 1)
		return false;

	std::memset(Data, 0, MaxSize);
	Data[0] = 1 << 5;
	Data[0] |= DataSize;
	std::memcpy(&Data[1], SlotData, DataSize);
	return true;
}
//---------------------------------------------------------------------------
