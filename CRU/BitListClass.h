//---------------------------------------------------------------------------
#ifndef BitListClassH
#define BitListClassH
//---------------------------------------------------------------------------
class BitListClass
{
protected:
	int DataSize;
	int BitCount;

	unsigned char *BitMask;
	unsigned char *BitData;
	unsigned char *UndoBitData;
	unsigned char *RedoBitData;

public:
	BitListClass(int, const char *);
	void Copy(const BitListClass &);
	void Delete();
	BitListClass(const BitListClass &);
	BitListClass &operator=(const BitListClass &);
	~BitListClass();
	bool AllPossible();
	bool All();
	bool NonePossible();
	bool None();
	bool UpdateUndo();
	bool UndoPossible();
	bool Undo();
	bool RedoPossible();
	bool Redo();
};
//---------------------------------------------------------------------------
#endif
