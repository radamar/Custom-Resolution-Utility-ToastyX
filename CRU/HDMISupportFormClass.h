//---------------------------------------------------------------------------
#ifndef HDMISupportFormClassH
#define HDMISupportFormClassH
//---------------------------------------------------------------------------
#include "CommonFormClass.h"
#include "HDMISupportClass.h"
#include "ColorFormatListClass.h"
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class THDMISupportForm : public TCommonForm
{
__published:	// IDE-managed Components
	TLabel *PhysicalAddressLabel;
	TLabel *TMDSClockLabel;
	TLabel *VideoLatencyLabel;
	TLabel *AudioLatencyLabel;
	TLabel *InterlacedVideoLatencyLabel;
	TLabel *InterlacedAudioLatencyLabel;
	TGroupBox *PhysicalAddressGroupBox;
	TEdit *PhysicalAddress;
	TGroupBox *ColorFormatsGroupBox;
	TCheckBox *YCbCr422;
	TCheckBox *YCbCr444;
	TCheckBox *DeepColorYCbCr444;
	TCheckBox *DeepColor30bit;
	TCheckBox *DeepColor36bit;
	TCheckBox *DeepColor48bit;
	TGroupBox *FeaturesGroupBox;
	TCheckBox *SupportsAI;
	TCheckBox *DualLinkDVI;
	TGroupBox *TMDSClockGroupBox;
	TCheckBox *OverrideTMDSClock;
	TEdit *TMDSClock;
	TGroupBox *ContentTypesGroupBox;
	TCheckBox *ContentType0;
	TCheckBox *ContentType1;
	TCheckBox *ContentType2;
	TCheckBox *ContentType3;
	TGroupBox *LatencyGroupBox;
	TCheckBox *IncludeLatency;
	TCheckBox *VideoSupported;
	TEdit *VideoLatency;
	TCheckBox *AudioSupported;
	TEdit *AudioLatency;
	TCheckBox *IncludeInterlacedLatency;
	TCheckBox *InterlacedVideoSupported;
	TEdit *InterlacedVideoLatency;
	TCheckBox *InterlacedAudioSupported;
	TEdit *InterlacedAudioLatency;
	TGroupBox *HDMIResolutionsGroupBox;
	TListBox *HDMIResolutionsListBox;
	TButton *HDMIResolutionsAddButton;
	TButton *HDMIResolutionsEditButton;
	TButton *HDMIResolutionsDeleteButton;
	TButton *HDMIResolutionsDeleteAllButton;
	TButton *HDMIResolutionsResetButton;
	TBitBtn *HDMIResolutionsUpButton;
	TBitBtn *HDMIResolutionsDownButton;
	TButton *FormOKButton;
	TButton *FormCancelButton;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall PhysicalAddressChange(TObject *Sender);
	void __fastcall PhysicalAddressExit(TObject *Sender);
	void __fastcall YCbCr422Click(TObject *Sender);
	void __fastcall YCbCr444Click(TObject *Sender);
	void __fastcall DeepColorYCbCr444Click(TObject *Sender);
	void __fastcall DeepColor30bitClick(TObject *Sender);
	void __fastcall DeepColor36bitClick(TObject *Sender);
	void __fastcall DeepColor48bitClick(TObject *Sender);
	void __fastcall SupportsAIClick(TObject *Sender);
	void __fastcall DualLinkDVIClick(TObject *Sender);
	void __fastcall OverrideTMDSClockClick(TObject *Sender);
	void __fastcall TMDSClockChange(TObject *Sender);
	void __fastcall TMDSClockExit(TObject *Sender);
	void __fastcall ContentTypeClick(TObject *Sender);
	void __fastcall IncludeLatencyClick(TObject *Sender);
	void __fastcall VideoSupportedClick(TObject *Sender);
	void __fastcall VideoLatencyChange(TObject *Sender);
	void __fastcall VideoLatencyExit(TObject *Sender);
	void __fastcall AudioSupportedClick(TObject *Sender);
	void __fastcall AudioLatencyChange(TObject *Sender);
	void __fastcall AudioLatencyExit(TObject *Sender);
	void __fastcall IncludeInterlacedLatencyClick(TObject *Sender);
	void __fastcall InterlacedVideoSupportedClick(TObject *Sender);
	void __fastcall InterlacedVideoLatencyChange(TObject *Sender);
	void __fastcall InterlacedVideoLatencyExit(TObject *Sender);
	void __fastcall InterlacedAudioSupportedClick(TObject *Sender);
	void __fastcall InterlacedAudioLatencyChange(TObject *Sender);
	void __fastcall InterlacedAudioLatencyExit(TObject *Sender);
	void __fastcall HDMIResolutionsListBoxDrawItem(TWinControl *Control, int Index, TRect &Rect, TOwnerDrawState State);
	void __fastcall HDMIResolutionsListBoxClick(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall HDMIResolutionsListBoxDblClick(TObject *Sender);
	void __fastcall HDMIResolutionsListBoxSelect(TObject *Sender);
	void __fastcall HDMIResolutionsAddButtonClick(TObject *Sender);
	void __fastcall HDMIResolutionsEditButtonClick(TObject *Sender);
	void __fastcall HDMIResolutionsDeleteButtonClick(TObject *Sender);
	void __fastcall HDMIResolutionsDeleteAllButtonClick(TObject *Sender);
	void __fastcall HDMIResolutionsResetButtonClick(TObject *Sender);
	void __fastcall HDMIResolutionsUpButtonClick(TObject *Sender);
	void __fastcall HDMIResolutionsDownButtonClick(TObject *Sender);
private:	// User declarations
	HDMISupportClass *HDMISupport;
	ColorFormatListClass *ColorFormatList;
	bool Refreshing;
	int HDMIResolutionsLastItemIndex;
	int HDMIResolutionsLastClickedItemIndex;
public:		// User declarations
	__fastcall THDMISupportForm(TComponent *Owner);
	bool Connect(HDMISupportClass &, ColorFormatListClass &);
	TColor GetTextColor(bool);
	TColor GetColor(bool);
	bool Refresh(void *, int);
	bool RefreshPhysicalAddressTextBox();
	bool RefreshColorFormatsCaption();
	bool RefreshColorFormatsCheckBoxes();
	bool RefreshFeaturesCaption();
	bool RefreshFeaturesCheckBoxes();
	bool RefreshTMDSClockCaption();
	bool RefreshTMDSClockCheckBox();
	bool RefreshTMDSClockTextBox();
	bool RefreshContentTypesCaption();
	bool RefreshContentTypesCheckBoxes();
	bool RefreshLatencyCaption();
	bool RefreshLatencyCheckBoxes();
	bool RefreshLatencyTextBoxes();
	bool RefreshHDMIResolutionsCaption();
	bool RefreshHDMIResolutionsListBox(int);
	bool RefreshHDMIResolutionsButtons();
	bool ScaleControls();
};
//---------------------------------------------------------------------------
extern PACKAGE THDMISupportForm *HDMISupportForm;
//---------------------------------------------------------------------------
#endif
