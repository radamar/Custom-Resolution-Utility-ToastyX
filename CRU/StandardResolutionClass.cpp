//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "StandardResolutionClass.h"
#include <cstdio>
//---------------------------------------------------------------------------
const int StandardResolutionClass::HAspect[] = {16,  4,  5, 16};
const int StandardResolutionClass::VAspect[] = {10,  3,  4,  9};
// 0 = 16:10
// 1 = 4:3
// 2 = 5:4
// 3 = 16:9
const int StandardResolutionClass::Modes[][2] =
{
	{640, 1},
	{720, 2},
	{800, 1},
	{1024, 1},
	{1152, 1},
	{1280, 3},
	{1280, 0},
	{1280, 1},
	{1280, 2},
	{1440, 0},
	{1600, 3},
	{1600, 1},
	{1680, 0},
	{1792, 1},
	{1800, 2},
	{1856, 1},
	{1920, 3},
	{1920, 0},
	{1920, 1},
	{2048, 1},
	{0}
};

const int StandardResolutionClass::MinMode = 0;
const int StandardResolutionClass::MaxMode = 20;
const int StandardResolutionClass::MinAspect = 0;
const int StandardResolutionClass::MaxAspect = 3;
const int StandardResolutionClass::MinWidth = 256;
const int StandardResolutionClass::MaxWidth = 2288;
const int StandardResolutionClass::ModWidth = 8;
const int StandardResolutionClass::MinRate = 60;
const int StandardResolutionClass::MaxRate = 123;
//---------------------------------------------------------------------------
StandardResolutionClass::StandardResolutionClass()
{
	Mode = 0;
	Aspect = 1;
	Width = 640;
	Height = 480;
	LastAspect = BLANK;
	LastWidth = BLANK;
	LastHeight = BLANK;
	Rate = 60;
}
//---------------------------------------------------------------------------
bool StandardResolutionClass::Read(const unsigned char *Data, int MaxSize)
{
	if (!Data)
		return false;

	if (MaxSize < 2)
		return false;

	Aspect = Data[1] >> 6;
	Width = Data[0] * 8 + 248;
	Height = Width * VAspect[Aspect] / HAspect[Aspect];

	for (Mode = MinMode; Mode < MaxMode; Mode++)
		if (Modes[Mode][0] == Width && Modes[Mode][1] == Aspect)
			break;

	if (Mode == MaxMode)
	{
		LastAspect = Aspect;
		LastWidth = Width;
		LastHeight = Height;
	}
	else
	{
		LastAspect = BLANK;
		LastWidth = BLANK;
		LastHeight = BLANK;
	}

	Rate = 60 + (Data[1] & 63);
	return true;
}
//---------------------------------------------------------------------------
bool StandardResolutionClass::Write(unsigned char *Data, int MaxSize)
{
	if (!Data)
		return false;

	if (MaxSize < 2)
		return false;

	if (!IsValid())
		return false;

	Data[0] = (Width - 248) / 8;
	Data[1] = Aspect << 6;
	Data[1] |= Rate - 60;
	return true;
}
//---------------------------------------------------------------------------
bool StandardResolutionClass::GetText(char *Text, int TextSize)
{
	if (!IsValid())
		return false;

	std::snprintf(Text, TextSize, "%dx%d (%d:%d) @ %d Hz", Width, Height, HAspect[Aspect], VAspect[Aspect], Rate);
	return true;
}
//---------------------------------------------------------------------------
bool StandardResolutionClass::GetModeText(int Mode, char *Text, int TextSize)
{
	if (Mode < MinMode || Mode > MaxMode)
		return false;

	int Aspect = Modes[Mode][1];
	int Width = Modes[Mode][0];
	int Height = Width * VAspect[Aspect] / HAspect[Aspect];

	if (Width != 0)
		std::snprintf(Text, TextSize, "%dx%d (%d:%d)", Width, Height, HAspect[Aspect], VAspect[Aspect]);
	else
		std::snprintf(Text, TextSize, "Other resolution");

	return true;
}
//---------------------------------------------------------------------------
int StandardResolutionClass::GetMode()
{
	if (!IsValidMode())
		return -1;

	return Mode;
}
//---------------------------------------------------------------------------
bool StandardResolutionClass::SetMode(int Value)
{
	Mode = Value;

	if (!IsValidMode())
	{
		Aspect = BLANK;
		Width = BLANK;
		Height = BLANK;
	}
	else if (Mode == MaxMode)
	{
		Aspect = LastAspect;
		Width = LastWidth;
		Height = LastHeight;
	}
	else
	{
		Aspect = Modes[Mode][1];
		Width = Modes[Mode][0];
		Height = Width * VAspect[Aspect] / HAspect[Aspect];
	}

	return true;
}
//---------------------------------------------------------------------------
bool StandardResolutionClass::UpdateAspect()
{
	for (Aspect = MinAspect; Aspect <= MaxAspect; Aspect++)
		if (Height == Width * VAspect[Aspect] / HAspect[Aspect])
			break;

	if (Aspect > MaxAspect)
		Aspect = BLANK;

	LastAspect = Aspect;
	return true;
}
//---------------------------------------------------------------------------
int StandardResolutionClass::GetWidth()
{
	return Width;
}
//---------------------------------------------------------------------------
bool StandardResolutionClass::SetWidth(int Value)
{
	Width = Value;
	LastWidth = Width;
	UpdateAspect();
	return true;
}
//---------------------------------------------------------------------------
int StandardResolutionClass::GetHeight()
{
	return Height;
}
//---------------------------------------------------------------------------
bool StandardResolutionClass::SetHeight(int Value)
{
	Height = Value;
	LastHeight = Height;
	UpdateAspect();
	return true;
}
//---------------------------------------------------------------------------
int StandardResolutionClass::GetRate()
{
	return Rate;
}
//---------------------------------------------------------------------------
bool StandardResolutionClass::SetRate(int Value)
{
	Rate = Value;
	return true;
}
//---------------------------------------------------------------------------
bool StandardResolutionClass::IsValid()
{
	return IsValidMode() && IsValidWidth() && IsValidHeight() && IsValidRate();
}
//---------------------------------------------------------------------------
bool StandardResolutionClass::IsValidMode()
{
	return Mode >= MinMode && Mode <= MaxMode;
}
//---------------------------------------------------------------------------
bool StandardResolutionClass::IsValidAspect()
{
	return Aspect >= MinAspect && Aspect <= MaxAspect;
}
//---------------------------------------------------------------------------
bool StandardResolutionClass::IsValidWidth()
{
	return Width >= MinWidth && Width <= MaxWidth && Width % ModWidth == 0;
}
//---------------------------------------------------------------------------
bool StandardResolutionClass::IsValidHeight()
{
	if (Width == BLANK)
		return true;

	return IsValidWidth() && IsValidAspect();
}
//---------------------------------------------------------------------------
bool StandardResolutionClass::IsValidRate()
{
	if (Width == 256 && Height == 160 && Rate == 61)
		return false;

	return Rate >= MinRate && Rate <= MaxRate;
}
//---------------------------------------------------------------------------
bool StandardResolutionClass::IsSupported()
{
	return Mode >= MinMode && Mode < MaxMode;
}
//---------------------------------------------------------------------------
bool StandardResolutionClass::IsOther()
{
	return Mode == MaxMode;
}
//---------------------------------------------------------------------------
