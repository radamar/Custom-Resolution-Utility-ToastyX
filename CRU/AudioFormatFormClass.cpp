//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "AudioFormatFormClass.h"
#include "Common.h"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TAudioFormatForm *AudioFormatForm;
//---------------------------------------------------------------------------
__fastcall TAudioFormatForm::TAudioFormatForm(TComponent *Owner) : TCommonForm(Owner)
{
	Refreshing = false;
}
//---------------------------------------------------------------------------
bool TAudioFormatForm::Connect(AudioFormatClass &NewAudioFormat)
{
	AudioFormat = &NewAudioFormat;
	return true;
}
//---------------------------------------------------------------------------
TColor TAudioFormatForm::GetTextColor(bool Valid)
{
	if (!Valid)
		return (TColor)RGB(255, 0, 0);

	return clWindowText;
}
//---------------------------------------------------------------------------
bool TAudioFormatForm::Refresh(void *Value)
{
	char Text[TEXTSIZE];

	Refreshing = true;

	if (AudioFormat->GetFormat() == 1)
	{
		BitDepthsGroupBox->Visible = true;
		BitRateGroupBox->Visible = false;
		FlagsGroupBox->Visible = false;
		FormOKButton->Top = BitDepthsGroupBox->Top + BitDepthsGroupBox->Height + GroupBoxBottom + Scale + ButtonTop;
	}
	else if (AudioFormat->GetFormat() >= 2 && AudioFormat->GetFormat() <= 8)
	{
		BitDepthsGroupBox->Visible = false;
		BitRateGroupBox->Visible = true;
		FlagsGroupBox->Visible = false;
		FormOKButton->Top = BitRateGroupBox->Top + BitRateGroupBox->Height + GroupBoxBottom + Scale + ButtonTop;
	}
	else
	{
		BitDepthsGroupBox->Visible = false;
		BitRateGroupBox->Visible = false;
		FlagsGroupBox->Visible = true;
		FormOKButton->Top = FlagsGroupBox->Top + FlagsGroupBox->Height + GroupBoxBottom + Scale + ButtonTop;
	}

	FormCancelButton->Top = FormOKButton->Top;
	ClientHeight = FormCancelButton->Top + FormCancelButton->Height + ButtonBottom + Scale;

	if (Value != FormatComboBox)
		FormatComboBox->ItemIndex = AudioFormat->GetFormat() - 1;

	if (Value != ChannelsComboBox)
		ChannelsComboBox->ItemIndex = AudioFormat->GetChannels() - 1;

	if (Value != SampleRatesGroupBox)
	{
		SampleRateCheckBox0->Checked = AudioFormat->GetSampleRate(0);
		SampleRateCheckBox1->Checked = AudioFormat->GetSampleRate(1);
		SampleRateCheckBox2->Checked = AudioFormat->GetSampleRate(2);
		SampleRateCheckBox3->Checked = AudioFormat->GetSampleRate(3);
		SampleRateCheckBox4->Checked = AudioFormat->GetSampleRate(4);
		SampleRateCheckBox5->Checked = AudioFormat->GetSampleRate(5);
		SampleRateCheckBox6->Checked = AudioFormat->GetSampleRate(6);
	}

	if (Value != BitDepthsGroupBox)
	{
		BitDepthCheckBox0->Checked = AudioFormat->GetBitDepth(0);
		BitDepthCheckBox1->Checked = AudioFormat->GetBitDepth(1);
		BitDepthCheckBox2->Checked = AudioFormat->GetBitDepth(2);
	}

	if (Value != BitRate && Common::IntegerToText(AudioFormat->GetBitRate(), Text, TEXTSIZE))
		BitRate->Text = Text;

	BitRate->Font->Color = GetTextColor(AudioFormat->IsValidBitRate());

	if (Value != Flags && Common::IntegerToText(AudioFormat->GetFlags(), Text, TEXTSIZE))
		Flags->Text = Text;

	Flags->Font->Color = GetTextColor(AudioFormat->IsValidFlags());

	if (Value != FormOKButton)
		FormOKButton->Enabled = AudioFormat->IsValid();

	Refreshing = false;
	return true;
}
//---------------------------------------------------------------------------
bool TAudioFormatForm::InitFormatComboBox()
{
	int ItemIndex;
	int Index;
	char Text[TEXTSIZE];

	ItemIndex = FormatComboBox->ItemIndex;
	FormatComboBox->Clear();
	FormatComboBox->Items->BeginUpdate();

	for (Index = 0; AudioFormat->GetFormatText(Index + 1, Text, TEXTSIZE); Index++)
		FormatComboBox->Items->Add(Text);

	FormatComboBox->ItemIndex = ItemIndex;
	FormatComboBox->Items->EndUpdate();
	return true;
}
//---------------------------------------------------------------------------
bool TAudioFormatForm::InitChannelsComboBox()
{
	int ItemIndex;
	int Index;
	char Text[TEXTSIZE];

	ItemIndex = ChannelsComboBox->ItemIndex;
	ChannelsComboBox->Clear();
	ChannelsComboBox->Items->BeginUpdate();

	for (Index = 0; AudioFormat->GetChannelsText(Index + 1, Text, TEXTSIZE); Index++)
		ChannelsComboBox->Items->Add(Text);

	ChannelsComboBox->ItemIndex = ItemIndex;
	ChannelsComboBox->Items->EndUpdate();
	return true;
}
//---------------------------------------------------------------------------
bool TAudioFormatForm::ScaleControls()
{
	FormatComboBox->Width = FormButtonsWidth - PaddingWidth * 2;
	FormatComboBox->Height = ComboBoxHeight;
	FormatComboBox->Left = PaddingWidth;
	FormatComboBox->Top = PaddingTop;

	ChannelsComboBox->Width = FormatComboBox->Width - ChannelsLabel->Width - LabelSpacing;
	ChannelsComboBox->Height = ComboBoxHeight;

	ChannelsLabel->Left = FormatComboBox->Left;
	ChannelsComboBox->Left = ChannelsLabel->Left + ChannelsLabel->Width + LabelSpacing;

	ChannelsLabel->Top = FormatComboBox->Top + FormatComboBox->Height + Scale + 4;
	ChannelsComboBox->Top = ChannelsLabel->Top - 4;

	FormatGroupBox->Width = FormatComboBox->Left + FormatComboBox->Width + PaddingWidth;
	FormatGroupBox->Height = ChannelsComboBox->Top + ChannelsComboBox->Height + PaddingBottom;
	FormatGroupBox->Left = Scale;
	FormatGroupBox->Top = GroupBoxTop;

	SampleRateCheckBox0->Width = CheckBoxWidth + Canvas->TextWidth(SampleRateCheckBox0->Caption);
	SampleRateCheckBox0->Height = CheckBoxHeight;
	SampleRateCheckBox0->Left = PaddingWidth;
	SampleRateCheckBox0->Top = PaddingTop + CheckBoxTop;

	SampleRateCheckBox1->Width = CheckBoxWidth + Canvas->TextWidth(SampleRateCheckBox1->Caption);
	SampleRateCheckBox1->Height = CheckBoxHeight;
	SampleRateCheckBox1->Left = SampleRateCheckBox0->Left;
	SampleRateCheckBox1->Top = SampleRateCheckBox0->Top + SampleRateCheckBox0->Height + CheckBoxSpacing;

	SampleRateCheckBox2->Width = CheckBoxWidth + Canvas->TextWidth(SampleRateCheckBox2->Caption);
	SampleRateCheckBox2->Height = CheckBoxHeight;
	SampleRateCheckBox2->Left = SampleRateCheckBox1->Left;
	SampleRateCheckBox2->Top = SampleRateCheckBox1->Top + SampleRateCheckBox1->Height + CheckBoxSpacing;

	SampleRateCheckBox3->Width = CheckBoxWidth + Canvas->TextWidth(SampleRateCheckBox3->Caption);
	SampleRateCheckBox3->Height = CheckBoxHeight;
	SampleRateCheckBox3->Left = SampleRateCheckBox2->Left;
	SampleRateCheckBox3->Top = SampleRateCheckBox2->Top + SampleRateCheckBox2->Height + CheckBoxSpacing;

	SampleRateCheckBox4->Width = CheckBoxWidth + Canvas->TextWidth(SampleRateCheckBox4->Caption);
	SampleRateCheckBox4->Height = CheckBoxHeight;
	SampleRateCheckBox4->Left = SampleRateCheckBox3->Left;
	SampleRateCheckBox4->Top = SampleRateCheckBox3->Top + SampleRateCheckBox3->Height + CheckBoxSpacing;

	SampleRateCheckBox5->Width = CheckBoxWidth + Canvas->TextWidth(SampleRateCheckBox5->Caption);
	SampleRateCheckBox5->Height = CheckBoxHeight;
	SampleRateCheckBox5->Left = SampleRateCheckBox4->Left;
	SampleRateCheckBox5->Top = SampleRateCheckBox4->Top + SampleRateCheckBox4->Height + CheckBoxSpacing;

	SampleRateCheckBox6->Width = CheckBoxWidth + Canvas->TextWidth(SampleRateCheckBox6->Caption);
	SampleRateCheckBox6->Height = CheckBoxHeight;
	SampleRateCheckBox6->Left = SampleRateCheckBox5->Left;
	SampleRateCheckBox6->Top = SampleRateCheckBox5->Top + SampleRateCheckBox5->Height + CheckBoxSpacing;

	SampleRatesGroupBox->Width = FormatGroupBox->Width;
	SampleRatesGroupBox->Height = SampleRateCheckBox6->Top + SampleRateCheckBox6->Height + CheckBoxBottom + PaddingBottom;
	SampleRatesGroupBox->Left = FormatGroupBox->Left;
	SampleRatesGroupBox->Top = FormatGroupBox->Top + FormatGroupBox->Height + GroupBoxBottom + GroupBoxTop;

	BitDepthCheckBox0->Width = CheckBoxWidth + Canvas->TextWidth(BitDepthCheckBox0->Caption);
	BitDepthCheckBox0->Height = CheckBoxHeight;
	BitDepthCheckBox0->Left = PaddingWidth;
	BitDepthCheckBox0->Top = PaddingTop + CheckBoxTop;

	BitDepthCheckBox1->Width = CheckBoxWidth + Canvas->TextWidth(BitDepthCheckBox1->Caption);
	BitDepthCheckBox1->Height = CheckBoxHeight;
	BitDepthCheckBox1->Left = BitDepthCheckBox0->Left;
	BitDepthCheckBox1->Top = BitDepthCheckBox0->Top + BitDepthCheckBox0->Height + CheckBoxSpacing;

	BitDepthCheckBox2->Width = CheckBoxWidth + Canvas->TextWidth(BitDepthCheckBox2->Caption);
	BitDepthCheckBox2->Height = CheckBoxHeight;
	BitDepthCheckBox2->Left = BitDepthCheckBox1->Left;
	BitDepthCheckBox2->Top = BitDepthCheckBox1->Top + BitDepthCheckBox1->Height + CheckBoxSpacing;

	BitDepthsGroupBox->Width = SampleRatesGroupBox->Width;
	BitDepthsGroupBox->Height = BitDepthCheckBox2->Top + BitDepthCheckBox2->Height + CheckBoxBottom + PaddingBottom;
	BitDepthsGroupBox->Left = SampleRatesGroupBox->Left;
	BitDepthsGroupBox->Top = SampleRatesGroupBox->Top + SampleRatesGroupBox->Height + GroupBoxBottom + GroupBoxTop;

	BitRate->AutoSize = false;
	BitRate->Width = BitRate->MaxLength * NumberWidth + TextBoxPadding;
	BitRate->Height = TextBoxHeight;
	BitRate->Left = PaddingWidth;
	BitRate->Top = PaddingTop;

	BitRateLabel->Left = BitRate->Left + BitRate->Width + PostLabelSpacing;
	BitRateLabel->Top = BitRate->Top + 3;

	BitRateGroupBox->Width = SampleRatesGroupBox->Width;
	BitRateGroupBox->Height = BitRate->Top + BitRate->Height + PaddingBottom;
	BitRateGroupBox->Left = SampleRatesGroupBox->Left;
	BitRateGroupBox->Top = SampleRatesGroupBox->Top + SampleRatesGroupBox->Height + GroupBoxBottom + GroupBoxTop;

	Flags->AutoSize = false;
	Flags->Width = Flags->MaxLength * NumberWidth + TextBoxPadding;
	Flags->Height = TextBoxHeight;
	Flags->Left = PaddingWidth;
	Flags->Top = PaddingTop;

	FlagsRangeLabel->Left = Flags->Left + Flags->Width + PostLabelSpacing;
	FlagsRangeLabel->Top = Flags->Top + 3;

	FlagsGroupBox->Width = SampleRatesGroupBox->Width;
	FlagsGroupBox->Height = Flags->Top + Flags->Height + PaddingBottom;
	FlagsGroupBox->Left = SampleRatesGroupBox->Left;
	FlagsGroupBox->Top = SampleRatesGroupBox->Top + SampleRatesGroupBox->Height + GroupBoxBottom + GroupBoxTop;

	FormOKButton->Width = FormButtonWidth;
	FormOKButton->Height = FormButtonHeight;
	FormOKButton->Top = BitDepthsGroupBox->Top + BitDepthsGroupBox->Height + GroupBoxBottom + Scale + ButtonTop;
	Common::FixButtonCaption(FormOKButton, Canvas->TextWidth(FormOKButton->Caption));

	FormCancelButton->Width = FormButtonWidth;
	FormCancelButton->Height = FormButtonHeight;
	FormCancelButton->Top = FormOKButton->Top;
	Common::FixButtonCaption(FormCancelButton, Canvas->TextWidth(FormCancelButton->Caption));

	FormCancelButton->Left = BitDepthsGroupBox->Left + BitDepthsGroupBox->Width - ButtonRight - FormCancelButton->Width;
	FormOKButton->Left = FormCancelButton->Left - ButtonLeft - Scale - ButtonRight - FormOKButton->Width;

	ClientWidth = FormCancelButton->Left + FormCancelButton->Width + ButtonRight + Scale;
	ClientHeight = FormCancelButton->Top + FormCancelButton->Height + ButtonBottom + Scale;
	return true;
}
//---------------------------------------------------------------------------
void __fastcall TAudioFormatForm::FormCreate(TObject *Sender)
{
	ScaleControls();
}
//---------------------------------------------------------------------------
void __fastcall TAudioFormatForm::FormShow(TObject *Sender)
{
	InitFormatComboBox();
	InitChannelsComboBox();
	Refresh(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TAudioFormatForm::FormatComboBoxChange(TObject *Sender)
{
	if (Refreshing)
		return;

	AudioFormat->SetFormat(FormatComboBox->ItemIndex + 1);
	Refresh(FormatComboBox);
}
//---------------------------------------------------------------------------
void __fastcall TAudioFormatForm::ChannelsComboBoxChange(TObject *Sender)
{
	if (Refreshing)
		return;

	AudioFormat->SetChannels(ChannelsComboBox->ItemIndex + 1);
	Refresh(ChannelsComboBox);
}
//---------------------------------------------------------------------------
void __fastcall TAudioFormatForm::SampleRateCheckBoxClick(TObject *Sender)
{
	if (Refreshing)
		return;

	TCheckBox *CheckBox = (TCheckBox *)Sender;
	AudioFormat->SetSampleRate(CheckBox->Tag, CheckBox->Checked);
	Refresh(SampleRatesGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TAudioFormatForm::BitDepthCheckBoxClick(TObject *Sender)
{
	if (Refreshing)
		return;

	TCheckBox *CheckBox = (TCheckBox *)Sender;
	AudioFormat->SetBitDepth(CheckBox->Tag, CheckBox->Checked);
	Refresh(BitDepthsGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TAudioFormatForm::BitRateChange(TObject *Sender)
{
	if (Refreshing)
		return;

	AudioFormat->SetBitRate(Common::TextToInteger(BitRate->Text.c_str()));
	Refresh(BitRate);
}
//---------------------------------------------------------------------------
void __fastcall TAudioFormatForm::BitRateExit(TObject *Sender)
{
	Refresh(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TAudioFormatForm::FlagsChange(TObject *Sender)
{
	if (Refreshing)
		return;

	AudioFormat->SetFlags(Common::TextToInteger(Flags->Text.c_str()));
	Refresh(Flags);
}
//---------------------------------------------------------------------------
void __fastcall TAudioFormatForm::FlagsExit(TObject *Sender)
{
	Refresh(NULL);
}
//---------------------------------------------------------------------------
