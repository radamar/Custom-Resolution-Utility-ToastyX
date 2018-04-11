//---------------------------------------------------------------------------
#ifndef StandardResolutionClassH
#define StandardResolutionClassH
//---------------------------------------------------------------------------
#include "ItemClass.h"
//---------------------------------------------------------------------------
class StandardResolutionClass : public ItemClass
{
private:
	static const int HAspect[];
	static const int VAspect[];
	static const int Modes[][2];

	static const int MinMode;
	static const int MaxMode;
	static const int MinAspect;
	static const int MaxAspect;
	static const int MinWidth;
	static const int MaxWidth;
	static const int ModWidth;
	static const int MinRate;
	static const int MaxRate;

	int Mode;
	int Aspect;
	int Width;
	int Height;
	int LastAspect;
	int LastWidth;
	int LastHeight;
	int Rate;

public:
	StandardResolutionClass();
	bool Read(const unsigned char *, int);
	bool Write(unsigned char *, int);
	bool GetText(char *, int);
	bool GetModeText(int, char *, int);
	int GetMode();
	bool SetMode(int);
	bool UpdateAspect();
	int GetWidth();
	bool SetWidth(int);
	int GetHeight();
	bool SetHeight(int);
	int GetRate();
	bool SetRate(int);
	bool IsValid();
	bool IsValidMode();
	bool IsValidAspect();
	bool IsValidWidth();
	bool IsValidHeight();
	bool IsValidRate();
	bool IsSupported();
	bool IsOther();
};
//---------------------------------------------------------------------------
#endif
