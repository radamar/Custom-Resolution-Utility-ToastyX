//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "TVResolutionListClass.h"
#include "TVResolutionClass.h"
#include <cstring>
//---------------------------------------------------------------------------
TVResolutionListClass::TVResolutionListClass(int Slots) : ListClass(Slots, 1)
{
	YCbCr420 = false;
	UndoYCbCr420 = false;
	RedoYCbCr420 = false;
}
//---------------------------------------------------------------------------
bool TVResolutionListClass::Read(const unsigned char *Data, int MaxSize)
{
	int Type;
	int Size;
	int Slots;
	int Slot;
	TVResolutionClass TVResolution;

	if (!Data)
		return false;

	Type = Data[0] >> 5;
	Size = Data[0] & 31;

	if (Type == 2)
		YCbCr420 = false;
	else if (Type == 7 && Size >= 1 && Data[1] == 14)
		YCbCr420 = true;
	else
		return false;

	DeleteAll();

	if (!SetMaxSize(MaxSize - 1 - YCbCr420))
		return false;

	Slots = (Size - YCbCr420) / SlotSize;

	for (Slot = 0; Slot < Slots && SlotCount < MaxSlotCount; Slot++)
	{
		if (!TVResolution.Read(&Data[Slot * SlotSize + 1 + YCbCr420], SlotSize))
			continue;

		if (!TVResolution.Write(&SlotData[SlotCount * SlotSize], SlotSize))
			continue;

		SlotCount++;
	}

	UpdateSize();
	UpdateUndo();
	return true;
}
//---------------------------------------------------------------------------
bool TVResolutionListClass::Write(unsigned char *Data, int MaxSize)
{
	if (!Data)
		return false;

	if (MaxSize < DataSize + 1 + YCbCr420)
		return false;

	std::memset(Data, 0, MaxSize);

	if (!YCbCr420)
	{
		Data[0] = 2 << 5;
		Data[0] |= DataSize;
	}
	else
	{
		Data[0] = 7 << 5;
		Data[0] |= DataSize + 1;
		Data[1] = 14;
	}

	std::memcpy(&Data[1 + YCbCr420], SlotData, DataSize);
	return true;
}
//---------------------------------------------------------------------------
bool TVResolutionListClass::YCbCr420Possible()
{
	if (YCbCr420)
		return true;

	return AddPossible();
}
//---------------------------------------------------------------------------
bool TVResolutionListClass::GetYCbCr420()
{
	return YCbCr420;
}
//---------------------------------------------------------------------------
bool TVResolutionListClass::SetYCbCr420(bool Enabled)
{
	if (!YCbCr420Possible())
		return false;

	MaxDataSize = MaxDataSize + YCbCr420 - Enabled;
	MaxSlotCount = MaxDataSize;
	YCbCr420 = Enabled;
	return true;
}
//---------------------------------------------------------------------------
bool TVResolutionListClass::UpdateUndo()
{
	UndoYCbCr420 = YCbCr420;
	RedoYCbCr420 = YCbCr420;
	return ListClass::UpdateUndo();
}
//---------------------------------------------------------------------------
bool TVResolutionListClass::UndoPossible()
{
	if (YCbCr420 != UndoYCbCr420)
		return true;

	return ListClass::UndoPossible();
}
//---------------------------------------------------------------------------
bool TVResolutionListClass::Undo()
{
	MaxDataSize = MaxDataSize + YCbCr420 - UndoYCbCr420;
	MaxSlotCount = MaxDataSize;
	RedoYCbCr420 = YCbCr420;
	YCbCr420 = UndoYCbCr420;
	return ListClass::Undo();
}
//---------------------------------------------------------------------------
bool TVResolutionListClass::RedoPossible()
{
	if (YCbCr420 != RedoYCbCr420)
		return true;

	return ListClass::RedoPossible();
}
//---------------------------------------------------------------------------
bool TVResolutionListClass::Redo()
{
	MaxDataSize = MaxDataSize + YCbCr420 - RedoYCbCr420;
	MaxSlotCount = MaxDataSize;
	UndoYCbCr420 = YCbCr420;
	YCbCr420 = RedoYCbCr420;
	return ListClass::Redo();
}
//---------------------------------------------------------------------------
