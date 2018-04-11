//---------------------------------------------------------------------------
#ifndef EstablishedResolutionListClassH
#define EstablishedResolutionListClassH
//---------------------------------------------------------------------------
#include "BitListClass.h"
//---------------------------------------------------------------------------
class EstablishedResolutionListClass : public BitListClass
{
public:
	EstablishedResolutionListClass();
	bool Read(const unsigned char *, int);
	bool Write(unsigned char *, int);
	bool Get(int);
	bool Set(int, bool);
};
//---------------------------------------------------------------------------
#endif
