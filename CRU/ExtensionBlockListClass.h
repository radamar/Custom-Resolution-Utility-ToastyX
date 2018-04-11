//---------------------------------------------------------------------------
#ifndef ExtensionBlockListClassH
#define ExtensionBlockListClassH
//---------------------------------------------------------------------------
#include "ListClass.h"
//---------------------------------------------------------------------------
class ExtensionBlockListClass : public ListClass
{
public:
	ExtensionBlockListClass(int);
	bool Read(const unsigned char *, int);
	bool Write(unsigned char *, int);
	bool WriteBlankExtension(unsigned char *, int);
	bool EditPossible(int);
};
//---------------------------------------------------------------------------
#endif
