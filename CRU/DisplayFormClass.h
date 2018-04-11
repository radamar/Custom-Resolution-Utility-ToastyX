//---------------------------------------------------------------------------
#ifndef DisplayFormClassH
#define DisplayFormClassH
//---------------------------------------------------------------------------
#include "CommonFormClass.h"
#include "DisplayListClass.h"
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TDisplayForm : public TCommonForm
{
__published:	// IDE-managed Components
	TLabel *EstablishedLabel1;
	TLabel *EstablishedLabel2;
	TLabel *EstablishedLabel3;
	TLabel *EstablishedLabel4;
	TComboBox *DisplayComboBox;
	TButton *DisplayEditButton;
	TButton *DisplayCopyButton;
	TButton *DisplayPasteButton;
	TButton *DisplayDeleteButton;
	TGroupBox *EstablishedGroupBox;
	TCheckBox *EstablishedCheckBox2;
	TCheckBox *EstablishedCheckBox4;
	TCheckBox *EstablishedCheckBox5;
	TCheckBox *EstablishedCheckBox6;
	TCheckBox *EstablishedCheckBox7;
	TCheckBox *EstablishedCheckBox8;
	TCheckBox *EstablishedCheckBox9;
	TCheckBox *EstablishedCheckBox12;
	TCheckBox *EstablishedCheckBox13;
	TCheckBox *EstablishedCheckBox14;
	TCheckBox *EstablishedCheckBox15;
	TButton *EstablishedAllButton;
	TButton *EstablishedNoneButton;
	TButton *EstablishedResetButton;
	TGroupBox *DetailedGroupBox;
	TListBox *DetailedListBox;
	TButton *DetailedAddButton;
	TButton *DetailedEditButton;
	TButton *DetailedDeleteButton;
	TButton *DetailedDeleteAllButton;
	TButton *DetailedResetButton;
	TBitBtn *DetailedUpButton;
	TBitBtn *DetailedDownButton;
	TGroupBox *StandardGroupBox;
	TListBox *StandardListBox;
	TButton *StandardAddButton;
	TButton *StandardEditButton;
	TButton *StandardDeleteButton;
	TButton *StandardDeleteAllButton;
	TButton *StandardResetButton;
	TBitBtn *StandardUpButton;
	TBitBtn *StandardDownButton;
	TButton *DisplayImportButton;
	TButton *DisplayExportButton;
	TGroupBox *ExtensionGroupBox;
	TListBox *ExtensionListBox;
	TButton *ExtensionAddButton;
	TButton *ExtensionEditButton;
	TButton *ExtensionDeleteButton;
	TButton *ExtensionDeleteAllButton;
	TButton *ExtensionResetButton;
	TBitBtn *ExtensionUpButton;
	TBitBtn *ExtensionDownButton;
	TButton *FormOKButton;
	TButton *FormCancelButton;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall DisplayComboBoxChange(TObject *Sender);
	void __fastcall DisplayEditButtonClick(TObject *Sender);
	void __fastcall DisplayCopyButtonClick(TObject *Sender);
	void __fastcall DisplayPasteButtonClick(TObject *Sender);
	void __fastcall DisplayDeleteButtonClick(TObject *Sender);
	void __fastcall EstablishedCheckBoxClick(TObject *Sender);
	void __fastcall EstablishedAllButtonClick(TObject *Sender);
	void __fastcall EstablishedNoneButtonClick(TObject *Sender);
	void __fastcall EstablishedResetButtonClick(TObject *Sender);
	void __fastcall DetailedListBoxDrawItem(TWinControl *Control, int Index, TRect &Rect, TOwnerDrawState State);
	void __fastcall DetailedListBoxClick(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall DetailedListBoxDoubleClick(TObject *Sender);
	void __fastcall DetailedListBoxSelect(TObject *Sender);
	void __fastcall DetailedAddButtonClick(TObject *Sender);
	void __fastcall DetailedEditButtonClick(TObject *Sender);
	void __fastcall DetailedDeleteButtonClick(TObject *Sender);
	void __fastcall DetailedDeleteAllButtonClick(TObject *Sender);
	void __fastcall DetailedResetButtonClick(TObject *Sender);
	void __fastcall DetailedUpButtonClick(TObject *Sender);
	void __fastcall DetailedDownButtonClick(TObject *Sender);
	void __fastcall StandardListBoxDrawItem(TWinControl *Control, int Index, TRect &Rect, TOwnerDrawState State);
	void __fastcall StandardListBoxClick(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall StandardListBoxDoubleClick(TObject *Sender);
	void __fastcall StandardListBoxSelect(TObject *Sender);
	void __fastcall StandardAddButtonClick(TObject *Sender);
	void __fastcall StandardEditButtonClick(TObject *Sender);
	void __fastcall StandardDeleteButtonClick(TObject *Sender);
	void __fastcall StandardDeleteAllButtonClick(TObject *Sender);
	void __fastcall StandardResetButtonClick(TObject *Sender);
	void __fastcall StandardUpButtonClick(TObject *Sender);
	void __fastcall StandardDownButtonClick(TObject *Sender);
	void __fastcall ExtensionListBoxDrawItem(TWinControl *Control, int Index, TRect &Rect, TOwnerDrawState State);
	void __fastcall ExtensionListBoxClick(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall ExtensionListBoxDoubleClick(TObject *Sender);
	void __fastcall ExtensionListBoxSelect(TObject *Sender);
	void __fastcall ExtensionAddButtonClick(TObject *Sender);
	void __fastcall ExtensionEditButtonClick(TObject *Sender);
	void __fastcall ExtensionDeleteButtonClick(TObject *Sender);
	void __fastcall ExtensionDeleteAllButtonClick(TObject *Sender);
	void __fastcall ExtensionResetButtonClick(TObject *Sender);
	void __fastcall ExtensionUpButtonClick(TObject *Sender);
	void __fastcall ExtensionDownButtonClick(TObject *Sender);
	void __fastcall DisplayImportButtonClick(TObject *Sender);
	void __fastcall DisplayExportButtonClick(TObject *Sender);
	void __fastcall FormOKButtonClick(TObject *Sender);
	void __fastcall FormCancelButtonClick(TObject *Sender);
private:	// User declarations
	DisplayListClass DisplayList;
	bool Refreshing;
	int DetailedLastItemIndex;
	int DetailedLastClickedItemIndex;
	int StandardLastItemIndex;
	int StandardLastClickedItemIndex;
	int ExtensionLastItemIndex;
	int ExtensionLastClickedItemIndex;
public:		// User declarations
	__fastcall TDisplayForm(TComponent *Owner);
	void FatalError(const char *);
	bool Refresh(void *, int);
	bool InitDisplayComboBox();
	bool RefreshDisplayComboBox();
	bool RefreshDisplayButtons();
	bool RefreshEstablishedCheckBoxes();
	bool RefreshEstablishedButtons();
	bool RefreshDetailedCaption();
	bool RefreshDetailedListBox(int);
	bool RefreshDetailedButtons();
	bool RefreshStandardCaption();
	bool RefreshStandardListBox(int);
	bool RefreshStandardButtons();
	bool RefreshExtensionCaption();
	bool RefreshExtensionListBox(int);
	bool RefreshExtensionButtons();
	bool RefreshImportExportButtons();
	bool ScaleControls();
};
//---------------------------------------------------------------------------
extern PACKAGE TDisplayForm *DisplayForm;
//---------------------------------------------------------------------------
#endif
