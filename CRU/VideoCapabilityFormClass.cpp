//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "VideoCapabilityFormClass.h"
#include "Common.h"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TVideoCapabilityForm *VideoCapabilityForm;
//---------------------------------------------------------------------------
__fastcall TVideoCapabilityForm::TVideoCapabilityForm(TComponent *Owner) : TCommonForm(Owner)
{
	Refreshing = false;
}
//---------------------------------------------------------------------------
bool TVideoCapabilityForm::Connect(VideoCapabilityClass &NewVideoCapability)
{
	VideoCapability = &NewVideoCapability;
	return true;
}
//---------------------------------------------------------------------------
bool TVideoCapabilityForm::Refresh(void *Value)
{
	Refreshing = true;

	if (Value == NULL || Value == TVGroupBox)
		RefreshTVRadioButtons();

	if (Value == NULL || Value == PCGroupBox)
		RefreshPCRadioButtons();

	if (Value == NULL || Value == NativeGroupBox)
		RefreshNativeRadioButtons();

	if (Value == NULL || Value == QuantizationGroupBox)
		RefreshQuantizationCheckBoxes();

	Refreshing = false;
	return true;
}
//---------------------------------------------------------------------------
bool TVideoCapabilityForm::RefreshTVRadioButtons()
{
	if (!VideoCapability->GetVideoCapability(S_CE1))
	{
		if (!VideoCapability->GetVideoCapability(S_CE0))
		{
			TVRadioButton0->Checked = true;
			TVRadioButton1->Checked = false;
		}
		else
		{
			TVRadioButton0->Checked = false;
			TVRadioButton1->Checked = true;
		}

		TVRadioButton2->Checked = false;
		TVRadioButton3->Checked = false;
	}
	else
	{
		TVRadioButton0->Checked = false;
		TVRadioButton1->Checked = false;

		if (!VideoCapability->GetVideoCapability(S_CE0))
		{
			TVRadioButton2->Checked = true;
			TVRadioButton3->Checked = false;
		}
		else
		{
			TVRadioButton2->Checked = false;
			TVRadioButton3->Checked = true;
		}
	}

	return true;
}
//---------------------------------------------------------------------------
bool TVideoCapabilityForm::RefreshPCRadioButtons()
{
	if (!VideoCapability->GetVideoCapability(S_IT1))
	{
		if (!VideoCapability->GetVideoCapability(S_IT0))
		{
			PCRadioButton0->Checked = true;
			PCRadioButton1->Checked = false;
		}
		else
		{
			PCRadioButton0->Checked = false;
			PCRadioButton1->Checked = true;
		}

		PCRadioButton2->Checked = false;
		PCRadioButton3->Checked = false;
	}
	else
	{
		PCRadioButton0->Checked = false;
		PCRadioButton1->Checked = false;

		if (!VideoCapability->GetVideoCapability(S_IT0))
		{
			PCRadioButton2->Checked = true;
			PCRadioButton3->Checked = false;
		}
		else
		{
			PCRadioButton2->Checked = false;
			PCRadioButton3->Checked = true;
		}
	}

	return true;
}
//---------------------------------------------------------------------------
bool TVideoCapabilityForm::RefreshNativeRadioButtons()
{
	if (!VideoCapability->GetVideoCapability(S_PT1))
	{
		if (!VideoCapability->GetVideoCapability(S_PT0))
		{
			NativeRadioButton0->Checked = true;
			NativeRadioButton1->Checked = false;
		}
		else
		{
			NativeRadioButton0->Checked = false;
			NativeRadioButton1->Checked = true;
		}

		NativeRadioButton2->Checked = false;
		NativeRadioButton3->Checked = false;
	}
	else
	{
		NativeRadioButton0->Checked = false;
		NativeRadioButton1->Checked = false;

		if (!VideoCapability->GetVideoCapability(S_PT0))
		{
			NativeRadioButton2->Checked = true;
			NativeRadioButton3->Checked = false;
		}
		else
		{
			NativeRadioButton2->Checked = false;
			NativeRadioButton3->Checked = true;
		}
	}

	return true;
}
//---------------------------------------------------------------------------
bool TVideoCapabilityForm::RefreshQuantizationCheckBoxes()
{
	RGBCheckBox->Checked = VideoCapability->GetVideoCapability(QS);
	YCCCheckBox->Checked = VideoCapability->GetVideoCapability(QY);
	return true;
}
//---------------------------------------------------------------------------
bool TVideoCapabilityForm::ScaleControls()
{
	TVRadioButton0->Width = RadioButtonWidth + Canvas->TextWidth(TVRadioButton0->Caption);
	TVRadioButton0->Height = RadioButtonHeight;
	TVRadioButton0->Left = PaddingWidth;
	TVRadioButton0->Top = PaddingTop + RadioButtonTop;

	TVRadioButton1->Width = RadioButtonWidth + Canvas->TextWidth(TVRadioButton1->Caption);
	TVRadioButton1->Height = RadioButtonHeight;
	TVRadioButton1->Left = TVRadioButton0->Left;
	TVRadioButton1->Top = TVRadioButton0->Top + TVRadioButton0->Height + RadioButtonSpacing;

	TVRadioButton2->Width = RadioButtonWidth + Canvas->TextWidth(TVRadioButton2->Caption);
	TVRadioButton2->Height = RadioButtonHeight;
	TVRadioButton2->Left = TVRadioButton1->Left;
	TVRadioButton2->Top = TVRadioButton1->Top + TVRadioButton1->Height + RadioButtonSpacing;

	TVRadioButton3->Width = RadioButtonWidth + Canvas->TextWidth(TVRadioButton3->Caption);
	TVRadioButton3->Height = RadioButtonHeight;
	TVRadioButton3->Left = TVRadioButton2->Left;
	TVRadioButton3->Top = TVRadioButton2->Top + TVRadioButton2->Height + RadioButtonSpacing;

	TVGroupBox->Width = FormButtonsWidth;
	TVGroupBox->Height = TVRadioButton3->Top + TVRadioButton3->Height + RadioButtonBottom + PaddingBottom;
	TVGroupBox->Left = Scale;
	TVGroupBox->Top = GroupBoxTop;

	PCRadioButton0->Width = RadioButtonWidth + Canvas->TextWidth(PCRadioButton0->Caption);
	PCRadioButton0->Height = RadioButtonHeight;
	PCRadioButton0->Left = PaddingWidth;
	PCRadioButton0->Top = PaddingTop + RadioButtonTop;

	PCRadioButton1->Width = RadioButtonWidth + Canvas->TextWidth(PCRadioButton1->Caption);
	PCRadioButton1->Height = RadioButtonHeight;
	PCRadioButton1->Left = PCRadioButton0->Left;
	PCRadioButton1->Top = PCRadioButton0->Top + PCRadioButton0->Height + RadioButtonSpacing;

	PCRadioButton2->Width = RadioButtonWidth + Canvas->TextWidth(PCRadioButton2->Caption);
	PCRadioButton2->Height = RadioButtonHeight;
	PCRadioButton2->Left = PCRadioButton1->Left;
	PCRadioButton2->Top = PCRadioButton1->Top + PCRadioButton1->Height + RadioButtonSpacing;

	PCRadioButton3->Width = RadioButtonWidth + Canvas->TextWidth(PCRadioButton3->Caption);
	PCRadioButton3->Height = RadioButtonHeight;
	PCRadioButton3->Left = PCRadioButton2->Left;
	PCRadioButton3->Top = PCRadioButton2->Top + PCRadioButton2->Height + RadioButtonSpacing;

	PCGroupBox->Width = TVGroupBox->Width;
	PCGroupBox->Height = PCRadioButton3->Top + PCRadioButton3->Height + RadioButtonBottom + PaddingBottom;
	PCGroupBox->Left = TVGroupBox->Left;
	PCGroupBox->Top = TVGroupBox->Top + TVGroupBox->Height + GroupBoxBottom + GroupBoxTop;

	NativeRadioButton0->Width = RadioButtonWidth + Canvas->TextWidth(NativeRadioButton0->Caption);
	NativeRadioButton0->Height = RadioButtonHeight;
	NativeRadioButton0->Left = PaddingWidth;
	NativeRadioButton0->Top = PaddingTop + RadioButtonTop;

	NativeRadioButton1->Width = RadioButtonWidth + Canvas->TextWidth(NativeRadioButton1->Caption);
	NativeRadioButton1->Height = RadioButtonHeight;
	NativeRadioButton1->Left = NativeRadioButton0->Left;
	NativeRadioButton1->Top = NativeRadioButton0->Top + NativeRadioButton0->Height + RadioButtonSpacing;

	NativeRadioButton2->Width = RadioButtonWidth + Canvas->TextWidth(NativeRadioButton2->Caption);
	NativeRadioButton2->Height = RadioButtonHeight;
	NativeRadioButton2->Left = NativeRadioButton1->Left;
	NativeRadioButton2->Top = NativeRadioButton1->Top + NativeRadioButton1->Height + RadioButtonSpacing;

	NativeRadioButton3->Width = RadioButtonWidth + Canvas->TextWidth(NativeRadioButton3->Caption);
	NativeRadioButton3->Height = RadioButtonHeight;
	NativeRadioButton3->Left = NativeRadioButton2->Left;
	NativeRadioButton3->Top = NativeRadioButton2->Top + NativeRadioButton2->Height + RadioButtonSpacing;

	NativeGroupBox->Width = PCGroupBox->Width;
	NativeGroupBox->Height = NativeRadioButton3->Top + NativeRadioButton3->Height + RadioButtonBottom + PaddingBottom;
	NativeGroupBox->Left = PCGroupBox->Left;
	NativeGroupBox->Top = PCGroupBox->Top + PCGroupBox->Height + GroupBoxBottom + GroupBoxTop;

	RGBCheckBox->Width = CheckBoxWidth + Canvas->TextWidth(RGBCheckBox->Caption);
	RGBCheckBox->Height = CheckBoxHeight;
	RGBCheckBox->Left = PaddingWidth;
	RGBCheckBox->Top = PaddingTop + CheckBoxTop;

	YCCCheckBox->Width = CheckBoxWidth + Canvas->TextWidth(YCCCheckBox->Caption);
	YCCCheckBox->Height = CheckBoxHeight;
	YCCCheckBox->Left = RGBCheckBox->Left;
	YCCCheckBox->Top = RGBCheckBox->Top + RGBCheckBox->Height + CheckBoxSpacing;

	QuantizationGroupBox->Width = NativeGroupBox->Width;
	QuantizationGroupBox->Height = YCCCheckBox->Top + YCCCheckBox->Height + CheckBoxBottom + PaddingBottom;
	QuantizationGroupBox->Left = NativeGroupBox->Left;
	QuantizationGroupBox->Top = NativeGroupBox->Top + NativeGroupBox->Height + GroupBoxBottom + GroupBoxTop;

	FormOKButton->Width = FormButtonWidth;
	FormOKButton->Height = FormButtonHeight;
	FormOKButton->Top = QuantizationGroupBox->Top + QuantizationGroupBox->Height + GroupBoxBottom + Scale + ButtonTop;
	Common::FixButtonCaption(FormOKButton, Canvas->TextWidth(FormOKButton->Caption));

	FormCancelButton->Width = FormButtonWidth;
	FormCancelButton->Height = FormButtonHeight;
	FormCancelButton->Top = FormOKButton->Top;
	Common::FixButtonCaption(FormCancelButton, Canvas->TextWidth(FormCancelButton->Caption));

	FormCancelButton->Left = QuantizationGroupBox->Left + QuantizationGroupBox->Width - ButtonRight - FormCancelButton->Width;
	FormOKButton->Left = FormCancelButton->Left - ButtonLeft - Scale - ButtonRight - FormOKButton->Width;

	ClientWidth = FormCancelButton->Left + FormCancelButton->Width + ButtonRight + Scale;
	ClientHeight = FormCancelButton->Top + FormCancelButton->Height + ButtonBottom + Scale;
	return true;
}
//---------------------------------------------------------------------------
void __fastcall TVideoCapabilityForm::FormCreate(TObject *Sender)
{
	ScaleControls();
}
//---------------------------------------------------------------------------
void __fastcall TVideoCapabilityForm::FormShow(TObject *Sender)
{
	Refresh(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TVideoCapabilityForm::TVRadioButton0Click(TObject *Sender)
{
	if (Refreshing)
		return;

	VideoCapability->SetVideoCapability(S_CE0, false);
	VideoCapability->SetVideoCapability(S_CE1, false);
	Refresh(TVGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TVideoCapabilityForm::TVRadioButton1Click(TObject *Sender)
{
	if (Refreshing)
		return;

	VideoCapability->SetVideoCapability(S_CE0, true);
	VideoCapability->SetVideoCapability(S_CE1, false);
	Refresh(TVGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TVideoCapabilityForm::TVRadioButton2Click(TObject *Sender)
{
	if (Refreshing)
		return;

	VideoCapability->SetVideoCapability(S_CE0, false);
	VideoCapability->SetVideoCapability(S_CE1, true);
	Refresh(TVGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TVideoCapabilityForm::TVRadioButton3Click(TObject *Sender)
{
	if (Refreshing)
		return;

	VideoCapability->SetVideoCapability(S_CE0, true);
	VideoCapability->SetVideoCapability(S_CE1, true);
	Refresh(TVGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TVideoCapabilityForm::PCRadioButton0Click(TObject *Sender)
{
	if (Refreshing)
		return;

	VideoCapability->SetVideoCapability(S_IT0, false);
	VideoCapability->SetVideoCapability(S_IT1, false);
	Refresh(PCGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TVideoCapabilityForm::PCRadioButton1Click(TObject *Sender)
{
	if (Refreshing)
		return;

	VideoCapability->SetVideoCapability(S_IT0, true);
	VideoCapability->SetVideoCapability(S_IT1, false);
	Refresh(PCGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TVideoCapabilityForm::PCRadioButton2Click(TObject *Sender)
{
	if (Refreshing)
		return;

	VideoCapability->SetVideoCapability(S_IT0, false);
	VideoCapability->SetVideoCapability(S_IT1, true);
	Refresh(PCGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TVideoCapabilityForm::PCRadioButton3Click(TObject *Sender)
{
	if (Refreshing)
		return;

	VideoCapability->SetVideoCapability(S_IT0, true);
	VideoCapability->SetVideoCapability(S_IT1, true);
	Refresh(PCGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TVideoCapabilityForm::NativeRadioButton0Click(TObject *Sender)
{
	if (Refreshing)
		return;

	VideoCapability->SetVideoCapability(S_PT0, false);
	VideoCapability->SetVideoCapability(S_PT1, false);
	Refresh(NativeGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TVideoCapabilityForm::NativeRadioButton1Click(TObject *Sender)
{
	if (Refreshing)
		return;

	VideoCapability->SetVideoCapability(S_PT0, true);
	VideoCapability->SetVideoCapability(S_PT1, false);
	Refresh(NativeGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TVideoCapabilityForm::NativeRadioButton2Click(TObject *Sender)
{
	if (Refreshing)
		return;

	VideoCapability->SetVideoCapability(S_PT0, false);
	VideoCapability->SetVideoCapability(S_PT1, true);
	Refresh(NativeGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TVideoCapabilityForm::NativeRadioButton3Click(TObject *Sender)
{
	if (Refreshing)
		return;

	VideoCapability->SetVideoCapability(S_PT0, true);
	VideoCapability->SetVideoCapability(S_PT1, true);
	Refresh(NativeGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TVideoCapabilityForm::RGBCheckBoxClick(TObject *Sender)
{
	if (Refreshing)
		return;

	VideoCapability->SetVideoCapability(QS, RGBCheckBox->Checked);
	Refresh(QuantizationGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TVideoCapabilityForm::YCCCheckBoxClick(TObject *Sender)
{
	if (Refreshing)
		return;

	VideoCapability->SetVideoCapability(QY, YCCCheckBox->Checked);
	Refresh(QuantizationGroupBox);
}
//---------------------------------------------------------------------------
