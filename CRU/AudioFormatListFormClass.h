//---------------------------------------------------------------------------
#ifndef AudioFormatListFormClassH
#define AudioFormatListFormClassH
//---------------------------------------------------------------------------
#include "CommonFormClass.h"
#include "AudioFormatListClass.h"
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TAudioFormatListForm : public TCommonForm
{
__published:	// IDE-managed Components
	TGroupBox *AudioGroupBox;
	TListBox *AudioListBox;
	TButton *AudioAddButton;
	TButton *AudioEditButton;
	TButton *AudioDeleteButton;
	TButton *AudioDeleteAllButton;
	TButton *AudioResetButton;
	TBitBtn *AudioUpButton;
	TBitBtn *AudioDownButton;
	TButton *FormOKButton;
	TButton *FormCancelButton;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall AudioListBoxDrawItem(TWinControl *Control, int Index, TRect &Rect, TOwnerDrawState State);
	void __fastcall AudioListBoxClick(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall AudioListBoxDoubleClick(TObject *Sender);
	void __fastcall AudioListBoxSelect(TObject *Sender);
	void __fastcall AudioAddButtonClick(TObject *Sender);
	void __fastcall AudioEditButtonClick(TObject *Sender);
	void __fastcall AudioDeleteButtonClick(TObject *Sender);
	void __fastcall AudioDeleteAllButtonClick(TObject *Sender);
	void __fastcall AudioResetButtonClick(TObject *Sender);
	void __fastcall AudioUpButtonClick(TObject *Sender);
	void __fastcall AudioDownButtonClick(TObject *Sender);
private:	// User declarations
	AudioFormatListClass *AudioFormatList;
	bool Refreshing;
	int AudioLastItemIndex;
	int AudioLastClickedItemIndex;
public:		// User declarations
	__fastcall TAudioFormatListForm(TComponent *Owner);
	bool Connect(AudioFormatListClass &);
	bool Refresh(void *, int);
	bool RefreshAudioCaption();
	bool RefreshAudioListBox(int);
	bool RefreshAudioButtons();
	bool ScaleControls();
};
//---------------------------------------------------------------------------
extern PACKAGE TAudioFormatListForm *AudioFormatListForm;
//---------------------------------------------------------------------------
#endif
