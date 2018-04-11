//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "FreeSyncRangeFormClass.h"
#include "Common.h"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TFreeSyncRangeForm *FreeSyncRangeForm;
//---------------------------------------------------------------------------
__fastcall TFreeSyncRangeForm::TFreeSyncRangeForm(TComponent *Owner) : TCommonForm(Owner)
{
	Refreshing = false;
}
//---------------------------------------------------------------------------
bool TFreeSyncRangeForm::Connect(FreeSyncRangeClass &NewFreeSyncRange)
{
	FreeSyncRange = &NewFreeSyncRange;
	return true;
}
//---------------------------------------------------------------------------
TColor TFreeSyncRangeForm::GetTextColor(bool Valid)
{
	if (!Valid)
		return (TColor)RGB(255, 0, 0);

	return clWindowText;
}
//---------------------------------------------------------------------------
bool TFreeSyncRangeForm::Refresh(void *Value)
{
	Refreshing = true;

	if (Value == NULL || Value == RangeLimitsGroupBox)
		RefreshRangeLimitsTextBoxes();

	if (Value != FormOKButton)
		FormOKButton->Enabled = FreeSyncRange->IsValid();

	Refreshing = false;
	return true;
}
//---------------------------------------------------------------------------
bool TFreeSyncRangeForm::RefreshRangeLimitsTextBoxes()
{
	char Text[TEXTSIZE];

	MinVRate->Font->Color = GetTextColor(FreeSyncRange->IsValidMinVRate());

	if (!MinVRate->Focused() && Common::IntegerToText(FreeSyncRange->GetMinVRate(), Text, TEXTSIZE))
		MinVRate->Text = Text;

	MaxVRate->Font->Color = GetTextColor(FreeSyncRange->IsValidMaxVRate());

	if (!MaxVRate->Focused() && Common::IntegerToText(FreeSyncRange->GetMaxVRate(), Text, TEXTSIZE))
		MaxVRate->Text = Text;

	return true;
}
//---------------------------------------------------------------------------
bool TFreeSyncRangeForm::ScaleControls()
{
	int DashWidth = NumberWidth;
	int DashHeight = Text.tmHeight < 22 ? 1 : (Text.tmHeight + 13) / 16;
	int DashSpacing = NumberWidth;

	MinVRate->AutoSize = false;
	MinVRate->Width = MinVRate->MaxLength * NumberWidth + TextBoxPadding;
	MinVRate->Height = TextBoxHeight;

	VRateDash->Width = DashWidth;
	VRateDash->Height = DashHeight;

	MaxVRate->AutoSize = false;
	MaxVRate->Width = MaxVRate->MaxLength * NumberWidth + TextBoxPadding;
	MaxVRate->Height = TextBoxHeight;

	VRateLabel->Left = PaddingWidth;
	MinVRate->Left = VRateLabel->Left + VRateLabel->Width + LabelSpacing;
	VRateDash->Left = MinVRate->Left + MinVRate->Width + DashSpacing;
	MaxVRate->Left = VRateDash->Left + VRateDash->Width + DashSpacing;
	HzLabel->Left = MaxVRate->Left + MaxVRate->Width + PostLabelSpacing;

	MinVRate->Top = PaddingTop;
	MaxVRate->Top = MinVRate->Top;

	VRateLabel->Top = MinVRate->Top + 3;
	VRateDash->Top = MinVRate->Top + MinVRate->Height / 2;
	HzLabel->Top = VRateLabel->Top;

	RangeLimitsGroupBox->Width = FormButtonsWidth;
	RangeLimitsGroupBox->Height = MinVRate->Top + MinVRate->Height + PaddingBottom;
	RangeLimitsGroupBox->Left = Scale;
	RangeLimitsGroupBox->Top = GroupBoxTop;

	FormOKButton->Width = FormButtonWidth;
	FormOKButton->Height = FormButtonHeight;
	FormOKButton->Top = RangeLimitsGroupBox->Top + RangeLimitsGroupBox->Height + GroupBoxBottom + Scale + ButtonTop;
	Common::FixButtonCaption(FormOKButton, Canvas->TextWidth(FormOKButton->Caption));

	FormCancelButton->Width = FormButtonWidth;
	FormCancelButton->Height = FormButtonHeight;
	FormCancelButton->Top = FormOKButton->Top;
	Common::FixButtonCaption(FormCancelButton, Canvas->TextWidth(FormCancelButton->Caption));

	FormCancelButton->Left = RangeLimitsGroupBox->Left + RangeLimitsGroupBox->Width - ButtonRight - FormCancelButton->Width;
	FormOKButton->Left = FormCancelButton->Left - ButtonLeft - Scale - ButtonRight - FormOKButton->Width;

	ClientWidth = FormCancelButton->Left + FormCancelButton->Width + ButtonRight + Scale;
	ClientHeight = FormCancelButton->Top + FormCancelButton->Height + ButtonBottom + Scale;
	return true;
}
//---------------------------------------------------------------------------
void __fastcall TFreeSyncRangeForm::FormCreate(TObject *Sender)
{
	ScaleControls();
}
//---------------------------------------------------------------------------
void __fastcall TFreeSyncRangeForm::FormShow(TObject *Sender)
{
	Refresh(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TFreeSyncRangeForm::MinVRateChange(TObject *Sender)
{
	if (Refreshing)
		return;

	FreeSyncRange->SetMinVRate(Common::TextToInteger(MinVRate->Text.c_str()));
	Refresh(RangeLimitsGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TFreeSyncRangeForm::MinVRateExit(TObject *Sender)
{
	Refresh(RangeLimitsGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TFreeSyncRangeForm::MaxVRateChange(TObject *Sender)
{
	if (Refreshing)
		return;

	FreeSyncRange->SetMaxVRate(Common::TextToInteger(MaxVRate->Text.c_str()));
	Refresh(RangeLimitsGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TFreeSyncRangeForm::MaxVRateExit(TObject *Sender)
{
	Refresh(RangeLimitsGroupBox);
}
//---------------------------------------------------------------------------
