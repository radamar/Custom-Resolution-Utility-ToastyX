//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "StandardResolutionFormClass.h"
#include "Common.h"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TStandardResolutionForm *StandardResolutionForm;
//---------------------------------------------------------------------------
__fastcall TStandardResolutionForm::TStandardResolutionForm(TComponent *Owner) : TCommonForm(Owner)
{
	Refreshing = false;
}
//---------------------------------------------------------------------------
bool TStandardResolutionForm::Connect(StandardResolutionClass &NewStandardResolution)
{
	StandardResolution = &NewStandardResolution;
	return true;
}
//---------------------------------------------------------------------------
TColor TStandardResolutionForm::GetTextColor(bool Valid)
{
	if (!Valid)
		return (TColor)RGB(255, 0, 0);

	return clWindowText;
}
//---------------------------------------------------------------------------
bool TStandardResolutionForm::Refresh(void *Value)
{
	char Text[TEXTSIZE];

	Refreshing = true;

	if (!StandardResolution->IsOther())
	{
		RateLabel->Visible = true;
		Width->Visible = false;
		ByLabel->Visible = false;
		Height->Visible = false;
		AtLabel->Visible = false;

		RateLabel->Left = ModeComboBox->Left + (ModeComboBox->Width - RateLabel->Width - LabelSpacing - Rate->Width - PostLabelSpacing - HzLabel->Width + 1) / 2;
		Rate->Left = RateLabel->Left + RateLabel->Width + LabelSpacing;
		HzLabel->Left = Rate->Left + Rate->Width + PostLabelSpacing;
	}
	else
	{
		RateLabel->Visible = false;
		Width->Visible = true;
		ByLabel->Visible = true;
		Height->Visible = true;
		AtLabel->Visible = true;

		int TotalSpacing = ModeComboBox->Width - Width->Width - ByLabel->Width - Height->Width - AtLabel->Width - Rate->Width - PostLabelSpacing - HzLabel->Width;
		int ByLabelSpacing = TotalSpacing / 4;
		int AtLabelSpacing = (TotalSpacing - ByLabelSpacing * 2) / 2;

		Width->Left = ModeComboBox->Left;
		ByLabel->Left = Width->Left + Width->Width + ByLabelSpacing;
		Height->Left = ByLabel->Left + ByLabel->Width + ByLabelSpacing;
		AtLabel->Left = Height->Left + Height->Width + AtLabelSpacing;
		Rate->Left = AtLabel->Left + AtLabel->Width + AtLabelSpacing;
		HzLabel->Left = Rate->Left + Rate->Width + PostLabelSpacing;
	}

	if (Value != ModeComboBox)
		ModeComboBox->ItemIndex = StandardResolution->GetMode();

	if (Value != Width && Common::IntegerToText(StandardResolution->GetWidth(), Text, TEXTSIZE))
		Width->Text = Text;

	Width->Font->Color = GetTextColor(StandardResolution->IsValidWidth());

	if (Value != Height && Common::IntegerToText(StandardResolution->GetHeight(), Text, TEXTSIZE))
		Height->Text = Text;

	Height->Font->Color = GetTextColor(StandardResolution->IsValidHeight());

	if (Value != Rate && Common::IntegerToText(StandardResolution->GetRate(), Text, TEXTSIZE))
		Rate->Text = Text;

	Rate->Font->Color = GetTextColor(StandardResolution->IsValidRate());

	if (Value != FormOKButton)
		FormOKButton->Enabled = StandardResolution->IsValid();

	Refreshing = false;
	return true;
}
//---------------------------------------------------------------------------
bool TStandardResolutionForm::InitModeComboBox()
{
	int ItemIndex;
	int Index;
	char Text[TEXTSIZE];

	ItemIndex = ModeComboBox->ItemIndex;
	ModeComboBox->Clear();
	ModeComboBox->Items->BeginUpdate();

	for (Index = 0; StandardResolution->GetModeText(Index, Text, TEXTSIZE); Index++)
		ModeComboBox->Items->Add(Text);

	ModeComboBox->ItemIndex = ItemIndex;
	ModeComboBox->Items->EndUpdate();
	return true;
}
//---------------------------------------------------------------------------
bool TStandardResolutionForm::ScaleControls()
{
	ModeComboBox->Width = FormButtonsWidth - PaddingWidth * 2;
	ModeComboBox->Height = ComboBoxHeight;
	ModeComboBox->Left = PaddingWidth;
	ModeComboBox->Top = PaddingTop;

	Width->AutoSize = false;
	Width->Width = Width->MaxLength * NumberWidth + TextBoxPadding;
	Width->Height = TextBoxHeight;

	Height->AutoSize = false;
	Height->Width = Height->MaxLength * NumberWidth + TextBoxPadding;
	Height->Height = TextBoxHeight;

	Rate->AutoSize = false;
	Rate->Width = Rate->MaxLength * NumberWidth + TextBoxPadding;
	Rate->Height = TextBoxHeight;

	RateLabel->Top = ModeComboBox->Top + ModeComboBox->Height + Scale + 3;
	Width->Top = RateLabel->Top - 3;
	ByLabel->Top = Width->Top + 3;
	Height->Top = ByLabel->Top - 3;
	AtLabel->Top = Height->Top + 3;
	Rate->Top = AtLabel->Top - 3;
	HzLabel->Top = Rate->Top + 3;

	ResolutionGroupBox->Width = ModeComboBox->Left + ModeComboBox->Width + PaddingWidth;
	ResolutionGroupBox->Height = Rate->Top + Rate->Height + PaddingBottom;
	ResolutionGroupBox->Left = Scale;
	ResolutionGroupBox->Top = GroupBoxTop;

	FormOKButton->Width = FormButtonWidth;
	FormOKButton->Height = FormButtonHeight;
	FormOKButton->Top = ResolutionGroupBox->Top + ResolutionGroupBox->Height + GroupBoxBottom + Scale + ButtonTop;
	Common::FixButtonCaption(FormOKButton, Canvas->TextWidth(FormOKButton->Caption));

	FormCancelButton->Width = FormButtonWidth;
	FormCancelButton->Height = FormButtonHeight;
	FormCancelButton->Top = FormOKButton->Top;
	Common::FixButtonCaption(FormCancelButton, Canvas->TextWidth(FormCancelButton->Caption));

	FormCancelButton->Left = ResolutionGroupBox->Left + ResolutionGroupBox->Width - ButtonRight - FormCancelButton->Width;
	FormOKButton->Left = FormCancelButton->Left - ButtonLeft - Scale - ButtonRight - FormOKButton->Width;

	ClientWidth = FormCancelButton->Left + FormCancelButton->Width + ButtonRight + Scale;
	ClientHeight = FormCancelButton->Top + FormCancelButton->Height + ButtonBottom + Scale;
	return true;
}
//---------------------------------------------------------------------------
void __fastcall TStandardResolutionForm::FormCreate(TObject *Sender)
{
	ScaleControls();
}
//---------------------------------------------------------------------------
void __fastcall TStandardResolutionForm::FormShow(TObject *Sender)
{
	InitModeComboBox();
	Refresh(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TStandardResolutionForm::ModeComboBoxChange(TObject *Sender)
{
	if (Refreshing)
		return;

	StandardResolution->SetMode(ModeComboBox->ItemIndex);
	Refresh(ModeComboBox);
}
//---------------------------------------------------------------------------
void __fastcall TStandardResolutionForm::WidthChange(TObject *Sender)
{
	if (Refreshing)
		return;

	StandardResolution->SetWidth(Common::TextToInteger(Width->Text.c_str()));
	Refresh(Width);
}
//---------------------------------------------------------------------------
void __fastcall TStandardResolutionForm::WidthExit(TObject *Sender)
{
	Refresh(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TStandardResolutionForm::HeightChange(TObject *Sender)
{
	if (Refreshing)
		return;

	StandardResolution->SetHeight(Common::TextToInteger(Height->Text.c_str()));
	Refresh(Height);
}
//---------------------------------------------------------------------------
void __fastcall TStandardResolutionForm::HeightExit(TObject *Sender)
{
	Refresh(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TStandardResolutionForm::RateChange(TObject *Sender)
{
	if (Refreshing)
		return;

	StandardResolution->SetRate(Common::TextToInteger(Rate->Text.c_str()));
	Refresh(Rate);
}
//---------------------------------------------------------------------------
void __fastcall TStandardResolutionForm::RateExit(TObject *Sender)
{
	Refresh(NULL);
}
//---------------------------------------------------------------------------
