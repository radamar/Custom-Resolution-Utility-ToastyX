//---------------------------------------------------------------------------
#ifndef DIDDetailedResolutionListClassH
#define DIDDetailedResolutionListClassH
//---------------------------------------------------------------------------
#include "ListClass.h"
#include "ItemClass.h"
//---------------------------------------------------------------------------
class DIDDetailedResolutionListClass : public ListClass, public ItemClass
{
public:
	DIDDetailedResolutionListClass(int = 5);
	bool Read(const unsigned char *, int);
	bool Write(unsigned char *, int);
};
//---------------------------------------------------------------------------
#endif
