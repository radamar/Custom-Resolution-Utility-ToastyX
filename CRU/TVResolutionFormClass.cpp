//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "TVResolutionFormClass.h"
#include "Common.h"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TTVResolutionForm *TVResolutionForm;
//---------------------------------------------------------------------------
__fastcall TTVResolutionForm::TTVResolutionForm(TComponent *Owner) : TCommonForm(Owner)
{
	Refreshing = false;
}
//---------------------------------------------------------------------------
bool TTVResolutionForm::Connect(TVResolutionClass &NewTVResolution)
{
	TVResolution = &NewTVResolution;
	return true;
}
//---------------------------------------------------------------------------
TColor TTVResolutionForm::GetTextColor(bool Valid)
{
	if (!Valid)
		return (TColor)RGB(255, 0, 0);

	return clWindowText;
}
//---------------------------------------------------------------------------
bool TTVResolutionForm::Refresh(void *Value)
{
	char Text[TEXTSIZE];

	Refreshing = true;

	if (!TVResolution->IsOther())
	{
		FormatLabel->Visible = true;
		CodeLabel->Visible = false;
		CodeRangeLabel->Visible = false;
		FormatComboBox->Visible = true;
		Code->Visible = false;
	}
	else
	{
		FormatLabel->Visible = false;
		CodeLabel->Visible = true;
		CodeRangeLabel->Visible = true;
		FormatComboBox->Visible = false;
		Code->Visible = true;
	}

	if (Value != ModeComboBox)
		ModeComboBox->ItemIndex = TVResolution->GetMode();

	if (Value != FormatComboBox)
		FormatComboBox->ItemIndex = TVResolution->GetFormat();

	if (Value != Code && Common::IntegerToText(TVResolution->GetCode(), Text, TEXTSIZE))
		Code->Text = Text;

	Code->Font->Color = GetTextColor(TVResolution->IsValidCode());

	if (Value != Native)
	{
		Native->Enabled = TVResolution->NativePossible();
		Native->Checked = TVResolution->GetNative();
	}

	if (Value != FormOKButton)
		FormOKButton->Enabled = TVResolution->IsValid();

	Refreshing = false;
	return true;
}
//---------------------------------------------------------------------------
bool TTVResolutionForm::InitModeComboBox()
{
	int ItemIndex;
	int Index;
	char Text[TEXTSIZE];

	ItemIndex = ModeComboBox->ItemIndex;
	ModeComboBox->Clear();
	ModeComboBox->Items->BeginUpdate();

	for (Index = 0; TVResolution->GetModeText(Index, Text, TEXTSIZE); Index++)
		ModeComboBox->Items->Add(Text);

	ModeComboBox->ItemIndex = ItemIndex;
	ModeComboBox->Items->EndUpdate();
	return true;
}
//---------------------------------------------------------------------------
bool TTVResolutionForm::InitFormatComboBox()
{
	int ItemIndex;
	int Index;
	char Text[TEXTSIZE];

	ItemIndex = FormatComboBox->ItemIndex;
	FormatComboBox->Clear();
	FormatComboBox->Items->BeginUpdate();

	for (Index = 0; TVResolution->GetFormatText(Index, Text, TEXTSIZE); Index++)
		FormatComboBox->Items->Add(Text);

	FormatComboBox->ItemIndex = ItemIndex;
	FormatComboBox->Items->EndUpdate();
	return true;
}
//---------------------------------------------------------------------------
bool TTVResolutionForm::ScaleControls()
{
	ModeComboBox->Width = FormButtonsWidth - PaddingWidth * 2;
	ModeComboBox->Height = ComboBoxHeight;
	ModeComboBox->Left = PaddingWidth;
	ModeComboBox->Top = PaddingTop;

	FormatComboBox->Width = ModeComboBox->Width - FormatLabel->Width - LabelSpacing;
	FormatComboBox->Height = ComboBoxHeight;

	FormatLabel->Left = ModeComboBox->Left;
	FormatComboBox->Left = FormatLabel->Left + FormatLabel->Width + LabelSpacing;

	FormatLabel->Top = ModeComboBox->Top + ModeComboBox->Height + Scale + 4;
	FormatComboBox->Top = FormatLabel->Top - 4;

	Code->AutoSize = false;
	Code->Width = Code->MaxLength * NumberWidth + TextBoxPadding;
	Code->Height = TextBoxHeight;

	CodeLabel->Left = ModeComboBox->Left + (ModeComboBox->Width - CodeLabel->Width - LabelSpacing - Code->Width - PostLabelSpacing - CodeRangeLabel->Width + 1) / 2;
	Code->Left = CodeLabel->Left + CodeLabel->Width + LabelSpacing;
	CodeRangeLabel->Left = Code->Left + Code->Width + PostLabelSpacing;

	CodeLabel->Top = FormatLabel->Top - 1;
	Code->Top = CodeLabel->Top - 3;
	CodeRangeLabel->Top = Code->Top + 3;

	Native->Width = CheckBoxWidth + Canvas->TextWidth(Native->Caption);
	Native->Height = CheckBoxHeight;
	Native->Left = ModeComboBox->Left + (ModeComboBox->Width - Native->Width - CheckBoxRight) / 2;
	Native->Top = FormatComboBox->Top + FormatComboBox->Height + Scale + CheckBoxTop;

	ResolutionGroupBox->Width = ModeComboBox->Left + ModeComboBox->Width + PaddingWidth;
	ResolutionGroupBox->Height = Native->Top + Native->Height + CheckBoxBottom + PaddingBottom;
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
void __fastcall TTVResolutionForm::FormCreate(TObject *Sender)
{
	ScaleControls();
}
//---------------------------------------------------------------------------
void __fastcall TTVResolutionForm::FormShow(TObject *Sender)
{
	InitModeComboBox();
	InitFormatComboBox();
	Refresh(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TTVResolutionForm::ModeComboBoxChange(TObject *Sender)
{
	if (Refreshing)
		return;

	TVResolution->SetMode(ModeComboBox->ItemIndex);
	InitFormatComboBox();
	Refresh(ModeComboBox);
}
//---------------------------------------------------------------------------
void __fastcall TTVResolutionForm::FormatComboBoxChange(TObject *Sender)
{
	if (Refreshing)
		return;

	TVResolution->SetFormat(FormatComboBox->ItemIndex);
	Refresh(FormatComboBox);
}
//---------------------------------------------------------------------------
void __fastcall TTVResolutionForm::CodeChange(TObject *Sender)
{
	if (Refreshing)
		return;

	TVResolution->SetCode(Common::TextToInteger(Code->Text.c_str()));
	Refresh(Code);
}
//---------------------------------------------------------------------------
void __fastcall TTVResolutionForm::CodeExit(TObject *Sender)
{
	Refresh(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TTVResolutionForm::NativeClick(TObject *Sender)
{
	if (Refreshing)
		return;

	TVResolution->SetNative(Native->Checked);
	Refresh(Native);
}
//---------------------------------------------------------------------------
