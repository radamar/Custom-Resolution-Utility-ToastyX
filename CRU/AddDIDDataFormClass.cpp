//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "AddDIDDataFormClass.h"
#include "Common.h"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TAddDIDDataForm *AddDIDDataForm;
//---------------------------------------------------------------------------
__fastcall TAddDIDDataForm::TAddDIDDataForm(TComponent *Owner) : TCommonForm(Owner)
{
	Refreshing = false;
}
//---------------------------------------------------------------------------
bool TAddDIDDataForm::Connect(AddDIDDataClass &NewAddDIDData)
{
	AddDIDData = &NewAddDIDData;
	return true;
}
//---------------------------------------------------------------------------
bool TAddDIDDataForm::Refresh(void *Value)
{
	Refreshing = true;

	if (Value == NULL || Value == TypeGroupBox)
		RefreshTypeRadioButtons();

	if (Value != FormOKButton)
		FormOKButton->Enabled = AddDIDData->IsValid();

	Refreshing = false;
	return true;
}
//---------------------------------------------------------------------------
bool TAddDIDDataForm::RefreshTypeRadioButtons()
{
	DetailedResolutionsRadioButton->Enabled = AddDIDData->TypePossible(ADD_DID_DETAILED_RESOLUTIONS);
	TiledDisplayTopologyRadioButton->Enabled = AddDIDData->TypePossible(ADD_DID_TILED_DISPLAY_TOPOLOGY);

	DetailedResolutionsRadioButton->Checked = AddDIDData->IsType(ADD_DID_DETAILED_RESOLUTIONS);
	TiledDisplayTopologyRadioButton->Checked = AddDIDData->IsType(ADD_DID_TILED_DISPLAY_TOPOLOGY);
	return true;
}
//---------------------------------------------------------------------------
bool TAddDIDDataForm::ScaleControls()
{
	DetailedResolutionsRadioButton->Width = RadioButtonWidth + Canvas->TextWidth(DetailedResolutionsRadioButton->Caption);
	DetailedResolutionsRadioButton->Height = RadioButtonHeight;
	DetailedResolutionsRadioButton->Left = PaddingWidth;
	DetailedResolutionsRadioButton->Top = PaddingTop + CheckBoxTop;

	TiledDisplayTopologyRadioButton->Width = RadioButtonWidth + Canvas->TextWidth(TiledDisplayTopologyRadioButton->Caption);
	TiledDisplayTopologyRadioButton->Height = RadioButtonHeight;
	TiledDisplayTopologyRadioButton->Left = DetailedResolutionsRadioButton->Left;
	TiledDisplayTopologyRadioButton->Top = DetailedResolutionsRadioButton->Top + DetailedResolutionsRadioButton->Height + CheckBoxSpacing;

	TypeGroupBox->Width = FormButtonsWidth;
	TypeGroupBox->Height = TiledDisplayTopologyRadioButton->Top + TiledDisplayTopologyRadioButton->Height + CheckBoxBottom + PaddingBottom;
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
void __fastcall TAddDIDDataForm::FormCreate(TObject *Sender)
{
	ScaleControls();
}
//---------------------------------------------------------------------------
void __fastcall TAddDIDDataForm::FormShow(TObject *Sender)
{
	Refresh(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TAddDIDDataForm::DetailedResolutionsRadioButtonClick(TObject *Sender)
{
	if (Refreshing)
		return;

	AddDIDData->SetType(ADD_DID_DETAILED_RESOLUTIONS);
	Refresh(TypeGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TAddDIDDataForm::TiledDisplayTopologyRadioButtonClick(TObject *Sender)
{
	if (Refreshing)
		return;

	AddDIDData->SetType(ADD_DID_TILED_DISPLAY_TOPOLOGY);
	Refresh(TypeGroupBox);
}
//---------------------------------------------------------------------------
