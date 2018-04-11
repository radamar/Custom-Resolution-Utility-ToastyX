//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "StandardResolutionListClass.h"
#include "StandardResolutionClass.h"
#include <cstring>
//---------------------------------------------------------------------------
StandardResolutionListClass::StandardResolutionListClass(int Slots) : ListClass(Slots, 2)
{
}
//---------------------------------------------------------------------------
bool StandardResolutionListClass::Read(const unsigned char *Data, int MaxSize)
{
	int Slot;
	StandardResolutionClass StandardResolution;
	int Block;
	const unsigned char *Byte;

	if (!Data)
		return false;

	DeleteAll();

	if (!SetMaxSize(MaxSize))
		return false;

	for (Slot = 0; Slot < 8 && SlotCount < MaxSlotCount; Slot++)
	{
		if (!StandardResolution.Read(&Data[Slot * SlotSize], SlotSize))
			continue;

		if (!StandardResolution.Write(&SlotData[SlotCount * SlotSize], SlotSize))
			continue;

		SlotCount++;
	}

	for (Block = 0; Block < 4 && SlotCount < MaxSlotCount; Block++)
	{
		Byte = &Data[Block * 18 + 16];

		if (std::memcmp(Byte, "\x00\x00\x00\xFA\x00", 5) == 0)
		{
			for (Slot = 0; Slot < 6 && SlotCount < MaxSlotCount; Slot++)
			{
				if (!StandardResolution.Read(&Byte[Slot * SlotSize + 5], SlotSize))
					continue;

				if (!StandardResolution.Write(&SlotData[SlotCount * SlotSize], SlotSize))
					continue;

				SlotCount++;
			}
		}
	}

	UpdateSize();
	return true;
}
//---------------------------------------------------------------------------
bool StandardResolutionListClass::Write(unsigned char *Data, int MaxSize)
{
	int Count;
	int Slot;
	int Block;
	unsigned char *Byte;

	if (!Data)
		return false;

	std::memset(Data, 1, 16);
	Count = 0;

	if (Count >= SlotCount)
		return true;

	for (Slot = 0; Slot < 8; Slot++)
	{
		std::memcpy(&Data[Slot * SlotSize], &SlotData[Count * SlotSize], SlotSize);
		Count++;

		if (Count >= SlotCount)
			return true;
	}

	for (Block = 0; Block < 4; Block++)
	{
		Byte = &Data[Block * 18 + 16];

		if (std::memcmp(Byte, "\x00\x00\x00\x10\x00", 5) == 0)
		{
			Byte[3] = 0xFA;
			std::memset(&Byte[5], 1, 12);
			Byte[17] = 0x0A;

			for (Slot = 0; Slot < 6; Slot++)
			{
				std::memcpy(&Byte[Slot * SlotSize + 5], &SlotData[Count * SlotSize], SlotSize);
				Count++;

				if (Count >= SlotCount)
					return true;
			}
		}
	}

	return false;
}
//---------------------------------------------------------------------------
bool StandardResolutionListClass::ReadExtension(const unsigned char *Data, int MaxSize)
{
	int Slots;
	int Slot;
	StandardResolutionClass StandardResolution;

	if (!Data)
		return false;

	DeleteAll();

	if (!SetMaxSize(MaxSize))
		return false;

	Slots = MaxSize / SlotSize;

	for (Slot = 0; Slot < Slots && SlotCount < MaxSlotCount; Slot++)
	{
		if (!StandardResolution.Read(&Data[Slot * SlotSize], SlotSize))
			continue;

		if (!StandardResolution.Write(&SlotData[SlotCount * SlotSize], SlotSize))
			continue;

		SlotCount++;
	}

	UpdateSize();
	return true;
}
//---------------------------------------------------------------------------
bool StandardResolutionListClass::WriteExtension(unsigned char *Data, int MaxSize)
{
	if (!Data)
		return false;

	if (MaxSize < DataSize)
		return false;

	std::memcpy(Data, SlotData, DataSize);
	return true;
}
//---------------------------------------------------------------------------
