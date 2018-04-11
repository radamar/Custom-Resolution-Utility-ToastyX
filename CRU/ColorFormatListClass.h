//---------------------------------------------------------------------------
#ifndef ColorFormatListClassH
#define ColorFormatListClassH
//---------------------------------------------------------------------------
class ColorFormatListClass
{
private:
	bool YCbCr422;
	bool UndoYCbCr422;
	bool RedoYCbCr422;

	bool YCbCr444;
	bool UndoYCbCr444;
	bool RedoYCbCr444;

public:
	ColorFormatListClass();
	bool Read(const unsigned char *);
	bool Write(unsigned char *);
	bool Get(ColorFormatListClass &);
	bool Set(const ColorFormatListClass &);
	bool GetYCbCr422();
	bool SetYCbCr422(bool);
	bool GetYCbCr444();
	bool SetYCbCr444(bool);
	bool UpdateUndo();
	bool UndoPossible();
	bool Undo();
	bool RedoPossible();
	bool Redo();
};
//---------------------------------------------------------------------------
#endif
