//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "TiledDisplayTopologyFormClass.h"
#include "Common.h"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TTiledDisplayTopologyForm *TiledDisplayTopologyForm;
//---------------------------------------------------------------------------
__fastcall TTiledDisplayTopologyForm::TTiledDisplayTopologyForm(TComponent *Owner) : TCommonForm(Owner)
{
	Refreshing = false;
}
//---------------------------------------------------------------------------
bool TTiledDisplayTopologyForm::Connect(TiledDisplayTopologyClass &NewTiledDisplayTopology)
{
	TiledDisplayTopology = &NewTiledDisplayTopology;
	return true;
}
//---------------------------------------------------------------------------
TColor TTiledDisplayTopologyForm::GetTextColor(bool Valid)
{
	if (!Valid)
		return (TColor)RGB(255, 0, 0);

	return clWindowText;
}
//---------------------------------------------------------------------------
bool TTiledDisplayTopologyForm::Refresh(void *Value)
{
	Refreshing = true;

	if (Value == NULL || Value == PhysicalEnclosuresGroupBox)
		RefreshPhysicalEnclosuresRadioButtons();

	if (Value == NULL || Value == SingleTileBehaviorGroupBox)
		RefreshSingleTileBehaviorRadioButtons();

	if (Value == NULL || Value == MultipleTileBehaviorGroupBox)
		RefreshMultipleTileBehaviorRadioButtons();

	if (Value == NULL || Value == TilesGroupBox)
		RefreshTilesTextBoxes();

	if (Value == NULL || Value == LocationGroupBox)
		RefreshLocationTextBoxes();

	if (Value == NULL || Value == SizeGroupBox)
		RefreshSizeTextBoxes();

	if (Value == NULL || Value == BezelGroupBox)
		RefreshBezelTextBoxes();

	if (Value == NULL || Value == TopologyIDGroupBox)
		RefreshTopologyIDTextBoxes();

	if (Value != FormOKButton)
		FormOKButton->Enabled = TiledDisplayTopology->IsValid();

	Refreshing = false;
	return true;
}
//---------------------------------------------------------------------------
bool TTiledDisplayTopologyForm::RefreshPhysicalEnclosuresRadioButtons()
{
	PhysicalEnclosuresRadioButton1->Checked = TiledDisplayTopology->GetPhysicalEnclosures() == 1;
	PhysicalEnclosuresRadioButton0->Checked = TiledDisplayTopology->GetPhysicalEnclosures() == 0;
	return true;
}
//---------------------------------------------------------------------------
bool TTiledDisplayTopologyForm::RefreshSingleTileBehaviorRadioButtons()
{
	SingleTileBehaviorRadioButton1->Checked = TiledDisplayTopology->GetSingleTileBehavior() == 1;
	SingleTileBehaviorRadioButton2->Checked = TiledDisplayTopology->GetSingleTileBehavior() == 2;
	SingleTileBehaviorRadioButton3->Checked = TiledDisplayTopology->GetSingleTileBehavior() == 3;
	SingleTileBehaviorRadioButton0->Checked = TiledDisplayTopology->GetSingleTileBehavior() == 0;
	return true;
}
//---------------------------------------------------------------------------
bool TTiledDisplayTopologyForm::RefreshMultipleTileBehaviorRadioButtons()
{
	MultipleTileBehaviorRadioButton1->Checked = TiledDisplayTopology->GetMultipleTileBehavior() == 1;
	MultipleTileBehaviorRadioButton0->Checked = TiledDisplayTopology->GetMultipleTileBehavior() == 0;
	return true;
}
//---------------------------------------------------------------------------
bool TTiledDisplayTopologyForm::RefreshTilesTextBoxes()
{
	char Text[TEXTSIZE];

	HTiles->Font->Color = GetTextColor(TiledDisplayTopology->IsValidHTiles());

	if (!HTiles->Focused() && Common::IntegerToText(TiledDisplayTopology->GetHTiles(), Text, TEXTSIZE))
		HTiles->Text = Text;

	VTiles->Font->Color = GetTextColor(TiledDisplayTopology->IsValidVTiles());

	if (!VTiles->Focused() && Common::IntegerToText(TiledDisplayTopology->GetVTiles(), Text, TEXTSIZE))
		VTiles->Text = Text;

	return true;
}
//---------------------------------------------------------------------------
bool TTiledDisplayTopologyForm::RefreshLocationTextBoxes()
{
	char Text[TEXTSIZE];

	HLocation->Font->Color = GetTextColor(TiledDisplayTopology->IsValidHLocation());

	if (!HLocation->Focused() && Common::IntegerToText(TiledDisplayTopology->GetHLocation(), Text, TEXTSIZE))
		HLocation->Text = Text;

	VLocation->Font->Color = GetTextColor(TiledDisplayTopology->IsValidVLocation());

	if (!VLocation->Focused() && Common::IntegerToText(TiledDisplayTopology->GetVLocation(), Text, TEXTSIZE))
		VLocation->Text = Text;

	return true;
}
//---------------------------------------------------------------------------
bool TTiledDisplayTopologyForm::RefreshSizeTextBoxes()
{
	char Text[TEXTSIZE];

	HSize->Font->Color = GetTextColor(TiledDisplayTopology->IsValidHSize());

	if (!HSize->Focused() && Common::IntegerToText(TiledDisplayTopology->GetHSize(), Text, TEXTSIZE))
		HSize->Text = Text;

	VSize->Font->Color = GetTextColor(TiledDisplayTopology->IsValidVSize());

	if (!VSize->Focused() && Common::IntegerToText(TiledDisplayTopology->GetVSize(), Text, TEXTSIZE))
		VSize->Text = Text;

	return true;
}
//---------------------------------------------------------------------------
bool TTiledDisplayTopologyForm::RefreshBezelTextBoxes()
{
	char Text[TEXTSIZE];

	PixelMultiplier->Font->Color = GetTextColor(TiledDisplayTopology->IsValidPixelMultiplier());

	if (!PixelMultiplier->Focused() && Common::IntegerToText(TiledDisplayTopology->GetPixelMultiplier(), Text, TEXTSIZE))
		PixelMultiplier->Text = Text;

	TopBezelSize->Font->Color = GetTextColor(TiledDisplayTopology->IsValidTopBezelSize());

	if (!TopBezelSize->Focused() && Common::IntegerToText(TiledDisplayTopology->GetTopBezelSize(), Text, TEXTSIZE))
		TopBezelSize->Text = Text;

	BottomBezelSize->Font->Color = GetTextColor(TiledDisplayTopology->IsValidBottomBezelSize());

	if (!BottomBezelSize->Focused() && Common::IntegerToText(TiledDisplayTopology->GetBottomBezelSize(), Text, TEXTSIZE))
		BottomBezelSize->Text = Text;

	RightBezelSize->Font->Color = GetTextColor(TiledDisplayTopology->IsValidRightBezelSize());

	if (!RightBezelSize->Focused() && Common::IntegerToText(TiledDisplayTopology->GetRightBezelSize(), Text, TEXTSIZE))
		RightBezelSize->Text = Text;

	LeftBezelSize->Font->Color = GetTextColor(TiledDisplayTopology->IsValidLeftBezelSize());

	if (!LeftBezelSize->Focused() && Common::IntegerToText(TiledDisplayTopology->GetLeftBezelSize(), Text, TEXTSIZE))
		LeftBezelSize->Text = Text;

	return true;
}
//---------------------------------------------------------------------------
bool TTiledDisplayTopologyForm::RefreshTopologyIDTextBoxes()
{
	char Text[TEXTSIZE];

	ProductID->Font->Color = GetTextColor(TiledDisplayTopology->IsValidProductID());

	if (!ProductID->Focused() && TiledDisplayTopology->GetProductID(Text, TEXTSIZE))
		ProductID->Text = Text;

	SerialID->Font->Color = GetTextColor(TiledDisplayTopology->IsValidSerialID());

	if (!SerialID->Focused() && Common::DecimalToText(TiledDisplayTopology->GetSerialID(), SerialID->MaxLength, 0, Text, TEXTSIZE))
		SerialID->Text = Text;

	ProductIDResetButton->Enabled = TiledDisplayTopology->ResetProductIDPossible();
	return true;
}
//---------------------------------------------------------------------------
bool TTiledDisplayTopologyForm::ScaleControls()
{
	PhysicalEnclosuresRadioButton1->Width = RadioButtonWidth + Canvas->TextWidth(PhysicalEnclosuresRadioButton1->Caption);
	PhysicalEnclosuresRadioButton1->Height = RadioButtonHeight;
	PhysicalEnclosuresRadioButton1->Left = PaddingWidth;
	PhysicalEnclosuresRadioButton1->Top = PaddingTop + RadioButtonTop;

	PhysicalEnclosuresRadioButton0->Width = RadioButtonWidth + Canvas->TextWidth(PhysicalEnclosuresRadioButton0->Caption);
	PhysicalEnclosuresRadioButton0->Height = RadioButtonHeight;
	PhysicalEnclosuresRadioButton0->Left = PhysicalEnclosuresRadioButton1->Left;
	PhysicalEnclosuresRadioButton0->Top = PhysicalEnclosuresRadioButton1->Top + PhysicalEnclosuresRadioButton1->Height + RadioButtonSpacing;

	PhysicalEnclosuresGroupBox->Width = FormButtonsWidth;
	PhysicalEnclosuresGroupBox->Height = PhysicalEnclosuresRadioButton0->Top + PhysicalEnclosuresRadioButton0->Height + RadioButtonBottom + PaddingBottom;
	PhysicalEnclosuresGroupBox->Left = Scale;
	PhysicalEnclosuresGroupBox->Top = GroupBoxTop;

	SingleTileBehaviorRadioButton1->Width = RadioButtonWidth + Canvas->TextWidth(SingleTileBehaviorRadioButton1->Caption);
	SingleTileBehaviorRadioButton1->Height = RadioButtonHeight;
	SingleTileBehaviorRadioButton1->Left = PaddingWidth;
	SingleTileBehaviorRadioButton1->Top = PaddingTop + RadioButtonTop;

	SingleTileBehaviorRadioButton2->Width = RadioButtonWidth + Canvas->TextWidth(SingleTileBehaviorRadioButton2->Caption);
	SingleTileBehaviorRadioButton2->Height = RadioButtonHeight;
	SingleTileBehaviorRadioButton2->Left = SingleTileBehaviorRadioButton1->Left;
	SingleTileBehaviorRadioButton2->Top = SingleTileBehaviorRadioButton1->Top + SingleTileBehaviorRadioButton1->Height + RadioButtonSpacing;

	SingleTileBehaviorRadioButton3->Width = RadioButtonWidth + Canvas->TextWidth(SingleTileBehaviorRadioButton3->Caption);
	SingleTileBehaviorRadioButton3->Height = RadioButtonHeight;
	SingleTileBehaviorRadioButton3->Left = SingleTileBehaviorRadioButton2->Left;
	SingleTileBehaviorRadioButton3->Top = SingleTileBehaviorRadioButton2->Top + SingleTileBehaviorRadioButton2->Height + RadioButtonSpacing;

	SingleTileBehaviorRadioButton0->Width = RadioButtonWidth + Canvas->TextWidth(SingleTileBehaviorRadioButton0->Caption);
	SingleTileBehaviorRadioButton0->Height = RadioButtonHeight;
	SingleTileBehaviorRadioButton0->Left = SingleTileBehaviorRadioButton3->Left;
	SingleTileBehaviorRadioButton0->Top = SingleTileBehaviorRadioButton3->Top + SingleTileBehaviorRadioButton3->Height + RadioButtonSpacing;

	SingleTileBehaviorGroupBox->Width = PhysicalEnclosuresGroupBox->Width;
	SingleTileBehaviorGroupBox->Height = SingleTileBehaviorRadioButton0->Top + SingleTileBehaviorRadioButton0->Height + RadioButtonBottom + PaddingBottom;
	SingleTileBehaviorGroupBox->Left = PhysicalEnclosuresGroupBox->Left;
	SingleTileBehaviorGroupBox->Top = PhysicalEnclosuresGroupBox->Top + PhysicalEnclosuresGroupBox->Height + GroupBoxBottom + GroupBoxTop;

	MultipleTileBehaviorRadioButton1->Width = RadioButtonWidth + Canvas->TextWidth(MultipleTileBehaviorRadioButton1->Caption);
	MultipleTileBehaviorRadioButton1->Height = RadioButtonHeight;
	MultipleTileBehaviorRadioButton1->Left = PaddingWidth;
	MultipleTileBehaviorRadioButton1->Top = PaddingTop + RadioButtonTop;

	MultipleTileBehaviorRadioButton0->Width = RadioButtonWidth + Canvas->TextWidth(MultipleTileBehaviorRadioButton0->Caption);
	MultipleTileBehaviorRadioButton0->Height = RadioButtonHeight;
	MultipleTileBehaviorRadioButton0->Left = MultipleTileBehaviorRadioButton1->Left;
	MultipleTileBehaviorRadioButton0->Top = MultipleTileBehaviorRadioButton1->Top + MultipleTileBehaviorRadioButton1->Height + RadioButtonSpacing;

	MultipleTileBehaviorGroupBox->Width = SingleTileBehaviorGroupBox->Width;
	MultipleTileBehaviorGroupBox->Height = MultipleTileBehaviorRadioButton0->Top + MultipleTileBehaviorRadioButton0->Height + RadioButtonBottom + PaddingBottom;
	MultipleTileBehaviorGroupBox->Left = SingleTileBehaviorGroupBox->Left;
	MultipleTileBehaviorGroupBox->Top = SingleTileBehaviorGroupBox->Top + SingleTileBehaviorGroupBox->Height + GroupBoxBottom + GroupBoxTop;

	HTiles->AutoSize = false;
	HTiles->Width = HTiles->MaxLength * NumberWidth + NumberWidth + TextBoxPadding;
	HTiles->Height = TextBoxHeight;
	HTiles->Left = PaddingWidth;
	HTiles->Top = PaddingTop;

	TilesLabel->Left = HTiles->Left + HTiles->Width + LabelSpacing;
	TilesLabel->Top = HTiles->Top + 3;

	VTiles->AutoSize = false;
	VTiles->Width = VTiles->MaxLength * NumberWidth + NumberWidth + TextBoxPadding;
	VTiles->Height = TextBoxHeight;
	VTiles->Left = TilesLabel->Left + TilesLabel->Width + LabelSpacing;
	VTiles->Top = HTiles->Top;

	TilesGroupBox->Width = MultipleTileBehaviorGroupBox->Width;
	TilesGroupBox->Height = HTiles->Top + HTiles->Height + PaddingBottom;
	TilesGroupBox->Left = MultipleTileBehaviorGroupBox->Left;
	TilesGroupBox->Top = MultipleTileBehaviorGroupBox->Top + MultipleTileBehaviorGroupBox->Height + GroupBoxBottom + GroupBoxTop;

	HLocation->AutoSize = false;
	HLocation->Width = HLocation->MaxLength * NumberWidth + NumberWidth + TextBoxPadding;
	HLocation->Height = TextBoxHeight;
	HLocation->Left = PaddingWidth;
	HLocation->Top = PaddingTop;

	LocationLabel->Left = HLocation->Left + HLocation->Width + LabelSpacing;
	LocationLabel->Top = HLocation->Top + 3;

	VLocation->AutoSize = false;
	VLocation->Width = VLocation->MaxLength * NumberWidth + NumberWidth + TextBoxPadding;
	VLocation->Height = TextBoxHeight;
	VLocation->Left = LocationLabel->Left + TilesLabel->Width + LabelSpacing;
	VLocation->Top = HLocation->Top;

	LocationGroupBox->Width = TilesGroupBox->Width;
	LocationGroupBox->Height = HLocation->Top + HLocation->Height + PaddingBottom;
	LocationGroupBox->Left = TilesGroupBox->Left;
	LocationGroupBox->Top = TilesGroupBox->Top + TilesGroupBox->Height + GroupBoxBottom + GroupBoxTop;

	HSize->AutoSize = false;
	HSize->Width = HSize->MaxLength * NumberWidth + TextBoxPadding;
	HSize->Height = TextBoxHeight;
	HSize->Left = PaddingWidth;
	HSize->Top = PaddingTop;

	SizeLabel->Left = HSize->Left + HSize->Width + LabelSpacing;
	SizeLabel->Top = HSize->Top + 3;

	VSize->AutoSize = false;
	VSize->Width = VSize->MaxLength * NumberWidth + TextBoxPadding;
	VSize->Height = TextBoxHeight;
	VSize->Left = SizeLabel->Left + SizeLabel->Width + LabelSpacing;
	VSize->Top = HSize->Top;

	SizeGroupBox->Width = LocationGroupBox->Width;
	SizeGroupBox->Height = HSize->Top + HSize->Height + PaddingBottom;
	SizeGroupBox->Left = LocationGroupBox->Left;
	SizeGroupBox->Top = LocationGroupBox->Top + LocationGroupBox->Height + GroupBoxBottom + GroupBoxTop;

	PixelMultiplier->AutoSize = false;
	PixelMultiplier->Width = PixelMultiplier->MaxLength * NumberWidth + TextBoxPadding;
	PixelMultiplier->Height = TextBoxHeight;

	TopBezelSize->AutoSize = false;
	TopBezelSize->Width = TopBezelSize->MaxLength * NumberWidth + TextBoxPadding;
	TopBezelSize->Height = TextBoxHeight;

	BottomBezelSize->AutoSize = false;
	BottomBezelSize->Width = BottomBezelSize->MaxLength * NumberWidth + TextBoxPadding;
	BottomBezelSize->Height = TextBoxHeight;

	RightBezelSize->AutoSize = false;
	RightBezelSize->Width = RightBezelSize->MaxLength * NumberWidth + TextBoxPadding;
	RightBezelSize->Height = TextBoxHeight;

	LeftBezelSize->AutoSize = false;
	LeftBezelSize->Width = LeftBezelSize->MaxLength * NumberWidth + TextBoxPadding;
	LeftBezelSize->Height = TextBoxHeight;

	PixelMultiplier->Top = PaddingTop;
	TopBezelSize->Top = PixelMultiplier->Top + PixelMultiplier->Height + TextBoxSpacing;
	BottomBezelSize->Top = TopBezelSize->Top + TopBezelSize->Height + TextBoxSpacing;
	RightBezelSize->Top = BottomBezelSize->Top + BottomBezelSize->Height + TextBoxSpacing;
	LeftBezelSize->Top = RightBezelSize->Top + RightBezelSize->Height + TextBoxSpacing;

	MultiplierLabel->Top = PixelMultiplier->Top + 3;
	TopLabel->Top = TopBezelSize->Top + 3;
	BottomLabel->Top = BottomBezelSize->Top + 3;
	RightLabel->Top = RightBezelSize->Top + 3;
	LeftLabel->Top = LeftBezelSize->Top + 3;

	MultiplierLabel->Left = PaddingWidth;
	TopLabel->Left = MultiplierLabel->Left;
	BottomLabel->Left = TopLabel->Left;
	RightLabel->Left = BottomLabel->Left;
	LeftLabel->Left = RightLabel->Left;

	PixelMultiplier->Left = MultiplierLabel->Left + MultiplierLabel->Width + LabelSpacing;
	TopBezelSize->Left = PixelMultiplier->Left;
	BottomBezelSize->Left = TopBezelSize->Left;
	RightBezelSize->Left = BottomBezelSize->Left;
	LeftBezelSize->Left = RightBezelSize->Left;

	BezelGroupBox->Width = SizeGroupBox->Width;
	BezelGroupBox->Height = LeftBezelSize->Top + LeftBezelSize->Height + PaddingBottom;
	BezelGroupBox->Left = SizeGroupBox->Left;
	BezelGroupBox->Top = SizeGroupBox->Top + SizeGroupBox->Height + GroupBoxBottom + GroupBoxTop;

	ProductIDResetButton->Width = ButtonWidth;
	ProductIDResetButton->Height = ButtonHeight;
	Common::FixButtonCaption(ProductIDResetButton, Canvas->TextWidth(ProductIDResetButton->Caption));

	ProductID->AutoSize = false;
	ProductID->Width = FormButtonsWidth - PaddingWidth - ProductIDLabel->Width - LabelSpacing - Scale - ButtonLeft - ProductIDResetButton->Width - ButtonRight - PaddingWidth;
	ProductID->Height = TextBoxHeight;

	SerialID->AutoSize = false;
	SerialID->Width = FormButtonsWidth - PaddingWidth - SerialIDLabel->Width - LabelSpacing - PaddingWidth;
	SerialID->Height = TextBoxHeight;

	ProductID->Top = PaddingTop;
	ProductIDLabel->Top = ProductID->Top + 3;
	ProductIDResetButton->Top = ProductID->Top;

	SerialID->Top = ProductID->Top + ProductID->Height + TextBoxSpacing;
	SerialIDLabel->Top = SerialID->Top + 3;

	ProductIDLabel->Left = PaddingWidth;
	ProductID->Left = ProductIDLabel->Left + ProductIDLabel->Width + LabelSpacing;
	ProductIDResetButton->Left = ProductID->Left + ProductID->Width + Scale + ButtonLeft;

	SerialIDLabel->Left = ProductIDLabel->Left;
	SerialID->Left = SerialIDLabel->Left + SerialIDLabel->Width + LabelSpacing;

	TopologyIDGroupBox->Width = BezelGroupBox->Width;
	TopologyIDGroupBox->Height = SerialID->Top + SerialID->Height + PaddingBottom;
	TopologyIDGroupBox->Left = BezelGroupBox->Left;
	TopologyIDGroupBox->Top = BezelGroupBox->Top + BezelGroupBox->Height + GroupBoxBottom + GroupBoxTop;

	FormOKButton->Width = FormButtonWidth;
	FormOKButton->Height = FormButtonHeight;
	FormOKButton->Top = TopologyIDGroupBox->Top + TopologyIDGroupBox->Height + GroupBoxBottom + Scale + ButtonTop;
	Common::FixButtonCaption(FormOKButton, Canvas->TextWidth(FormOKButton->Caption));

	FormCancelButton->Width = FormButtonWidth;
	FormCancelButton->Height = FormButtonHeight;
	FormCancelButton->Top = FormOKButton->Top;
	Common::FixButtonCaption(FormCancelButton, Canvas->TextWidth(FormCancelButton->Caption));

	FormCancelButton->Left = TopologyIDGroupBox->Left + TopologyIDGroupBox->Width - ButtonRight - FormCancelButton->Width;
	FormOKButton->Left = FormCancelButton->Left - ButtonLeft - Scale - ButtonRight - FormOKButton->Width;

	ClientWidth = FormCancelButton->Left + FormCancelButton->Width + ButtonRight + Scale;
	ClientHeight = FormCancelButton->Top + FormCancelButton->Height + ButtonBottom + Scale;
	return true;
}
//---------------------------------------------------------------------------
void __fastcall TTiledDisplayTopologyForm::FormCreate(TObject *Sender)
{
	ScaleControls();
}
//---------------------------------------------------------------------------
void __fastcall TTiledDisplayTopologyForm::FormShow(TObject *Sender)
{
	Refresh(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TTiledDisplayTopologyForm::EnclosuresRadioButtonClick(TObject *Sender)
{
	if (Refreshing)
		return;

	TRadioButton *RadioButton = (TRadioButton *)Sender;
	TiledDisplayTopology->SetPhysicalEnclosures(RadioButton->Tag);
	Refresh(PhysicalEnclosuresGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TTiledDisplayTopologyForm::SingleTileBehaviorRadioButtonClick(TObject *Sender)
{
	if (Refreshing)
		return;

	TRadioButton *RadioButton = (TRadioButton *)Sender;
	TiledDisplayTopology->SetSingleTileBehavior(RadioButton->Tag);
	Refresh(SingleTileBehaviorGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TTiledDisplayTopologyForm::MultipleTileBehaviorRadioButtonClick(TObject *Sender)
{
	if (Refreshing)
		return;

	TRadioButton *RadioButton = (TRadioButton *)Sender;
	TiledDisplayTopology->SetMultipleTileBehavior(RadioButton->Tag);
	Refresh(MultipleTileBehaviorGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TTiledDisplayTopologyForm::HTilesChange(TObject *Sender)
{
	if (Refreshing)
		return;

	TiledDisplayTopology->SetHTiles(Common::TextToInteger(HTiles->Text.c_str()));
	Refresh(TilesGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TTiledDisplayTopologyForm::HTilesExit(TObject *Sender)
{
	Refresh(TilesGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TTiledDisplayTopologyForm::VTilesChange(TObject *Sender)
{
	if (Refreshing)
		return;

	TiledDisplayTopology->SetVTiles(Common::TextToInteger(VTiles->Text.c_str()));
	Refresh(TilesGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TTiledDisplayTopologyForm::VTilesExit(TObject *Sender)
{
	Refresh(TilesGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TTiledDisplayTopologyForm::HLocationChange(TObject *Sender)
{
	if (Refreshing)
		return;

	TiledDisplayTopology->SetHLocation(Common::TextToInteger(HLocation->Text.c_str()));
	Refresh(LocationGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TTiledDisplayTopologyForm::HLocationExit(TObject *Sender)
{
	Refresh(LocationGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TTiledDisplayTopologyForm::VLocationChange(TObject *Sender)
{
	if (Refreshing)
		return;

	TiledDisplayTopology->SetVLocation(Common::TextToInteger(VLocation->Text.c_str()));
	Refresh(LocationGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TTiledDisplayTopologyForm::VLocationExit(TObject *Sender)
{
	Refresh(LocationGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TTiledDisplayTopologyForm::HSizeChange(TObject *Sender)
{
	if (Refreshing)
		return;

	TiledDisplayTopology->SetHSize(Common::TextToInteger(HSize->Text.c_str()));
	Refresh(SizeGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TTiledDisplayTopologyForm::HSizeExit(TObject *Sender)
{
	Refresh(SizeGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TTiledDisplayTopologyForm::VSizeChange(TObject *Sender)
{
	if (Refreshing)
		return;

	TiledDisplayTopology->SetVSize(Common::TextToInteger(VSize->Text.c_str()));
	Refresh(SizeGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TTiledDisplayTopologyForm::VSizeExit(TObject *Sender)
{
	Refresh(SizeGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TTiledDisplayTopologyForm::PixelMultiplierChange(TObject *Sender)
{
	if (Refreshing)
		return;

	TiledDisplayTopology->SetPixelMultiplier(Common::TextToInteger(PixelMultiplier->Text.c_str()));
	Refresh(BezelGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TTiledDisplayTopologyForm::PixelMultiplierExit(TObject *Sender)
{
	Refresh(BezelGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TTiledDisplayTopologyForm::TopBezelSizeChange(TObject *Sender)
{
	if (Refreshing)
		return;

	TiledDisplayTopology->SetTopBezelSize(Common::TextToInteger(TopBezelSize->Text.c_str()));
	Refresh(BezelGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TTiledDisplayTopologyForm::TopBezelSizeExit(TObject *Sender)
{
	Refresh(BezelGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TTiledDisplayTopologyForm::BottomBezelSizeChange(TObject *Sender)
{
	if (Refreshing)
		return;

	TiledDisplayTopology->SetBottomBezelSize(Common::TextToInteger(BottomBezelSize->Text.c_str()));
	Refresh(BezelGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TTiledDisplayTopologyForm::BottomBezelSizeExit(TObject *Sender)
{
	Refresh(BezelGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TTiledDisplayTopologyForm::RightBezelSizeChange(TObject *Sender)
{
	if (Refreshing)
		return;

	TiledDisplayTopology->SetRightBezelSize(Common::TextToInteger(RightBezelSize->Text.c_str()));
	Refresh(BezelGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TTiledDisplayTopologyForm::RightBezelSizeExit(TObject *Sender)
{
	Refresh(BezelGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TTiledDisplayTopologyForm::LeftBezelSizeChange(TObject *Sender)
{
	if (Refreshing)
		return;

	TiledDisplayTopology->SetLeftBezelSize(Common::TextToInteger(LeftBezelSize->Text.c_str()));
	Refresh(BezelGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TTiledDisplayTopologyForm::LeftBezelSizeExit(TObject *Sender)
{
	Refresh(BezelGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TTiledDisplayTopologyForm::ProductIDChange(TObject *Sender)
{
	if (Refreshing)
		return;

	TiledDisplayTopology->SetProductID(ProductID->Text.c_str());
	Refresh(TopologyIDGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TTiledDisplayTopologyForm::ProductIDExit(TObject *Sender)
{
	Refresh(TopologyIDGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TTiledDisplayTopologyForm::ProductIDKeyPress(TObject *Sender, char &Key)
{
	if (GetAsyncKeyState(VK_SHIFT) < 0)
	{
		if (Key >= 'A' && Key <= 'Z')
			Key |= 32;
	}
	else
	{
		if (Key >= 'a' && Key <= 'z')
			Key &= ~32;
	}
}
//---------------------------------------------------------------------------
void __fastcall TTiledDisplayTopologyForm::ProductIDResetButtonClick(TObject *Sender)
{
	TiledDisplayTopology->ResetProductID();
	Refresh(TopologyIDGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TTiledDisplayTopologyForm::SerialIDChange(TObject *Sender)
{
	if (Refreshing)
		return;

	TiledDisplayTopology->SetSerialID(Common::TextToDecimal(SerialID->Text.c_str(), 0));
	Refresh(TopologyIDGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TTiledDisplayTopologyForm::SerialIDExit(TObject *Sender)
{
	Refresh(TopologyIDGroupBox);
}
//---------------------------------------------------------------------------
