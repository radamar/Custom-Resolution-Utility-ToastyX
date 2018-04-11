//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "ExtensionBlockListClass.h"
#include "ExtensionBlockClass.h"
#include <cstring>
//---------------------------------------------------------------------------
ExtensionBlockListClass::ExtensionBlockListClass(int Slots) : ListClass(Slots, 128)
{
}
//---------------------------------------------------------------------------
bool ExtensionBlockListClass::Read(const unsigned char *Data, int MaxSize)
{
	int Slots;
	int Slot;
	ExtensionBlockClass ExtensionBlock;

	if (!Data)
		return false;

	DeleteAll();

	if (!SetMaxSize(MaxSize - 2))
		return false;

	Slots = Data[0];

	for (Slot = 0; Slot < Slots && SlotCount < MaxSlotCount; Slot++)
	{
		if (!ExtensionBlock.Read(&Data[Slot * SlotSize + 2], SlotSize))
			continue;

		if (!ExtensionBlock.Write(&SlotData[SlotCount * SlotSize], SlotSize))
			continue;

		SlotCount++;
	}

	UpdateSize();
	return true;
}
//---------------------------------------------------------------------------
bool ExtensionBlockListClass::Write(unsigned char *Data, int MaxSize)
{
	if (!Data)
		return false;

	if (MaxSize < DataSize + 2)
		return false;

	std::memset(Data, 0, MaxSize);
	Data[0] = SlotCount;
	std::memcpy(&Data[2], SlotData, DataSize);
	return true;
}
//---------------------------------------------------------------------------
bool ExtensionBlockListClass::WriteBlankExtension(unsigned char *Data, int MaxSize)
{
	if (!Data)
		return false;

	if (MaxSize < SlotSize)
		return false;

	std::memset(Data, 0, MaxSize);
	Data[0] = 2;
	Data[1] = 3;
	Data[127] = 251;
	return true;
}
//---------------------------------------------------------------------------
bool ExtensionBlockListClass::EditPossible(int Slot)
{
	ExtensionBlockClass ExtensionBlock;

	if (!Get(Slot, ExtensionBlock))
		return false;

	return ExtensionBlock.IsValidType();
}
//---------------------------------------------------------------------------
