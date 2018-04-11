//---------------------------------------------------------------------------
#ifndef VideoCapabilityClassH
#define VideoCapabilityClassH
//---------------------------------------------------------------------------
#include "ItemClass.h"
//---------------------------------------------------------------------------
enum
{
	S_CE0,
	S_CE1,
	S_IT0,
	S_IT1,
	S_PT0,
	S_PT1,
	QS,
	QY,
};
//---------------------------------------------------------------------------
class VideoCapabilityClass : public ItemClass
{
private:
	static const int VideoCapabilityMask;

	int VideoCapability;

public:
	VideoCapabilityClass();
	bool Read(const unsigned char *, int);
	bool Write(unsigned char *, int);
	bool GetVideoCapability(int);
	bool SetVideoCapability(int, bool);
};
//---------------------------------------------------------------------------
#endif
