//---------------------------------------------------------------------------
#ifndef PropertiesFormClassH
#define PropertiesFormClassH
//---------------------------------------------------------------------------
#include "CommonFormClass.h"
#include "PropertiesClass.h"
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TPropertiesForm : public TCommonForm
{
__published:	// IDE-managed Components
	TLabel *ProductIDLabel;
	TLabel *SerialIDLabel;
	TLabel *VRateLabel;
	TShape *VRateDash;
	TLabel *HzLabel;
	TLabel *HRateLabel;
	TShape *HRateDash;
	TLabel *kHzLabel;
	TLabel *MaxPClockLabel;
	TLabel *MHzLabel;
	TGroupBox *ProductIDGroupBox;
	TEdit *ProductID;
	TButton *ProductIDResetButton;
	TEdit *SerialID;
	TGroupBox *NameGroupBox;
	TEdit *Name;
	TCheckBox *IncludeName;
	TGroupBox *SerialNumberGroupBox;
	TEdit *SerialNumber;
	TCheckBox *IncludeSerialNumber;
	TGroupBox *RangeLimitsGroupBox;
	TEdit *MinVRate;
	TEdit *MaxVRate;
	TEdit *MinHRate;
	TEdit *MaxHRate;
	TEdit *MaxPClock;
	TCheckBox *IncludeRangeLimits;
	TButton *FormOKButton;
	TButton *FormCancelButton;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall ProductIDChange(TObject *Sender);
	void __fastcall ProductIDExit(TObject *Sender);
	void __fastcall ProductIDResetButtonClick(TObject *Sender);
	void __fastcall SerialIDChange(TObject *Sender);
	void __fastcall SerialIDExit(TObject *Sender);
	void __fastcall NameChange(TObject *Sender);
	void __fastcall NameExit(TObject *Sender);
	void __fastcall IncludeNameClick(TObject *Sender);
	void __fastcall SerialNumberChange(TObject *Sender);
	void __fastcall SerialNumberExit(TObject *Sender);
	void __fastcall IncludeSerialNumberClick(TObject *Sender);
	void __fastcall MinVRateChange(TObject *Sender);
	void __fastcall MinVRateExit(TObject *Sender);
	void __fastcall MaxVRateChange(TObject *Sender);
	void __fastcall MaxVRateExit(TObject *Sender);
	void __fastcall MinHRateChange(TObject *Sender);
	void __fastcall MinHRateExit(TObject *Sender);
	void __fastcall MaxHRateChange(TObject *Sender);
	void __fastcall MaxHRateExit(TObject *Sender);
	void __fastcall MaxPClockChange(TObject *Sender);
	void __fastcall MaxPClockExit(TObject *Sender);
	void __fastcall IncludeRangeLimitsClick(TObject *Sender);
private:	// User declarations
	PropertiesClass *Properties;
	bool Refreshing;
public:		// User declarations
	__fastcall TPropertiesForm(TComponent *Owner);
	bool Connect(PropertiesClass &);
	TColor GetTextColor(bool);
	bool Refresh(void *);
	bool ScaleControls();
};
//---------------------------------------------------------------------------
extern PACKAGE TPropertiesForm *PropertiesForm;
//---------------------------------------------------------------------------
#endif
