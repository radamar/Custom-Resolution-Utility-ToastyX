//---------------------------------------------------------------------------
#ifndef DetailedResolutionListClassH
#define DetailedResolutionListClassH
//---------------------------------------------------------------------------
#include "ListClass.h"
#include "DetailedResolutionClass.h"
//---------------------------------------------------------------------------
class DetailedResolutionListClass : public ListClass
{
public:
	DetailedResolutionListClass(int);
	bool Read(const unsigned char *, int);
	bool Write(unsigned char *, int);
	bool GetNative(DetailedResolutionClass &);
	bool GetStandardText(int, char *, int, int);
	bool GetExtensionText(int, char *, int, int);
	bool GetExtensionStandardText(int, char *, int, int);
};
//---------------------------------------------------------------------------
#endif
