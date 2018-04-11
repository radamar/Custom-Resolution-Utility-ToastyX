//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "ColorimetryClass.h"
#include <cstring>
//---------------------------------------------------------------------------
const unsigned char ColorimetryClass::ColorimetryMask[2] = {255, 143};
const int ColorimetryClass::MinColorimetry = 0;
const int ColorimetryClass::MaxColorimetry = 8;
const int ColorimetryClass::MinMetadata = 0;
const int ColorimetryClass::MaxMetadata = 3;
//---------------------------------------------------------------------------
ColorimetryClass::ColorimetryClass()
{
	Colorimetry[0] = 3;
	Colorimetry[1] = 1;
}
//---------------------------------------------------------------------------
bool ColorimetryClass::Read(const unsigned char *Data, int MaxSize)
{
	int Type;
	int Size;

	if (!Data)
		return false;

	if (MaxSize < 4)
		return false;

	Type = Data[0] >> 5;
	Size = Data[0] & 31;

	if (Type != 7)
		return false;

	if (Size < 3)
		return false;

	if (Data[1] != 5)
		return false;

	Colorimetry[0] = Data[2] & ColorimetryMask[0];
	Colorimetry[1] = Data[3] & ColorimetryMask[1];
	return true;
}
//---------------------------------------------------------------------------
bool ColorimetryClass::Write(unsigned char *Data, int MaxSize)
{
	if (!Data)
		return false;

	if (MaxSize < 4)
		return false;

	std::memset(Data, 0, MaxSize);
	Data[0] = 7 << 5;
	Data[0] |= 3;
	Data[1] = 5;
	Data[2] = Colorimetry[0] & ColorimetryMask[0];
	Data[3] = Colorimetry[1] & ColorimetryMask[1];
	return true;
}
//---------------------------------------------------------------------------
bool ColorimetryClass::GetColorimetry(int Index)
{
	if (Index < MinColorimetry || Index > MaxColorimetry)
		return false;

	if (Index == 8)
		return Colorimetry[1] & 128;

	return Colorimetry[0] & (1 << Index);
}
//---------------------------------------------------------------------------
bool ColorimetryClass::SetColorimetry(int Index, bool Enabled)
{
	if (Index < MinColorimetry || Index > MaxColorimetry)
		return false;

	if (Index == 8)
	{
		if (Enabled)
			Colorimetry[1] |= 128;
		else
			Colorimetry[1] &= ~128;
	}
	else
	{
		if (Enabled)
			Colorimetry[0] |= 1 << Index;
		else
			Colorimetry[0] &= ~(1 << Index);
	}

	return true;
}
//---------------------------------------------------------------------------
bool ColorimetryClass::GetMetadata(int Index)
{
	if (Index < MinMetadata || Index > MaxMetadata)
		return false;

	return Colorimetry[1] & (1 << Index);
}
//---------------------------------------------------------------------------
bool ColorimetryClass::SetMetadata(int Index, bool Enabled)
{
	if (Index < MinMetadata || Index > MaxMetadata)
		return false;

	if (Enabled)
		Colorimetry[1] |= 1 << Index;
	else
		Colorimetry[1] &= ~(1 << Index);

	return true;
}
//---------------------------------------------------------------------------
