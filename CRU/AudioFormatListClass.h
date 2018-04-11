//---------------------------------------------------------------------------
#ifndef AudioFormatListClassH
#define AudioFormatListClassH
//---------------------------------------------------------------------------
#include "ListClass.h"
#include "ItemClass.h"
//---------------------------------------------------------------------------
class AudioFormatListClass : public ListClass, public ItemClass
{
public:
	AudioFormatListClass(int = 10);
	bool Read(const unsigned char *, int);
	bool Write(unsigned char *, int);
};
//---------------------------------------------------------------------------
#endif
