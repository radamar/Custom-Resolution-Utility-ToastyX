//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "DetailedResolutionListClass.h"
#include <cstdio>
#include <cstring>
//---------------------------------------------------------------------------
DetailedResolutionListClass::DetailedResolutionListClass(int Slots) : ListClass(Slots, 18)
{
}
//---------------------------------------------------------------------------
bool DetailedResolutionListClass::Read(const unsigned char *Data, int MaxSize)
{
	int Slots;
	int Slot;
	DetailedResolutionClass DetailedResolution;

	if (!Data)
		return false;

	DeleteAll();

	if (!SetMaxSize(MaxSize))
		return false;

	Slots = MaxSize / SlotSize;

	for (Slot = 0; Slot < Slots && SlotCount < MaxSlotCount; Slot++)
	{
		if (!DetailedResolution.Read(&Data[Slot * SlotSize], SlotSize))
			continue;

		if (!DetailedResolution.Write(&SlotData[SlotCount * SlotSize], SlotSize))
			continue;

		SlotCount++;
	}

	UpdateSize();
	return true;
}
//---------------------------------------------------------------------------
bool DetailedResolutionListClass::Write(unsigned char *Data, int MaxSize)
{
	if (!Data)
		return false;

	if (MaxSize < DataSize)
		return false;

	std::memcpy(Data, SlotData, DataSize);
	return true;
}
//---------------------------------------------------------------------------
bool DetailedResolutionListClass::GetNative(DetailedResolutionClass &DetailedResolution)
{
	if (!DetailedResolution.Read(SlotData, SlotSize))
		if (!DetailedResolution.Read(UndoSlotData, SlotSize))
			return false;

	return true;
}
//---------------------------------------------------------------------------
bool DetailedResolutionListClass::GetStandardText(int Slot, char *Text, int TextSize, int SlotsLeft)
{
	int Slots;
	int Count;

	Slots = MaxMaxSlotCount - MaxSlotCount;

	if (Slot < 0 || Slot >= Slots)
		return false;

	if (Slot == Slots - 1)
		Count = 6 - SlotsLeft % 6;
	else
		Count = 6;

	std::snprintf(Text, TextSize, "Standard resolutions (%d resolution%s)", Count, Count != 1 ? "s" : "");
	return true;
}
//---------------------------------------------------------------------------
bool DetailedResolutionListClass::GetExtensionText(int Slot, char *Text, int TextSize, int BytesLeft)
{
	int Slots;
	int Count;

	Slots = MaxMaxSlotCount - MaxSlotCount;

	if (Slot < 0 || Slot >= Slots)
		return false;

	if (Slot == Slots - 1)
		Count = 18 - BytesLeft % 18;
	else
		Count = 18;

	std::snprintf(Text, TextSize, "Data blocks (%d byte%s)", Count, Count != 1 ? "s" : "");
	return true;
}
//---------------------------------------------------------------------------
bool DetailedResolutionListClass::GetExtensionStandardText(int Slot, char *Text, int TextSize, int SlotsLeft)
{
	int Slots;
	int Count;

	Slots = MaxMaxSlotCount - MaxSlotCount;

	if (Slot < 0 || Slot >= Slots)
		return false;

	if (Slot == Slots - 1)
		Count = 9 - SlotsLeft % 9;
	else
		Count = 9;

	std::snprintf(Text, TextSize, "Standard resolutions (%d resolution%s)", Count, Count != 1 ? "s" : "");
	return true;
}
//---------------------------------------------------------------------------
