//---------------------------------------------------------------------------
#ifndef AudioFormatClassH
#define AudioFormatClassH
//---------------------------------------------------------------------------
#include "ItemClass.h"
//---------------------------------------------------------------------------
class AudioFormatClass : public ItemClass
{
private:
	static const char *FormatText[];
	static const char *ChannelsText[];

	static const int MinFormat;
	static const int MaxFormat;
	static const int MinChannels;
	static const int MaxChannels;
	static const int SampleRatesMask;
	static const int BitDepthsMask;
	static const int MinBitRate;
	static const int MaxBitRate;
	static const int ModBitRate;
	static const int MinFlags;
	static const int MaxFlags;

	int Format;
	int Channels;
	int SampleRates;
	int BitDepths;
	int BitRate;
	int Flags;

public:
	AudioFormatClass();
	bool Read(const unsigned char *, int);
	bool Write(unsigned char *, int);
	bool GetInfoText(char *, int);
	bool GetFormatText(int, char *, int);
	int GetFormat();
	bool SetFormat(int);
	bool GetChannelsText(int, char *, int);
	int GetChannels();
	bool SetChannels(int);
	bool GetSampleRate(int);
	bool SetSampleRate(int, bool);
	bool GetBitDepth(int);
	bool SetBitDepth(int, bool);
	int GetBitRate();
	bool SetBitRate(int);
	int GetFlags();
	bool SetFlags(int);
	bool IsValid();
	bool IsValidFormat();
	bool IsValidChannels();
	bool IsValidBitRate();
	bool IsValidFlags();
	bool IsSupported();
};
//---------------------------------------------------------------------------
#endif
