//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "AddCEADataFormClass.h"
#include "Common.h"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TAddCEADataForm *AddCEADataForm;
//---------------------------------------------------------------------------
__fastcall TAddCEADataForm::TAddCEADataForm(TComponent *Owner) : TCommonForm(Owner)
{
	Refreshing = false;
}
//---------------------------------------------------------------------------
bool TAddCEADataForm::Connect(AddCEADataClass &NewAddCEAData)
{
	AddCEAData = &NewAddCEAData;
	return true;
}
//---------------------------------------------------------------------------
bool TAddCEADataForm::Refresh(void *Value)
{
	Refreshing = true;

	if (Value == NULL || Value == TypeGroupBox)
		RefreshTypeRadioButtons();

	if (Value != FormOKButton)
		FormOKButton->Enabled = AddCEAData->IsValid();

	Refreshing = false;
	return true;
}
//---------------------------------------------------------------------------
bool TAddCEADataForm::RefreshTypeRadioButtons()
{
	TVRadioButton->Enabled = AddCEAData->TypePossible(ADD_CEA_VIDEO);
	AudioRadioButton->Enabled = AddCEAData->TypePossible(ADD_CEA_AUDIO);
	SpeakerRadioButton->Enabled = AddCEAData->TypePossible(ADD_CEA_SPEAKER_ALLOCATION);
	HDMIRadioButton->Enabled = AddCEAData->TypePossible(ADD_CEA_HDMI);
	HDMI2RadioButton->Enabled = AddCEAData->TypePossible(ADD_CEA_HDMI2);
	FreeSyncRadioButton->Enabled = AddCEAData->TypePossible(ADD_CEA_FREESYNC);
	ColorimetryRadioButton->Enabled = AddCEAData->TypePossible(ADD_CEA_COLORIMETRY);
	VideoCapabilityRadioButton->Enabled = AddCEAData->TypePossible(ADD_CEA_VIDEO_CAPABILITY);

	TVRadioButton->Checked = AddCEAData->IsType(ADD_CEA_VIDEO);
	AudioRadioButton->Checked = AddCEAData->IsType(ADD_CEA_AUDIO);
	SpeakerRadioButton->Checked = AddCEAData->IsType(ADD_CEA_SPEAKER_ALLOCATION);
	HDMIRadioButton->Checked = AddCEAData->IsType(ADD_CEA_HDMI);
	HDMI2RadioButton->Checked = AddCEAData->IsType(ADD_CEA_HDMI2);
	FreeSyncRadioButton->Checked = AddCEAData->IsType(ADD_CEA_FREESYNC);
	ColorimetryRadioButton->Checked = AddCEAData->IsType(ADD_CEA_COLORIMETRY);
	VideoCapabilityRadioButton->Checked = AddCEAData->IsType(ADD_CEA_VIDEO_CAPABILITY);
	return true;
}
//---------------------------------------------------------------------------
bool TAddCEADataForm::ScaleControls()
{
	TVRadioButton->Width = RadioButtonWidth + Canvas->TextWidth(TVRadioButton->Caption);
	TVRadioButton->Height = RadioButtonHeight;
	TVRadioButton->Left = PaddingWidth;
	TVRadioButton->Top = PaddingTop + CheckBoxTop;

	AudioRadioButton->Width = RadioButtonWidth + Canvas->TextWidth(AudioRadioButton->Caption);
	AudioRadioButton->Height = RadioButtonHeight;
	AudioRadioButton->Left = TVRadioButton->Left;
	AudioRadioButton->Top = TVRadioButton->Top + TVRadioButton->Height + CheckBoxSpacing;

	SpeakerRadioButton->Width = RadioButtonWidth + Canvas->TextWidth(SpeakerRadioButton->Caption);
	SpeakerRadioButton->Height = RadioButtonHeight;
	SpeakerRadioButton->Left = AudioRadioButton->Left;
	SpeakerRadioButton->Top = AudioRadioButton->Top + AudioRadioButton->Height + CheckBoxSpacing;

	HDMIRadioButton->Width = RadioButtonWidth + Canvas->TextWidth(HDMIRadioButton->Caption);
	HDMIRadioButton->Height = RadioButtonHeight;
	HDMIRadioButton->Left = SpeakerRadioButton->Left;
	HDMIRadioButton->Top = SpeakerRadioButton->Top + SpeakerRadioButton->Height + CheckBoxSpacing;

	HDMI2RadioButton->Width = RadioButtonWidth + Canvas->TextWidth(HDMI2RadioButton->Caption);
	HDMI2RadioButton->Height = RadioButtonHeight;
	HDMI2RadioButton->Left = HDMIRadioButton->Left;
	HDMI2RadioButton->Top = HDMIRadioButton->Top + HDMIRadioButton->Height + CheckBoxSpacing;

	FreeSyncRadioButton->Width = RadioButtonWidth + Canvas->TextWidth(FreeSyncRadioButton->Caption);
	FreeSyncRadioButton->Height = RadioButtonHeight;
	FreeSyncRadioButton->Left = HDMI2RadioButton->Left;
	FreeSyncRadioButton->Top = HDMI2RadioButton->Top + HDMI2RadioButton->Height + CheckBoxSpacing;

	ColorimetryRadioButton->Width = RadioButtonWidth + Canvas->TextWidth(ColorimetryRadioButton->Caption);
	ColorimetryRadioButton->Height = RadioButtonHeight;
	ColorimetryRadioButton->Left = FreeSyncRadioButton->Left;
	ColorimetryRadioButton->Top = FreeSyncRadioButton->Top + FreeSyncRadioButton->Height + CheckBoxSpacing;

	VideoCapabilityRadioButton->Width = RadioButtonWidth + Canvas->TextWidth(VideoCapabilityRadioButton->Caption);
	VideoCapabilityRadioButton->Height = RadioButtonHeight;
	VideoCapabilityRadioButton->Left = ColorimetryRadioButton->Left;
	VideoCapabilityRadioButton->Top = ColorimetryRadioButton->Top + ColorimetryRadioButton->Height + CheckBoxSpacing;

	TypeGroupBox->Width = FormButtonsWidth;
	TypeGroupBox->Height = VideoCapabilityRadioButton->Top + VideoCapabilityRadioButton->Height + CheckBoxBottom + PaddingBottom;
	TypeGroupBox->Left = Scale;
	TypeGroupBox->Top = GroupBoxTop;

	FormOKButton->Width = FormButtonWidth;
	FormOKButton->Height = FormButtonHeight;
	FormOKButton->Top = TypeGroupBox->Top + TypeGroupBox->Height + GroupBoxBottom + Scale + ButtonTop;
	Common::FixButtonCaption(FormOKButton, Canvas->TextWidth(FormOKButton->Caption));

	FormCancelButton->Width = FormButtonWidth;
	FormCancelButton->Height = FormButtonHeight;
	FormCancelButton->Top = FormOKButton->Top;
	Common::FixButtonCaption(FormCancelButton, Canvas->TextWidth(FormCancelButton->Caption));

	FormCancelButton->Left = TypeGroupBox->Left + TypeGroupBox->Width - ButtonRight - FormCancelButton->Width;
	FormOKButton->Left = FormCancelButton->Left - ButtonLeft - Scale - ButtonRight - FormOKButton->Width;

	ClientWidth = FormCancelButton->Left + FormCancelButton->Width + ButtonRight + Scale;
	ClientHeight = FormCancelButton->Top + FormCancelButton->Height + ButtonBottom + Scale;
	return true;
}
//---------------------------------------------------------------------------
void __fastcall TAddCEADataForm::FormCreate(TObject *Sender)
{
	ScaleControls();
}
//---------------------------------------------------------------------------
void __fastcall TAddCEADataForm::FormShow(TObject *Sender)
{
	Refresh(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TAddCEADataForm::TVRadioButtonClick(TObject *Sender)
{
	if (Refreshing)
		return;

	AddCEAData->SetType(ADD_CEA_VIDEO);
	Refresh(TypeGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TAddCEADataForm::AudioRadioButtonClick(TObject *Sender)
{
	if (Refreshing)
		return;

	AddCEAData->SetType(ADD_CEA_AUDIO);
	Refresh(TypeGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TAddCEADataForm::SpeakerRadioButtonClick(TObject *Sender)
{
	if (Refreshing)
		return;

	AddCEAData->SetType(ADD_CEA_SPEAKER_ALLOCATION);
	Refresh(TypeGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TAddCEADataForm::HDMIRadioButtonClick(TObject *Sender)
{
	if (Refreshing)
		return;

	AddCEAData->SetType(ADD_CEA_HDMI);
	Refresh(TypeGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TAddCEADataForm::HDMI2RadioButtonClick(TObject *Sender)
{
	if (Refreshing)
		return;

	AddCEAData->SetType(ADD_CEA_HDMI2);
	Refresh(TypeGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TAddCEADataForm::FreeSyncRadioButtonClick(TObject *Sender)
{
	if (Refreshing)
		return;

	AddCEAData->SetType(ADD_CEA_FREESYNC);
	Refresh(TypeGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TAddCEADataForm::ColorimetryRadioButtonClick(TObject *Sender)
{
	if (Refreshing)
		return;

	AddCEAData->SetType(ADD_CEA_COLORIMETRY);
	Refresh(TypeGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TAddCEADataForm::VideoCapabilityRadioButtonClick(TObject *Sender)
{
	if (Refreshing)
		return;

	AddCEAData->SetType(ADD_CEA_VIDEO_CAPABILITY);
	Refresh(TypeGroupBox);
}
//---------------------------------------------------------------------------
