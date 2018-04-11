//---------------------------------------------------------------------------
#ifndef FreeSyncRangeFormClassH
#define FreeSyncRangeFormClassH
//---------------------------------------------------------------------------
#include "CommonFormClass.h"
#include "FreeSyncRangeClass.h"
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TFreeSyncRangeForm : public TCommonForm
{
__published:	// IDE-managed Components
	TLabel *VRateLabel;
	TShape *VRateDash;
	TLabel *HzLabel;
	TGroupBox *RangeLimitsGroupBox;
	TEdit *MinVRate;
	TEdit *MaxVRate;
	TButton *FormOKButton;
	TButton *FormCancelButton;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall MinVRateChange(TObject *Sender);
	void __fastcall MinVRateExit(TObject *Sender);
	void __fastcall MaxVRateChange(TObject *Sender);
	void __fastcall MaxVRateExit(TObject *Sender);
private:	// User declarations
	FreeSyncRangeClass *FreeSyncRange;
	bool Refreshing;
public:		// User declarations
	__fastcall TFreeSyncRangeForm(TComponent *Owner);
	bool Connect(FreeSyncRangeClass &);
	TColor GetTextColor(bool);
	bool Refresh(void *);
	bool RefreshRangeLimitsTextBoxes();
	bool ScaleControls();
};
//---------------------------------------------------------------------------
extern PACKAGE TFreeSyncRangeForm *FreeSyncRangeForm;
//---------------------------------------------------------------------------
#endif
