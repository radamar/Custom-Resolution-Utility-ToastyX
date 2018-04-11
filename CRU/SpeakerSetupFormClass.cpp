//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "SpeakerSetupFormClass.h"
#include "Common.h"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TSpeakerSetupForm *SpeakerSetupForm;
//---------------------------------------------------------------------------
__fastcall TSpeakerSetupForm::TSpeakerSetupForm(TComponent *Owner) : TCommonForm(Owner)
{
	Refreshing = false;
}
//---------------------------------------------------------------------------
bool TSpeakerSetupForm::Connect(SpeakerSetupClass &NewSpeakerSetup)
{
	SpeakerSetup = &NewSpeakerSetup;
	return true;
}
//---------------------------------------------------------------------------
bool TSpeakerSetupForm::Refresh(void *Value)
{
	Refreshing = true;

	if (Value == NULL || Value == SpeakerGroupBox)
	{
		RefreshSpeakerCheckBoxes();
		RefreshSpeakerButtons();
	}

	Refreshing = false;
	return true;
}
//---------------------------------------------------------------------------
bool TSpeakerSetupForm::RefreshSpeakerCheckBoxes()
{
	SpeakerCheckBox0->Checked = SpeakerSetup->Get(0);
	SpeakerCheckBox1->Checked = SpeakerSetup->Get(1);
	SpeakerCheckBox2->Checked = SpeakerSetup->Get(2);
	SpeakerCheckBox3->Checked = SpeakerSetup->Get(3);
	SpeakerCheckBox4->Checked = SpeakerSetup->Get(4);
	SpeakerCheckBox5->Checked = SpeakerSetup->Get(5);
	SpeakerCheckBox6->Checked = SpeakerSetup->Get(6);
	SpeakerCheckBox7->Checked = SpeakerSetup->Get(7);
	SpeakerCheckBox8->Checked = SpeakerSetup->Get(8);
	SpeakerCheckBox9->Checked = SpeakerSetup->Get(9);
	SpeakerCheckBox10->Checked = SpeakerSetup->Get(10);
	return true;
}
//---------------------------------------------------------------------------
bool TSpeakerSetupForm::RefreshSpeakerButtons()
{
	//Speaker20Button->Perform(BM_SETSTATE, !SpeakerBlock.Set20Possible(), 0);
	//Speaker51Button->Perform(BM_SETSTATE, !SpeakerBlock.Set51Possible(), 0);
	//Speaker71Button->Perform(BM_SETSTATE, !SpeakerBlock.Set71Possible(), 0);
	Speaker20Button->Enabled = SpeakerSetup->Set20Possible();
	Speaker51Button->Enabled = SpeakerSetup->Set51Possible();
	Speaker71Button->Enabled = SpeakerSetup->Set71Possible();
	SpeakerResetButton->Enabled = SpeakerSetup->UndoPossible();
	return true;
}
//---------------------------------------------------------------------------
bool TSpeakerSetupForm::ScaleControls()
{
	SpeakerCheckBox0->Width = CheckBoxWidth + Canvas->TextWidth(SpeakerCheckBox0->Caption);
	SpeakerCheckBox0->Height = CheckBoxHeight;
	SpeakerCheckBox0->Left = PaddingWidth;
	SpeakerCheckBox0->Top = PaddingTop + CheckBoxTop;

	SpeakerCheckBox1->Width = CheckBoxWidth + Canvas->TextWidth(SpeakerCheckBox1->Caption);
	SpeakerCheckBox1->Height = CheckBoxHeight;
	SpeakerCheckBox1->Left = SpeakerCheckBox0->Left;
	SpeakerCheckBox1->Top = SpeakerCheckBox0->Top + SpeakerCheckBox0->Height + CheckBoxSpacing;

	SpeakerCheckBox2->Width = CheckBoxWidth + Canvas->TextWidth(SpeakerCheckBox2->Caption);
	SpeakerCheckBox2->Height = CheckBoxHeight;
	SpeakerCheckBox2->Left = SpeakerCheckBox1->Left;
	SpeakerCheckBox2->Top = SpeakerCheckBox1->Top + SpeakerCheckBox1->Height + CheckBoxSpacing;

	SpeakerCheckBox3->Width = CheckBoxWidth + Canvas->TextWidth(SpeakerCheckBox3->Caption);
	SpeakerCheckBox3->Height = CheckBoxHeight;
	SpeakerCheckBox3->Left = SpeakerCheckBox2->Left;
	SpeakerCheckBox3->Top = SpeakerCheckBox2->Top + SpeakerCheckBox2->Height + CheckBoxSpacing;

	SpeakerCheckBox4->Width = CheckBoxWidth + Canvas->TextWidth(SpeakerCheckBox4->Caption);
	SpeakerCheckBox4->Height = CheckBoxHeight;
	SpeakerCheckBox4->Left = SpeakerCheckBox3->Left;
	SpeakerCheckBox4->Top = SpeakerCheckBox3->Top + SpeakerCheckBox3->Height + CheckBoxSpacing;

	SpeakerCheckBox5->Width = CheckBoxWidth + Canvas->TextWidth(SpeakerCheckBox5->Caption);
	SpeakerCheckBox5->Height = CheckBoxHeight;
	SpeakerCheckBox5->Left = SpeakerCheckBox4->Left;
	SpeakerCheckBox5->Top = SpeakerCheckBox4->Top + SpeakerCheckBox4->Height + CheckBoxSpacing;

	SpeakerCheckBox6->Width = CheckBoxWidth + Canvas->TextWidth(SpeakerCheckBox6->Caption);
	SpeakerCheckBox6->Height = CheckBoxHeight;
	SpeakerCheckBox6->Left = SpeakerCheckBox5->Left;
	SpeakerCheckBox6->Top = SpeakerCheckBox5->Top + SpeakerCheckBox5->Height + CheckBoxSpacing;

	SpeakerCheckBox7->Width = CheckBoxWidth + Canvas->TextWidth(SpeakerCheckBox7->Caption);
	SpeakerCheckBox7->Height = CheckBoxHeight;
	SpeakerCheckBox7->Left = SpeakerCheckBox6->Left;
	SpeakerCheckBox7->Top = SpeakerCheckBox6->Top + SpeakerCheckBox6->Height + CheckBoxSpacing;

	SpeakerCheckBox8->Width = CheckBoxWidth + Canvas->TextWidth(SpeakerCheckBox8->Caption);
	SpeakerCheckBox8->Height = CheckBoxHeight;
	SpeakerCheckBox8->Left = SpeakerCheckBox7->Left;
	SpeakerCheckBox8->Top = SpeakerCheckBox7->Top + SpeakerCheckBox7->Height + CheckBoxSpacing;

	SpeakerCheckBox9->Width = CheckBoxWidth + Canvas->TextWidth(SpeakerCheckBox9->Caption);
	SpeakerCheckBox9->Height = CheckBoxHeight;
	SpeakerCheckBox9->Left = SpeakerCheckBox8->Left;
	SpeakerCheckBox9->Top = SpeakerCheckBox8->Top + SpeakerCheckBox8->Height + CheckBoxSpacing;

	SpeakerCheckBox10->Width = CheckBoxWidth + Canvas->TextWidth(SpeakerCheckBox10->Caption);
	SpeakerCheckBox10->Height = CheckBoxHeight;
	SpeakerCheckBox10->Left = SpeakerCheckBox9->Left;
	SpeakerCheckBox10->Top = SpeakerCheckBox9->Top + SpeakerCheckBox9->Height + CheckBoxSpacing;

	Speaker20Button->Width = ButtonWidth;
	Speaker20Button->Height = ButtonHeight;
	Speaker20Button->Left = PaddingWidth + ButtonLeft;
	Speaker20Button->Top = SpeakerCheckBox10->Top + SpeakerCheckBox10->Height + CheckBoxBottom + Scale + ButtonTop;
	Common::FixButtonCaption(Speaker20Button, Canvas->TextWidth(Speaker20Button->Caption));

	Speaker51Button->Width = (FormButtonsWidth - PaddingWidth * 2 - ButtonLeft - ButtonWidth * 2 - ButtonRight) / 2;
	Speaker51Button->Height = ButtonHeight;
	Speaker51Button->Left = Speaker20Button->Left + Speaker20Button->Width;
	Speaker51Button->Top = Speaker20Button->Top;
	Common::FixButtonCaption(Speaker51Button, Canvas->TextWidth(Speaker51Button->Caption));

	Speaker71Button->Width = (FormButtonsWidth - PaddingWidth * 2 - ButtonLeft - ButtonWidth * 2 - ButtonRight) / 2;
	Speaker71Button->Height = ButtonHeight;
	Speaker71Button->Left = Speaker51Button->Left + Speaker51Button->Width;
	Speaker71Button->Top = Speaker51Button->Top;
	Common::FixButtonCaption(Speaker71Button, Canvas->TextWidth(Speaker71Button->Caption));

	SpeakerResetButton->Width = ButtonWidth;
	SpeakerResetButton->Height = ButtonHeight;
	SpeakerResetButton->Left = Speaker71Button->Left + Speaker71Button->Width;
	SpeakerResetButton->Top = Speaker71Button->Top;
	Common::FixButtonCaption(SpeakerResetButton, Canvas->TextWidth(SpeakerResetButton->Caption));

	SpeakerGroupBox->Width = SpeakerResetButton->Left + SpeakerResetButton->Width + ButtonRight + PaddingWidth;
	SpeakerGroupBox->Height = Speaker20Button->Top + Speaker20Button->Height + ButtonBottom + PaddingBottom;
	SpeakerGroupBox->Left = Scale;
	SpeakerGroupBox->Top = GroupBoxTop;

	FormOKButton->Width = FormButtonWidth;
	FormOKButton->Height = FormButtonHeight;
	FormOKButton->Top = SpeakerGroupBox->Top + SpeakerGroupBox->Height + GroupBoxBottom + Scale + ButtonTop;
	Common::FixButtonCaption(FormOKButton, Canvas->TextWidth(FormOKButton->Caption));

	FormCancelButton->Width = FormButtonWidth;
	FormCancelButton->Height = FormButtonHeight;
	FormCancelButton->Top = FormOKButton->Top;
	Common::FixButtonCaption(FormCancelButton, Canvas->TextWidth(FormCancelButton->Caption));

	FormCancelButton->Left = SpeakerGroupBox->Left + SpeakerGroupBox->Width - ButtonRight - FormCancelButton->Width;
	FormOKButton->Left = FormCancelButton->Left - ButtonLeft - Scale - ButtonRight - FormOKButton->Width;

	ClientWidth = FormCancelButton->Left + FormCancelButton->Width + ButtonRight + Scale;
	ClientHeight = FormCancelButton->Top + FormCancelButton->Height + ButtonBottom + Scale;
	return true;
}
//---------------------------------------------------------------------------
void __fastcall TSpeakerSetupForm::FormCreate(TObject *Sender)
{
	ScaleControls();
}
//---------------------------------------------------------------------------
void __fastcall TSpeakerSetupForm::FormShow(TObject *Sender)
{
	Refresh(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TSpeakerSetupForm::SpeakerCheckBoxClick(TObject *Sender)
{
	if (Refreshing)
		return;

	TCheckBox *CheckBox = (TCheckBox *)Sender;
	SpeakerSetup->Set(CheckBox->Tag, CheckBox->Checked);
	Refresh(SpeakerGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TSpeakerSetupForm::Speaker20ButtonClick(TObject *Sender)
{
	SpeakerSetup->Set20();
	Refresh(SpeakerGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TSpeakerSetupForm::Speaker51ButtonClick(TObject *Sender)
{
	SpeakerSetup->Set51();
	Refresh(SpeakerGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TSpeakerSetupForm::Speaker71ButtonClick(TObject *Sender)
{
	SpeakerSetup->Set71();
	Refresh(SpeakerGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TSpeakerSetupForm::SpeakerResetButtonClick(TObject *Sender)
{
	SpeakerSetup->Undo();
	Refresh(SpeakerGroupBox);
}
//---------------------------------------------------------------------------
