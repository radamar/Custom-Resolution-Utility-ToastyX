//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "DIDDetailedResolutionListClass.h"
#include "DetailedResolutionClass.h"
#include <cstring>
//---------------------------------------------------------------------------
DIDDetailedResolutionListClass::DIDDetailedResolutionListClass(int Slots) : ListClass(Slots, 20)
{
}
//---------------------------------------------------------------------------
bool DIDDetailedResolutionListClass::Read(const unsigned char *Data, int MaxSize)
{
	int Type;
	int Size;
	int Slots;
	int Slot;
	DetailedResolutionClass DetailedResolution(1);

	if (!Data)
		return false;

	Type = Data[0];
	Size = Data[2];

	if (Type != 3)
		return false;

	DeleteAll();

	if (!SetMaxSize(MaxSize - 3))
		return false;

	Slots = Size / SlotSize;

	for (Slot = 0; Slot < Slots && SlotCount < MaxSlotCount; Slot++)
	{
		if (!DetailedResolution.Read(&Data[Slot * SlotSize + 3], SlotSize))
			continue;

		if (!DetailedResolution.Write(&SlotData[SlotCount * SlotSize], SlotSize))
			continue;

		SlotCount++;
	}

	UpdateSize();
	UpdateUndo();
	return true;
}
//---------------------------------------------------------------------------
bool DIDDetailedResolutionListClass::Write(unsigned char *Data, int MaxSize)
{
	if (!Data)
		return false;

	if (MaxSize < DataSize + 3)
		return false;

	std::memset(Data, 0, MaxSize);
	Data[0] = 3;
	Data[2] = DataSize;
	std::memcpy(&Data[3], SlotData, DataSize);
	return true;
}
//---------------------------------------------------------------------------
