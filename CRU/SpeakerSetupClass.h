//---------------------------------------------------------------------------
#ifndef SpeakerSetupClassH
#define SpeakerSetupClassH
//---------------------------------------------------------------------------
#include "BitListClass.h"
#include "ItemClass.h"
//---------------------------------------------------------------------------
class SpeakerSetupClass : public BitListClass, public ItemClass
{
public:
	SpeakerSetupClass();
	bool Read(const unsigned char *, int);
	bool Write(unsigned char *, int);
	bool Get(int);
	bool Set(int, bool);
	bool Set20Possible();
	bool Set20();
	bool Set51Possible();
	bool Set51();
	bool Set71Possible();
	bool Set71();
};
//---------------------------------------------------------------------------
#endif
