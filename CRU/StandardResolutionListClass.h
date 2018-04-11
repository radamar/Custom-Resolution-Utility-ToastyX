//---------------------------------------------------------------------------
#ifndef StandardResolutionListClassH
#define StandardResolutionListClassH
//---------------------------------------------------------------------------
#include "ListClass.h"
//---------------------------------------------------------------------------
class StandardResolutionListClass : public ListClass
{
public:
	StandardResolutionListClass(int);
	bool Read(const unsigned char *, int);
	bool Write(unsigned char *, int);
	bool ReadExtension(const unsigned char *, int);
	bool WriteExtension(unsigned char *, int);
};
//---------------------------------------------------------------------------
#endif
