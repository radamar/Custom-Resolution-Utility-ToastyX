//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "AudioFormatListFormClass.h"
#include "AudioFormatFormClass.h"
#include "Common.h"
#include <cstdio>
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TAudioFormatListForm *AudioFormatListForm;
//---------------------------------------------------------------------------
__fastcall TAudioFormatListForm::TAudioFormatListForm(TComponent *Owner) : TCommonForm(Owner)
{
	Refreshing = false;
	AudioLastItemIndex = -1;
	AudioLastClickedItemIndex = -1;
}
//---------------------------------------------------------------------------
bool TAudioFormatListForm::Connect(AudioFormatListClass &NewAudioFormatList)
{
	AudioFormatList = &NewAudioFormatList;
	return true;
}
//---------------------------------------------------------------------------
bool TAudioFormatListForm::Refresh(void *Value, int ItemIndex)
{
	Refreshing = true;

	if (Value == NULL || Value == AudioGroupBox)
	{
		RefreshAudioCaption();
		RefreshAudioListBox(ItemIndex);
		RefreshAudioButtons();
	}

	Refreshing = false;
	return true;
}
//---------------------------------------------------------------------------
bool TAudioFormatListForm::RefreshAudioCaption()
{
	const char *Caption = " Audio formats ";
	char Text[TEXTSIZE];

	AudioFormatList->GetSlotsLeftText(Caption, Text, TEXTSIZE);
	AudioGroupBox->Caption = Text;
	return true;
}
//---------------------------------------------------------------------------
bool TAudioFormatListForm::RefreshAudioListBox(int ItemIndex)
{
	int Index;

	if (AudioFormatList->GetMaxCount() > 0)
	{
		AudioListBox->Enabled = true;
		AudioListBox->Color = clWindow;
		AudioListBox->Font->Color = clWindowText;
	}
	else
	{
		AudioListBox->Enabled = false;
		AudioListBox->Color = clBtnFace;
		AudioListBox->Font->Color = clGrayText;
		ItemIndex = -1;
	}

	AudioListBox->Clear();
	AudioListBox->Items->BeginUpdate();

	for (Index = 0; Index < AudioFormatList->GetCount(); Index++)
		AudioListBox->Items->Add("Text");

	if (Index == 0)
		AudioListBox->Items->Add("No audio formats");

	AudioListBox->ItemIndex = ItemIndex;
	AudioListBox->Items->EndUpdate();
	return true;
}
//---------------------------------------------------------------------------
bool TAudioFormatListForm::RefreshAudioButtons()
{
	AudioLastItemIndex = AudioListBox->ItemIndex;
	AudioAddButton->Enabled = AudioFormatList->AddPossible();
	AudioEditButton->Enabled = AudioFormatList->EditPossible(AudioListBox->ItemIndex);
	AudioDeleteButton->Enabled = AudioFormatList->DeletePossible(AudioListBox->ItemIndex);
	AudioDeleteAllButton->Enabled = AudioFormatList->DeleteAllPossible();
	AudioResetButton->Enabled = AudioFormatList->UndoPossible();
	AudioUpButton->Enabled = AudioFormatList->ExchangePossible(AudioListBox->ItemIndex, AudioListBox->ItemIndex - 1);
	AudioDownButton->Enabled = AudioFormatList->ExchangePossible(AudioListBox->ItemIndex, AudioListBox->ItemIndex + 1);
	return true;
}
//---------------------------------------------------------------------------
bool TAudioFormatListForm::ScaleControls()
{
	AudioListBox->Width = ListBoxWidth;
	AudioListBox->Height = Text.tmHeight * 10 + 4;
	AudioListBox->ItemHeight = Text.tmHeight;
	AudioListBox->Left = PaddingWidth;
	AudioListBox->Top = PaddingTop;

	AudioAddButton->Width = ButtonWidth;
	AudioAddButton->Height = ButtonHeight;
	AudioAddButton->Left = AudioListBox->Left + ButtonLeft;
	AudioAddButton->Top = AudioListBox->Top + AudioListBox->Height + Scale + ButtonTop;
	Common::FixButtonCaption(AudioAddButton, Canvas->TextWidth(AudioAddButton->Caption));

	AudioEditButton->Width = ButtonWidth;
	AudioEditButton->Height = ButtonHeight;
	AudioEditButton->Left = AudioAddButton->Left + AudioAddButton->Width;
	AudioEditButton->Top = AudioAddButton->Top;
	Common::FixButtonCaption(AudioEditButton, Canvas->TextWidth(AudioEditButton->Caption));

	AudioDeleteButton->Width = ButtonWidth;
	AudioDeleteButton->Height = ButtonHeight;
	AudioDeleteButton->Left = AudioEditButton->Left + AudioEditButton->Width;
	AudioDeleteButton->Top = AudioEditButton->Top;
	Common::FixButtonCaption(AudioDeleteButton, Canvas->TextWidth(AudioDeleteButton->Caption));

	AudioDeleteAllButton->Width = LongButtonWidth;
	AudioDeleteAllButton->Height = LongButtonHeight;
	AudioDeleteAllButton->Left = AudioDeleteButton->Left + AudioDeleteButton->Width;
	AudioDeleteAllButton->Top = AudioDeleteButton->Top;
	Common::FixButtonCaption(AudioDeleteAllButton, Canvas->TextWidth(AudioDeleteAllButton->Caption));

	AudioResetButton->Width = ButtonWidth;
	AudioResetButton->Height = ButtonHeight;
	AudioResetButton->Left = AudioDeleteAllButton->Left + AudioDeleteAllButton->Width;
	AudioResetButton->Top = AudioDeleteAllButton->Top;
	Common::FixButtonCaption(AudioResetButton, Canvas->TextWidth(AudioResetButton->Caption));

	AudioUpButton->Width = ArrowButtonWidth;
	AudioUpButton->Height = ArrowButtonHeight;
	AudioUpButton->Top = AudioResetButton->Top;
	AudioUpButton->Enabled = false;
	AudioUpButton->NumGlyphs = NumGlyphs;
	AudioUpButton->Glyph->LoadFromResourceID(0, Common::GetScaledResourceID(ARROW_UP));

	AudioDownButton->Width = ArrowButtonWidth;
	AudioDownButton->Height = ArrowButtonHeight;
	AudioDownButton->Top = AudioUpButton->Top;
	AudioDownButton->Enabled = false;
	AudioDownButton->NumGlyphs = NumGlyphs;
	AudioDownButton->Glyph->LoadFromResourceID(0, Common::GetScaledResourceID(ARROW_DOWN));

	AudioDownButton->Left = AudioListBox->Left + AudioListBox->Width - ButtonRight - AudioDownButton->Width;
	AudioUpButton->Left = AudioDownButton->Left - AudioUpButton->Width;

	AudioGroupBox->Width = AudioListBox->Left + AudioListBox->Width + PaddingWidth;
	AudioGroupBox->Height = AudioAddButton->Top + AudioAddButton->Height + ButtonBottom + PaddingBottom;
	AudioGroupBox->Left = Scale;
	AudioGroupBox->Top = GroupBoxTop;

	FormOKButton->Width = FormButtonWidth;
	FormOKButton->Height = FormButtonHeight;
	FormOKButton->Top = AudioGroupBox->Top + AudioGroupBox->Height + GroupBoxBottom + Scale + ButtonTop;
	Common::FixButtonCaption(FormOKButton, Canvas->TextWidth(FormOKButton->Caption));

	FormCancelButton->Width = FormButtonWidth;
	FormCancelButton->Height = FormButtonHeight;
	FormCancelButton->Top = FormOKButton->Top;
	Common::FixButtonCaption(FormCancelButton, Canvas->TextWidth(FormCancelButton->Caption));

	FormCancelButton->Left = AudioGroupBox->Left + AudioGroupBox->Width - ButtonRight - FormCancelButton->Width;
	FormOKButton->Left = FormCancelButton->Left - ButtonLeft - Scale - ButtonRight - FormOKButton->Width;

	ClientWidth = FormCancelButton->Left + FormCancelButton->Width + ButtonRight + Scale;
	ClientHeight = FormCancelButton->Top + FormCancelButton->Height + ButtonBottom + Scale;
	return true;
}
//---------------------------------------------------------------------------
void __fastcall TAudioFormatListForm::FormCreate(TObject *Sender)
{
	ScaleControls();
}
//---------------------------------------------------------------------------
void __fastcall TAudioFormatListForm::FormShow(TObject *Sender)
{
	Refresh(NULL, -1);
}
//---------------------------------------------------------------------------
void __fastcall TAudioFormatListForm::AudioListBoxDrawItem(TWinControl *Control, int Index, TRect &Rect, TOwnerDrawState State)
{
	AudioFormatClass AudioFormat;
	Common::Column Columns[4];

	if (AudioFormatList->Get(Index, AudioFormat))
	{
		AudioFormat.GetFormatText(AudioFormat.GetFormat(), Columns[0].Text, TEXTSIZE);
		Columns[0].Width = AudioListBox->Width / 12 * 2;
		Columns[0].Format = DT_LEFT;

		std::snprintf(Columns[1].Text, TEXTSIZE, "%d", AudioFormat.GetChannels());
		Columns[1].Width = AudioListBox->Width / 12;
		Columns[1].Format = DT_RIGHT;

		std::snprintf(Columns[2].Text, TEXTSIZE, " channel%s", AudioFormat.GetChannels() != 1 ? "s" : "");
		Columns[2].Width = AudioListBox->Width / 12 * 3;
		Columns[2].Format = DT_LEFT;

		AudioFormat.GetInfoText(Columns[3].Text, TEXTSIZE);
		Columns[3].Width = AudioListBox->Width / 12 * 4;
		Columns[3].Format = DT_LEFT;

		Common::ListBoxDrawItems(AudioListBox, Rect, State, Columns, 4, AudioFormat.IsSupported(), false);
		return;
	}

	Common::ListBoxDrawItem(AudioListBox, Rect, State, AudioListBox->Items->Strings[Index].c_str(), false, false);
}
//---------------------------------------------------------------------------
void __fastcall TAudioFormatListForm::AudioListBoxClick(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
	AudioLastClickedItemIndex = AudioListBox->ItemIndex;

	if (AudioListBox->ItemIndex == AudioLastItemIndex)
		AudioListBox->ItemIndex = -1;

	RefreshAudioButtons();
}
//---------------------------------------------------------------------------
void __fastcall TAudioFormatListForm::AudioListBoxDoubleClick(TObject *Sender)
{
	AudioListBox->ItemIndex = AudioLastClickedItemIndex;
	RefreshAudioButtons();

	if (AudioFormatList->EditPossible(AudioListBox->ItemIndex))
		AudioEditButtonClick(AudioListBox);

	AudioLastItemIndex = -1;
}
//---------------------------------------------------------------------------
void __fastcall TAudioFormatListForm::AudioListBoxSelect(TObject *Sender)
{
	RefreshAudioButtons();
}
//---------------------------------------------------------------------------
void __fastcall TAudioFormatListForm::AudioAddButtonClick(TObject *Sender)
{
	AudioFormatClass AudioFormat;
	TAudioFormatForm *AudioFormatForm = new TAudioFormatForm(this);

	AudioFormatForm->Connect(AudioFormat);

	if (AudioFormatForm->ShowModal() == mrOk)
	{
		AudioFormatList->Add(AudioFormat);
		Refresh(AudioGroupBox, AudioFormatList->GetCount() - 1);
	}

	delete AudioFormatForm;
}
//---------------------------------------------------------------------------
void __fastcall TAudioFormatListForm::AudioEditButtonClick(TObject *Sender)
{
	AudioFormatClass AudioFormat;
	TAudioFormatForm *AudioFormatForm = new TAudioFormatForm(this);

	AudioFormatList->Get(AudioListBox->ItemIndex, AudioFormat);
	AudioFormatForm->Connect(AudioFormat);

	if (AudioFormatForm->ShowModal() == mrOk)
	{
		AudioFormatList->Set(AudioListBox->ItemIndex, AudioFormat);
		Refresh(AudioGroupBox, AudioListBox->ItemIndex);
	}

	delete AudioFormatForm;
}
//---------------------------------------------------------------------------
void __fastcall TAudioFormatListForm::AudioDeleteButtonClick(TObject *Sender)
{
	AudioFormatList->Delete(AudioListBox->ItemIndex);

	if (AudioListBox->ItemIndex >= AudioFormatList->GetCount())
		AudioListBox->ItemIndex = -1;

	Refresh(AudioGroupBox, AudioListBox->ItemIndex);
}
//---------------------------------------------------------------------------
void __fastcall TAudioFormatListForm::AudioDeleteAllButtonClick(TObject *Sender)
{
	AudioFormatList->DeleteAll();
	Refresh(AudioGroupBox, -1);
}
//---------------------------------------------------------------------------
void __fastcall TAudioFormatListForm::AudioResetButtonClick(TObject *Sender)
{
	AudioFormatList->Undo();
	Refresh(AudioGroupBox, -1);
}
//---------------------------------------------------------------------------
void __fastcall TAudioFormatListForm::AudioUpButtonClick(TObject *Sender)
{
	AudioFormatList->Exchange(AudioListBox->ItemIndex, AudioListBox->ItemIndex - 1);
	Refresh(AudioGroupBox, AudioListBox->ItemIndex - 1);
}
//---------------------------------------------------------------------------
void __fastcall TAudioFormatListForm::AudioDownButtonClick(TObject *Sender)
{
	AudioFormatList->Exchange(AudioListBox->ItemIndex, AudioListBox->ItemIndex + 1);
	Refresh(AudioGroupBox, AudioListBox->ItemIndex + 1);
}
//---------------------------------------------------------------------------
