//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "HDMIResolutionListClass.h"
#include "HDMIResolutionClass.h"
#include <cstring>
//---------------------------------------------------------------------------
HDMIResolutionListClass::HDMIResolutionListClass(int Slots) : ListClass(Slots, 1)
{
}
//---------------------------------------------------------------------------
bool HDMIResolutionListClass::Read(const unsigned char *Data, int MaxSize)
{
	int Slots;
	int Slot;
	HDMIResolutionClass HDMIResolution;

	if (!Data)
		return false;

	DeleteAll();

	if (!SetMaxSize(MaxSize))
		return false;

	Slots = MaxSize / SlotSize;

	for (Slot = 0; Slot < Slots && SlotCount < MaxSlotCount; Slot++)
	{
		if (!HDMIResolution.Read(&Data[Slot * SlotSize], SlotSize))
			continue;

		if (!HDMIResolution.Write(&SlotData[SlotCount * SlotSize], SlotSize))
			continue;

		SlotCount++;
	}

	UpdateSize();
	UpdateUndo();
	return true;
}
//---------------------------------------------------------------------------
bool HDMIResolutionListClass::Write(unsigned char *Data, int MaxSize)
{
	if (!Data)
		return false;

	if (MaxSize < DataSize)
		return false;

	std::memcpy(Data, SlotData, DataSize);
	return true;
}
//---------------------------------------------------------------------------
