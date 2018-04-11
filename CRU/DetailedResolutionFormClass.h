//---------------------------------------------------------------------------
#ifndef DetailedResolutionFormClassH
#define DetailedResolutionFormClassH
//---------------------------------------------------------------------------
#include "CommonFormClass.h"
#include "DetailedResolutionClass.h"
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TDetailedResolutionForm : public TCommonForm
{
__published:	// IDE-managed Components
	TLabel *Timing;
	TLabel *Active;
	TLabel *Front;
	TLabel *Sync;
	TLabel *Back;
	TLabel *Blank;
	TLabel *Total;
	TLabel *Polarity;
	TLabel *Horizontal;
	TLabel *ActivePixels;
	TLabel *FrontPixels;
	TLabel *SyncPixels;
	TLabel *BackPixels;
	TLabel *BlankPixels;
	TLabel *TotalPixels;
	TLabel *Vertical;
	TLabel *ActiveLines;
	TLabel *FrontLines;
	TLabel *SyncLines;
	TLabel *BackLines;
	TLabel *BlankLines;
	TLabel *TotalLines;
	TLabel *Rate0;
	TLabel *Rate1;
	TLabel *Rate2;
	TLabel *Hz;
	TLabel *kHz;
	TLabel *MHz;
	TLabel *ActualVRate;
	TLabel *ActualHRate;
	TComboBox *TimingComboBox;
	TButton *TimingCopyButton;
	TButton *TimingPasteButton;
	TButton *TimingResetButton;
	TGroupBox *ParametersGroupBox;
	TRadioButton *Last0;
	TRadioButton *Last1;
	TRadioButton *Last2;
	TEdit *HActive;
	TEdit *HFront;
	TEdit *HSync;
	TEdit *HBack;
	TEdit *HBlank;
	TEdit *HTotal;
	TComboBox *HPolarity;
	TEdit *VActive;
	TEdit *VFront;
	TEdit *VSync;
	TEdit *VBack;
	TEdit *VBlank;
	TEdit *VTotal;
	TComboBox *VPolarity;
	TGroupBox *FrequencyGroupBox;
	TRadioButton *LastRate0;
	TRadioButton *LastRate1;
	TRadioButton *LastRate2;
	TEdit *VRate;
	TEdit *HRate;
	TEdit *PClock;
	TCheckBox *Interlaced;
	TButton *FormOKButton;
	TButton *FormCancelButton;
	TCheckBox *Native;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall TimingComboBoxChange(TObject *Sender);
	void __fastcall TimingCopyButtonClick(TObject *Sender);
	void __fastcall TimingPasteButtonClick(TObject *Sender);
	void __fastcall TimingResetButtonClick(TObject *Sender);
	void __fastcall Last0Click(TObject *Sender);
	void __fastcall Last1Click(TObject *Sender);
	void __fastcall Last2Click(TObject *Sender);
	void __fastcall HActiveChange(TObject *Sender);
	void __fastcall HActiveExit(TObject *Sender);
	void __fastcall HFrontChange(TObject *Sender);
	void __fastcall HFrontExit(TObject *Sender);
	void __fastcall HSyncChange(TObject *Sender);
	void __fastcall HSyncExit(TObject *Sender);
	void __fastcall HBackChange(TObject *Sender);
	void __fastcall HBackExit(TObject *Sender);
	void __fastcall HBlankChange(TObject *Sender);
	void __fastcall HBlankExit(TObject *Sender);
	void __fastcall HTotalChange(TObject *Sender);
	void __fastcall HTotalExit(TObject *Sender);
	void __fastcall HPolarityChange(TObject *Sender);
	void __fastcall VActiveChange(TObject *Sender);
	void __fastcall VActiveExit(TObject *Sender);
	void __fastcall VFrontChange(TObject *Sender);
	void __fastcall VFrontExit(TObject *Sender);
	void __fastcall VSyncChange(TObject *Sender);
	void __fastcall VSyncExit(TObject *Sender);
	void __fastcall VBackChange(TObject *Sender);
	void __fastcall VBackExit(TObject *Sender);
	void __fastcall VBlankChange(TObject *Sender);
	void __fastcall VBlankExit(TObject *Sender);
	void __fastcall VTotalChange(TObject *Sender);
	void __fastcall VTotalExit(TObject *Sender);
	void __fastcall VPolarityChange(TObject *Sender);
	void __fastcall LastRate0Click(TObject *Sender);
	void __fastcall LastRate1Click(TObject *Sender);
	void __fastcall LastRate2Click(TObject *Sender);
	void __fastcall VRateChange(TObject *Sender);
	void __fastcall VRateExit(TObject *Sender);
	void __fastcall HRateChange(TObject *Sender);
	void __fastcall HRateExit(TObject *Sender);
	void __fastcall PClockChange(TObject *Sender);
	void __fastcall PClockExit(TObject *Sender);
	void __fastcall InterlacedClick(TObject *Sender);
	void __fastcall NativeClick(TObject *Sender);
private:	// User declarations
	DetailedResolutionClass *DetailedResolution;
	bool Refreshing;
public:		// User declarations
	__fastcall TDetailedResolutionForm(TComponent *Owner);
	bool Connect(DetailedResolutionClass &);
	TColor GetTextColor(bool, bool);
	TColor GetColor(bool);
	bool Refresh(void *);
	bool InitTimingComboBox();
	bool RefreshTimingComboBox();
	bool RefreshTimingButtons();
	bool RefreshParametersRadioButtons();
	bool RefreshParametersTextBoxes();
	bool RefreshParametersComboBoxes();
	bool RefreshParametersLabels();
	bool RefreshFrequencyRadioButtons();
	bool RefreshFrequencyTextBoxes();
	bool RefreshFrequencyLabels();
	bool RefreshInterlacedCheckBox();
	bool RefreshNativeCheckBox();
	bool ScaleControls();
};
//---------------------------------------------------------------------------
extern PACKAGE TDetailedResolutionForm *DetailedResolutionForm;
//---------------------------------------------------------------------------
#endif
