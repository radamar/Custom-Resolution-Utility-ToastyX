//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "ColorimetryFormClass.h"
#include "Common.h"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TColorimetryForm *ColorimetryForm;
//---------------------------------------------------------------------------
__fastcall TColorimetryForm::TColorimetryForm(TComponent *Owner) : TCommonForm(Owner)
{
	Refreshing = false;
}
//---------------------------------------------------------------------------
bool TColorimetryForm::Connect(ColorimetryClass &NewColorimetry)
{
	Colorimetry = &NewColorimetry;
	return true;
}
//---------------------------------------------------------------------------
bool TColorimetryForm::Refresh(void *Value)
{
	Refreshing = true;

	if (Value == NULL || Value == ColorimetryGroupBox)
		RefreshColorimetryCheckBoxes();

	if (Value == NULL || Value == MetadataGroupBox)
		RefreshMetadataCheckBoxes();

	Refreshing = false;
	return true;
}
//---------------------------------------------------------------------------
bool TColorimetryForm::RefreshColorimetryCheckBoxes()
{
	ColorimetryCheckBox0->Checked = Colorimetry->GetColorimetry(0);
	ColorimetryCheckBox1->Checked = Colorimetry->GetColorimetry(1);
	ColorimetryCheckBox2->Checked = Colorimetry->GetColorimetry(2);
	ColorimetryCheckBox3->Checked = Colorimetry->GetColorimetry(3);
	ColorimetryCheckBox4->Checked = Colorimetry->GetColorimetry(4);
	ColorimetryCheckBox5->Checked = Colorimetry->GetColorimetry(5);
	ColorimetryCheckBox6->Checked = Colorimetry->GetColorimetry(6);
	ColorimetryCheckBox7->Checked = Colorimetry->GetColorimetry(7);
	ColorimetryCheckBox8->Checked = Colorimetry->GetColorimetry(8);
	return true;
}
//---------------------------------------------------------------------------
bool TColorimetryForm::RefreshMetadataCheckBoxes()
{
	MetadataCheckBox0->Checked = Colorimetry->GetMetadata(0);
	MetadataCheckBox1->Checked = Colorimetry->GetMetadata(1);
	MetadataCheckBox2->Checked = Colorimetry->GetMetadata(2);
	MetadataCheckBox3->Checked = Colorimetry->GetMetadata(3);
	return true;
}
//---------------------------------------------------------------------------
bool TColorimetryForm::ScaleControls()
{
	ColorimetryCheckBox0->Width = CheckBoxWidth + Canvas->TextWidth(ColorimetryCheckBox0->Caption);
	ColorimetryCheckBox0->Height = CheckBoxHeight;
	ColorimetryCheckBox0->Left = PaddingWidth;
	ColorimetryCheckBox0->Top = PaddingTop + CheckBoxTop;

	ColorimetryCheckBox1->Width = CheckBoxWidth + Canvas->TextWidth(ColorimetryCheckBox1->Caption);
	ColorimetryCheckBox1->Height = CheckBoxHeight;
	ColorimetryCheckBox1->Left = ColorimetryCheckBox0->Left;
	ColorimetryCheckBox1->Top = ColorimetryCheckBox0->Top + ColorimetryCheckBox0->Height + CheckBoxSpacing;

	ColorimetryCheckBox2->Width = CheckBoxWidth + Canvas->TextWidth(ColorimetryCheckBox2->Caption);
	ColorimetryCheckBox2->Height = CheckBoxHeight;
	ColorimetryCheckBox2->Left = ColorimetryCheckBox1->Left;
	ColorimetryCheckBox2->Top = ColorimetryCheckBox1->Top + ColorimetryCheckBox1->Height + CheckBoxSpacing;

	ColorimetryCheckBox3->Width = CheckBoxWidth + Canvas->TextWidth(ColorimetryCheckBox3->Caption);
	ColorimetryCheckBox3->Height = CheckBoxHeight;
	ColorimetryCheckBox3->Left = ColorimetryCheckBox2->Left;
	ColorimetryCheckBox3->Top = ColorimetryCheckBox2->Top + ColorimetryCheckBox2->Height + CheckBoxSpacing;

	ColorimetryCheckBox4->Width = CheckBoxWidth + Canvas->TextWidth(ColorimetryCheckBox4->Caption);
	ColorimetryCheckBox4->Height = CheckBoxHeight;
	ColorimetryCheckBox4->Left = ColorimetryCheckBox3->Left;
	ColorimetryCheckBox4->Top = ColorimetryCheckBox3->Top + ColorimetryCheckBox3->Height + CheckBoxSpacing;

	ColorimetryCheckBox5->Width = CheckBoxWidth + Canvas->TextWidth(ColorimetryCheckBox5->Caption);
	ColorimetryCheckBox5->Height = CheckBoxHeight;
	ColorimetryCheckBox5->Left = ColorimetryCheckBox4->Left;
	ColorimetryCheckBox5->Top = ColorimetryCheckBox4->Top + ColorimetryCheckBox4->Height + CheckBoxSpacing;

	ColorimetryCheckBox6->Width = CheckBoxWidth + Canvas->TextWidth(ColorimetryCheckBox6->Caption);
	ColorimetryCheckBox6->Height = CheckBoxHeight;
	ColorimetryCheckBox6->Left = ColorimetryCheckBox5->Left;
	ColorimetryCheckBox6->Top = ColorimetryCheckBox5->Top + ColorimetryCheckBox5->Height + CheckBoxSpacing;

	ColorimetryCheckBox7->Width = CheckBoxWidth + Canvas->TextWidth(ColorimetryCheckBox7->Caption);
	ColorimetryCheckBox7->Height = CheckBoxHeight;
	ColorimetryCheckBox7->Left = ColorimetryCheckBox6->Left;
	ColorimetryCheckBox7->Top = ColorimetryCheckBox6->Top + ColorimetryCheckBox6->Height + CheckBoxSpacing;

	ColorimetryCheckBox8->Width = CheckBoxWidth + Canvas->TextWidth(ColorimetryCheckBox8->Caption);
	ColorimetryCheckBox8->Height = CheckBoxHeight;
	ColorimetryCheckBox8->Left = ColorimetryCheckBox7->Left;
	ColorimetryCheckBox8->Top = ColorimetryCheckBox7->Top + ColorimetryCheckBox7->Height + CheckBoxSpacing;

	ColorimetryGroupBox->Width = FormButtonsWidth;
	ColorimetryGroupBox->Height = ColorimetryCheckBox8->Top + ColorimetryCheckBox8->Height + CheckBoxBottom + PaddingBottom;
	ColorimetryGroupBox->Left = Scale;
	ColorimetryGroupBox->Top = GroupBoxTop;

	MetadataCheckBox0->Width = CheckBoxWidth + Canvas->TextWidth(MetadataCheckBox0->Caption);
	MetadataCheckBox0->Height = CheckBoxHeight;
	MetadataCheckBox0->Left = PaddingWidth;
	MetadataCheckBox0->Top = PaddingTop + CheckBoxTop;

	MetadataCheckBox1->Width = CheckBoxWidth + Canvas->TextWidth(MetadataCheckBox1->Caption);
	MetadataCheckBox1->Height = CheckBoxHeight;
	MetadataCheckBox1->Left = MetadataCheckBox0->Left;
	MetadataCheckBox1->Top = MetadataCheckBox0->Top + MetadataCheckBox0->Height + CheckBoxSpacing;

	MetadataCheckBox2->Width = CheckBoxWidth + Canvas->TextWidth(MetadataCheckBox2->Caption);
	MetadataCheckBox2->Height = CheckBoxHeight;
	MetadataCheckBox2->Left = MetadataCheckBox1->Left;
	MetadataCheckBox2->Top = MetadataCheckBox1->Top + MetadataCheckBox1->Height + CheckBoxSpacing;

	MetadataCheckBox3->Width = CheckBoxWidth + Canvas->TextWidth(MetadataCheckBox3->Caption);
	MetadataCheckBox3->Height = CheckBoxHeight;
	MetadataCheckBox3->Left = MetadataCheckBox2->Left;
	MetadataCheckBox3->Top = MetadataCheckBox2->Top + MetadataCheckBox2->Height + CheckBoxSpacing;

	MetadataGroupBox->Width = ColorimetryGroupBox->Width;
	MetadataGroupBox->Height = MetadataCheckBox3->Top + MetadataCheckBox3->Height + CheckBoxBottom + PaddingBottom;
	MetadataGroupBox->Left = ColorimetryGroupBox->Left;
	MetadataGroupBox->Top = ColorimetryGroupBox->Top + ColorimetryGroupBox->Height + GroupBoxBottom + GroupBoxTop;

	FormOKButton->Width = FormButtonWidth;
	FormOKButton->Height = FormButtonHeight;
	FormOKButton->Top = MetadataGroupBox->Top + MetadataGroupBox->Height + GroupBoxBottom + Scale + ButtonTop;
	Common::FixButtonCaption(FormOKButton, Canvas->TextWidth(FormOKButton->Caption));

	FormCancelButton->Width = FormButtonWidth;
	FormCancelButton->Height = FormButtonHeight;
	FormCancelButton->Top = FormOKButton->Top;
	Common::FixButtonCaption(FormCancelButton, Canvas->TextWidth(FormCancelButton->Caption));

	FormCancelButton->Left = MetadataGroupBox->Left + MetadataGroupBox->Width - ButtonRight - FormCancelButton->Width;
	FormOKButton->Left = FormCancelButton->Left - ButtonLeft - Scale - ButtonRight - FormOKButton->Width;

	ClientWidth = FormCancelButton->Left + FormCancelButton->Width + ButtonRight + Scale;
	ClientHeight = FormCancelButton->Top + FormCancelButton->Height + ButtonBottom + Scale;
	return true;
}
//---------------------------------------------------------------------------
void __fastcall TColorimetryForm::FormCreate(TObject *Sender)
{
	ScaleControls();
}
//---------------------------------------------------------------------------
void __fastcall TColorimetryForm::FormShow(TObject *Sender)
{
	Refresh(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TColorimetryForm::ColorimetryCheckBoxClick(TObject *Sender)
{
	if (Refreshing)
		return;

	TCheckBox *CheckBox = (TCheckBox *)Sender;
	Colorimetry->SetColorimetry(CheckBox->Tag, CheckBox->Checked);
	Refresh(ColorimetryGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TColorimetryForm::MetadataCheckBoxClick(TObject *Sender)
{
	if (Refreshing)
		return;

	TCheckBox *CheckBox = (TCheckBox *)Sender;
	Colorimetry->SetMetadata(CheckBox->Tag, CheckBox->Checked);
	Refresh(MetadataGroupBox);
}
//---------------------------------------------------------------------------
