//---------------------------------------------------------------------------
#ifndef EDIDListClassH
#define EDIDListClassH
//---------------------------------------------------------------------------
#include <vector>
//---------------------------------------------------------------------------
#define MAX_EDID_BLOCKS                 4
#define MAX_EDID_EXTENSION_BLOCKS       3
//---------------------------------------------------------------------------
class EDIDListClass
{
private:
	std::vector<unsigned char *> Items;
	int Count;

public:
	EDIDListClass();
	void Copy(const EDIDListClass &);
	void Delete();
	EDIDListClass(const EDIDListClass &);
	EDIDListClass &operator=(const EDIDListClass &);
	~EDIDListClass();
	bool Add(unsigned char *);
	bool Delete(int);
	int GetCount();
	bool MatchFullActive(unsigned char *);
	bool MatchFullOverride(unsigned char *, unsigned char *);
	bool MatchPartialOverride(unsigned char *, unsigned char *);
	bool MatchFirstActive(unsigned char *);
};
//---------------------------------------------------------------------------
#endif
