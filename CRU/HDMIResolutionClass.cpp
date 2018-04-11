//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "HDMIResolutionClass.h"
#include <cstdio>
//---------------------------------------------------------------------------
const char *HDMIResolutionClass::AspectText[] =
{
	"",
	"",
	"",
	"",
	"4:3",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"1250",
	"",
	"",
	"",
	"16:9",
	"17:9",
	"",
	"",
	"",
	"21:9",
};

const int HDMIResolutionClass::MinMode = 0;
const int HDMIResolutionClass::MaxMode = 2;
const int HDMIResolutionClass::MinFormat = 0;
const int HDMIResolutionClass::MaxFormat = 2;

const int HDMIResolutionClass::Modes[][4] =
{
	// 3840x2160
	{3, 2, 1},

	// 4096x2160
	{4},

	// Other resolution
	{0},
};

const int HDMIResolutionClass::MinCode = 0;
const int HDMIResolutionClass::MaxCode = 255;

const short HDMIResolutionClass::Codes[256][6] =
{
	{0},                            //   0
	{3840, 2160, 0, 16,  30, 1},    //   1
	{3840, 2160, 0, 16,  25, 1},    //   2
	{3840, 2160, 0, 16,  24, 1},    //   3
	{4096, 2160, 0, 17,  24, 1},    //   4
};
//---------------------------------------------------------------------------
HDMIResolutionClass::HDMIResolutionClass()
{
	Mode = 0;
	Format = 0;
	Code = 3;
	LastCode = BLANK;
}
//---------------------------------------------------------------------------
bool HDMIResolutionClass::Read(const unsigned char *Data, int MaxSize)
{
	if (!Data)
		return false;

	if (MaxSize < 1)
		return false;

	Code = Data[0];

	for (Mode = MinMode; Mode < MaxMode; Mode++)
	{
		for (Format = MinFormat; Modes[Mode][Format] != 0; Format++)
			if (Modes[Mode][Format] == Code)
				break;

		if (Modes[Mode][Format] != 0)
			break;
	}

	if (Mode == MaxMode)
		LastCode = Code;
	else
		LastCode = BLANK;

	return true;
}
//---------------------------------------------------------------------------
bool HDMIResolutionClass::Write(unsigned char *Data, int MaxSize)
{
	if (!Data)
		return false;

	if (MaxSize < 1)
		return false;

	if (!IsValid())
		return false;

	Data[0] = Code;
	return true;
}
//---------------------------------------------------------------------------
bool HDMIResolutionClass::GetText(char *Text, int TextSize)
{
	if (!IsValid())
		return false;

	int Width = Codes[Code][0];
	int Height = Codes[Code][1];
	int Interlaced = Codes[Code][2];
	int Aspect = Codes[Code][3];
	int Refresh = Codes[Code][4];

	if (Width != 0)
		std::snprintf(Text, TextSize, "%dx%d%s (%s) @ %d Hz", Width, Height, Interlaced ? "i" : "", AspectText[Aspect], Refresh);
	else
		std::snprintf(Text, TextSize, "Other (%d)", Code);

	return true;
}
//---------------------------------------------------------------------------
bool HDMIResolutionClass::GetModeText(int Mode, char *Text, int TextSize)
{
	if (Mode < MinMode || Mode > MaxMode)
		return false;

	int Code = Modes[Mode][0];
	int Width = Codes[Code][0];
	int Height = Codes[Code][1];
	int Interlaced = Codes[Code][2];

	if (Width != 0)
		std::snprintf(Text, TextSize, "%dx%d%s", Width, Height, Interlaced ? "i" : "");
	else
		std::snprintf(Text, TextSize, "Other resolution");

	return true;
}
//---------------------------------------------------------------------------
int HDMIResolutionClass::GetMode()
{
	if (!IsValidMode())
		return -1;

	return Mode;
}
//---------------------------------------------------------------------------
bool HDMIResolutionClass::SetMode(int Value)
{
	if (Value == Mode)
		return true;

	Mode = Value;
	Format = BLANK;

	if (Mode == MaxMode)
		Code = LastCode;
	else
		Code = BLANK;

	return true;
}
//---------------------------------------------------------------------------
bool HDMIResolutionClass::GetFormatText(int Format, char *Text, int TextSize)
{
	if (!IsValidMode())
		return false;

	if (Format < MinFormat || Format > MaxFormat)
		return false;

	if (Modes[Mode][Format] == 0)
		return false;

	int Code = Modes[Mode][Format];
	int Width = Codes[Code][0];
	int Aspect = Codes[Code][3];
	int Refresh = Codes[Code][4];

	if (Width != 0)
		std::snprintf(Text, TextSize, "%d Hz (%s)", Refresh, AspectText[Aspect]);
	else
		std::snprintf(Text, TextSize, "Other (%d)", Code);

	return true;
}
//---------------------------------------------------------------------------
int HDMIResolutionClass::GetFormat()
{
	if (!IsValidModeFormat())
		return -1;

	return Format;
}
//---------------------------------------------------------------------------
bool HDMIResolutionClass::SetFormat(int Value)
{
	Format = Value;

	if (!IsValidModeFormat())
		Code = BLANK;
	else
		Code = Modes[Mode][Format];

	return true;
}
//---------------------------------------------------------------------------
int HDMIResolutionClass::GetCode()
{
	return Code;
}
//---------------------------------------------------------------------------
bool HDMIResolutionClass::SetCode(int Value)
{
	Code = Value;
	LastCode = Code;
	return true;
}
//---------------------------------------------------------------------------
bool HDMIResolutionClass::IsValid()
{
	return IsValidMode() && IsValidCode();
}
//---------------------------------------------------------------------------
bool HDMIResolutionClass::IsValidMode()
{
	return Mode >= MinMode && Mode <= MaxMode;
}
//---------------------------------------------------------------------------
bool HDMIResolutionClass::IsValidModeFormat()
{
	return IsValidMode() && Format >= MinFormat && Format <= MaxFormat && Modes[Mode][Format];
}
//---------------------------------------------------------------------------
bool HDMIResolutionClass::IsValidCode()
{
	return Code >= MinCode && Code <= MaxCode;
}
//---------------------------------------------------------------------------
bool HDMIResolutionClass::IsSupported()
{
	return IsValidCode() && Codes[Code][5];
}
//---------------------------------------------------------------------------
bool HDMIResolutionClass::IsOther()
{
	return Mode == MaxMode;
}
//---------------------------------------------------------------------------
