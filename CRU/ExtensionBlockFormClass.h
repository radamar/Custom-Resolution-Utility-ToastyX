//---------------------------------------------------------------------------
#ifndef ExtensionBlockFormClassH
#define ExtensionBlockFormClassH
//---------------------------------------------------------------------------
#include "CommonFormClass.h"
#include "ExtensionBlockClass.h"
#include "DetailedResolutionClass.h"
#include "PropertiesClass.h"
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TExtensionBlockForm : public TCommonForm
{
__published:	// IDE-managed Components
	TLabel *ExtensionTypeLabel;
	TComboBox *ExtensionTypeComboBox;
	TButton *ExtensionCopyButton;
	TButton *ExtensionPasteButton;
	TButton *ExtensionResetButton;
	TGroupBox *DetailedGroupBox;
	TListBox *DetailedListBox;
	TButton *DetailedAddButton;
	TButton *DetailedEditButton;
	TButton *DetailedDeleteButton;
	TButton *DetailedDeleteAllButton;
	TButton *DetailedResetButton;
	TBitBtn *DetailedUpButton;
	TBitBtn *DetailedDownButton;
	TGroupBox *CEADataGroupBox;
	TListBox *CEADataListBox;
	TButton *CEADataAddButton;
	TButton *CEADataEditButton;
	TButton *CEADataDeleteButton;
	TButton *CEADataDeleteAllButton;
	TButton *CEADataResetButton;
	TBitBtn *CEADataUpButton;
	TBitBtn *CEADataDownButton;
	TGroupBox *StandardGroupBox;
	TListBox *StandardListBox;
	TButton *StandardAddButton;
	TButton *StandardEditButton;
	TButton *StandardDeleteButton;
	TButton *StandardDeleteAllButton;
	TButton *StandardResetButton;
	TBitBtn *StandardUpButton;
	TBitBtn *StandardDownButton;
	TButton *FormOKButton;
	TButton *FormCancelButton;
	TShape *DefaultOutline;
	TGroupBox *DIDDataGroupBox;
	TListBox *DIDDataListBox;
	TButton *DIDDataAddButton;
	TButton *DIDDataEditButton;
	TButton *DIDDataDeleteButton;
	TButton *DIDDataDeleteAllButton;
	TButton *DIDDataResetButton;
	TBitBtn *DIDDataUpButton;
	TBitBtn *DIDDataDownButton;
	TLabel *DefaultLabel;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall ExtensionTypeComboBoxChange(TObject *Sender);
	void __fastcall ExtensionCopyButtonClick(TObject *Sender);
	void __fastcall ExtensionPasteButtonClick(TObject *Sender);
	void __fastcall ExtensionResetButtonClick(TObject *Sender);
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
	void __fastcall CEADataListBoxDrawItem(TWinControl *Control, int Index, TRect &Rect, TOwnerDrawState State);
	void __fastcall CEADataListBoxClick(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall CEADataListBoxDoubleClick(TObject *Sender);
	void __fastcall CEADataListBoxSelect(TObject *Sender);
	void __fastcall CEADataAddButtonClick(TObject *Sender);
	void __fastcall CEADataEditButtonClick(TObject *Sender);
	void __fastcall CEADataDeleteButtonClick(TObject *Sender);
	void __fastcall CEADataDeleteAllButtonClick(TObject *Sender);
	void __fastcall CEADataResetButtonClick(TObject *Sender);
	void __fastcall CEADataUpButtonClick(TObject *Sender);
	void __fastcall CEADataDownButtonClick(TObject *Sender);
	void __fastcall StandardListBoxSelect(TObject *Sender);
	void __fastcall StandardListBoxDoubleClick(TObject *Sender);
	void __fastcall StandardListBoxClick(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall StandardListBoxDrawItem(TWinControl *Control, int Index, TRect &Rect, TOwnerDrawState State);
	void __fastcall StandardAddButtonClick(TObject *Sender);
	void __fastcall StandardEditButtonClick(TObject *Sender);
	void __fastcall StandardDeleteButtonClick(TObject *Sender);
	void __fastcall StandardDeleteAllButtonClick(TObject *Sender);
	void __fastcall StandardResetButtonClick(TObject *Sender);
	void __fastcall StandardUpButtonClick(TObject *Sender);
	void __fastcall StandardDownButtonClick(TObject *Sender);
	void __fastcall DIDDataListBoxDrawItem(TWinControl *Control, int Index, TRect &Rect, TOwnerDrawState State);
	void __fastcall DIDDataListBoxClick(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall DIDDataListBoxDoubleClick(TObject *Sender);
	void __fastcall DIDDataListBoxSelect(TObject *Sender);
	void __fastcall DIDDataAddButtonClick(TObject *Sender);
	void __fastcall DIDDataEditButtonClick(TObject *Sender);
	void __fastcall DIDDataDeleteButtonClick(TObject *Sender);
	void __fastcall DIDDataDeleteAllButtonClick(TObject *Sender);
	void __fastcall DIDDataResetButtonClick(TObject *Sender);
	void __fastcall DIDDataUpButtonClick(TObject *Sender);
	void __fastcall DIDDataDownButtonClick(TObject *Sender);
private:	// User declarations
	ExtensionBlockClass *ExtensionBlock;
	DetailedResolutionClass NativeResolution;
	PropertiesClass Properties;
	bool Refreshing;
	int DetailedLastItemIndex;
	int DetailedLastClickedItemIndex;
	int CEADataLastItemIndex;
	int CEADataLastClickedItemIndex;
	int StandardLastItemIndex;
	int StandardLastClickedItemIndex;
	int DIDDataLastItemIndex;
	int DIDDataLastClickedItemIndex;
public:		// User declarations
	__fastcall TExtensionBlockForm(TComponent *Owner);
	bool Connect(ExtensionBlockClass &, const DetailedResolutionClass &, const PropertiesClass &);
	bool Refresh(void *, int);
	bool InitExtensionTypeComboBox();
	bool RefreshExtensionTypeComboBox();
	bool RefreshExtensionButtons();
	bool RefreshDetailedCaption();
	bool RefreshDetailedListBox(int);
	bool RefreshDetailedButtons();
	bool RefreshCEADataCaption();
	bool RefreshCEADataListBox(int);
	bool RefreshCEADataButtons();
	bool RefreshStandardCaption();
	bool RefreshStandardListBox(int);
	bool RefreshStandardButtons();
	bool RefreshDIDDataCaption();
	bool RefreshDIDDataListBox(int);
	bool RefreshDIDDataButtons();
	bool ScaleControls();
	bool CEADataAddTVResolutions();
	bool CEADataEditTVResolutions(int);
	bool CEADataAddAudioFormats();
	bool CEADataEditAudioFormats(int);
	bool CEADataAddSpeakerSetup();
	bool CEADataEditSpeakerSetup(int);
	bool CEADataAddHDMISupport();
	bool CEADataEditHDMISupport(int);
	bool CEADataAddHDMI2Support();
	bool CEADataEditHDMI2Support(int);
	bool CEADataAddFreeSyncRange();
	bool CEADataEditFreeSyncRange(int);
	bool CEADataAddColorimetry();
	bool CEADataEditColorimetry(int);
	bool CEADataAddVideoCapability();
	bool CEADataEditVideoCapability(int);
	bool CEADataAdd(int);
	bool CEADataEdit(int);
	bool DIDDataAddDetailedResolutions();
	bool DIDDataEditDetailedResolutions(int);
	bool DIDDataAddTiledDisplayTopology();
	bool DIDDataEditTiledDisplayTopology(int);
	bool DIDDataAdd(int);
	bool DIDDataEdit(int);
};
//---------------------------------------------------------------------------
extern PACKAGE TExtensionBlockForm *ExtensionBlockForm;
//---------------------------------------------------------------------------
#endif
