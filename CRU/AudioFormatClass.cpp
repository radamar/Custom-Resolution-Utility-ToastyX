//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "AudioFormatClass.h"
#include <cstdio>
//---------------------------------------------------------------------------
const char *AudioFormatClass::FormatText[] =
{
	"Other (0)",
	"LPCM",
	"AC-3",
	"MPEG-1",
	"MP3",
	"MPEG-2",
	"AAC",
	"DTS",
	"ATRAC",
	"DSD",
	"E-AC-3",
	"DTS-HD",
	"TrueHD",
	"DST",
	"WMA Pro",
	"Extension",
};

const char *AudioFormatClass::ChannelsText[] =
{
	"0",
	"1",
	"2 (Stereo)",
	"3",
	"4",
	"5",
	"6 (5.1)",
	"7",
	"8 (7.1)",
};

const int AudioFormatClass::MinFormat = 0;
const int AudioFormatClass::MaxFormat = 15;
const int AudioFormatClass::MinChannels = 1;
const int AudioFormatClass::MaxChannels = 8;
const int AudioFormatClass::SampleRatesMask = 127;
const int AudioFormatClass::BitDepthsMask = 7;
const int AudioFormatClass::MinBitRate = 0;
const int AudioFormatClass::MaxBitRate = 2040;
const int AudioFormatClass::ModBitRate = 8;
const int AudioFormatClass::MinFlags = 0;
const int AudioFormatClass::MaxFlags = 255;
//---------------------------------------------------------------------------
AudioFormatClass::AudioFormatClass()
{
	Format = 1;
	Channels = 8;
	SampleRates = 127;
	BitDepths = 7;
	BitRate = 640;
	Flags = 0;
}
//---------------------------------------------------------------------------
bool AudioFormatClass::Read(const unsigned char *Data, int MaxSize)
{
	if (!Data)
		return false;

	if (MaxSize < 3)
		return false;

	Format = (Data[0] >> 3) & 15;
	Channels = (Data[0] & 7) + 1;
	SampleRates = Data[1] & SampleRatesMask;

	if (Format == 1)
		BitDepths = Data[2] & BitDepthsMask;
	else if (Format >= 2 && Format <= 8)
		BitRate = Data[2] << 3;
	else
		Flags = Data[2];

	return true;
}
//---------------------------------------------------------------------------
bool AudioFormatClass::Write(unsigned char *Data, int MaxSize)
{
	if (!Data)
		return false;

	if (MaxSize < 3)
		return false;

	if (!IsValid())
		return false;

	Data[0] = ((Format & 15) << 3) | ((Channels - 1) & 7);
	Data[1] = SampleRates & SampleRatesMask;

	if (Format == 1)
		Data[2] = BitDepths & BitDepthsMask;
	else if (Format >= 2 && Format <= 8)
		Data[2] = (BitRate >> 3) & 255;
	else
		Data[2] = Flags & 255;

	return true;
}
//---------------------------------------------------------------------------
bool AudioFormatClass::GetInfoText(char *Text, int TextSize)
{
	if (!IsValid())
		return false;

	if (Format >= 2 && Format <= 8)
		std::snprintf(Text, TextSize, "Max: %d kbit/s", BitRate);
	else if (Format != 1 && Flags != 0)
		std::snprintf(Text, TextSize, "Flags: %d", Flags);
	else
		Text[0] = 0;

	return true;
}
//---------------------------------------------------------------------------
bool AudioFormatClass::GetFormatText(int Format, char *Text, int TextSize)
{
	if (Format < MinFormat || Format > MaxFormat)
		return false;

	std::snprintf(Text, TextSize, "%s", FormatText[Format]);
	return true;
}
//---------------------------------------------------------------------------
int AudioFormatClass::GetFormat()
{
	if (!IsValidFormat())
		return -1;

	return Format;
}
//---------------------------------------------------------------------------
bool AudioFormatClass::SetFormat(int Value)
{
	Format = Value;
	return true;
}
//---------------------------------------------------------------------------
bool AudioFormatClass::GetChannelsText(int Channels, char *Text, int TextSize)
{
	if (Channels < MinChannels || Channels > MaxChannels)
		return false;

	std::snprintf(Text, TextSize, "%s", ChannelsText[Channels]);
	return true;
}
//---------------------------------------------------------------------------
int AudioFormatClass::GetChannels()
{
	if (!IsValidChannels())
		return -1;

	return Channels;
}
//---------------------------------------------------------------------------
bool AudioFormatClass::SetChannels(int Value)
{
	Channels = Value;
	return true;
}
//---------------------------------------------------------------------------
bool AudioFormatClass::GetSampleRate(int Index)
{
	if (!(SampleRatesMask & (1 << Index)))
		return false;

	return SampleRates & (1 << Index);
}
//---------------------------------------------------------------------------
bool AudioFormatClass::SetSampleRate(int Index, bool Enabled)
{
	if (!(SampleRatesMask & (1 << Index)))
		return false;

	if (Enabled)
		SampleRates |= 1 << Index;
	else
		SampleRates &= ~(1 << Index);

	return true;
}
//---------------------------------------------------------------------------
bool AudioFormatClass::GetBitDepth(int Index)
{
	if (!(BitDepthsMask & (1 << Index)))
		return false;

	return BitDepths & (1 << Index);
}
//---------------------------------------------------------------------------
bool AudioFormatClass::SetBitDepth(int Index, bool Enabled)
{
	if (!(BitDepthsMask & (1 << Index)))
		return false;

	if (Enabled)
		BitDepths |= 1 << Index;
	else
		BitDepths &= ~(1 << Index);

	return true;
}
//---------------------------------------------------------------------------
int AudioFormatClass::GetBitRate()
{
	return BitRate;
}
//---------------------------------------------------------------------------
bool AudioFormatClass::SetBitRate(int Value)
{
	BitRate = Value;
	return true;
}
//---------------------------------------------------------------------------
int AudioFormatClass::GetFlags()
{
	return Flags;
}
//---------------------------------------------------------------------------
bool AudioFormatClass::SetFlags(int Value)
{
	Flags = Value;
	return true;
}
//---------------------------------------------------------------------------
bool AudioFormatClass::IsValid()
{
	if (Format == 1)
		return IsValidFormat() && IsValidChannels();

	if (Format >= 2 && Format <= 8)
		return IsValidFormat() && IsValidChannels() && IsValidBitRate();

	return IsValidFormat() && IsValidChannels() && IsValidFlags();
}
//---------------------------------------------------------------------------
bool AudioFormatClass::IsValidFormat()
{
	return Format >= MinFormat && Format <= MaxFormat;
}
//---------------------------------------------------------------------------
bool AudioFormatClass::IsValidChannels()
{
	return Channels >= MinChannels && Channels <= MaxChannels;
}
//---------------------------------------------------------------------------
bool AudioFormatClass::IsValidBitRate()
{
	return BitRate >= MinBitRate && BitRate <= MaxBitRate && BitRate % ModBitRate == 0;
}
//---------------------------------------------------------------------------
bool AudioFormatClass::IsValidFlags()
{
	return Flags >= MinFlags && Flags <= MaxFlags;
}
//---------------------------------------------------------------------------
bool AudioFormatClass::IsSupported()
{
	if (Format == 0)
		return false;

	return IsValidFormat();
}
//---------------------------------------------------------------------------
