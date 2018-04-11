//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "DIDDetailedResolutionListFormClass.h"
#include "DetailedResolutionFormClass.h"
#include "Common.h"
#include <cstdio>
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TDIDDetailedResolutionListForm *DIDDetailedResolutionListForm;
//---------------------------------------------------------------------------
__fastcall TDIDDetailedResolutionListForm::TDIDDetailedResolutionListForm(TComponent *Owner) : TCommonForm(Owner)
{
	Refreshing = false;
	DetailedLastItemIndex = -1;
	DetailedLastClickedItemIndex = -1;
}
//---------------------------------------------------------------------------
bool TDIDDetailedResolutionListForm::Connect(DIDDetailedResolutionListClass &NewDIDDetailedResolutionList, const DetailedResolutionClass &NewNativeResolution)
{
	DIDDetailedResolutionList = &NewDIDDetailedResolutionList;
	NativeResolution = NewNativeResolution;
	NativeResolution.SetType(1);
	return true;
}
//---------------------------------------------------------------------------
bool TDIDDetailedResolutionListForm::Refresh(void *Value, int ItemIndex)
{
	Refreshing = true;

	if (Value == NULL || Value == DetailedGroupBox)
	{
		RefreshDetailedCaption();
		RefreshDetailedListBox(ItemIndex);
		RefreshDetailedButtons();
	}

	Refreshing = false;
	return true;
}
//---------------------------------------------------------------------------
bool TDIDDetailedResolutionListForm::RefreshDetailedCaption()
{
	const char *Caption = " Detailed resolutions ";
	char Text[TEXTSIZE];

	DIDDetailedResolutionList->GetSlotsLeftText(Caption, Text, TEXTSIZE);
	DetailedGroupBox->Caption = Text;
	return true;
}
//---------------------------------------------------------------------------
bool TDIDDetailedResolutionListForm::RefreshDetailedListBox(int ItemIndex)
{
	int Index;
	DetailedResolutionClass DetailedResolution(1);
	char Text[TEXTSIZE];

	if (DIDDetailedResolutionList->GetMaxCount() > 0)
	{
		DetailedListBox->Enabled = true;
		DetailedListBox->Color = clWindow;
		DetailedListBox->Font->Color = clWindowText;
	}
	else
	{
		DetailedListBox->Enabled = false;
		DetailedListBox->Color = clBtnFace;
		DetailedListBox->Font->Color = clGrayText;
		ItemIndex = -1;
	}

	DetailedListBox->Clear();
	DetailedListBox->Items->BeginUpdate();

	for (Index = 0; DIDDetailedResolutionList->Get(Index, DetailedResolution); Index++)
		if (DetailedResolution.GetText(Text, TEXTSIZE))
			DetailedListBox->Items->Add(Text);

	if (Index == 0)
		DetailedListBox->Items->Add("No detailed resolutions");

	DetailedListBox->ItemIndex = ItemIndex;
	DetailedListBox->Items->EndUpdate();
	return true;
}
//---------------------------------------------------------------------------
bool TDIDDetailedResolutionListForm::RefreshDetailedButtons()
{
	DetailedLastItemIndex = DetailedListBox->ItemIndex;
	DetailedAddButton->Enabled = DIDDetailedResolutionList->AddPossible();
	DetailedEditButton->Enabled = DIDDetailedResolutionList->EditPossible(DetailedListBox->ItemIndex);
	DetailedDeleteButton->Enabled = DIDDetailedResolutionList->DeletePossible(DetailedListBox->ItemIndex);
	DetailedDeleteAllButton->Enabled = DIDDetailedResolutionList->DeleteAllPossible();
	DetailedResetButton->Enabled = DIDDetailedResolutionList->UndoPossible();
	DetailedUpButton->Enabled = DIDDetailedResolutionList->ExchangePossible(DetailedListBox->ItemIndex, DetailedListBox->ItemIndex - 1);
	DetailedDownButton->Enabled = DIDDetailedResolutionList->ExchangePossible(DetailedListBox->ItemIndex, DetailedListBox->ItemIndex + 1);
	return true;
}
//---------------------------------------------------------------------------
bool TDIDDetailedResolutionListForm::ScaleControls()
{
	DetailedListBox->Width = ListBoxWidth;
	DetailedListBox->Height = Text.tmHeight * 5 + 4;
	DetailedListBox->ItemHeight = Text.tmHeight;
	DetailedListBox->Left = PaddingWidth;
	DetailedListBox->Top = PaddingTop;

	DetailedAddButton->Width = ButtonWidth;
	DetailedAddButton->Height = ButtonHeight;
	DetailedAddButton->Left = DetailedListBox->Left + ButtonLeft;
	DetailedAddButton->Top = DetailedListBox->Top + DetailedListBox->Height + Scale + ButtonTop;
	Common::FixButtonCaption(DetailedAddButton, Canvas->TextWidth(DetailedAddButton->Caption));

	DetailedEditButton->Width = ButtonWidth;
	DetailedEditButton->Height = ButtonHeight;
	DetailedEditButton->Left = DetailedAddButton->Left + DetailedAddButton->Width;
	DetailedEditButton->Top = DetailedAddButton->Top;
	Common::FixButtonCaption(DetailedEditButton, Canvas->TextWidth(DetailedEditButton->Caption));

	DetailedDeleteButton->Width = ButtonWidth;
	DetailedDeleteButton->Height = ButtonHeight;
	DetailedDeleteButton->Left = DetailedEditButton->Left + DetailedEditButton->Width;
	DetailedDeleteButton->Top = DetailedEditButton->Top;
	Common::FixButtonCaption(DetailedDeleteButton, Canvas->TextWidth(DetailedDeleteButton->Caption));

	DetailedDeleteAllButton->Width = LongButtonWidth;
	DetailedDeleteAllButton->Height = LongButtonHeight;
	DetailedDeleteAllButton->Left = DetailedDeleteButton->Left + DetailedDeleteButton->Width;
	DetailedDeleteAllButton->Top = DetailedDeleteButton->Top;
	Common::FixButtonCaption(DetailedDeleteAllButton, Canvas->TextWidth(DetailedDeleteAllButton->Caption));

	DetailedResetButton->Width = ButtonWidth;
	DetailedResetButton->Height = ButtonHeight;
	DetailedResetButton->Left = DetailedDeleteAllButton->Left + DetailedDeleteAllButton->Width;
	DetailedResetButton->Top = DetailedDeleteAllButton->Top;
	Common::FixButtonCaption(DetailedResetButton, Canvas->TextWidth(DetailedResetButton->Caption));

	DetailedUpButton->Width = ArrowButtonWidth;
	DetailedUpButton->Height = ArrowButtonHeight;
	DetailedUpButton->Top = DetailedResetButton->Top;
	DetailedUpButton->Enabled = false;
	DetailedUpButton->NumGlyphs = NumGlyphs;
	DetailedUpButton->Glyph->LoadFromResourceID(0, Common::GetScaledResourceID(ARROW_UP));

	DetailedDownButton->Width = ArrowButtonWidth;
	DetailedDownButton->Height = ArrowButtonHeight;
	DetailedDownButton->Top = DetailedUpButton->Top;
	DetailedDownButton->Enabled = false;
	DetailedDownButton->NumGlyphs = NumGlyphs;
	DetailedDownButton->Glyph->LoadFromResourceID(0, Common::GetScaledResourceID(ARROW_DOWN));

	DetailedDownButton->Left = DetailedListBox->Left + DetailedListBox->Width - ButtonRight - DetailedDownButton->Width;
	DetailedUpButton->Left = DetailedDownButton->Left - DetailedUpButton->Width;

	DetailedGroupBox->Width = DetailedListBox->Left + DetailedListBox->Width + PaddingWidth;
	DetailedGroupBox->Height = DetailedAddButton->Top + DetailedAddButton->Height + ButtonBottom + PaddingBottom;
	DetailedGroupBox->Left = Scale;
	DetailedGroupBox->Top = GroupBoxTop;

	FormOKButton->Width = FormButtonWidth;
	FormOKButton->Height = FormButtonHeight;
	FormOKButton->Top = DetailedGroupBox->Top + DetailedGroupBox->Height + GroupBoxBottom + Scale + ButtonTop;
	Common::FixButtonCaption(FormOKButton, Canvas->TextWidth(FormOKButton->Caption));

	FormCancelButton->Width = FormButtonWidth;
	FormCancelButton->Height = FormButtonHeight;
	FormCancelButton->Top = FormOKButton->Top;
	Common::FixButtonCaption(FormCancelButton, Canvas->TextWidth(FormCancelButton->Caption));

	FormCancelButton->Left = DetailedGroupBox->Left + DetailedGroupBox->Width - ButtonRight - FormCancelButton->Width;
	FormOKButton->Left = FormCancelButton->Left - ButtonLeft - Scale - ButtonRight - FormOKButton->Width;

	ClientWidth = FormCancelButton->Left + FormCancelButton->Width + ButtonRight + Scale;
	ClientHeight = FormCancelButton->Top + FormCancelButton->Height + ButtonBottom + Scale;
	return true;
}
//---------------------------------------------------------------------------
void __fastcall TDIDDetailedResolutionListForm::FormCreate(TObject *Sender)
{
	ScaleControls();
}
//---------------------------------------------------------------------------
void __fastcall TDIDDetailedResolutionListForm::FormShow(TObject *Sender)
{
	Refresh(NULL, -1);
}
//---------------------------------------------------------------------------
void __fastcall TDIDDetailedResolutionListForm::DetailedListBoxDrawItem(TWinControl *Control, int Index, TRect &Rect, TOwnerDrawState State)
{
	Common::ListBoxDrawItem(DetailedListBox, Rect, State, DetailedListBox->Items->Strings[Index].c_str(), DIDDetailedResolutionList->EditPossible(Index), false);
}
//---------------------------------------------------------------------------
void __fastcall TDIDDetailedResolutionListForm::DetailedListBoxClick(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
	DetailedLastClickedItemIndex = DetailedListBox->ItemIndex;

	if (DetailedListBox->ItemIndex == DetailedLastItemIndex)
		DetailedListBox->ItemIndex = -1;

	RefreshDetailedButtons();
}
//---------------------------------------------------------------------------
void __fastcall TDIDDetailedResolutionListForm::DetailedListBoxDoubleClick(TObject *Sender)
{
	DetailedListBox->ItemIndex = DetailedLastClickedItemIndex;
	RefreshDetailedButtons();

	if (DIDDetailedResolutionList->EditPossible(DetailedListBox->ItemIndex))
		DetailedEditButtonClick(DetailedListBox);

	DetailedLastItemIndex = -1;
}
//---------------------------------------------------------------------------
void __fastcall TDIDDetailedResolutionListForm::DetailedListBoxSelect(TObject *Sender)
{
	RefreshDetailedButtons();
}
//---------------------------------------------------------------------------
void __fastcall TDIDDetailedResolutionListForm::DetailedAddButtonClick(TObject *Sender)
{
	DetailedResolutionClass DetailedResolution(1);
	TDetailedResolutionForm *DetailedResolutionForm = new TDetailedResolutionForm(this);

	DetailedResolution = NativeResolution;
	DetailedResolutionForm->Connect(DetailedResolution);

	if (DetailedResolutionForm->ShowModal() == mrOk)
	{
		DIDDetailedResolutionList->Add(DetailedResolution);
		Refresh(DetailedGroupBox, DIDDetailedResolutionList->GetCount() - 1);
	}

	delete DetailedResolutionForm;
}
//---------------------------------------------------------------------------
void __fastcall TDIDDetailedResolutionListForm::DetailedEditButtonClick(TObject *Sender)
{
	DetailedResolutionClass DetailedResolution(1);
	TDetailedResolutionForm *DetailedResolutionForm = new TDetailedResolutionForm(this);

	DIDDetailedResolutionList->Get(DetailedListBox->ItemIndex, DetailedResolution);
	DetailedResolutionForm->Connect(DetailedResolution);

	if (DetailedResolutionForm->ShowModal() == mrOk)
	{
		DIDDetailedResolutionList->Set(DetailedListBox->ItemIndex, DetailedResolution);
		Refresh(DetailedGroupBox, DetailedListBox->ItemIndex);
	}

	delete DetailedResolutionForm;
}
//---------------------------------------------------------------------------
void __fastcall TDIDDetailedResolutionListForm::DetailedDeleteButtonClick(TObject *Sender)
{
	DIDDetailedResolutionList->Delete(DetailedListBox->ItemIndex);

	if (DetailedListBox->ItemIndex >= DIDDetailedResolutionList->GetCount())
		DetailedListBox->ItemIndex = -1;

	Refresh(DetailedGroupBox, DetailedListBox->ItemIndex);
}
//---------------------------------------------------------------------------
void __fastcall TDIDDetailedResolutionListForm::DetailedDeleteAllButtonClick(TObject *Sender)
{
	DIDDetailedResolutionList->DeleteAll();
	Refresh(DetailedGroupBox, -1);
}
//---------------------------------------------------------------------------
void __fastcall TDIDDetailedResolutionListForm::DetailedResetButtonClick(TObject *Sender)
{
	DIDDetailedResolutionList->Undo();
	Refresh(DetailedGroupBox, -1);
}
//---------------------------------------------------------------------------
void __fastcall TDIDDetailedResolutionListForm::DetailedUpButtonClick(TObject *Sender)
{
	DIDDetailedResolutionList->Exchange(DetailedListBox->ItemIndex, DetailedListBox->ItemIndex - 1);
	Refresh(DetailedGroupBox, DetailedListBox->ItemIndex - 1);
}
//---------------------------------------------------------------------------
void __fastcall TDIDDetailedResolutionListForm::DetailedDownButtonClick(TObject *Sender)
{
	DIDDetailedResolutionList->Exchange(DetailedListBox->ItemIndex, DetailedListBox->ItemIndex + 1);
	Refresh(DetailedGroupBox, DetailedListBox->ItemIndex + 1);
}
//---------------------------------------------------------------------------
