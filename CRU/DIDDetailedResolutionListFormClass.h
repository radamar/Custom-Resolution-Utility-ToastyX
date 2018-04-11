//---------------------------------------------------------------------------
#ifndef DIDDetailedResolutionListFormClassH
#define DIDDetailedResolutionListFormClassH
//---------------------------------------------------------------------------
#include "CommonFormClass.h"
#include "DIDDetailedResolutionListClass.h"
#include "DetailedResolutionClass.h"
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TDIDDetailedResolutionListForm : public TCommonForm
{
__published:	// IDE-managed Components
	TGroupBox *DetailedGroupBox;
	TListBox *DetailedListBox;
	TButton *DetailedAddButton;
	TButton *DetailedEditButton;
	TButton *DetailedDeleteButton;
	TButton *DetailedDeleteAllButton;
	TButton *DetailedResetButton;
	TBitBtn *DetailedUpButton;
	TBitBtn *DetailedDownButton;
	TButton *FormOKButton;
	TButton *FormCancelButton;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
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
private:	// User declarations
	DIDDetailedResolutionListClass *DIDDetailedResolutionList;
	DetailedResolutionClass NativeResolution;
	bool Refreshing;
	int DetailedLastItemIndex;
	int DetailedLastClickedItemIndex;
public:		// User declarations
	__fastcall TDIDDetailedResolutionListForm(TComponent *Owner);
	bool Connect(DIDDetailedResolutionListClass &, const DetailedResolutionClass &);
	bool Refresh(void *, int);
	bool RefreshDetailedCaption();
	bool RefreshDetailedListBox(int);
	bool RefreshDetailedButtons();
	bool ScaleControls();
};
//---------------------------------------------------------------------------
extern PACKAGE TDIDDetailedResolutionListForm *DIDDetailedResolutionListForm;
//---------------------------------------------------------------------------
#endif
