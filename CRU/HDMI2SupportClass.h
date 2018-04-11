//---------------------------------------------------------------------------
#ifndef HDMI2SupportClassH
#define HDMI2SupportClassH
//---------------------------------------------------------------------------
#include "ItemClass.h"
//---------------------------------------------------------------------------
class HDMI2SupportClass : public ItemClass
{
private:
	static const int MinTMDSRate;
	static const int MaxTMDSRate;
	static const int ModTMDSRate;
	static const int FeaturesMask;
	static const int ColorFormatsMask;

	int Version;
	int TMDSRate;
	int Features;
	int ColorFormats;

public:
	HDMI2SupportClass();
	bool Read(const unsigned char *, int);
	bool Write(unsigned char *, int);
	int GetTMDSRate();
	bool SetTMDSRate(int);
	bool GetFeature(int);
	bool SetFeature(int, bool);
	bool GetColorFormat(int);
	bool SetColorFormat(int, bool);
	bool IsValid();
	bool IsValidTMDSRate();
};
//---------------------------------------------------------------------------
#endif
