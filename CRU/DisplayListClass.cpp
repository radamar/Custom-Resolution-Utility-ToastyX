//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "DisplayListClass.h"
#include "EDIDListClass.h"
#include "AMDDisplayClass.h"
#include "NVIDIADisplayClass.h"
#include <algorithm>
#include <cstdio>
//---------------------------------------------------------------------------
DisplayListClass::DisplayListClass()
{
	Count = 0;
	ItemIndex = -1;
}
//---------------------------------------------------------------------------
bool DisplayListClass::Load()
{
	EDIDListClass EDIDList;
	AMDDisplayClass AMDDisplay;
	NVIDIADisplayClass NVIDIADisplay;
	int Index;

	if (!LoadDisplays())
		return false;

	if (Count == 0)
		return true;

	AMDDisplay.LoadEDIDList(EDIDList);
	NVIDIADisplay.LoadEDIDList(EDIDList);

	if (EDIDList.GetCount() > 0)
	{
		for (Index = 0; Index < Count; Index++)
			Items[Index]->MatchFullActive(EDIDList);

		for (Index = 0; Index < Count; Index++)
			Items[Index]->MatchFullOverride(EDIDList);

		for (Index = 0; Index < Count; Index++)
			Items[Index]->MatchPartialOverride(EDIDList);

		for (Index = 0; Index < Count; Index++)
			Items[Index]->MatchFirstActive(EDIDList);
	}

	for (Index = 0; Index < Count; Index++)
		Items[Index]->Init();

	return true;
}
//---------------------------------------------------------------------------
bool DisplayListClass::LoadDisplays()
{
	HKEY Key;
	char DisplayID[TEXTSIZE];
	unsigned long TextSize;
	int Index;

	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SYSTEM\\CurrentControlSet\\Enum\\DISPLAY", 0, KEY_ENUMERATE_SUB_KEYS, &Key) != ERROR_SUCCESS)
		return false;

	for (Index = 0; TextSize = TEXTSIZE, RegEnumKeyEx(Key, Index, DisplayID, &TextSize, NULL, NULL, NULL, NULL) == ERROR_SUCCESS; Index++)
		LoadDisplay(DisplayID);

	RegCloseKey(Key);
	return true;
}
//---------------------------------------------------------------------------
bool DisplayListClass::LoadDisplay(const char *DisplayID)
{
	HKEY Key;
	char Path[TEXTSIZE];
	char DeviceID[TEXTSIZE];
	unsigned long TextSize;
	int Index;

	if (std::snprintf(Path, TEXTSIZE, "SYSTEM\\CurrentControlSet\\Enum\\DISPLAY\\%s", DisplayID) >= TEXTSIZE)
		return false;

	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, Path, 0, KEY_ENUMERATE_SUB_KEYS, &Key) != ERROR_SUCCESS)
		return false;

	for (Index = 0; TextSize = TEXTSIZE, RegEnumKeyEx(Key, Index, DeviceID, &TextSize, NULL, NULL, NULL, NULL) == ERROR_SUCCESS; Index++)
		LoadDevice(DisplayID, DeviceID);

	RegCloseKey(Key);
	return true;
}
//---------------------------------------------------------------------------
bool DisplayListClass::LoadDevice(const char *DisplayID, const char *DeviceID)
{
	DisplayClass *NewDisplay = new DisplayClass(DisplayID, DeviceID);

	if (!NewDisplay->Load())
	{
		delete NewDisplay;
		return false;
	}

	Add(NewDisplay);
	return true;
}
//---------------------------------------------------------------------------
bool DisplayListClass::Add(DisplayClass *NewDisplay)
{
	Items.push_back(NewDisplay);
	Count++;
	return true;
}
//---------------------------------------------------------------------------
bool DisplayListClass::Save()
{
	int Index;
	int Result = 0;

	for (Index = 0; Index < Count; Index++)
		Result |= Items[Index]->Save();

	if (Result & 1)
		for (Index = 0; Index < Count; Index++)
			Result |= Items[Index]->SaveActiveData();

	if (Result < 0)
		return false;

	return true;
}
//---------------------------------------------------------------------------
int DisplayListClass::GetCount()
{
	return Count;
}
//---------------------------------------------------------------------------
bool DisplayListClass::Sort()
{
	std::sort(Items.begin(), Items.end(), DisplayClass::Compare);
	return true;
}
//---------------------------------------------------------------------------
bool DisplayListClass::GetItemText(int Index, char *Text, int TextSize)
{
	if (Index < 0 || Index >= Count)
		return false;

	Items[Index]->GetText(Text, TextSize, true);
	return true;
}
//---------------------------------------------------------------------------
int DisplayListClass::GetCurrent()
{
	return ItemIndex;
}
//---------------------------------------------------------------------------
bool DisplayListClass::SetCurrent(int NewItemIndex)
{
	ItemIndex = NewItemIndex;
	return true;
}
//---------------------------------------------------------------------------
DisplayClass *DisplayListClass::Current()
{
	if (ItemIndex < 0 || ItemIndex >= Count)
		return NULL;

	return Items[ItemIndex];
}
//---------------------------------------------------------------------------
