//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "CommonFormClass.h"
#include "Common.h"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TCommonForm *CommonForm;
//---------------------------------------------------------------------------
__fastcall TCommonForm::TCommonForm(TComponent *Owner) : TForm(Owner)
{
	bool Small;
	int ListBoxWidth1;
	int ListBoxWidth2;

	Font->Height = Common::GetFontHeight();
	Canvas->Font->Height = Font->Height;
	GetTextMetrics(Canvas->Handle, &Text);

	Scale = Common::GetFormScale();
	Themed = Common::IsAppThemed();
	Small = Scale < 8;
	LabelSpacing = Scale * 7 / 10 - 1;
	PostLabelSpacing = Small ? LabelSpacing : Scale / 2 + 2;
	ComboBoxHeight = Text.tmHeight + 8;
	NumberWidth = Canvas->TextWidth("9");
	TextBoxPadding = NumberWidth < 6 ? 6 : NumberWidth;
	TextBoxHeight = Text.tmHeight + 8;
	TextBoxSpacing = Scale + Small - 4;
	ButtonWidth = Canvas->TextWidth("Delete") / 2 * 2 + NumberWidth * 2 + Scale % 2;
	ButtonHeight = Text.tmHeight + 8;
	ButtonLeft = -1;
	ButtonRight = -1;
	ButtonTop = -1;
	ButtonBottom = -1;
	LongButtonWidth = Canvas->TextWidth("Delete all") / 2 * 2 + NumberWidth * 2 + Scale % 2;
	LongButtonHeight = ButtonHeight;
	ArrowButtonWidth = ButtonHeight;
	ArrowButtonHeight = ButtonHeight;
	NumGlyphs = 1 + Themed;
	CheckBoxWidth = Common::GetCheckBoxWidth() + (Canvas->TextWidth("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz") + 16) / 104;
	CheckBoxHeight = Text.tmHeight + 4;
	CheckBoxRight = Common::GetCheckBoxRight();
	CheckBoxTop = -1 - Themed + (Small && Themed);
	CheckBoxBottom = -3 + Themed;
	CheckBoxSpacing = Scale / 4 + Small - 2;
	RadioButtonWidth = Common::GetRadioButtonWidth() + (Canvas->TextWidth("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz") + 16) / 104;
	RadioButtonHeight = CheckBoxHeight;
	RadioButtonRight = Common::GetRadioButtonRight();
	RadioButtonTop = CheckBoxTop;
	RadioButtonBottom = CheckBoxBottom;
	RadioButtonSpacing = CheckBoxSpacing;
	PaddingWidth = Scale + 1;
	PaddingTop = Text.tmAscent + Scale;
	PaddingBottom = Scale + 2;
	GroupBoxTop = PaddingTop - Text.tmHeight / 2 * 2 - 1;
	GroupBoxBottom = -1;
	ListBoxWidth1 = Canvas->TextWidth("9999x9999 (99:99) @ 999 Hz") * 2 + NumberWidth * 4 + Small * 4 + 4;
	ListBoxWidth2 = Canvas->TextWidth("Type:") + LabelSpacing + Canvas->TextWidth("VTB-EXT: Video Timing Block") + NumberWidth + ComboBoxHeight + Scale + ButtonLeft + ButtonWidth * 3 + ButtonRight - PaddingWidth * 2;
	ListBoxWidth2 = (ListBoxWidth2 + 1) / 2 * 2;
	ListBoxWidth = ListBoxWidth1 > ListBoxWidth2 ? ListBoxWidth1 : ListBoxWidth2;
	Canvas->Font->Style = TFontStyles() << fsBold;
	LongListBoxWidth = Canvas->TextWidth("9999x9999i (99:9) @ 999 Hz") * 2 + NumberWidth * 4 + Small * 4 + 4;
	Canvas->Font->Style = TFontStyles();
	FormButtonWidth = Text.tmHeight * 5 + Scale + Small + 2;
	FormButtonHeight = Text.tmHeight + Scale + 2;
	FormButtonsWidth = (ButtonLeft + FormButtonWidth + ButtonRight) * 2 + Scale;
}
//---------------------------------------------------------------------------
