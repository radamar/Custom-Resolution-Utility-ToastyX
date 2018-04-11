//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "VideoCapabilityClass.h"
#include <cstring>
//---------------------------------------------------------------------------
const int VideoCapabilityClass::VideoCapabilityMask = 255;
//---------------------------------------------------------------------------
VideoCapabilityClass::VideoCapabilityClass()
{
	VideoCapability = 0;
}
//---------------------------------------------------------------------------
bool VideoCapabilityClass::Read(const unsigned char *Data, int MaxSize)
{
	int Type;
	int Size;

	if (!Data)
		return false;

	if (MaxSize < 3)
		return false;

	Type = Data[0] >> 5;
	Size = Data[0] & 31;

	if (Type != 7)
		return false;

	if (Size < 2)
		return false;

	if (Data[1] != 0)
		return false;

	VideoCapability = Data[2] & VideoCapabilityMask;
	return true;
}
//---------------------------------------------------------------------------
bool VideoCapabilityClass::Write(unsigned char *Data, int MaxSize)
{
	if (!Data)
		return false;

	if (MaxSize < 3)
		return false;

	std::memset(Data, 0, MaxSize);
	Data[0] = 7 << 5;
	Data[0] |= 2;
	Data[1] = 0;
	Data[2] = VideoCapability & VideoCapabilityMask;
	return true;
}
//---------------------------------------------------------------------------
bool VideoCapabilityClass::GetVideoCapability(int Index)
{
	if (!(VideoCapabilityMask & (1 << Index)))
		return false;

	return VideoCapability & (1 << Index);
}
//---------------------------------------------------------------------------
bool VideoCapabilityClass::SetVideoCapability(int Index, bool Enabled)
{
	if (!(VideoCapabilityMask & (1 << Index)))
		return false;

	if (Enabled)
		VideoCapability |= 1 << Index;
	else
		VideoCapability &= ~(1 << Index);

	return true;
}
//---------------------------------------------------------------------------
