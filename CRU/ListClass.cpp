//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "ListClass.h"
#include <cstdio>
#include <cstring>
//---------------------------------------------------------------------------
ListClass::ListClass(int NewMaxSlotCount, int NewSlotSize)
{
	SlotCount = 0;
	UndoSlotCount = 0;
	RedoSlotCount = 0;
	MaxSlotCount = NewMaxSlotCount;
	MaxMaxSlotCount = MaxSlotCount;

	SlotSize = NewSlotSize;

	DataSize = 0;
	UndoDataSize = 0;
	RedoDataSize = 0;
	MaxDataSize = MaxSlotCount * SlotSize;
	MaxMaxDataSize = MaxDataSize;

	SlotData = new unsigned char[MaxMaxDataSize];
	std::memset(SlotData, 0, MaxMaxDataSize);

	UndoSlotData = new unsigned char[MaxMaxDataSize];
	std::memset(UndoSlotData, 0, MaxMaxDataSize);

	RedoSlotData = new unsigned char[MaxMaxDataSize];
	std::memset(RedoSlotData, 0, MaxMaxDataSize);
}
//---------------------------------------------------------------------------
void ListClass::Copy(const ListClass &Source)
{
	SlotCount = Source.SlotCount;
	UndoSlotCount = Source.UndoSlotCount;
	RedoSlotCount = Source.RedoSlotCount;
	MaxSlotCount = Source.MaxSlotCount;
	MaxMaxSlotCount = Source.MaxMaxSlotCount;

	SlotSize = Source.SlotSize;

	DataSize = Source.DataSize;
	UndoDataSize = Source.UndoDataSize;
	RedoDataSize = Source.RedoDataSize;
	MaxDataSize = Source.MaxDataSize;
	MaxMaxDataSize = Source.MaxMaxDataSize;

	SlotData = new unsigned char[MaxMaxDataSize];
	std::memcpy(SlotData, Source.SlotData, MaxMaxDataSize);

	UndoSlotData = new unsigned char[MaxMaxDataSize];
	std::memcpy(UndoSlotData, Source.UndoSlotData, MaxMaxDataSize);

	RedoSlotData = new unsigned char[MaxMaxDataSize];
	std::memcpy(RedoSlotData, Source.RedoSlotData, MaxMaxDataSize);
}
//---------------------------------------------------------------------------
void ListClass::Delete()
{
	delete[] SlotData;
	delete[] UndoSlotData;
	delete[] RedoSlotData;
}
//---------------------------------------------------------------------------
ListClass::ListClass(const ListClass &Source)
{
	Copy(Source);
}
//---------------------------------------------------------------------------
ListClass &ListClass::operator=(const ListClass &Source)
{
	Delete();
	Copy(Source);
	return *this;
}
//---------------------------------------------------------------------------
ListClass::~ListClass()
{
	Delete();
}
//---------------------------------------------------------------------------
int ListClass::GetCount()
{
	return SlotCount;
}
//---------------------------------------------------------------------------
int ListClass::GetMaxCount()
{
	return MaxSlotCount;
}
//---------------------------------------------------------------------------
int ListClass::GetSize()
{
	return DataSize;
}
//---------------------------------------------------------------------------
int ListClass::GetMaxSize()
{
	return MaxDataSize;
}
//---------------------------------------------------------------------------
int ListClass::GetSlotSize(int Slot)
{
	if (Slot < 0 || Slot >= SlotCount)
		return 0;

	return SlotSize;
}
//---------------------------------------------------------------------------
int ListClass::GetMaxSlotSize(int Slot)
{
	int MaxSlotSize = MaxDataSize - DataSize + GetSlotSize(Slot);

	if (MaxSlotSize > SlotSize)
		MaxSlotSize = SlotSize;

	return MaxSlotSize;
}
//---------------------------------------------------------------------------
int ListClass::GetSlotsLeft()
{
	return MaxSlotCount - SlotCount;
}
//---------------------------------------------------------------------------
int ListClass::GetBytesLeft()
{
	return MaxDataSize - DataSize;
}
//---------------------------------------------------------------------------
bool ListClass::GetSlotsLeftText(const char *Caption, char *Text, int TextSize)
{
	int Slots = GetSlotsLeft();

	if (GetMaxCount() > 0)
		std::snprintf(Text, TextSize, "%s(%d slot%s left) ", Caption, Slots, Slots != 1 ? "s" : "");
	else
		std::snprintf(Text, TextSize, "%s(no space left) ", Caption);

	return true;
}
//---------------------------------------------------------------------------
bool ListClass::GetBytesLeftText(const char *Caption, char *Text, int TextSize)
{
	int Bytes = GetBytesLeft();

	std::snprintf(Text, TextSize, "%s(%d byte%s left) ", Caption, Bytes, Bytes != 1 ? "s" : "");
	return true;
}
//---------------------------------------------------------------------------
bool ListClass::UpdateSize()
{
	DataSize = SlotCount * SlotSize;
	return true;
}
//---------------------------------------------------------------------------
bool ListClass::SetMaxCount(int NewMaxSlotCount)
{
	if (NewMaxSlotCount < SlotCount)
		return false;

	if (NewMaxSlotCount > MaxMaxSlotCount)
		NewMaxSlotCount = MaxMaxSlotCount;

	MaxSlotCount = NewMaxSlotCount;
	MaxDataSize = MaxSlotCount * SlotSize;
	return true;
}
//---------------------------------------------------------------------------
bool ListClass::SetMaxSize(int NewMaxDataSize)
{
	int NewMaxSlotCount = NewMaxDataSize / SlotSize;

	if (!SetMaxCount(NewMaxSlotCount))
		return false;

	return true;
}
//---------------------------------------------------------------------------
bool ListClass::AddPossible()
{
	if (SlotCount < 0 || SlotCount >= MaxSlotCount)
		return false;

	if (DataSize < 0 || DataSize >= MaxDataSize)
		return false;

	return true;
}
//---------------------------------------------------------------------------
bool ListClass::Add(ItemClass &Item)
{
	if (SlotCount < 0 || SlotCount >= MaxSlotCount)
		return false;

	if (!Item.Write(&SlotData[SlotCount * SlotSize], GetMaxSlotSize(SlotCount)))
		return false;

	SlotCount++;
	UpdateSize();
	return true;
}
//---------------------------------------------------------------------------
bool ListClass::EditPossible(int Slot)
{
	if (Slot < 0 || Slot >= SlotCount)
		return false;

	return true;
}
//---------------------------------------------------------------------------
bool ListClass::Get(int Slot, ItemClass &Item)
{
	if (Slot < 0 || Slot >= SlotCount)
		return false;

	if (!Item.Read(&SlotData[Slot * SlotSize], GetMaxSlotSize(Slot)))
		return false;

	return true;
}
//---------------------------------------------------------------------------
bool ListClass::Set(int Slot, ItemClass &Item)
{
	if (Slot < 0 || Slot >= SlotCount)
		return false;

	if (!Item.Write(&SlotData[Slot * SlotSize], GetMaxSlotSize(Slot)))
		return false;

	UpdateSize();
	return true;
}
//---------------------------------------------------------------------------
bool ListClass::DeletePossible(int Slot)
{
	if (Slot < 0 || Slot >= SlotCount)
		return false;

	return true;
}
//---------------------------------------------------------------------------
bool ListClass::Delete(int Slot)
{
	if (Slot < 0 || Slot >= SlotCount)
		return false;

	std::memmove(&SlotData[Slot * SlotSize], &SlotData[(Slot + 1) * SlotSize], (SlotCount - Slot - 1) * SlotSize);
	std::memset(&SlotData[(SlotCount - 1) * SlotSize], 0, SlotSize);
	SlotCount--;
	UpdateSize();
	return true;
}
//---------------------------------------------------------------------------
bool ListClass::DeleteAllPossible()
{
	if (SlotCount == 0)
		return false;

	return true;
}
//---------------------------------------------------------------------------
bool ListClass::DeleteAll()
{
	std::memset(SlotData, 0, MaxMaxDataSize);
	SlotCount = 0;
	DataSize = 0;
	return true;
}
//---------------------------------------------------------------------------
bool ListClass::UpdateUndo()
{
	std::memcpy(UndoSlotData, SlotData, MaxMaxDataSize);
	std::memcpy(RedoSlotData, SlotData, MaxMaxDataSize);
	UndoSlotCount = SlotCount;
	RedoSlotCount = SlotCount;
	UndoDataSize = DataSize;
	RedoDataSize = DataSize;
	return true;
}
//---------------------------------------------------------------------------
bool ListClass::UndoPossible()
{
	if (UndoSlotCount < 0 || UndoSlotCount > MaxSlotCount)
		return false;

	if (UndoDataSize < 0 || UndoDataSize > MaxDataSize)
		return false;

	if (SlotCount != UndoSlotCount)
		return true;

	if (std::memcmp(SlotData, UndoSlotData, MaxMaxDataSize) == 0)
		return false;

	return true;
}
//---------------------------------------------------------------------------
bool ListClass::Undo()
{
	if (UndoSlotCount < 0 || UndoSlotCount > MaxSlotCount)
		return false;

	if (UndoDataSize < 0 || UndoDataSize > MaxDataSize)
		return false;

	std::memcpy(RedoSlotData, SlotData, MaxMaxDataSize);
	std::memcpy(SlotData, UndoSlotData, MaxMaxDataSize);
	RedoSlotCount = SlotCount;
	SlotCount = UndoSlotCount;
	RedoDataSize = DataSize;
	DataSize = UndoDataSize;
	return true;
}
//---------------------------------------------------------------------------
bool ListClass::RedoPossible()
{
	if (RedoSlotCount < 0 || RedoSlotCount > MaxSlotCount)
		return false;

	if (RedoDataSize < 0 || RedoDataSize > MaxDataSize)
		return false;

	if (SlotCount != RedoSlotCount)
		return true;

	if (std::memcmp(SlotData, RedoSlotData, MaxMaxDataSize) == 0)
		return false;

	return true;
}
//---------------------------------------------------------------------------
bool ListClass::Redo()
{
	if (RedoSlotCount < 0 || RedoSlotCount > MaxSlotCount)
		return false;

	if (RedoDataSize < 0 || RedoDataSize > MaxDataSize)
		return false;

	std::memcpy(UndoSlotData, SlotData, MaxMaxDataSize);
	std::memcpy(SlotData, RedoSlotData, MaxMaxDataSize);
	UndoSlotCount = SlotCount;
	SlotCount = RedoSlotCount;
	UndoDataSize = DataSize;
	DataSize = RedoDataSize;
	return true;
}
//---------------------------------------------------------------------------
bool ListClass::ExchangePossible(int Slot1, int Slot2)
{
	if (Slot1 < 0 || Slot1 >= SlotCount)
		return false;

	if (Slot2 < 0 || Slot2 >= SlotCount)
		return false;

	return true;
}
//---------------------------------------------------------------------------
bool ListClass::Exchange(int Slot1, int Slot2)
{
	if (Slot1 < 0 || Slot1 >= SlotCount)
		return false;

	if (Slot2 < 0 || Slot2 >= SlotCount)
		return false;

	if (!ExchangeData(&SlotData[Slot1 * SlotSize], &SlotData[Slot2 * SlotSize], SlotSize))
		return false;

	return true;
}
//---------------------------------------------------------------------------
bool ListClass::ExchangeData(unsigned char *Data1, unsigned char *Data2, int Size)
{
	int Index;

	if (!Data1 || !Data2)
		return false;

	if (Data1 == Data2)
		return true;

	for (Index = 0; Index < Size; Index++, Data1++, Data2++)
	{
		*Data1 ^= *Data2;
		*Data2 ^= *Data1;
		*Data1 ^= *Data2;
	}

	return true;
}
//---------------------------------------------------------------------------
