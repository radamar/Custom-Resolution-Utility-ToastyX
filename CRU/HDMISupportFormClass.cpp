//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "HDMISupportFormClass.h"
#include "HDMIResolutionFormClass.h"
#include "Common.h"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
THDMISupportForm *HDMISupportForm;
//---------------------------------------------------------------------------
__fastcall THDMISupportForm::THDMISupportForm(TComponent *Owner) : TCommonForm(Owner)
{
	Refreshing = false;
	HDMIResolutionsLastItemIndex = -1;
	HDMIResolutionsLastClickedItemIndex = -1;
}
//---------------------------------------------------------------------------
bool THDMISupportForm::Connect(HDMISupportClass &NewHDMISupport, ColorFormatListClass &NewColorFormatList)
{
	HDMISupport = &NewHDMISupport;
	ColorFormatList = &NewColorFormatList;
	return true;
}
//---------------------------------------------------------------------------
TColor THDMISupportForm::GetTextColor(bool Valid)
{
	if (!Valid)
		return (TColor)RGB(255, 0, 0);

	return clWindowText;
}
//---------------------------------------------------------------------------
TColor THDMISupportForm::GetColor(bool Set)
{
	if (!Set)
		return clBtnFace;

	return clWindow;
}
//---------------------------------------------------------------------------
bool THDMISupportForm::Refresh(void *Value, int ItemIndex)
{
	Refreshing = true;

	if (Value == NULL || Value == PhysicalAddressGroupBox)
		RefreshPhysicalAddressTextBox();

	if (Value == NULL || Value == ColorFormatsGroupBox)
	{
		RefreshColorFormatsCaption();
		RefreshColorFormatsCheckBoxes();
	}

	if (Value == NULL || Value == FeaturesGroupBox)
	{
		RefreshFeaturesCaption();
		RefreshFeaturesCheckBoxes();
	}

	if (Value == NULL || Value == TMDSClockGroupBox)
	{
		RefreshTMDSClockCaption();
		RefreshTMDSClockCheckBox();
		RefreshTMDSClockTextBox();
	}

	if (Value == NULL || Value == ContentTypesGroupBox)
	{
		RefreshContentTypesCaption();
		RefreshContentTypesCheckBoxes();
	}

	if (Value == NULL || Value == LatencyGroupBox || Value == HDMIResolutionsGroupBox)
	{
		RefreshLatencyCaption();
		RefreshLatencyCheckBoxes();
		RefreshLatencyTextBoxes();
		RefreshHDMIResolutionsCaption();
		RefreshHDMIResolutionsListBox(ItemIndex);
		RefreshHDMIResolutionsButtons();
	}

	if (Value != FormOKButton)
		FormOKButton->Enabled = HDMISupport->IsValid();

	Refreshing = false;
	return true;
}
//---------------------------------------------------------------------------
bool THDMISupportForm::RefreshPhysicalAddressTextBox()
{
	char Text[TEXTSIZE];

	PhysicalAddress->Font->Color = GetTextColor(HDMISupport->IsValidPhysicalAddress());

	if (!PhysicalAddress->Focused() && HDMISupport->GetPhysicalAddressText(Text, TEXTSIZE))
		PhysicalAddress->Text = Text;

	return true;
}
//---------------------------------------------------------------------------
bool THDMISupportForm::RefreshColorFormatsCaption()
{
	if (HDMISupport->ExtensionPossible())
		ColorFormatsGroupBox->Caption = " Color formats ";
	else
		ColorFormatsGroupBox->Caption = " Color formats (no space left for deep color) ";

	return true;
}
//---------------------------------------------------------------------------
bool THDMISupportForm::RefreshColorFormatsCheckBoxes()
{
	if (HDMISupport->ExtensionPossible())
	{
		DeepColorYCbCr444->Enabled = true;
		DeepColor30bit->Enabled = true;
		DeepColor36bit->Enabled = true;
		DeepColor48bit->Enabled = true;
	}
	else
	{
		DeepColorYCbCr444->Enabled = false;
		DeepColor30bit->Enabled = false;
		DeepColor36bit->Enabled = false;
		DeepColor48bit->Enabled = false;
	}

	YCbCr422->Checked = ColorFormatList->GetYCbCr422();
	YCbCr444->Checked = ColorFormatList->GetYCbCr444();
	DeepColorYCbCr444->Checked = HDMISupport->GetDeepColorYCbCr444();
	DeepColor30bit->Checked = HDMISupport->GetDeepColor30bit();
	DeepColor36bit->Checked = HDMISupport->GetDeepColor36bit();
	DeepColor48bit->Checked = HDMISupport->GetDeepColor48bit();
	return true;
}
//---------------------------------------------------------------------------
bool THDMISupportForm::RefreshFeaturesCaption()
{
	if (HDMISupport->ExtensionPossible())
		FeaturesGroupBox->Caption = " Supported features ";
	else
		FeaturesGroupBox->Caption = " Supported features (no space left) ";

	return true;
}
//---------------------------------------------------------------------------
bool THDMISupportForm::RefreshFeaturesCheckBoxes()
{
	if (HDMISupport->ExtensionPossible())
	{
		SupportsAI->Enabled = true;
		DualLinkDVI->Enabled = true;
	}
	else
	{
		SupportsAI->Enabled = false;
		DualLinkDVI->Enabled = false;
	}

	SupportsAI->Checked = HDMISupport->GetSupportsAI();
	DualLinkDVI->Checked = HDMISupport->GetDualLinkDVI();
	return true;
}
//---------------------------------------------------------------------------
bool THDMISupportForm::RefreshTMDSClockCaption()
{
	if (HDMISupport->TMDSClockPossible())
		TMDSClockGroupBox->Caption = " Maximum TMDS clock ";
	else
		TMDSClockGroupBox->Caption = " Maximum TMDS clock (no space left) ";

	return true;
}
//---------------------------------------------------------------------------
bool THDMISupportForm::RefreshTMDSClockCheckBox()
{
	if (HDMISupport->TMDSClockPossible())
		OverrideTMDSClock->Enabled = true;
	else
		OverrideTMDSClock->Enabled = false;

	OverrideTMDSClock->Checked = HDMISupport->GetOverrideTMDSClock();
	return true;
}
//---------------------------------------------------------------------------
bool THDMISupportForm::RefreshTMDSClockTextBox()
{
	char Text[TEXTSIZE];

	if (HDMISupport->TMDSClockPossible() && HDMISupport->GetOverrideTMDSClock())
	{
		TMDSClock->Enabled = true;
		TMDSClock->Color = clWindow;
		TMDSClock->Font->Color = GetTextColor(HDMISupport->IsValidTMDSClock());
		TMDSClockLabel->Font->Color = clWindowText;
	}
	else
	{
		TMDSClock->Enabled = false;
		TMDSClock->Color = clBtnFace;
		TMDSClock->Font->Color = clGrayText;
		TMDSClockLabel->Font->Color = clGrayText;
	}

	if (!TMDSClock->Focused() && Common::IntegerToText(HDMISupport->GetTMDSClock(), Text, TEXTSIZE))
		TMDSClock->Text = Text;

	return true;
}
//---------------------------------------------------------------------------
bool THDMISupportForm::RefreshContentTypesCaption()
{
	if (HDMISupport->ContentTypesPossible())
		ContentTypesGroupBox->Caption = " Supported content types ";
	else
		ContentTypesGroupBox->Caption = " Supported content types (no space left) ";

	return true;
}
//---------------------------------------------------------------------------
bool THDMISupportForm::RefreshContentTypesCheckBoxes()
{
	if (HDMISupport->ContentTypesPossible())
	{
		ContentType0->Enabled = true;
		ContentType1->Enabled = true;
		ContentType2->Enabled = true;
		ContentType3->Enabled = true;
	}
	else
	{
		ContentType0->Enabled = false;
		ContentType1->Enabled = false;
		ContentType2->Enabled = false;
		ContentType3->Enabled = false;
	}

	ContentType0->Checked = HDMISupport->GetContentType(0);
	ContentType1->Checked = HDMISupport->GetContentType(1);
	ContentType2->Checked = HDMISupport->GetContentType(2);
	ContentType3->Checked = HDMISupport->GetContentType(3);
	return true;
}
//---------------------------------------------------------------------------
bool THDMISupportForm::RefreshLatencyCaption()
{
	if (HDMISupport->IncludeLatencyPossible() && HDMISupport->IncludeInterlacedLatencyPossible())
		LatencyGroupBox->Caption = " Latency information ";
	else if (HDMISupport->IncludeLatencyPossible())
		LatencyGroupBox->Caption = " Latency information (no space left for interlaced data) ";
	else
		LatencyGroupBox->Caption = " Latency information (no space left) ";

	return true;
}
//---------------------------------------------------------------------------
bool THDMISupportForm::RefreshLatencyCheckBoxes()
{
	if (HDMISupport->IncludeLatencyPossible())
		IncludeLatency->Enabled = true;
	else
		IncludeLatency->Enabled = false;

	IncludeLatency->Checked = HDMISupport->GetIncludeLatency();

	if (HDMISupport->IncludeLatencyPossible() && HDMISupport->GetIncludeLatency())
	{
		VideoSupported->Enabled = true;
		AudioSupported->Enabled = true;
	}
	else
	{
		VideoSupported->Enabled = false;
		AudioSupported->Enabled = false;
	}

	VideoSupported->Checked = HDMISupport->GetVideoSupported();
	AudioSupported->Checked = HDMISupport->GetAudioSupported();

	if (HDMISupport->IncludeLatencyPossible() && HDMISupport->GetIncludeLatency() && HDMISupport->IncludeInterlacedLatencyPossible())
		IncludeInterlacedLatency->Enabled = true;
	else
		IncludeInterlacedLatency->Enabled = false;

	IncludeInterlacedLatency->Checked = HDMISupport->GetIncludeInterlacedLatency();

	if (HDMISupport->IncludeLatencyPossible() && HDMISupport->GetIncludeLatency() && HDMISupport->IncludeInterlacedLatencyPossible() && HDMISupport->GetIncludeInterlacedLatency())
	{
		InterlacedVideoSupported->Enabled = true;
		InterlacedAudioSupported->Enabled = true;
	}
	else
	{
		InterlacedVideoSupported->Enabled = false;
		InterlacedAudioSupported->Enabled = false;
	}

	InterlacedVideoSupported->Checked = HDMISupport->GetInterlacedVideoSupported();
	InterlacedAudioSupported->Checked = HDMISupport->GetInterlacedAudioSupported();
	return true;
}
//---------------------------------------------------------------------------
bool THDMISupportForm::RefreshLatencyTextBoxes()
{
	char Text[TEXTSIZE];

	if (HDMISupport->IncludeLatencyPossible() && HDMISupport->GetIncludeLatency() && HDMISupport->GetVideoSupported())
	{
		VideoLatency->Enabled = true;
		VideoLatency->Color = clWindow;
		VideoLatency->Font->Color = GetTextColor(HDMISupport->IsValidVideoLatency());
		VideoLatencyLabel->Font->Color = clWindowText;
	}
	else
	{
		VideoLatency->Enabled = false;
		VideoLatency->Color = clBtnFace;
		VideoLatency->Font->Color = clGrayText;
		VideoLatencyLabel->Font->Color = clGrayText;
	}

	if (!VideoLatency->Focused() && Common::IntegerToText(HDMISupport->GetVideoLatency(), Text, TEXTSIZE))
		VideoLatency->Text = Text;

	if (HDMISupport->IncludeLatencyPossible() && HDMISupport->GetIncludeLatency() && HDMISupport->GetAudioSupported())
	{
		AudioLatency->Enabled = true;
		AudioLatency->Color = clWindow;
		AudioLatency->Font->Color = GetTextColor(HDMISupport->IsValidAudioLatency());
		AudioLatencyLabel->Font->Color = clWindowText;
	}
	else
	{
		AudioLatency->Enabled = false;
		AudioLatency->Color = clBtnFace;
		AudioLatency->Font->Color = clGrayText;
		AudioLatencyLabel->Font->Color = clGrayText;
	}

	if (!AudioLatency->Focused() && Common::IntegerToText(HDMISupport->GetAudioLatency(), Text, TEXTSIZE))
		AudioLatency->Text = Text;

	if (HDMISupport->IncludeLatencyPossible() && HDMISupport->GetIncludeLatency() && HDMISupport->IncludeInterlacedLatencyPossible() && HDMISupport->GetIncludeInterlacedLatency() && HDMISupport->GetInterlacedVideoSupported())
	{
		InterlacedVideoLatency->Enabled = true;
		InterlacedVideoLatency->Color = clWindow;
		InterlacedVideoLatency->Font->Color = GetTextColor(HDMISupport->IsValidInterlacedVideoLatency());
		InterlacedVideoLatencyLabel->Font->Color = clWindowText;
	}
	else
	{
		InterlacedVideoLatency->Enabled = false;
		InterlacedVideoLatency->Color = clBtnFace;
		InterlacedVideoLatency->Font->Color = clGrayText;
		InterlacedVideoLatencyLabel->Font->Color = clGrayText;
	}

	if (!InterlacedVideoLatency->Focused() && Common::IntegerToText(HDMISupport->GetInterlacedVideoLatency(), Text, TEXTSIZE))
		InterlacedVideoLatency->Text = Text;

	if (HDMISupport->IncludeLatencyPossible() && HDMISupport->GetIncludeLatency() && HDMISupport->IncludeInterlacedLatencyPossible() && HDMISupport->GetIncludeInterlacedLatency() && HDMISupport->GetInterlacedAudioSupported())
	{
		InterlacedAudioLatency->Enabled = true;
		InterlacedAudioLatency->Color = clWindow;
		InterlacedAudioLatency->Font->Color = GetTextColor(HDMISupport->IsValidInterlacedAudioLatency());
		InterlacedAudioLatencyLabel->Font->Color = clWindowText;
	}
	else
	{
		InterlacedAudioLatency->Enabled = false;
		InterlacedAudioLatency->Color = clBtnFace;
		InterlacedAudioLatency->Font->Color = clGrayText;
		InterlacedAudioLatencyLabel->Font->Color = clGrayText;
	}

	if (!InterlacedAudioLatency->Focused() && Common::IntegerToText(HDMISupport->GetInterlacedAudioLatency(), Text, TEXTSIZE))
		InterlacedAudioLatency->Text = Text;

	return true;
}
//---------------------------------------------------------------------------
bool THDMISupportForm::RefreshHDMIResolutionsCaption()
{
	const char *Caption = " HDMI resolutions ";
	char Text[TEXTSIZE];

	HDMISupport->Resolutions()->GetSlotsLeftText(Caption, Text, TEXTSIZE);
	HDMIResolutionsGroupBox->Caption = Text;
	return true;
}
//---------------------------------------------------------------------------
bool THDMISupportForm::RefreshHDMIResolutionsListBox(int ItemIndex)
{
	int Index;
	HDMIResolutionClass HDMIResolution;
	char Text[TEXTSIZE];

	if (HDMISupport->Resolutions()->GetMaxCount() > 0)
	{
		HDMIResolutionsListBox->Enabled = true;
		HDMIResolutionsListBox->Color = clWindow;
		HDMIResolutionsListBox->Font->Color = clWindowText;
	}
	else
	{
		HDMIResolutionsListBox->Enabled = false;
		HDMIResolutionsListBox->Color = clBtnFace;
		HDMIResolutionsListBox->Font->Color = clGrayText;
		ItemIndex = -1;
	}

	HDMIResolutionsListBox->Clear();
	HDMIResolutionsListBox->Items->BeginUpdate();

	for (Index = 0; HDMISupport->Resolutions()->Get(Index, HDMIResolution); Index++)
		if (HDMIResolution.GetText(Text, TEXTSIZE))
			HDMIResolutionsListBox->Items->Add(Text);

	if (Index == 0)
		HDMIResolutionsListBox->Items->Add("No HDMI resolutions");

	HDMIResolutionsListBox->ItemIndex = ItemIndex;
	HDMIResolutionsListBox->Items->EndUpdate();
	return true;
}
//---------------------------------------------------------------------------
bool THDMISupportForm::RefreshHDMIResolutionsButtons()
{
	HDMIResolutionsLastItemIndex = HDMIResolutionsListBox->ItemIndex;
	HDMIResolutionsAddButton->Enabled = HDMISupport->Resolutions()->AddPossible();
	HDMIResolutionsEditButton->Enabled = HDMISupport->Resolutions()->EditPossible(HDMIResolutionsListBox->ItemIndex);
	HDMIResolutionsDeleteButton->Enabled = HDMISupport->Resolutions()->DeletePossible(HDMIResolutionsListBox->ItemIndex);
	HDMIResolutionsDeleteAllButton->Enabled = HDMISupport->Resolutions()->DeleteAllPossible();
	HDMIResolutionsResetButton->Enabled = HDMISupport->Resolutions()->UndoPossible();
	HDMIResolutionsUpButton->Enabled = HDMISupport->Resolutions()->ExchangePossible(HDMIResolutionsListBox->ItemIndex, HDMIResolutionsListBox->ItemIndex - 1);
	HDMIResolutionsDownButton->Enabled = HDMISupport->Resolutions()->ExchangePossible(HDMIResolutionsListBox->ItemIndex, HDMIResolutionsListBox->ItemIndex + 1);
	return true;
}
//---------------------------------------------------------------------------
bool THDMISupportForm::ScaleControls()
{
	int GroupBoxWidth = FormButtonsWidth * 2 + Scale;
	int ListBoxWidth = GroupBoxWidth - PaddingWidth * 2;
	int Column1Left = PaddingWidth;
	int Column2Left = GroupBoxWidth - FormButtonsWidth;

	PhysicalAddress->AutoSize = false;
	PhysicalAddress->Width = PhysicalAddress->MaxLength * Canvas->TextWidth("@") + TextBoxPadding;
	PhysicalAddress->Height = TextBoxHeight;
	PhysicalAddress->Left = PaddingWidth;
	PhysicalAddress->Top = PaddingTop;

	PhysicalAddressLabel->Left = PhysicalAddress->Left + PhysicalAddress->Width + PostLabelSpacing;
	PhysicalAddressLabel->Top = PhysicalAddress->Top + 3;

	PhysicalAddressGroupBox->Width = GroupBoxWidth;
	PhysicalAddressGroupBox->Height = PhysicalAddress->Top + PhysicalAddress->Height + PaddingBottom;
	PhysicalAddressGroupBox->Left = Scale;
	PhysicalAddressGroupBox->Top = GroupBoxTop;

	YCbCr422->Width = CheckBoxWidth + Canvas->TextWidth(YCbCr422->Caption);
	YCbCr422->Height = CheckBoxHeight;
	YCbCr422->Left = Column1Left;
	YCbCr422->Top = PaddingTop + CheckBoxTop;

	YCbCr444->Width = CheckBoxWidth + Canvas->TextWidth(YCbCr444->Caption);
	YCbCr444->Height = CheckBoxHeight;
	YCbCr444->Left = YCbCr422->Left;
	YCbCr444->Top = YCbCr422->Top + YCbCr422->Height + CheckBoxSpacing;

	DeepColorYCbCr444->Width = CheckBoxWidth + Canvas->TextWidth(DeepColorYCbCr444->Caption);
	DeepColorYCbCr444->Height = CheckBoxHeight;
	DeepColorYCbCr444->Left = YCbCr444->Left;
	DeepColorYCbCr444->Top = YCbCr444->Top + YCbCr444->Height + CheckBoxSpacing;

	DeepColor30bit->Width = CheckBoxWidth + Canvas->TextWidth(DeepColor30bit->Caption);
	DeepColor30bit->Height = CheckBoxHeight;
	DeepColor30bit->Left = Column2Left;
	DeepColor30bit->Top = YCbCr422->Top;

	DeepColor36bit->Width = CheckBoxWidth + Canvas->TextWidth(DeepColor36bit->Caption);
	DeepColor36bit->Height = CheckBoxHeight;
	DeepColor36bit->Left = DeepColor30bit->Left;
	DeepColor36bit->Top = YCbCr444->Top;

	DeepColor48bit->Width = CheckBoxWidth + Canvas->TextWidth(DeepColor48bit->Caption);
	DeepColor48bit->Height = CheckBoxHeight;
	DeepColor48bit->Left = DeepColor36bit->Left;
	DeepColor48bit->Top = DeepColorYCbCr444->Top;

	ColorFormatsGroupBox->Width = PhysicalAddressGroupBox->Width;
	ColorFormatsGroupBox->Height = DeepColorYCbCr444->Top + DeepColorYCbCr444->Height + CheckBoxBottom + PaddingBottom;
	ColorFormatsGroupBox->Left = PhysicalAddressGroupBox->Left;
	ColorFormatsGroupBox->Top = PhysicalAddressGroupBox->Top + PhysicalAddressGroupBox->Height + GroupBoxBottom + GroupBoxTop;

	SupportsAI->Width = CheckBoxWidth + Canvas->TextWidth(SupportsAI->Caption);
	SupportsAI->Height = CheckBoxHeight;
	SupportsAI->Left = PaddingWidth;
	SupportsAI->Top = PaddingTop + CheckBoxTop;

	DualLinkDVI->Width = CheckBoxWidth + Canvas->TextWidth(DualLinkDVI->Caption);
	DualLinkDVI->Height = CheckBoxHeight;
	DualLinkDVI->Left = SupportsAI->Left;
	DualLinkDVI->Top = SupportsAI->Top + SupportsAI->Height + CheckBoxSpacing;

	FeaturesGroupBox->Width = ColorFormatsGroupBox->Width;
	FeaturesGroupBox->Height = DualLinkDVI->Top + DualLinkDVI->Height + CheckBoxBottom + PaddingBottom;
	FeaturesGroupBox->Left = ColorFormatsGroupBox->Left;
	FeaturesGroupBox->Top = ColorFormatsGroupBox->Top + ColorFormatsGroupBox->Height + GroupBoxBottom + GroupBoxTop;

	OverrideTMDSClock->Width = CheckBoxWidth + Canvas->TextWidth(OverrideTMDSClock->Caption);
	OverrideTMDSClock->Height = CheckBoxHeight;

	TMDSClock->AutoSize = false;
	TMDSClock->Width = TMDSClock->MaxLength * NumberWidth + TextBoxPadding;
	TMDSClock->Height = TextBoxHeight;

	OverrideTMDSClock->Left = PaddingWidth;
	TMDSClock->Left = OverrideTMDSClock->Left + OverrideTMDSClock->Width + CheckBoxRight + LabelSpacing;
	TMDSClockLabel->Left = TMDSClock->Left + TMDSClock->Width + PostLabelSpacing;

	TMDSClock->Top = PaddingTop;
	OverrideTMDSClock->Top = TMDSClock->Top + 3 + CheckBoxTop;
	TMDSClockLabel->Top = TMDSClock->Top + 3;

	TMDSClockGroupBox->Width = FeaturesGroupBox->Width;
	TMDSClockGroupBox->Height = TMDSClock->Top + TMDSClock->Height + PaddingBottom;
	TMDSClockGroupBox->Left = FeaturesGroupBox->Left;
	TMDSClockGroupBox->Top = FeaturesGroupBox->Top + FeaturesGroupBox->Height + GroupBoxBottom + GroupBoxTop;

	ContentType0->Width = CheckBoxWidth + Canvas->TextWidth(ContentType0->Caption);
	ContentType0->Height = CheckBoxHeight;
	ContentType0->Left = Column1Left;
	ContentType0->Top = PaddingTop + CheckBoxTop;

	ContentType1->Width = CheckBoxWidth + Canvas->TextWidth(ContentType1->Caption);
	ContentType1->Height = CheckBoxHeight;
	ContentType1->Left = (Column2Left - ContentType0->Left - ContentType0->Width - ContentType1->Width) / 2 + ContentType0->Left + ContentType0->Width;
	ContentType1->Top = ContentType0->Top;

	ContentType2->Width = CheckBoxWidth + Canvas->TextWidth(ContentType2->Caption);
	ContentType2->Height = CheckBoxHeight;
	ContentType2->Left = Column2Left;
	ContentType2->Top = ContentType1->Top;

	ContentType3->Width = CheckBoxWidth + Canvas->TextWidth(ContentType3->Caption);
	ContentType3->Height = CheckBoxHeight;
	ContentType3->Left = ContentType1->Left - ContentType0->Left - ContentType0->Width + ContentType2->Left + ContentType2->Width;
	ContentType3->Top = ContentType2->Top;

	ContentTypesGroupBox->Width = TMDSClockGroupBox->Width;
	ContentTypesGroupBox->Height = ContentType0->Top + ContentType0->Height + CheckBoxBottom + PaddingBottom;
	ContentTypesGroupBox->Left = TMDSClockGroupBox->Left;
	ContentTypesGroupBox->Top = TMDSClockGroupBox->Top + TMDSClockGroupBox->Height + GroupBoxBottom + GroupBoxTop;

	IncludeLatency->Width = CheckBoxWidth + Canvas->TextWidth(IncludeLatency->Caption);
	IncludeLatency->Height = CheckBoxHeight;
	IncludeLatency->Left = Column1Left;
	IncludeLatency->Top = PaddingTop + CheckBoxTop;

	VideoSupported->Width = CheckBoxWidth + Canvas->TextWidth(VideoSupported->Caption);
	VideoSupported->Height = CheckBoxHeight;

	VideoLatency->AutoSize = false;
	VideoLatency->Width = VideoLatency->MaxLength * NumberWidth + TextBoxPadding;
	VideoLatency->Height = TextBoxHeight;

	AudioSupported->Width = CheckBoxWidth + Canvas->TextWidth(AudioSupported->Caption);
	AudioSupported->Height = CheckBoxHeight;

	AudioLatency->AutoSize = false;
	AudioLatency->Width = AudioLatency->MaxLength * NumberWidth + TextBoxPadding;
	AudioLatency->Height = TextBoxHeight;

	VideoSupported->Left = IncludeLatency->Left + Scale * 5 / 2;
	AudioSupported->Left = VideoSupported->Left;

	VideoLatency->Left = AudioSupported->Left + AudioSupported->Width + CheckBoxRight + LabelSpacing;
	AudioLatency->Left = VideoLatency->Left;

	VideoLatencyLabel->Left = VideoLatency->Left + VideoLatency->Width + PostLabelSpacing;
	AudioLatencyLabel->Left = VideoLatencyLabel->Left;

	VideoLatency->Top = IncludeLatency->Top + IncludeLatency->Height + CheckBoxBottom + Scale;
	AudioLatency->Top = VideoLatency->Top + VideoLatency->Height + TextBoxSpacing;

	VideoSupported->Top = VideoLatency->Top + 3 + CheckBoxTop;
	AudioSupported->Top = AudioLatency->Top + 3 + CheckBoxTop;

	VideoLatencyLabel->Top = VideoLatency->Top + 3;
	AudioLatencyLabel->Top = AudioLatency->Top + 3;

	IncludeInterlacedLatency->Width = CheckBoxWidth + Canvas->TextWidth(IncludeInterlacedLatency->Caption);
	IncludeInterlacedLatency->Height = CheckBoxHeight;
	IncludeInterlacedLatency->Left = Column2Left;
	IncludeInterlacedLatency->Top = IncludeLatency->Top;

	InterlacedVideoSupported->Width = CheckBoxWidth + Canvas->TextWidth(InterlacedVideoSupported->Caption);
	InterlacedVideoSupported->Height = CheckBoxHeight;

	InterlacedVideoLatency->AutoSize = false;
	InterlacedVideoLatency->Width = InterlacedVideoLatency->MaxLength * NumberWidth + TextBoxPadding;
	InterlacedVideoLatency->Height = TextBoxHeight;

	InterlacedAudioSupported->Width = CheckBoxWidth + Canvas->TextWidth(InterlacedAudioSupported->Caption);
	InterlacedAudioSupported->Height = CheckBoxHeight;

	InterlacedAudioLatency->AutoSize = false;
	InterlacedAudioLatency->Width = InterlacedAudioLatency->MaxLength * NumberWidth + TextBoxPadding;
	InterlacedAudioLatency->Height = TextBoxHeight;

	InterlacedVideoSupported->Left = IncludeInterlacedLatency->Left + Scale * 5 / 2;
	InterlacedAudioSupported->Left = InterlacedVideoSupported->Left;

	InterlacedVideoLatency->Left = InterlacedAudioSupported->Left + InterlacedAudioSupported->Width + CheckBoxRight + LabelSpacing;
	InterlacedAudioLatency->Left = InterlacedVideoLatency->Left;

	InterlacedVideoLatencyLabel->Left = InterlacedVideoLatency->Left + InterlacedVideoLatency->Width + PostLabelSpacing;
	InterlacedAudioLatencyLabel->Left = InterlacedVideoLatencyLabel->Left;

	InterlacedVideoLatency->Top = VideoLatency->Top;
	InterlacedAudioLatency->Top = AudioLatency->Top;

	InterlacedVideoSupported->Top = InterlacedVideoLatency->Top + 3 + CheckBoxTop;
	InterlacedAudioSupported->Top = InterlacedAudioLatency->Top + 3 + CheckBoxTop;

	InterlacedVideoLatencyLabel->Top = InterlacedVideoLatency->Top + 3;
	InterlacedAudioLatencyLabel->Top = InterlacedAudioLatency->Top + 3;

	LatencyGroupBox->Width = ContentTypesGroupBox->Width;
	LatencyGroupBox->Height = AudioLatency->Top + AudioLatency->Height + PaddingBottom;
	LatencyGroupBox->Left = ContentTypesGroupBox->Left;
	LatencyGroupBox->Top = ContentTypesGroupBox->Top + ContentTypesGroupBox->Height + GroupBoxBottom + GroupBoxTop;

	HDMIResolutionsListBox->Width = ListBoxWidth;
	HDMIResolutionsListBox->Height = Text.tmHeight * 4 + 4;
	HDMIResolutionsListBox->ItemHeight = Text.tmHeight;
	HDMIResolutionsListBox->Left = PaddingWidth;
	HDMIResolutionsListBox->Top = PaddingTop;

	HDMIResolutionsAddButton->Width = ButtonWidth;
	HDMIResolutionsAddButton->Height = ButtonHeight;
	HDMIResolutionsAddButton->Left = HDMIResolutionsListBox->Left + ButtonLeft;
	HDMIResolutionsAddButton->Top = HDMIResolutionsListBox->Top + HDMIResolutionsListBox->Height + Scale + ButtonTop;
	Common::FixButtonCaption(HDMIResolutionsAddButton, Canvas->TextWidth(HDMIResolutionsAddButton->Caption));

	HDMIResolutionsEditButton->Width = ButtonWidth;
	HDMIResolutionsEditButton->Height = ButtonHeight;
	HDMIResolutionsEditButton->Left = HDMIResolutionsAddButton->Left + HDMIResolutionsAddButton->Width;
	HDMIResolutionsEditButton->Top = HDMIResolutionsAddButton->Top;
	Common::FixButtonCaption(HDMIResolutionsEditButton, Canvas->TextWidth(HDMIResolutionsEditButton->Caption));

	HDMIResolutionsDeleteButton->Width = ButtonWidth;
	HDMIResolutionsDeleteButton->Height = ButtonHeight;
	HDMIResolutionsDeleteButton->Left = HDMIResolutionsEditButton->Left + HDMIResolutionsEditButton->Width;
	HDMIResolutionsDeleteButton->Top = HDMIResolutionsEditButton->Top;
	Common::FixButtonCaption(HDMIResolutionsDeleteButton, Canvas->TextWidth(HDMIResolutionsDeleteButton->Caption));

	HDMIResolutionsDeleteAllButton->Width = LongButtonWidth;
	HDMIResolutionsDeleteAllButton->Height = LongButtonHeight;
	HDMIResolutionsDeleteAllButton->Left = HDMIResolutionsDeleteButton->Left + HDMIResolutionsDeleteButton->Width;
	HDMIResolutionsDeleteAllButton->Top = HDMIResolutionsDeleteButton->Top;
	Common::FixButtonCaption(HDMIResolutionsDeleteAllButton, Canvas->TextWidth(HDMIResolutionsDeleteAllButton->Caption));

	HDMIResolutionsResetButton->Width = ButtonWidth;
	HDMIResolutionsResetButton->Height = ButtonHeight;
	HDMIResolutionsResetButton->Left = HDMIResolutionsDeleteAllButton->Left + HDMIResolutionsDeleteAllButton->Width;
	HDMIResolutionsResetButton->Top = HDMIResolutionsDeleteAllButton->Top;
	Common::FixButtonCaption(HDMIResolutionsResetButton, Canvas->TextWidth(HDMIResolutionsResetButton->Caption));

	HDMIResolutionsUpButton->Width = ArrowButtonWidth;
	HDMIResolutionsUpButton->Height = ArrowButtonHeight;
	HDMIResolutionsUpButton->Top = HDMIResolutionsResetButton->Top;
	HDMIResolutionsUpButton->Enabled = false;
	HDMIResolutionsUpButton->NumGlyphs = NumGlyphs;
	HDMIResolutionsUpButton->Glyph->LoadFromResourceID(0, Common::GetScaledResourceID(ARROW_UP));

	HDMIResolutionsDownButton->Width = ArrowButtonWidth;
	HDMIResolutionsDownButton->Height = ArrowButtonHeight;
	HDMIResolutionsDownButton->Top = HDMIResolutionsUpButton->Top;
	HDMIResolutionsDownButton->Enabled = false;
	HDMIResolutionsDownButton->NumGlyphs = NumGlyphs;
	HDMIResolutionsDownButton->Glyph->LoadFromResourceID(0, Common::GetScaledResourceID(ARROW_DOWN));

	HDMIResolutionsDownButton->Left = HDMIResolutionsListBox->Left + HDMIResolutionsListBox->Width - ButtonRight - HDMIResolutionsDownButton->Width;
	HDMIResolutionsUpButton->Left = HDMIResolutionsDownButton->Left - HDMIResolutionsUpButton->Width;

	HDMIResolutionsGroupBox->Width = LatencyGroupBox->Width;
	HDMIResolutionsGroupBox->Height = HDMIResolutionsAddButton->Top + HDMIResolutionsAddButton->Height + ButtonBottom + PaddingBottom;
	HDMIResolutionsGroupBox->Left = LatencyGroupBox->Left;
	HDMIResolutionsGroupBox->Top = LatencyGroupBox->Top + LatencyGroupBox->Height + GroupBoxBottom + GroupBoxTop;

	FormOKButton->Width = FormButtonWidth;
	FormOKButton->Height = FormButtonHeight;
	FormOKButton->Top = HDMIResolutionsGroupBox->Top + HDMIResolutionsGroupBox->Height + GroupBoxBottom + Scale + ButtonTop;
	Common::FixButtonCaption(FormOKButton, Canvas->TextWidth(FormOKButton->Caption));

	FormCancelButton->Width = FormButtonWidth;
	FormCancelButton->Height = FormButtonHeight;
	FormCancelButton->Top = FormOKButton->Top;
	Common::FixButtonCaption(FormCancelButton, Canvas->TextWidth(FormCancelButton->Caption));

	FormCancelButton->Left = HDMIResolutionsGroupBox->Left + HDMIResolutionsGroupBox->Width - ButtonRight - FormCancelButton->Width;
	FormOKButton->Left = FormCancelButton->Left - ButtonLeft - Scale - ButtonRight - FormOKButton->Width;

	ClientWidth = FormCancelButton->Left + FormCancelButton->Width + ButtonRight + Scale;
	ClientHeight = FormCancelButton->Top + FormCancelButton->Height + ButtonBottom + Scale;
	return true;
}
//---------------------------------------------------------------------------
void __fastcall THDMISupportForm::FormCreate(TObject *Sender)
{
	ScaleControls();
}
//---------------------------------------------------------------------------
void __fastcall THDMISupportForm::FormShow(TObject *Sender)
{
	Refresh(NULL, -1);
}
//---------------------------------------------------------------------------
void __fastcall THDMISupportForm::PhysicalAddressChange(TObject *Sender)
{
	if (Refreshing)
		return;

	HDMISupport->SetPhysicalAddressText(PhysicalAddress->Text.c_str());
	Refresh(PhysicalAddressGroupBox, -1);
}
//---------------------------------------------------------------------------
void __fastcall THDMISupportForm::PhysicalAddressExit(TObject *Sender)
{
	Refresh(PhysicalAddressGroupBox, -1);
}
//---------------------------------------------------------------------------
void __fastcall THDMISupportForm::YCbCr422Click(TObject *Sender)
{
	if (Refreshing)
		return;

	ColorFormatList->SetYCbCr422(YCbCr422->Checked);
	Refresh(ColorFormatsGroupBox, -1);
}
//---------------------------------------------------------------------------
void __fastcall THDMISupportForm::YCbCr444Click(TObject *Sender)
{
	if (Refreshing)
		return;

	ColorFormatList->SetYCbCr444(YCbCr444->Checked);
	Refresh(ColorFormatsGroupBox, -1);
}
//---------------------------------------------------------------------------
void __fastcall THDMISupportForm::DeepColorYCbCr444Click(TObject *Sender)
{
	if (Refreshing)
		return;

	HDMISupport->SetDeepColorYCbCr444(DeepColorYCbCr444->Checked);
	Refresh(ColorFormatsGroupBox, -1);
}
//---------------------------------------------------------------------------
void __fastcall THDMISupportForm::DeepColor30bitClick(TObject *Sender)
{
	if (Refreshing)
		return;

	HDMISupport->SetDeepColor30bit(DeepColor30bit->Checked);
	Refresh(ColorFormatsGroupBox, -1);
}
//---------------------------------------------------------------------------
void __fastcall THDMISupportForm::DeepColor36bitClick(TObject *Sender)
{
	if (Refreshing)
		return;

	HDMISupport->SetDeepColor36bit(DeepColor36bit->Checked);
	Refresh(ColorFormatsGroupBox, -1);
}
//---------------------------------------------------------------------------
void __fastcall THDMISupportForm::DeepColor48bitClick(TObject *Sender)
{
	if (Refreshing)
		return;

	HDMISupport->SetDeepColor48bit(DeepColor48bit->Checked);
	Refresh(ColorFormatsGroupBox, -1);
}
//---------------------------------------------------------------------------
void __fastcall THDMISupportForm::SupportsAIClick(TObject *Sender)
{
	if (Refreshing)
		return;

	HDMISupport->SetSupportsAI(SupportsAI->Checked);
	Refresh(FeaturesGroupBox, -1);
}
//---------------------------------------------------------------------------
void __fastcall THDMISupportForm::DualLinkDVIClick(TObject *Sender)
{
	if (Refreshing)
		return;

	HDMISupport->SetDualLinkDVI(DualLinkDVI->Checked);
	Refresh(FeaturesGroupBox, -1);
}
//---------------------------------------------------------------------------
void __fastcall THDMISupportForm::OverrideTMDSClockClick(TObject *Sender)
{
	if (Refreshing)
		return;

	HDMISupport->SetOverrideTMDSClock(OverrideTMDSClock->Checked);
	Refresh(TMDSClockGroupBox, -1);
}
//---------------------------------------------------------------------------
void __fastcall THDMISupportForm::TMDSClockChange(TObject *Sender)
{
	if (Refreshing)
		return;

	HDMISupport->SetTMDSClock(Common::TextToInteger(TMDSClock->Text.c_str()));
	Refresh(TMDSClockGroupBox, -1);
}
//---------------------------------------------------------------------------
void __fastcall THDMISupportForm::TMDSClockExit(TObject *Sender)
{
	Refresh(TMDSClockGroupBox, -1);
}
//---------------------------------------------------------------------------
void __fastcall THDMISupportForm::ContentTypeClick(TObject *Sender)
{
	if (Refreshing)
		return;

	TCheckBox *CheckBox = (TCheckBox *)Sender;
	HDMISupport->SetContentType(CheckBox->Tag, CheckBox->Checked);
	Refresh(ContentTypesGroupBox, -1);
}
//---------------------------------------------------------------------------
void __fastcall THDMISupportForm::IncludeLatencyClick(TObject *Sender)
{
	if (Refreshing)
		return;

	HDMISupport->SetIncludeLatency(IncludeLatency->Checked);
	Refresh(LatencyGroupBox, HDMIResolutionsListBox->ItemIndex);
}
//---------------------------------------------------------------------------
void __fastcall THDMISupportForm::VideoSupportedClick(TObject *Sender)
{
	if (Refreshing)
		return;

	HDMISupport->SetVideoSupported(VideoSupported->Checked);
	Refresh(LatencyGroupBox, HDMIResolutionsListBox->ItemIndex);
}
//---------------------------------------------------------------------------
void __fastcall THDMISupportForm::VideoLatencyChange(TObject *Sender)
{
	if (Refreshing)
		return;

	HDMISupport->SetVideoLatency(Common::TextToInteger(VideoLatency->Text.c_str()));
	Refresh(LatencyGroupBox, HDMIResolutionsListBox->ItemIndex);
}
//---------------------------------------------------------------------------
void __fastcall THDMISupportForm::VideoLatencyExit(TObject *Sender)
{
	Refresh(LatencyGroupBox, HDMIResolutionsListBox->ItemIndex);
}
//---------------------------------------------------------------------------
void __fastcall THDMISupportForm::AudioSupportedClick(TObject *Sender)
{
	if (Refreshing)
		return;

	HDMISupport->SetAudioSupported(AudioSupported->Checked);
	Refresh(LatencyGroupBox, HDMIResolutionsListBox->ItemIndex);
}
//---------------------------------------------------------------------------
void __fastcall THDMISupportForm::AudioLatencyChange(TObject *Sender)
{
	if (Refreshing)
		return;

	HDMISupport->SetAudioLatency(Common::TextToInteger(AudioLatency->Text.c_str()));
	Refresh(LatencyGroupBox, HDMIResolutionsListBox->ItemIndex);
}
//---------------------------------------------------------------------------
void __fastcall THDMISupportForm::AudioLatencyExit(TObject *Sender)
{
	Refresh(LatencyGroupBox, HDMIResolutionsListBox->ItemIndex);
}
//---------------------------------------------------------------------------
void __fastcall THDMISupportForm::IncludeInterlacedLatencyClick(TObject *Sender)
{
	if (Refreshing)
		return;

	HDMISupport->SetIncludeInterlacedLatency(IncludeInterlacedLatency->Checked);
	Refresh(LatencyGroupBox, HDMIResolutionsListBox->ItemIndex);
}
//---------------------------------------------------------------------------
void __fastcall THDMISupportForm::InterlacedVideoSupportedClick(TObject *Sender)
{
	if (Refreshing)
		return;

	HDMISupport->SetInterlacedVideoSupported(InterlacedVideoSupported->Checked);
	Refresh(LatencyGroupBox, HDMIResolutionsListBox->ItemIndex);
}
//---------------------------------------------------------------------------
void __fastcall THDMISupportForm::InterlacedVideoLatencyChange(TObject *Sender)
{
	if (Refreshing)
		return;

	HDMISupport->SetInterlacedVideoLatency(Common::TextToInteger(InterlacedVideoLatency->Text.c_str()));
	Refresh(LatencyGroupBox, HDMIResolutionsListBox->ItemIndex);
}
//---------------------------------------------------------------------------
void __fastcall THDMISupportForm::InterlacedVideoLatencyExit(TObject *Sender)
{
	Refresh(LatencyGroupBox, HDMIResolutionsListBox->ItemIndex);
}
//---------------------------------------------------------------------------
void __fastcall THDMISupportForm::InterlacedAudioSupportedClick(TObject *Sender)
{
	if (Refreshing)
		return;

	HDMISupport->SetInterlacedAudioSupported(InterlacedAudioSupported->Checked);
	Refresh(LatencyGroupBox, HDMIResolutionsListBox->ItemIndex);
}
//---------------------------------------------------------------------------
void __fastcall THDMISupportForm::InterlacedAudioLatencyChange(TObject *Sender)
{
	if (Refreshing)
		return;

	HDMISupport->SetInterlacedAudioLatency(Common::TextToInteger(InterlacedAudioLatency->Text.c_str()));
	Refresh(LatencyGroupBox, HDMIResolutionsListBox->ItemIndex);
}
//---------------------------------------------------------------------------
void __fastcall THDMISupportForm::InterlacedAudioLatencyExit(TObject *Sender)
{
	Refresh(LatencyGroupBox, HDMIResolutionsListBox->ItemIndex);
}
//---------------------------------------------------------------------------
void __fastcall THDMISupportForm::HDMIResolutionsListBoxDrawItem(TWinControl *Control, int Index, TRect &Rect, TOwnerDrawState State)
{
	HDMIResolutionClass HDMIResolution;
	bool Supported = false;

	if (HDMISupport->Resolutions()->Get(Index, HDMIResolution))
		Supported = HDMIResolution.IsSupported();

	Common::ListBoxDrawItem(HDMIResolutionsListBox, Rect, State, HDMIResolutionsListBox->Items->Strings[Index].c_str(), Supported, false);
}
//---------------------------------------------------------------------------
void __fastcall THDMISupportForm::HDMIResolutionsListBoxClick(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
	HDMIResolutionsLastClickedItemIndex = HDMIResolutionsListBox->ItemIndex;

	if (HDMIResolutionsListBox->ItemIndex == HDMIResolutionsLastItemIndex)
		HDMIResolutionsListBox->ItemIndex = -1;

	RefreshHDMIResolutionsButtons();
}
//---------------------------------------------------------------------------
void __fastcall THDMISupportForm::HDMIResolutionsListBoxDblClick(TObject *Sender)
{
	HDMIResolutionsListBox->ItemIndex = HDMIResolutionsLastClickedItemIndex;
	RefreshHDMIResolutionsButtons();

	if (HDMISupport->Resolutions()->EditPossible(HDMIResolutionsListBox->ItemIndex))
		HDMIResolutionsEditButtonClick(HDMIResolutionsListBox);

	HDMIResolutionsLastItemIndex = -1;
}
//---------------------------------------------------------------------------
void __fastcall THDMISupportForm::HDMIResolutionsListBoxSelect(TObject *Sender)
{
	RefreshHDMIResolutionsButtons();
}
//---------------------------------------------------------------------------
void __fastcall THDMISupportForm::HDMIResolutionsAddButtonClick(TObject *Sender)
{
	HDMIResolutionClass HDMIResolution;
	THDMIResolutionForm *HDMIResolutionForm = new THDMIResolutionForm(this);

	HDMIResolutionForm->Connect(HDMIResolution);

	if (HDMIResolutionForm->ShowModal() == mrOk)
	{
		HDMISupport->Resolutions()->Add(HDMIResolution);
		Refresh(HDMIResolutionsGroupBox, HDMISupport->Resolutions()->GetCount() - 1);
	}

	delete HDMIResolutionForm;
}
//---------------------------------------------------------------------------
void __fastcall THDMISupportForm::HDMIResolutionsEditButtonClick(TObject *Sender)
{
	HDMIResolutionClass HDMIResolution;
	THDMIResolutionForm *HDMIResolutionForm = new THDMIResolutionForm(this);

	HDMISupport->Resolutions()->Get(HDMIResolutionsListBox->ItemIndex, HDMIResolution);
	HDMIResolutionForm->Connect(HDMIResolution);

	if (HDMIResolutionForm->ShowModal() == mrOk)
	{
		HDMISupport->Resolutions()->Set(HDMIResolutionsListBox->ItemIndex, HDMIResolution);
		Refresh(HDMIResolutionsGroupBox, HDMIResolutionsListBox->ItemIndex);
	}

	delete HDMIResolutionForm;
}
//---------------------------------------------------------------------------
void __fastcall THDMISupportForm::HDMIResolutionsDeleteButtonClick(TObject *Sender)
{
	HDMISupport->Resolutions()->Delete(HDMIResolutionsListBox->ItemIndex);

	if (HDMIResolutionsListBox->ItemIndex >= HDMISupport->Resolutions()->GetCount())
		HDMIResolutionsListBox->ItemIndex = -1;

	Refresh(HDMIResolutionsGroupBox, HDMIResolutionsListBox->ItemIndex);
}
//---------------------------------------------------------------------------
void __fastcall THDMISupportForm::HDMIResolutionsDeleteAllButtonClick(TObject *Sender)
{
	HDMISupport->Resolutions()->DeleteAll();
	Refresh(HDMIResolutionsGroupBox, -1);
}
//---------------------------------------------------------------------------
void __fastcall THDMISupportForm::HDMIResolutionsResetButtonClick(TObject *Sender)
{
	HDMISupport->Resolutions()->Undo();
	Refresh(HDMIResolutionsGroupBox, -1);
}
//---------------------------------------------------------------------------
void __fastcall THDMISupportForm::HDMIResolutionsUpButtonClick(TObject *Sender)
{
	HDMISupport->Resolutions()->Exchange(HDMIResolutionsListBox->ItemIndex, HDMIResolutionsListBox->ItemIndex - 1);
	Refresh(HDMIResolutionsGroupBox, HDMIResolutionsListBox->ItemIndex - 1);
}
//---------------------------------------------------------------------------
void __fastcall THDMISupportForm::HDMIResolutionsDownButtonClick(TObject *Sender)
{
	HDMISupport->Resolutions()->Exchange(HDMIResolutionsListBox->ItemIndex, HDMIResolutionsListBox->ItemIndex + 1);
	Refresh(HDMIResolutionsGroupBox, HDMIResolutionsListBox->ItemIndex + 1);
}
//---------------------------------------------------------------------------
