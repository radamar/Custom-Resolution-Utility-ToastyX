//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "TVResolutionListFormClass.h"
#include "TVResolutionFormClass.h"
#include "Common.h"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TTVResolutionListForm *TVResolutionListForm;
//---------------------------------------------------------------------------
__fastcall TTVResolutionListForm::TTVResolutionListForm(TComponent *Owner) : TCommonForm(Owner)
{
	Refreshing = false;
	TVLastItemIndex = -1;
	TVLastClickedItemIndex = -1;
}
//---------------------------------------------------------------------------
bool TTVResolutionListForm::Connect(TVResolutionListClass &NewTVResolutionList)
{
	TVResolutionList = &NewTVResolutionList;
	return true;
}
//---------------------------------------------------------------------------
bool TTVResolutionListForm::Refresh(void *Value, int ItemIndex)
{
	Refreshing = true;

	if (Value == NULL || Value == TVGroupBox)
	{
		RefreshYCbCr420();
		RefreshTVCaption();
		RefreshTVListBox(ItemIndex);
		RefreshTVButtons();
	}

	Refreshing = false;
	return true;
}
//---------------------------------------------------------------------------
bool TTVResolutionListForm::RefreshYCbCr420()
{
	YCbCr420->Enabled = TVResolutionList->YCbCr420Possible();
	YCbCr420->Checked = TVResolutionList->GetYCbCr420();
	return true;
}
//---------------------------------------------------------------------------
bool TTVResolutionListForm::RefreshTVCaption()
{
	const char *Caption = " TV resolutions ";
	char Text[TEXTSIZE];

	TVResolutionList->GetSlotsLeftText(Caption, Text, TEXTSIZE);
	TVGroupBox->Caption = Text;
	return true;
}
//---------------------------------------------------------------------------
bool TTVResolutionListForm::RefreshTVListBox(int ItemIndex)
{
	int Index;
	TVResolutionClass TVResolution;
	char Text[TEXTSIZE];

	if (TVResolutionList->GetMaxCount() > 0)
	{
		TVListBox->Enabled = true;
		TVListBox->Color = clWindow;
		TVListBox->Font->Color = clWindowText;
	}
	else
	{
		TVListBox->Enabled = false;
		TVListBox->Color = clBtnFace;
		TVListBox->Font->Color = clGrayText;
		ItemIndex = -1;
	}

	TVListBox->Clear();
	TVListBox->Items->BeginUpdate();

	for (Index = 0; TVResolutionList->Get(Index, TVResolution); Index++)
		if (TVResolution.GetText(Text, TEXTSIZE))
			TVListBox->Items->Add(Text);

	if (Index == 0)
		TVListBox->Items->Add("No TV resolutions");

	TVListBox->ItemIndex = ItemIndex;
	TVListBox->Items->EndUpdate();
	return true;
}
//---------------------------------------------------------------------------
bool TTVResolutionListForm::RefreshTVButtons()
{
	TVLastItemIndex = TVListBox->ItemIndex;
	TVAddButton->Enabled = TVResolutionList->AddPossible();
	TVEditButton->Enabled = TVResolutionList->EditPossible(TVListBox->ItemIndex);
	TVDeleteButton->Enabled = TVResolutionList->DeletePossible(TVListBox->ItemIndex);
	TVDeleteAllButton->Enabled = TVResolutionList->DeleteAllPossible();
	TVResetButton->Enabled = TVResolutionList->UndoPossible();
	TVUpButton->Enabled = TVResolutionList->ExchangePossible(TVListBox->ItemIndex, TVListBox->ItemIndex - 1);
	TVDownButton->Enabled = TVResolutionList->ExchangePossible(TVListBox->ItemIndex, TVListBox->ItemIndex + 1);
	return true;
}
//---------------------------------------------------------------------------
bool TTVResolutionListForm::ScaleControls()
{
	TVListBox->Width = LongListBoxWidth;
	TVListBox->Height = Text.tmHeight * 16 + 4;
	TVListBox->ItemHeight = Text.tmHeight;
	TVListBox->Left = PaddingWidth;
	TVListBox->Top = PaddingTop;

	TVAddButton->Width = ButtonWidth;
	TVAddButton->Height = ButtonHeight;
	TVAddButton->Left = TVListBox->Left + ButtonLeft;
	TVAddButton->Top = TVListBox->Top + TVListBox->Height + Scale + ButtonTop;
	Common::FixButtonCaption(TVAddButton, Canvas->TextWidth(TVAddButton->Caption));

	TVEditButton->Width = ButtonWidth;
	TVEditButton->Height = ButtonHeight;
	TVEditButton->Left = TVAddButton->Left + TVAddButton->Width;
	TVEditButton->Top = TVAddButton->Top;
	Common::FixButtonCaption(TVEditButton, Canvas->TextWidth(TVEditButton->Caption));

	TVDeleteButton->Width = ButtonWidth;
	TVDeleteButton->Height = ButtonHeight;
	TVDeleteButton->Left = TVEditButton->Left + TVEditButton->Width;
	TVDeleteButton->Top = TVEditButton->Top;
	Common::FixButtonCaption(TVDeleteButton, Canvas->TextWidth(TVDeleteButton->Caption));

	TVDeleteAllButton->Width = LongButtonWidth;
	TVDeleteAllButton->Height = LongButtonHeight;
	TVDeleteAllButton->Left = TVDeleteButton->Left + TVDeleteButton->Width;
	TVDeleteAllButton->Top = TVDeleteButton->Top;
	Common::FixButtonCaption(TVDeleteAllButton, Canvas->TextWidth(TVDeleteAllButton->Caption));

	TVResetButton->Width = ButtonWidth;
	TVResetButton->Height = ButtonHeight;
	TVResetButton->Left = TVDeleteAllButton->Left + TVDeleteAllButton->Width;
	TVResetButton->Top = TVDeleteAllButton->Top;
	Common::FixButtonCaption(TVResetButton, Canvas->TextWidth(TVResetButton->Caption));

	TVUpButton->Width = ArrowButtonWidth;
	TVUpButton->Height = ArrowButtonHeight;
	TVUpButton->Top = TVResetButton->Top;
	TVUpButton->Enabled = false;
	TVUpButton->NumGlyphs = NumGlyphs;
	TVUpButton->Glyph->LoadFromResourceID(0, Common::GetScaledResourceID(ARROW_UP));

	TVDownButton->Width = ArrowButtonWidth;
	TVDownButton->Height = ArrowButtonHeight;
	TVDownButton->Top = TVUpButton->Top;
	TVDownButton->Enabled = false;
	TVDownButton->NumGlyphs = NumGlyphs;
	TVDownButton->Glyph->LoadFromResourceID(0, Common::GetScaledResourceID(ARROW_DOWN));

	TVDownButton->Left = TVListBox->Left + TVListBox->Width - ButtonRight - TVDownButton->Width;
	TVUpButton->Left = TVDownButton->Left - TVUpButton->Width;

	TVGroupBox->Width = TVListBox->Left + TVListBox->Width + PaddingWidth;
	TVGroupBox->Height = TVAddButton->Top + TVAddButton->Height + ButtonBottom + PaddingBottom;
	TVGroupBox->Left = Scale;
	TVGroupBox->Top = GroupBoxTop;

	YCbCr420->Width = CheckBoxWidth + Canvas->TextWidth(YCbCr420->Caption);
	YCbCr420->Height = CheckBoxHeight;
	YCbCr420->Left = TVGroupBox->Left + TVListBox->Left + TVListBox->Width - CheckBoxRight - YCbCr420->Width - 1;
	YCbCr420->Top = TVGroupBox->Top + CheckBoxTop;

	FormOKButton->Width = FormButtonWidth;
	FormOKButton->Height = FormButtonHeight;
	FormOKButton->Top = TVGroupBox->Top + TVGroupBox->Height + GroupBoxBottom + Scale + ButtonTop;
	Common::FixButtonCaption(FormOKButton, Canvas->TextWidth(FormOKButton->Caption));

	FormCancelButton->Width = FormButtonWidth;
	FormCancelButton->Height = FormButtonHeight;
	FormCancelButton->Top = FormOKButton->Top;
	Common::FixButtonCaption(FormCancelButton, Canvas->TextWidth(FormCancelButton->Caption));

	FormCancelButton->Left = TVGroupBox->Left + TVGroupBox->Width - ButtonRight - FormCancelButton->Width;
	FormOKButton->Left = FormCancelButton->Left - ButtonLeft - Scale - ButtonRight - FormOKButton->Width;

	ClientWidth = FormCancelButton->Left + FormCancelButton->Width + ButtonRight + Scale;
	ClientHeight = FormCancelButton->Top + FormCancelButton->Height + ButtonBottom + Scale;
	return true;
}
//---------------------------------------------------------------------------
void __fastcall TTVResolutionListForm::FormCreate(TObject *Sender)
{
	ScaleControls();
}
//---------------------------------------------------------------------------
void __fastcall TTVResolutionListForm::FormShow(TObject *Sender)
{
	Refresh(NULL, -1);
}
//---------------------------------------------------------------------------
void __fastcall TTVResolutionListForm::YCbCr420Click(TObject *Sender)
{
	if (Refreshing)
		return;

	TVResolutionList->SetYCbCr420(YCbCr420->Checked);
	Refresh(TVGroupBox, TVListBox->ItemIndex);
}
//---------------------------------------------------------------------------
void __fastcall TTVResolutionListForm::TVListBoxDrawItem(TWinControl *Control, int Index, TRect &Rect, TOwnerDrawState State)
{
	TVResolutionClass TVResolution;
	bool Supported = false;
	bool Native = false;

	if (TVResolutionList->Get(Index, TVResolution))
	{
		Supported = TVResolution.IsSupported();
		Native = TVResolution.GetNative();
	}

	Common::ListBoxDrawItem(TVListBox, Rect, State, TVListBox->Items->Strings[Index].c_str(), Supported, Native);
}
//---------------------------------------------------------------------------
void __fastcall TTVResolutionListForm::TVListBoxClick(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
	TVLastClickedItemIndex = TVListBox->ItemIndex;

	if (TVListBox->ItemIndex == TVLastItemIndex)
		TVListBox->ItemIndex = -1;

	RefreshTVButtons();
}
//---------------------------------------------------------------------------
void __fastcall TTVResolutionListForm::TVListBoxDoubleClick(TObject *Sender)
{
	TVListBox->ItemIndex = TVLastClickedItemIndex;
	RefreshTVButtons();

	if (TVResolutionList->EditPossible(TVListBox->ItemIndex))
		TVEditButtonClick(TVListBox);

	TVLastItemIndex = -1;
}
//---------------------------------------------------------------------------
void __fastcall TTVResolutionListForm::TVListBoxSelect(TObject *Sender)
{
	RefreshTVButtons();
}
//---------------------------------------------------------------------------
void __fastcall TTVResolutionListForm::TVAddButtonClick(TObject *Sender)
{
	TVResolutionClass TVResolution;
	TTVResolutionForm *TVResolutionForm = new TTVResolutionForm(this);

	TVResolutionForm->Connect(TVResolution);

	if (TVResolutionForm->ShowModal() == mrOk)
	{
		TVResolutionList->Add(TVResolution);
		Refresh(TVGroupBox, TVResolutionList->GetCount() - 1);
	}

	delete TVResolutionForm;
}
//---------------------------------------------------------------------------
void __fastcall TTVResolutionListForm::TVEditButtonClick(TObject *Sender)
{
	TVResolutionClass TVResolution;
	TTVResolutionForm *TVResolutionForm = new TTVResolutionForm(this);

	TVResolutionList->Get(TVListBox->ItemIndex, TVResolution);
	TVResolutionForm->Connect(TVResolution);

	if (TVResolutionForm->ShowModal() == mrOk)
	{
		TVResolutionList->Set(TVListBox->ItemIndex, TVResolution);
		Refresh(TVGroupBox, TVListBox->ItemIndex);
	}

	delete TVResolutionForm;
}
//---------------------------------------------------------------------------
void __fastcall TTVResolutionListForm::TVDeleteButtonClick(TObject *Sender)
{
	TVResolutionList->Delete(TVListBox->ItemIndex);

	if (TVListBox->ItemIndex >= TVResolutionList->GetCount())
		TVListBox->ItemIndex = -1;

	Refresh(TVGroupBox, TVListBox->ItemIndex);
}
//---------------------------------------------------------------------------
void __fastcall TTVResolutionListForm::TVDeleteAllButtonClick(TObject *Sender)
{
	TVResolutionList->DeleteAll();
	Refresh(TVGroupBox, -1);
}
//---------------------------------------------------------------------------
void __fastcall TTVResolutionListForm::TVResetButtonClick(TObject *Sender)
{
	TVResolutionList->Undo();
	Refresh(TVGroupBox, -1);
}
//---------------------------------------------------------------------------
void __fastcall TTVResolutionListForm::TVUpButtonClick(TObject *Sender)
{
	TVResolutionList->Exchange(TVListBox->ItemIndex, TVListBox->ItemIndex - 1);
	Refresh(TVGroupBox, TVListBox->ItemIndex - 1);
}
//---------------------------------------------------------------------------
void __fastcall TTVResolutionListForm::TVDownButtonClick(TObject *Sender)
{
	TVResolutionList->Exchange(TVListBox->ItemIndex, TVListBox->ItemIndex + 1);
	Refresh(TVGroupBox, TVListBox->ItemIndex + 1);
}
//---------------------------------------------------------------------------
