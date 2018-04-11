//---------------------------------------------------------------------------
#ifndef CommonH
#define CommonH
//---------------------------------------------------------------------------
#include "ItemClass.h"
//---------------------------------------------------------------------------
#define ARROW_UP	100
#define ARROW_DOWN	200
//---------------------------------------------------------------------------
namespace Common
{
	struct Column
	{
		char Text[TEXTSIZE];
		int Width;
		int Format;
	};

	int GetFormSize();
	int GetFormScale();
	int GetFontHeight();
	BOOL IsAppThemed();
	int GetCheckBoxWidth();
	int GetCheckBoxRight();
	int GetRadioButtonWidth();
	int GetRadioButtonRight();
	int GetScaledResourceID(int);
	bool FixButtonCaption(TButton *, int);
	void ListBoxDrawItems(TListBox *, RECT, TOwnerDrawState, struct Column *, int, bool, bool);
	void ListBoxDrawItem(TListBox *, RECT, TOwnerDrawState, const char *, bool, bool);
	int TextToInteger(const char *);
	bool IntegerToText(int, char *, int);
	long long TextToDecimal(const char *, int);
	bool DecimalToText(long long, int, int, char *, int);
}
//---------------------------------------------------------------------------
#endif
