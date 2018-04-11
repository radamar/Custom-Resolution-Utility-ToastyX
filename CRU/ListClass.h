//---------------------------------------------------------------------------
#ifndef ListClassH
#define ListClassH
//---------------------------------------------------------------------------
#include "ItemClass.h"
//---------------------------------------------------------------------------
class ListClass
{
protected:
	int SlotCount;
	int UndoSlotCount;
	int RedoSlotCount;
	int MaxSlotCount;
	int MaxMaxSlotCount;

	int SlotSize;

	int DataSize;
	int UndoDataSize;
	int RedoDataSize;
	int MaxDataSize;
	int MaxMaxDataSize;

	unsigned char *SlotData;
	unsigned char *UndoSlotData;
	unsigned char *RedoSlotData;

public:
	ListClass(int, int);
	void Copy(const ListClass &);
	void Delete();
	ListClass(const ListClass &);
	ListClass &operator=(const ListClass &);
	~ListClass();
	virtual int GetCount();
	virtual int GetMaxCount();
	virtual int GetSize();
	virtual int GetMaxSize();
	virtual int GetSlotSize(int);
	virtual int GetMaxSlotSize(int);
	virtual int GetSlotsLeft();
	virtual int GetBytesLeft();
	virtual bool GetSlotsLeftText(const char *, char *, int);
	virtual bool GetBytesLeftText(const char *, char *, int);
	virtual bool UpdateSize();
	virtual bool SetMaxCount(int);
	virtual bool SetMaxSize(int);
	virtual bool AddPossible();
	virtual bool Add(ItemClass &);
	virtual bool EditPossible(int);
	virtual bool Get(int, ItemClass &);
	virtual bool Set(int, ItemClass &);
	virtual bool DeletePossible(int);
	virtual bool Delete(int);
	virtual bool DeleteAllPossible();
	virtual bool DeleteAll();
	virtual bool UpdateUndo();
	virtual bool UndoPossible();
	virtual bool Undo();
	virtual bool RedoPossible();
	virtual bool Redo();
	virtual bool ExchangePossible(int, int);
	virtual bool Exchange(int, int);
	static bool ExchangeData(unsigned char *, unsigned char *, int);
};
//---------------------------------------------------------------------------
#endif
