//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "FreeSyncRangeClass.h"
#include <cstring>
//---------------------------------------------------------------------------
const int FreeSyncRangeClass::MinVRange = 1;
const int FreeSyncRangeClass::MaxVRange = 255;
//---------------------------------------------------------------------------
FreeSyncRangeClass::FreeSyncRangeClass()
{
	MinVRate = BLANK;
	MaxVRate = BLANK;
}
//---------------------------------------------------------------------------
bool FreeSyncRangeClass::Read(const unsigned char *Data, int MaxSize)
{
	int Type;
	int Size;

	if (!Data)
		return false;

	if (MaxSize < 9)
		return false;

	Type = Data[0] >> 5;
	Size = Data[0] & 31;

	if (Type != 3)
		return false;

	if (Size < 8)
		return false;

	if (std::memcmp(&Data[1], "\x1A\x00\x00\x01\x01", 5) != 0)
		return false;

	if (Data[6] != 0)
		MinVRate = Data[6];
	else
		MinVRate = BLANK;

	if (Data[7] != 0)
		MaxVRate = Data[7];
	else
		MaxVRate = BLANK;

	return true;
}
//---------------------------------------------------------------------------
bool FreeSyncRangeClass::Write(unsigned char *Data, int MaxSize)
{
	if (!Data)
		return false;

	if (MaxSize < 9)
		return false;

	std::memset(Data, 0, MaxSize);
	Data[0] = 3 << 5;
	Data[0] |= 8;
	std::memcpy(&Data[1], "\x1A\x00\x00\x01\x01", 5);

	if (MinVRate != BLANK)
		Data[6] = MinVRate;

	if (MaxVRate != BLANK)
		Data[7] = MaxVRate;

	return true;
}
//---------------------------------------------------------------------------
int FreeSyncRangeClass::GetMinVRate()
{
	return MinVRate;
}
//---------------------------------------------------------------------------
bool FreeSyncRangeClass::SetMinVRate(int Value)
{
	MinVRate = Value;
	return true;
}
//---------------------------------------------------------------------------
int FreeSyncRangeClass::GetMaxVRate()
{
	return MaxVRate;
}
//---------------------------------------------------------------------------
bool FreeSyncRangeClass::SetMaxVRate(int Value)
{
	MaxVRate = Value;
	return true;
}
//---------------------------------------------------------------------------
bool FreeSyncRangeClass::IsValid()
{
	return IsValidMinVRate() && IsValidMaxVRate();
}
//---------------------------------------------------------------------------
bool FreeSyncRangeClass::IsValidMinVRate()
{
	if (MinVRate < MinVRange || MinVRate > MaxVRange)
		return false;

	if (MaxVRate < MinVRange || MaxVRate > MaxVRange)
		return true;

	return MinVRate <= MaxVRate;
}
//---------------------------------------------------------------------------
bool FreeSyncRangeClass::IsValidMaxVRate()
{
	if (MaxVRate < MinVRange || MaxVRate > MaxVRange)
		return false;

	if (MinVRate < MinVRange || MinVRate > MaxVRange)
		return true;

	return MaxVRate >= MinVRate;
}
//---------------------------------------------------------------------------
