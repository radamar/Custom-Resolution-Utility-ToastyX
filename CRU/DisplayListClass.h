//---------------------------------------------------------------------------
#ifndef DisplayListClassH
#define DisplayListClassH
//---------------------------------------------------------------------------
#include "DisplayClass.h"
#include <vector>
//---------------------------------------------------------------------------
class DisplayListClass
{
private:
	std::vector<DisplayClass *> Items;
	int Count;
	int ItemIndex;

public:
	DisplayListClass();
	bool Load();
	bool LoadDisplays();
	bool LoadDisplay(const char *);
	bool LoadDevice(const char *, const char *);
	bool Add(DisplayClass *);
	bool Save();
	int GetCount();
	bool Sort();
	bool GetItemText(int, char *, int);
	int GetCurrent();
	bool SetCurrent(int);
	DisplayClass *Current();
};
//---------------------------------------------------------------------------
#endif
