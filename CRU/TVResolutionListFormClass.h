//---------------------------------------------------------------------------
#ifndef TVResolutionListFormClassH
#define TVResolutionListFormClassH
//---------------------------------------------------------------------------
#include "CommonFormClass.h"
#include "TVResolutionListClass.h"
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TTVResolutionListForm : public TCommonForm
{
__published:	// IDE-managed Components
	TCheckBox *YCbCr420;
	TGroupBox *TVGroupBox;
	TListBox *TVListBox;
	TButton *TVAddButton;
	TButton *TVEditButton;
	TButton *TVDeleteButton;
	TButton *TVDeleteAllButton;
	TButton *TVResetButton;
	TBitBtn *TVUpButton;
	TBitBtn *TVDownButton;
	TButton *FormOKButton;
	TButton *FormCancelButton;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall YCbCr420Click(TObject *Sender);
	void __fastcall TVListBoxDrawItem(TWinControl *Control, int Index, TRect &Rect, TOwnerDrawState State);
	void __fastcall TVListBoxClick(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall TVListBoxDoubleClick(TObject *Sender);
	void __fastcall TVListBoxSelect(TObject *Sender);
	void __fastcall TVAddButtonClick(TObject *Sender);
	void __fastcall TVEditButtonClick(TObject *Sender);
	void __fastcall TVDeleteButtonClick(TObject *Sender);
	void __fastcall TVDeleteAllButtonClick(TObject *Sender);
	void __fastcall TVResetButtonClick(TObject *Sender);
	void __fastcall TVUpButtonClick(TObject *Sender);
	void __fastcall TVDownButtonClick(TObject *Sender);
private:	// User declarations
	TVResolutionListClass *TVResolutionList;
	bool Refreshing;
	int TVLastItemIndex;
	int TVLastClickedItemIndex;
public:		// User declarations
	__fastcall TTVResolutionListForm(TComponent *Owner);
	bool Connect(TVResolutionListClass &);
	bool Refresh(void *, int);
	bool RefreshYCbCr420();
	bool RefreshTVCaption();
	bool RefreshTVListBox(int);
	bool RefreshTVButtons();
	bool ScaleControls();
};
//---------------------------------------------------------------------------
extern PACKAGE TTVResolutionListForm *TVResolutionListForm;
//---------------------------------------------------------------------------
#endif
