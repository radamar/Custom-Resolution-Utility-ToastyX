//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Common.h"
#include <cstdio>
#include <cstring>
//---------------------------------------------------------------------------
int Common::GetFormSize()
{
	if (Screen->Width < 720 || Screen->Height < 576)
		return 6;

	return 8;
}
//---------------------------------------------------------------------------
int Common::GetFormScale()
{
	return (GetFormSize() * Screen->PixelsPerInch + 96) / 192 * 2;
}
//---------------------------------------------------------------------------
int Common::GetFontHeight()
{
	return GetFormSize() * Screen->PixelsPerInch * 5 / 576 * 2 + 1;
}
//---------------------------------------------------------------------------
BOOL Common::IsAppThemed()
{
	typedef BOOL IsAppThemedProc();
	static IsAppThemedProc *IsAppThemed;
	static HMODULE Library;

	if (!IsAppThemed)
	{
		if (!Library)
		{
			Library = LoadLibrary("uxtheme.dll");

			if (!Library)
				return FALSE;
		}

		IsAppThemed = (IsAppThemedProc *)GetProcAddress(Library, "IsAppThemed");

		if (!IsAppThemed)
			return FALSE;
	}

	return IsAppThemed();
}
//---------------------------------------------------------------------------
int Common::GetCheckBoxWidth()
{
	int i;
	int x[] = {120, 144, 192, 240, 288, 384,   0};
	int y[] = { 15,  18,  23,  29,  35,  43,  55};

	if (!IsAppThemed() || Screen->PixelsPerInch > 480)
		return Screen->PixelsPerInch / 8 + 5;

	for (i = 0; x[i]; i++)
		if (Screen->PixelsPerInch < x[i])
			break;

	return y[i];
}
//---------------------------------------------------------------------------
int Common::GetCheckBoxRight()
{
	int i;
	int x[] = {144,   0};
	int y[] = { -2,  -3};

	if (!IsAppThemed())
		return -2;

	for (i = 0; x[i]; i++)
		if (Screen->PixelsPerInch < x[i])
			break;

	return y[i];
}
//---------------------------------------------------------------------------
int Common::GetRadioButtonWidth()
{
	int i;
	int x[] = {120, 144, 192, 240, 288, 384,   0};
	int y[] = { 15,  18,  23,  29,  35,  42,  55};

	if (!IsAppThemed() || Screen->PixelsPerInch > 480)
		return Screen->PixelsPerInch / 8 + 5;

	for (i = 0; x[i]; i++)
		if (Screen->PixelsPerInch < x[i])
			break;

	return y[i];
}
//---------------------------------------------------------------------------
int Common::GetRadioButtonRight()
{
	int i;
	int x[] = {144,   0};
	int y[] = { -2,  -3};

	if (!IsAppThemed())
		return -2;

	for (i = 0; x[i]; i++)
		if (Screen->PixelsPerInch < x[i])
			break;

	return y[i];
}
//---------------------------------------------------------------------------
int Common::GetScaledResourceID(int ResourceID)
{
	int i;
	int x[] = {9, 11, 13, 15, 17, 19, 21, 23, 0};

	for (i = 0; x[i]; i++)
		if (GetFormScale() < x[i])
			break;

	return ResourceID + IsAppThemed() * 10 + i;
}
//---------------------------------------------------------------------------
bool Common::FixButtonCaption(TButton *Button, int TextWidth)
{
	if (GetFormScale() == 8 && TextWidth % 2 != 0)
		Button->Caption = "{                " + Button->Caption + "                ]";

	return true;
}
//---------------------------------------------------------------------------
void Common::ListBoxDrawItems(TListBox *ListBox, RECT Rect, TOwnerDrawState State, struct Column *Columns, int Count, bool Enabled, bool Bold)
{
	RECT ItemRect;
	int Index;

	if (!Enabled)
	{
		if (State.Contains(odSelected))
			ListBox->Canvas->Brush->Color = clGrayText;
		else
			ListBox->Canvas->Font->Color = clGrayText;
	}

	if (Bold)
		ListBox->Canvas->Font->Style = TFontStyles() << fsBold;

	ListBox->Canvas->FillRect(Rect);
	ItemRect = Rect;
	ItemRect.left += 2;

	if (GetFormScale() == 8)
		ItemRect.left++;

	for (Index = 0; Index < Count; Index++)
	{
		ItemRect.right = ItemRect.left + Columns[Index].Width;
		DrawText(ListBox->Canvas->Handle, Columns[Index].Text, -1, &ItemRect, Columns[Index].Format | DT_NOPREFIX);
		ItemRect.left = ItemRect.right;
	}

	if (State.Contains(odFocused))
		ListBox->Canvas->DrawFocusRect(Rect);
}
//---------------------------------------------------------------------------
void Common::ListBoxDrawItem(TListBox *ListBox, RECT Rect, TOwnerDrawState State, const char *Text, bool Enabled, bool Bold)
{
	RECT ItemRect;

	if (!Enabled)
	{
		if (State.Contains(odSelected))
			ListBox->Canvas->Brush->Color = clGrayText;
		else
			ListBox->Canvas->Font->Color = clGrayText;
	}

	if (Bold)
		ListBox->Canvas->Font->Style = TFontStyles() << fsBold;

	ListBox->Canvas->FillRect(Rect);
	ItemRect = Rect;
	ItemRect.left += 2;

	if (GetFormScale() == 8)
		if (Text[0] < '0' || Text[0] > '9')
			ItemRect.left++;

	DrawText(ListBox->Canvas->Handle, Text, -1, &ItemRect, DT_LEFT | DT_NOPREFIX);

	if (State.Contains(odFocused))
		ListBox->Canvas->DrawFocusRect(Rect);
}
//---------------------------------------------------------------------------
int Common::TextToInteger(const char *Text)
{
	int Value;

	if (std::sscanf(Text, "%d", &Value) <= 0)
		return BLANK;

	return Value;
}
//---------------------------------------------------------------------------
bool Common::IntegerToText(int Value, char *Text, int TextSize)
{
	if (Value == BLANK)
	{
		Text[0] = 0;
		return true;
	}

	std::snprintf(Text, TextSize, "%d", Value);
	return true;
}
//---------------------------------------------------------------------------
long long Common::TextToDecimal(const char *Text, int Digits)
{
	const char *Byte;
	int Negative;
	bool Blank;
	long long Value;
	int Count;

	Byte = Text;

	while (*Byte == ' ')
		Byte++;

	if (*Byte == '-')
	{
		Negative = -1;
		Byte++;
	}
	else
	{
		Negative = 1;

		if (*Byte == '+')
			Byte++;
	}

	Blank = true;
	Value = 0;

	if (*Byte >= '0' && *Byte <= '9')
	{
		Blank = false;

		do
		{
			Value *= 10;
			Value += *Byte - '0';
			Byte++;
		}
		while (*Byte >= '0' && *Byte <= '9');
	}

	Count = 0;

	if (*Byte == '.')
	{
		Byte++;

		if (Count < Digits && *Byte >= '0' && *Byte <= '9')
		{
			Blank = false;

			do
			{
				Value *= 10;
				Value += *Byte - '0';
				Byte++;
				Count++;
			}
			while (Count < Digits && *Byte >= '0' && *Byte <= '9');
		}
	}

	if (Blank)
		return BLANK;

	while (Count < Digits)
	{
		Value *= 10;
		Count++;
	}

	return Negative * Value;
}
//---------------------------------------------------------------------------
bool Common::DecimalToText(long long Value, int MaxLength, int Digits, char *Text, int TextSize)
{
	char *Byte;
	int Count;
	int Negative;

	if (Value == BLANK)
	{
		Text[0] = 0;
		return true;
	}

	Byte = Text;
	Count = 1;

	if (Value < 0)
		Negative = -1;
	else
		Negative = 1;

	while (Count <= Digits && Count < TextSize)
	{
		*Byte = Negative * Value % 10 + '0';
		Value /= 10;
		Byte++;
		Count++;
	}

	if (Count < TextSize)
	{
		if (Digits > 0)
		{
			*Byte = '.';
			Byte++;
			Count++;
        }

		if (Count < TextSize)
		{
			do
			{
				*Byte = Negative * Value % 10 + '0';
				Value /= 10;
				Byte++;
				Count++;
			}
			while (Value != 0 && Count < TextSize);

			if (Negative < 0 && Count < TextSize)
			{
				*Byte = '-';
				Byte++;
			}
		}
	}

	*Byte = 0;
	std::strrev(Text);

	if (MaxLength < TextSize)
	{
		if (Text[MaxLength - 1] == '.')
			Text[MaxLength - 1] = 0;
		else
			Text[MaxLength] = 0;
	}

	return true;
}
//---------------------------------------------------------------------------
