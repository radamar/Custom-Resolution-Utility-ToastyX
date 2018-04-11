//---------------------------------------------------------------------------
#ifndef ColorimetryClassH
#define ColorimetryClassH
//---------------------------------------------------------------------------
#include "ItemClass.h"
//---------------------------------------------------------------------------
class ColorimetryClass : public ItemClass
{
private:
	static const unsigned char ColorimetryMask[2];
	static const int MinColorimetry;
	static const int MaxColorimetry;
	static const int MinMetadata;
	static const int MaxMetadata;

	unsigned char Colorimetry[2];

public:
	ColorimetryClass();
	bool Read(const unsigned char *, int);
	bool Write(unsigned char *, int);
	bool GetColorimetry(int);
	bool SetColorimetry(int, bool);
	bool GetMetadata(int);
	bool SetMetadata(int, bool);
};
//---------------------------------------------------------------------------
#endif
