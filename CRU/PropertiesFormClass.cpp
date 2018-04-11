//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "PropertiesFormClass.h"
#include "Common.h"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TPropertiesForm *PropertiesForm;
//---------------------------------------------------------------------------
__fastcall TPropertiesForm::TPropertiesForm(TComponent *Owner) : TCommonForm(Owner)
{
	Refreshing = false;
}
//---------------------------------------------------------------------------
bool TPropertiesForm::Connect(PropertiesClass &NewProperties)
{
	Properties = &NewProperties;
	return true;
}
//---------------------------------------------------------------------------
TColor TPropertiesForm::GetTextColor(bool Valid)
{
	if (!Valid)
		return (TColor)RGB(255, 0, 0);

	return clWindowText;
}
//---------------------------------------------------------------------------
bool TPropertiesForm::Refresh(void *Value)
{
	char Text[TEXTSIZE];

	Refreshing = true;

	if (Value == NULL || Value == ProductIDGroupBox)
	{
		ProductID->Font->Color = GetTextColor(Properties->IsValidProductID());

		if (!ProductID->Focused() && Properties->GetProductID(Text, TEXTSIZE))
			ProductID->Text = Text;

		SerialID->Font->Color = GetTextColor(Properties->IsValidSerialID());

		if (!SerialID->Focused() && Common::DecimalToText(Properties->GetSerialID(), SerialID->MaxLength, 0, Text, TEXTSIZE))
			SerialID->Text = Text;

		ProductIDResetButton->Enabled = Properties->ResetProductIDPossible();
	}

	if (Value == NULL || Value == NameGroupBox)
	{
		Name->Font->Color = GetTextColor(Properties->IsValidName());

		if (!Name->Focused() && Properties->GetName(Text, TEXTSIZE))
			Name->Text = Text;

		IncludeName->Checked = Properties->GetIncludeName();
	}

	if (Value == NULL || Value == SerialNumberGroupBox)
	{
		SerialNumber->Font->Color = GetTextColor(Properties->IsValidSerialNumber());

		if (!SerialNumber->Focused() && Properties->GetSerialNumber(Text, TEXTSIZE))
			SerialNumber->Text = Text;

		IncludeSerialNumber->Checked = Properties->GetIncludeSerialNumber();
	}

	if (Value == NULL || Value == RangeLimitsGroupBox)
	{
		MinVRate->Font->Color = GetTextColor(Properties->IsValidMinVRate());

		if (!MinVRate->Focused() && Common::IntegerToText(Properties->GetMinVRate(), Text, TEXTSIZE))
			MinVRate->Text = Text;

		MaxVRate->Font->Color = GetTextColor(Properties->IsValidMaxVRate());

		if (!MaxVRate->Focused() && Common::IntegerToText(Properties->GetMaxVRate(), Text, TEXTSIZE))
			MaxVRate->Text = Text;

		MinHRate->Font->Color = GetTextColor(Properties->IsValidMinHRate());

		if (!MinHRate->Focused() && Common::IntegerToText(Properties->GetMinHRate(), Text, TEXTSIZE))
			MinHRate->Text = Text;

		MaxHRate->Font->Color = GetTextColor(Properties->IsValidMaxHRate());

		if (!MaxHRate->Focused() && Common::IntegerToText(Properties->GetMaxHRate(), Text, TEXTSIZE))
			MaxHRate->Text = Text;

		MaxPClock->Font->Color = GetTextColor(Properties->IsValidMaxPClock());

		if (!MaxPClock->Focused() && Common::IntegerToText(Properties->GetMaxPClock(), Text, TEXTSIZE))
			MaxPClock->Text = Text;

		IncludeRangeLimits->Checked = Properties->GetIncludeRangeLimits();
	}

	if (Value != FormOKButton)
		FormOKButton->Enabled = Properties->IsValid();

	Refreshing = false;
	return true;
}
//---------------------------------------------------------------------------
bool TPropertiesForm::ScaleControls()
{
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

	ProductIDGroupBox->Width = FormButtonsWidth;
	ProductIDGroupBox->Height = SerialID->Top + SerialID->Height + PaddingBottom;
	ProductIDGroupBox->Left = Scale;
	ProductIDGroupBox->Top = GroupBoxTop;

	Name->AutoSize = false;
	Name->Width = FormButtonsWidth - PaddingWidth * 2;
	Name->Height = TextBoxHeight;
	Name->Left = PaddingWidth;
	Name->Top = PaddingTop;

	IncludeName->Width = CheckBoxWidth + Canvas->TextWidth(IncludeName->Caption);
	IncludeName->Height = CheckBoxHeight;
	IncludeName->Left = Name->Left;
	IncludeName->Top = Name->Top + Name->Height + Scale + CheckBoxTop;

	NameGroupBox->Width = ProductIDGroupBox->Width;
	NameGroupBox->Height = IncludeName->Top + IncludeName->Height + CheckBoxBottom + PaddingBottom;
	NameGroupBox->Left = ProductIDGroupBox->Left;
	NameGroupBox->Top = ProductIDGroupBox->Top + ProductIDGroupBox->Height + GroupBoxBottom + GroupBoxTop;

	SerialNumber->AutoSize = false;
	SerialNumber->Width = FormButtonsWidth - PaddingWidth * 2;
	SerialNumber->Height = TextBoxHeight;
	SerialNumber->Left = PaddingWidth;
	SerialNumber->Top = PaddingTop;

	IncludeSerialNumber->Width = CheckBoxWidth + Canvas->TextWidth(IncludeSerialNumber->Caption);
	IncludeSerialNumber->Height = CheckBoxHeight;
	IncludeSerialNumber->Left = SerialNumber->Left;
	IncludeSerialNumber->Top = SerialNumber->Top + SerialNumber->Height + Scale + CheckBoxTop;

	SerialNumberGroupBox->Width = NameGroupBox->Width;
	SerialNumberGroupBox->Height = IncludeSerialNumber->Top + IncludeSerialNumber->Height + CheckBoxBottom + PaddingBottom;
	SerialNumberGroupBox->Left = NameGroupBox->Left;
	SerialNumberGroupBox->Top = NameGroupBox->Top + NameGroupBox->Height + GroupBoxBottom + GroupBoxTop;

	MinVRate->AutoSize = false;
	MinVRate->Width = MinVRate->MaxLength * NumberWidth + TextBoxPadding;
	MinVRate->Height = TextBoxHeight;

	MaxVRate->AutoSize = false;
	MaxVRate->Width = MaxVRate->MaxLength * NumberWidth + TextBoxPadding;
	MaxVRate->Height = TextBoxHeight;

	MinHRate->AutoSize = false;
	MinHRate->Width = MinHRate->MaxLength * NumberWidth + TextBoxPadding;
	MinHRate->Height = TextBoxHeight;

	MaxHRate->AutoSize = false;
	MaxHRate->Width = MaxHRate->MaxLength * NumberWidth + TextBoxPadding;
	MaxHRate->Height = TextBoxHeight;

	MaxPClock->AutoSize = false;
	MaxPClock->Width = MaxPClock->MaxLength * NumberWidth + TextBoxPadding;
	MaxPClock->Height = TextBoxHeight;

	VRateLabel->Left = PaddingWidth;
	HRateLabel->Left = VRateLabel->Left;
	MaxPClockLabel->Left = HRateLabel->Left;

	MaxVRate->Left = MaxPClockLabel->Left + MaxPClockLabel->Width + LabelSpacing;
	MaxHRate->Left = MaxVRate->Left;
	MaxPClock->Left = MaxHRate->Left;

	HzLabel->Left = MaxVRate->Left + MaxVRate->Width + PostLabelSpacing;
	kHzLabel->Left = MaxHRate->Left + MaxHRate->Width + PostLabelSpacing;
	MHzLabel->Left = MaxPClock->Left + MaxPClock->Width + PostLabelSpacing;

	int Space = MaxHRate->Left - HRateLabel->Left - HRateLabel->Width - LabelSpacing - MinHRate->Width;
	int DashWidth = Space / 3 + Space % 3;
	int DashHeight = Text.tmHeight < 22 ? 1 : (Text.tmHeight + 13) / 16;
	int DashSpacing = (Space - DashWidth) / 2;

	if (DashWidth > NumberWidth)
		DashWidth = NumberWidth;

	if (DashSpacing > DashWidth)
		DashSpacing = DashWidth;

	VRateDash->Width = DashWidth;
	VRateDash->Height = DashHeight;

	HRateDash->Width = DashWidth;
	HRateDash->Height = DashHeight;

	VRateDash->Left = MaxVRate->Left - DashSpacing - VRateDash->Width;
	HRateDash->Left = VRateDash->Left;

	MinVRate->Left = VRateDash->Left - DashSpacing - MinVRate->Width;
	MinHRate->Left = MinVRate->Left;

	MaxVRate->Top = PaddingTop;
	MaxHRate->Top = MaxVRate->Top + MaxVRate->Height + TextBoxSpacing;
	MaxPClock->Top = MaxHRate->Top + MaxHRate->Height + TextBoxSpacing;

	VRateLabel->Top = MaxVRate->Top + 3;
	HRateLabel->Top = MaxHRate->Top + 3;
	MaxPClockLabel->Top = MaxPClock->Top + 3;

	MinVRate->Top = MaxVRate->Top;
	MinHRate->Top = MaxHRate->Top;

	VRateDash->Top = MaxVRate->Top + MaxVRate->Height / 2;
	HRateDash->Top = MaxHRate->Top + MaxHRate->Height / 2;

	HzLabel->Top = VRateLabel->Top;
	kHzLabel->Top = HRateLabel->Top;
	MHzLabel->Top = MaxPClockLabel->Top;

	IncludeRangeLimits->Width = CheckBoxWidth + Canvas->TextWidth(IncludeRangeLimits->Caption);
	IncludeRangeLimits->Height = CheckBoxHeight;
	IncludeRangeLimits->Left = MaxPClockLabel->Left;
	IncludeRangeLimits->Top = MaxPClock->Top + MaxPClock->Height + Scale + CheckBoxTop;

	RangeLimitsGroupBox->Width = SerialNumberGroupBox->Width;
	RangeLimitsGroupBox->Height = IncludeRangeLimits->Top + IncludeRangeLimits->Height + CheckBoxBottom + PaddingBottom;
	RangeLimitsGroupBox->Left = SerialNumberGroupBox->Left;
	RangeLimitsGroupBox->Top = SerialNumberGroupBox->Top + SerialNumberGroupBox->Height + GroupBoxBottom + GroupBoxTop;

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
void __fastcall TPropertiesForm::FormCreate(TObject *Sender)
{
	ScaleControls();
}
//---------------------------------------------------------------------------
void __fastcall TPropertiesForm::FormShow(TObject *Sender)
{
	Refresh(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TPropertiesForm::ProductIDChange(TObject *Sender)
{
	if (Refreshing)
		return;

	Properties->SetProductID(ProductID->Text.c_str());
	Refresh(ProductIDGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TPropertiesForm::ProductIDExit(TObject *Sender)
{
	Refresh(ProductIDGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TPropertiesForm::ProductIDResetButtonClick(TObject *Sender)
{
	Properties->ResetProductID();
	Refresh(ProductIDGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TPropertiesForm::SerialIDChange(TObject *Sender)
{
	if (Refreshing)
		return;

	Properties->SetSerialID(Common::TextToDecimal(SerialID->Text.c_str(), 0));
	Refresh(ProductIDGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TPropertiesForm::SerialIDExit(TObject *Sender)
{
	Refresh(ProductIDGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TPropertiesForm::NameChange(TObject *Sender)
{
	if (Refreshing)
		return;

	Properties->SetName(Name->Text.c_str());
	Refresh(NameGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TPropertiesForm::NameExit(TObject *Sender)
{
	Refresh(NameGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TPropertiesForm::IncludeNameClick(TObject *Sender)
{
	if (Refreshing)
		return;

	Properties->SetIncludeName(IncludeName->Checked);
	Refresh(NameGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TPropertiesForm::SerialNumberChange(TObject *Sender)
{
	if (Refreshing)
		return;

	Properties->SetSerialNumber(SerialNumber->Text.c_str());
	Refresh(SerialNumberGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TPropertiesForm::SerialNumberExit(TObject *Sender)
{
	Refresh(SerialNumberGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TPropertiesForm::IncludeSerialNumberClick(TObject *Sender)
{
	if (Refreshing)
		return;

	Properties->SetIncludeSerialNumber(IncludeSerialNumber->Checked);
	Refresh(SerialNumberGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TPropertiesForm::MinVRateChange(TObject *Sender)
{
	if (Refreshing)
		return;

	Properties->SetMinVRate(Common::TextToInteger(MinVRate->Text.c_str()));
	Refresh(RangeLimitsGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TPropertiesForm::MinVRateExit(TObject *Sender)
{
	Refresh(RangeLimitsGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TPropertiesForm::MaxVRateChange(TObject *Sender)
{
	if (Refreshing)
		return;

	Properties->SetMaxVRate(Common::TextToInteger(MaxVRate->Text.c_str()));
	Refresh(RangeLimitsGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TPropertiesForm::MaxVRateExit(TObject *Sender)
{
	Refresh(RangeLimitsGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TPropertiesForm::MinHRateChange(TObject *Sender)
{
	if (Refreshing)
		return;

	Properties->SetMinHRate(Common::TextToInteger(MinHRate->Text.c_str()));
	Refresh(RangeLimitsGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TPropertiesForm::MinHRateExit(TObject *Sender)
{
	Refresh(RangeLimitsGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TPropertiesForm::MaxHRateChange(TObject *Sender)
{
	if (Refreshing)
		return;

	Properties->SetMaxHRate(Common::TextToInteger(MaxHRate->Text.c_str()));
	Refresh(RangeLimitsGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TPropertiesForm::MaxHRateExit(TObject *Sender)
{
	Refresh(RangeLimitsGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TPropertiesForm::MaxPClockChange(TObject *Sender)
{
	if (Refreshing)
		return;

	Properties->SetMaxPClock(Common::TextToInteger(MaxPClock->Text.c_str()));
	Refresh(RangeLimitsGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TPropertiesForm::MaxPClockExit(TObject *Sender)
{
	Refresh(RangeLimitsGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TPropertiesForm::IncludeRangeLimitsClick(TObject *Sender)
{
	if (Refreshing)
		return;

	Properties->SetIncludeRangeLimits(IncludeRangeLimits->Checked);
	Refresh(RangeLimitsGroupBox);
}
//---------------------------------------------------------------------------
