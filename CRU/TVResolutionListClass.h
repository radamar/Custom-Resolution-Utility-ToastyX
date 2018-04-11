//---------------------------------------------------------------------------
#ifndef TVResolutionListClassH
#define TVResolutionListClassH
//---------------------------------------------------------------------------
#include "ListClass.h"
#include "ItemClass.h"
//---------------------------------------------------------------------------
class TVResolutionListClass : public ListClass, public ItemClass
{
private:
	bool YCbCr420;
	bool UndoYCbCr420;
	bool RedoYCbCr420;

public:
	TVResolutionListClass(int = 31);
	bool Read(const unsigned char *, int);
	bool Write(unsigned char *, int);
	bool YCbCr420Possible();
	bool GetYCbCr420();
	bool SetYCbCr420(bool);
	bool UpdateUndo();
	bool UndoPossible();
	bool Undo();
	bool RedoPossible();
	bool Redo();
};
//---------------------------------------------------------------------------
#endif
