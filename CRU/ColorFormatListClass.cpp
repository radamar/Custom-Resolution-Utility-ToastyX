//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "ColorFormatListClass.h"
//---------------------------------------------------------------------------
ColorFormatListClass::ColorFormatListClass()
{
	YCbCr422 = true;
	UndoYCbCr422 = YCbCr422;
	RedoYCbCr422 = YCbCr422;

	YCbCr444 = true;
	UndoYCbCr444 = YCbCr444;
	RedoYCbCr444 = YCbCr444;
}
//---------------------------------------------------------------------------
bool ColorFormatListClass::Read(const unsigned char *Data)
{
	if (!Data)
		return false;

	YCbCr422 = false;
	YCbCr444 = false;

	if (Data[0] & 16)
		YCbCr422 = true;

	if (Data[0] & 32)
		YCbCr444 = true;

	return true;
}
//---------------------------------------------------------------------------
bool ColorFormatListClass::Write(unsigned char *Data)
{
	if (!Data)
		return false;

	Data[0] &= 207;

	if (YCbCr422)
		Data[0] |= 16;

	if (YCbCr444)
		Data[0] |= 32;

	return true;
}
//---------------------------------------------------------------------------
bool ColorFormatListClass::Get(ColorFormatListClass &ColorFormatList)
{
	ColorFormatList.YCbCr422 = YCbCr422;
	ColorFormatList.YCbCr444 = YCbCr444;
	return true;
}
//---------------------------------------------------------------------------
bool ColorFormatListClass::Set(const ColorFormatListClass &ColorFormatList)
{
	YCbCr422 = ColorFormatList.YCbCr422;
	YCbCr444 = ColorFormatList.YCbCr444;
	return true;
}
//---------------------------------------------------------------------------
bool ColorFormatListClass::GetYCbCr422()
{
	return YCbCr422;
}
//---------------------------------------------------------------------------
bool ColorFormatListClass::SetYCbCr422(bool Enabled)
{
	YCbCr422 = Enabled;
	return true;
}
//---------------------------------------------------------------------------
bool ColorFormatListClass::GetYCbCr444()
{
	return YCbCr444;
}
//---------------------------------------------------------------------------
bool ColorFormatListClass::SetYCbCr444(bool Enabled)
{
	YCbCr444 = Enabled;
	return true;
}
//---------------------------------------------------------------------------
bool ColorFormatListClass::UpdateUndo()
{
	UndoYCbCr422 = YCbCr422;
	RedoYCbCr422 = YCbCr422;
	UndoYCbCr444 = YCbCr444;
	RedoYCbCr444 = YCbCr444;
	return true;
}
//---------------------------------------------------------------------------
bool ColorFormatListClass::UndoPossible()
{
	if (YCbCr422 != UndoYCbCr422)
		return true;

	if (YCbCr444 != UndoYCbCr444)
		return true;

	return false;
}
//---------------------------------------------------------------------------
bool ColorFormatListClass::Undo()
{
	RedoYCbCr422 = YCbCr422;
	YCbCr422 = UndoYCbCr422;
	RedoYCbCr444 = YCbCr444;
	YCbCr444 = UndoYCbCr444;
	return true;
}
//---------------------------------------------------------------------------
bool ColorFormatListClass::RedoPossible()
{
	if (YCbCr422 != RedoYCbCr422)
		return true;

	if (YCbCr444 != RedoYCbCr444)
		return true;

	return false;
}
//---------------------------------------------------------------------------
bool ColorFormatListClass::Redo()
{
	UndoYCbCr422 = YCbCr422;
	YCbCr422 = RedoYCbCr422;
	UndoYCbCr444 = YCbCr444;
	YCbCr444 = RedoYCbCr444;
	return true;
}
//---------------------------------------------------------------------------
