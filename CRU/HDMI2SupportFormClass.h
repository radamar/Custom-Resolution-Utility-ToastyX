//---------------------------------------------------------------------------
#ifndef HDMI2SupportFormClassH
#define HDMI2SupportFormClassH
//---------------------------------------------------------------------------
#include "CommonFormClass.h"
#include "HDMI2SupportClass.h"
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class THDMI2SupportForm : public TCommonForm
{
__published:	// IDE-managed Components
	TLabel *TMDSRateLabel;
	TGroupBox *TMDSRateGroupBox;
	TEdit *TMDSRate;
	TGroupBox *FeaturesGroupBox;
	TCheckBox *FeaturesCheckBox0;
	TCheckBox *FeaturesCheckBox1;
	TCheckBox *FeaturesCheckBox2;
	TCheckBox *FeaturesCheckBox3;
	TCheckBox *FeaturesCheckBox6;
	TCheckBox *FeaturesCheckBox7;
	TGroupBox *ColorFormatsGroupBox;
	TCheckBox *ColorFormatsCheckBox0;
	TCheckBox *ColorFormatsCheckBox1;
	TCheckBox *ColorFormatsCheckBox2;
	TButton *FormOKButton;
	TButton *FormCancelButton;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall TMDSRateChange(TObject *Sender);
	void __fastcall TMDSRateExit(TObject *Sender);
	void __fastcall FeaturesCheckBoxClick(TObject *Sender);
	void __fastcall ColorFormatsCheckBoxClick(TObject *Sender);
private:	// User declarations
	HDMI2SupportClass *HDMI2Support;
	bool Refreshing;
public:		// User declarations
	__fastcall THDMI2SupportForm(TComponent *Owner);
	bool Connect(HDMI2SupportClass &);
	TColor GetTextColor(bool);
	bool Refresh(void *);
	bool RefreshTMDSRateTextBox();
	bool RefreshFeaturesCheckBoxes();
	bool RefreshColorFormatsCheckBoxes();
	bool ScaleControls();
};
//---------------------------------------------------------------------------
extern PACKAGE THDMI2SupportForm *HDMI2SupportForm;
//---------------------------------------------------------------------------
#endif
