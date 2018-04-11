//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "HDMI2SupportFormClass.h"
#include "Common.h"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
THDMI2SupportForm *HDMI2SupportForm;
//---------------------------------------------------------------------------
__fastcall THDMI2SupportForm::THDMI2SupportForm(TComponent *Owner) : TCommonForm(Owner)
{
	Refreshing = false;
}
//---------------------------------------------------------------------------
bool THDMI2SupportForm::Connect(HDMI2SupportClass &NewHDMI2Support)
{
	HDMI2Support = &NewHDMI2Support;
	return true;
}
//---------------------------------------------------------------------------
TColor THDMI2SupportForm::GetTextColor(bool Valid)
{
	if (!Valid)
		return (TColor)RGB(255, 0, 0);

	return clWindowText;
}
//---------------------------------------------------------------------------
bool THDMI2SupportForm::Refresh(void *Value)
{
	Refreshing = true;

	if (Value == NULL || Value == TMDSRateGroupBox)
		RefreshTMDSRateTextBox();

	if (Value == NULL || Value == FeaturesGroupBox)
		RefreshFeaturesCheckBoxes();

	if (Value == NULL || Value == ColorFormatsGroupBox)
		RefreshColorFormatsCheckBoxes();

	if (Value != FormOKButton)
		FormOKButton->Enabled = HDMI2Support->IsValid();

	Refreshing = false;
	return true;
}
//---------------------------------------------------------------------------
bool THDMI2SupportForm::RefreshTMDSRateTextBox()
{
	char Text[TEXTSIZE];

	TMDSRate->Font->Color = GetTextColor(HDMI2Support->IsValidTMDSRate());

	if (!TMDSRate->Focused() && Common::IntegerToText(HDMI2Support->GetTMDSRate(), Text, TEXTSIZE))
		TMDSRate->Text = Text;

	return true;
}
//---------------------------------------------------------------------------
bool THDMI2SupportForm::RefreshFeaturesCheckBoxes()
{
	FeaturesCheckBox7->Checked = HDMI2Support->GetFeature(7);
	FeaturesCheckBox6->Checked = HDMI2Support->GetFeature(6);
	FeaturesCheckBox3->Checked = HDMI2Support->GetFeature(3);
	FeaturesCheckBox2->Checked = HDMI2Support->GetFeature(2);
	FeaturesCheckBox1->Checked = HDMI2Support->GetFeature(1);
	FeaturesCheckBox0->Checked = HDMI2Support->GetFeature(0);
	return true;
}
//---------------------------------------------------------------------------
bool THDMI2SupportForm::RefreshColorFormatsCheckBoxes()
{
	ColorFormatsCheckBox0->Checked = HDMI2Support->GetColorFormat(0);
	ColorFormatsCheckBox1->Checked = HDMI2Support->GetColorFormat(1);
	ColorFormatsCheckBox2->Checked = HDMI2Support->GetColorFormat(2);
	return true;
}
//---------------------------------------------------------------------------
bool THDMI2SupportForm::ScaleControls()
{
	TMDSRate->AutoSize = false;
	TMDSRate->Width = TMDSRate->MaxLength * NumberWidth + TextBoxPadding;
	TMDSRate->Height = TextBoxHeight;
	TMDSRate->Left = PaddingWidth;
	TMDSRate->Top = PaddingTop;

	TMDSRateLabel->Left = TMDSRate->Left + TMDSRate->Width + PostLabelSpacing;
	TMDSRateLabel->Top = TMDSRate->Top + 3;

	TMDSRateGroupBox->Width = FormButtonsWidth;
	TMDSRateGroupBox->Height = TMDSRate->Top + TMDSRate->Height + PaddingBottom;
	TMDSRateGroupBox->Left = Scale;
	TMDSRateGroupBox->Top = GroupBoxTop;

	FeaturesCheckBox7->Width = CheckBoxWidth + Canvas->TextWidth(FeaturesCheckBox7->Caption);
	FeaturesCheckBox7->Height = CheckBoxHeight;
	FeaturesCheckBox7->Left = PaddingWidth;
	FeaturesCheckBox7->Top = PaddingTop + CheckBoxTop;

	FeaturesCheckBox6->Width = CheckBoxWidth + Canvas->TextWidth(FeaturesCheckBox6->Caption);
	FeaturesCheckBox6->Height = CheckBoxHeight;
	FeaturesCheckBox6->Left = FeaturesCheckBox7->Left;
	FeaturesCheckBox6->Top = FeaturesCheckBox7->Top + FeaturesCheckBox7->Height + CheckBoxSpacing;

	FeaturesCheckBox3->Width = CheckBoxWidth + Canvas->TextWidth(FeaturesCheckBox3->Caption);
	FeaturesCheckBox3->Height = CheckBoxHeight;
	FeaturesCheckBox3->Left = FeaturesCheckBox6->Left;
	FeaturesCheckBox3->Top = FeaturesCheckBox6->Top + FeaturesCheckBox6->Height + CheckBoxSpacing;

	FeaturesCheckBox2->Width = CheckBoxWidth + Canvas->TextWidth(FeaturesCheckBox2->Caption);
	FeaturesCheckBox2->Height = CheckBoxHeight;
	FeaturesCheckBox2->Left = FeaturesCheckBox3->Left;
	FeaturesCheckBox2->Top = FeaturesCheckBox3->Top + FeaturesCheckBox3->Height + CheckBoxSpacing;

	FeaturesCheckBox1->Width = CheckBoxWidth + Canvas->TextWidth(FeaturesCheckBox1->Caption);
	FeaturesCheckBox1->Height = CheckBoxHeight;
	FeaturesCheckBox1->Left = FeaturesCheckBox2->Left;
	FeaturesCheckBox1->Top = FeaturesCheckBox2->Top + FeaturesCheckBox2->Height + CheckBoxSpacing;

	FeaturesCheckBox0->Width = CheckBoxWidth + Canvas->TextWidth(FeaturesCheckBox0->Caption);
	FeaturesCheckBox0->Height = CheckBoxHeight;
	FeaturesCheckBox0->Left = FeaturesCheckBox1->Left;
	FeaturesCheckBox0->Top = FeaturesCheckBox1->Top + FeaturesCheckBox1->Height + CheckBoxSpacing;

	FeaturesGroupBox->Width = TMDSRateGroupBox->Width;
	FeaturesGroupBox->Height = FeaturesCheckBox0->Top + FeaturesCheckBox0->Height + CheckBoxBottom + PaddingBottom;
	FeaturesGroupBox->Left = TMDSRateGroupBox->Left;
	FeaturesGroupBox->Top = TMDSRateGroupBox->Top + TMDSRateGroupBox->Height + GroupBoxBottom + GroupBoxTop;

	ColorFormatsCheckBox0->Width = CheckBoxWidth + Canvas->TextWidth(ColorFormatsCheckBox0->Caption);
	ColorFormatsCheckBox0->Height = CheckBoxHeight;
	ColorFormatsCheckBox0->Left = PaddingWidth;
	ColorFormatsCheckBox0->Top = PaddingTop + CheckBoxTop;

	ColorFormatsCheckBox1->Width = CheckBoxWidth + Canvas->TextWidth(ColorFormatsCheckBox1->Caption);
	ColorFormatsCheckBox1->Height = CheckBoxHeight;
	ColorFormatsCheckBox1->Left = ColorFormatsCheckBox0->Left;
	ColorFormatsCheckBox1->Top = ColorFormatsCheckBox0->Top + ColorFormatsCheckBox0->Height + CheckBoxSpacing;

	ColorFormatsCheckBox2->Width = CheckBoxWidth + Canvas->TextWidth(ColorFormatsCheckBox2->Caption);
	ColorFormatsCheckBox2->Height = CheckBoxHeight;
	ColorFormatsCheckBox2->Left = ColorFormatsCheckBox1->Left;
	ColorFormatsCheckBox2->Top = ColorFormatsCheckBox1->Top + ColorFormatsCheckBox1->Height + CheckBoxSpacing;

	ColorFormatsGroupBox->Width = FeaturesGroupBox->Width;
	ColorFormatsGroupBox->Height = ColorFormatsCheckBox2->Top + ColorFormatsCheckBox2->Height + CheckBoxBottom + PaddingBottom;
	ColorFormatsGroupBox->Left = FeaturesGroupBox->Left;
	ColorFormatsGroupBox->Top = FeaturesGroupBox->Top + FeaturesGroupBox->Height + GroupBoxBottom + GroupBoxTop;

	FormOKButton->Width = FormButtonWidth;
	FormOKButton->Height = FormButtonHeight;
	FormOKButton->Top = ColorFormatsGroupBox->Top + ColorFormatsGroupBox->Height + GroupBoxBottom + Scale + ButtonTop;
	Common::FixButtonCaption(FormOKButton, Canvas->TextWidth(FormOKButton->Caption));

	FormCancelButton->Width = FormButtonWidth;
	FormCancelButton->Height = FormButtonHeight;
	FormCancelButton->Top = FormOKButton->Top;
	Common::FixButtonCaption(FormCancelButton, Canvas->TextWidth(FormCancelButton->Caption));

	FormCancelButton->Left = ColorFormatsGroupBox->Left + ColorFormatsGroupBox->Width - ButtonRight - FormCancelButton->Width;
	FormOKButton->Left = FormCancelButton->Left - ButtonLeft - Scale - ButtonRight - FormOKButton->Width;

	ClientWidth = FormCancelButton->Left + FormCancelButton->Width + ButtonRight + Scale;
	ClientHeight = FormCancelButton->Top + FormCancelButton->Height + ButtonBottom + Scale;
	return true;
}
//---------------------------------------------------------------------------
void __fastcall THDMI2SupportForm::FormCreate(TObject *Sender)
{
	ScaleControls();
}
//---------------------------------------------------------------------------
void __fastcall THDMI2SupportForm::FormShow(TObject *Sender)
{
	Refresh(NULL);
}
//---------------------------------------------------------------------------
void __fastcall THDMI2SupportForm::TMDSRateChange(TObject *Sender)
{
	if (Refreshing)
		return;

	HDMI2Support->SetTMDSRate(Common::TextToInteger(TMDSRate->Text.c_str()));
	Refresh(TMDSRateGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall THDMI2SupportForm::TMDSRateExit(TObject *Sender)
{
	Refresh(TMDSRateGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall THDMI2SupportForm::FeaturesCheckBoxClick(TObject *Sender)
{
	if (Refreshing)
		return;

	TCheckBox *CheckBox = (TCheckBox *)Sender;
	HDMI2Support->SetFeature(CheckBox->Tag, CheckBox->Checked);
	Refresh(FeaturesGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall THDMI2SupportForm::ColorFormatsCheckBoxClick(TObject *Sender)
{
	if (Refreshing)
		return;

	TCheckBox *CheckBox = (TCheckBox *)Sender;
	HDMI2Support->SetColorFormat(CheckBox->Tag, CheckBox->Checked);
	Refresh(ColorFormatsGroupBox);
}
//---------------------------------------------------------------------------
