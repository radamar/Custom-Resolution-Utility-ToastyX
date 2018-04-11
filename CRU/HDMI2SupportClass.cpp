//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "HDMI2SupportClass.h"
#include <cstring>
//---------------------------------------------------------------------------
const int HDMI2SupportClass::MinTMDSRate = 5;
const int HDMI2SupportClass::MaxTMDSRate = 1275;
const int HDMI2SupportClass::ModTMDSRate = 5;
const int HDMI2SupportClass::FeaturesMask = 207;
const int HDMI2SupportClass::ColorFormatsMask = 7;
//---------------------------------------------------------------------------
HDMI2SupportClass::HDMI2SupportClass()
{
	Version = 1;
	TMDSRate = 600;
	Features = 0;
	ColorFormats = 0;
}
//---------------------------------------------------------------------------
bool HDMI2SupportClass::Read(const unsigned char *Data, int MaxSize)
{
	int Type;
	int Size;

	if (!Data)
		return false;

	if (MaxSize < 8)
		return false;

	Type = Data[0] >> 5;
	Size = Data[0] & 31;

	if (Type != 3)
		return false;

	if (Size < 7)
		return false;

	if (std::memcmp(&Data[1], "\xD8\x5D\xC4", 3) != 0)
		return false;

	if (Data[4] != 0)
		Version = Data[4];
	else
		Version = 1;

	if (Data[5] != 0)
		TMDSRate = Data[5] * 5;
	else
		TMDSRate = BLANK;

	Features = Data[6] & FeaturesMask;
	ColorFormats = Data[7] & ColorFormatsMask;
	return true;
}
//---------------------------------------------------------------------------
bool HDMI2SupportClass::Write(unsigned char *Data, int MaxSize)
{
	if (!Data)
		return false;

	if (MaxSize < 8)
		return false;

	std::memset(Data, 0, MaxSize);
	Data[0] = 3 << 5;
	Data[0] |= 7;
	std::memcpy(&Data[1], "\xD8\x5D\xC4", 3);
	Data[4] = Version;

	if (TMDSRate != BLANK)
		Data[5] = TMDSRate / 5;

	Data[6] = Features & FeaturesMask;
	Data[7] = ColorFormats & ColorFormatsMask;
	return true;
}
//---------------------------------------------------------------------------
int HDMI2SupportClass::GetTMDSRate()
{
	return TMDSRate;
}
//---------------------------------------------------------------------------
bool HDMI2SupportClass::SetTMDSRate(int Value)
{
	TMDSRate = Value;
	return true;
}
//---------------------------------------------------------------------------
bool HDMI2SupportClass::GetFeature(int Index)
{
	if (!(FeaturesMask & (1 << Index)))
		return false;

	return Features & (1 << Index);
}
//---------------------------------------------------------------------------
bool HDMI2SupportClass::SetFeature(int Index, bool Enabled)
{
	if (!(FeaturesMask & (1 << Index)))
		return false;

	if (Enabled)
		Features |= 1 << Index;
	else
		Features &= ~(1 << Index);

	return true;
}
//---------------------------------------------------------------------------
bool HDMI2SupportClass::GetColorFormat(int Index)
{
	if (!(ColorFormatsMask & (1 << Index)))
		return false;

	return ColorFormats & (1 << Index);
}
//---------------------------------------------------------------------------
bool HDMI2SupportClass::SetColorFormat(int Index, bool Enabled)
{
	if (!(ColorFormatsMask & (1 << Index)))
		return false;

	if (Enabled)
		ColorFormats |= 1 << Index;
	else
		ColorFormats &= ~(1 << Index);

	return true;
}
//---------------------------------------------------------------------------
bool HDMI2SupportClass::IsValid()
{
	return IsValidTMDSRate();
}
//---------------------------------------------------------------------------
bool HDMI2SupportClass::IsValidTMDSRate()
{
	if (TMDSRate == BLANK)
		return true;

	return TMDSRate >= MinTMDSRate && TMDSRate <= MaxTMDSRate && TMDSRate % ModTMDSRate == 0;
}
//---------------------------------------------------------------------------
