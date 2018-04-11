//---------------------------------------------------------------------------
#ifndef HDMIResolutionClassH
#define HDMIResolutionClassH
//---------------------------------------------------------------------------
#include "ItemClass.h"
//---------------------------------------------------------------------------
class HDMIResolutionClass : public ItemClass
{
private:
	static const char *AspectText[];
	static const int MinMode;
	static const int MaxMode;
	static const int MinFormat;
	static const int MaxFormat;
	static const int Modes[][4];
	static const int MinCode;
	static const int MaxCode;
	static const short Codes[256][6];

	int Mode;
	int Format;
	int Code;
	int LastCode;

public:
	HDMIResolutionClass();
	bool Read(const unsigned char *, int);
	bool Write(unsigned char *, int);
	bool GetText(char *, int);
	bool GetModeText(int, char *, int);
	int GetMode();
	bool SetMode(int);
	bool GetFormatText(int, char *, int);
	int GetFormat();
	bool SetFormat(int);
	int GetCode();
	bool SetCode(int);
	bool IsValid();
	bool IsValidMode();
	bool IsValidModeFormat();
	bool IsValidCode();
	bool IsSupported();
	bool IsOther();
};
//---------------------------------------------------------------------------
#endif
