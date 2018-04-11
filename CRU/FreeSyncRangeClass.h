//---------------------------------------------------------------------------
#ifndef FreeSyncRangeClassH
#define FreeSyncRangeClassH
//---------------------------------------------------------------------------
#include "ItemClass.h"
//---------------------------------------------------------------------------
class FreeSyncRangeClass : public ItemClass
{
private:
	static const int MinVRange;
	static const int MaxVRange;

	int MinVRate;
	int MaxVRate;

public:
	FreeSyncRangeClass();
	bool Read(const unsigned char *, int);
	bool Write(unsigned char *, int);
	int GetMinVRate();
	bool SetMinVRate(int);
	int GetMaxVRate();
	bool SetMaxVRate(int);
	bool IsValid();
	bool IsValidMinVRate();
	bool IsValidMaxVRate();
};
//---------------------------------------------------------------------------
#endif
