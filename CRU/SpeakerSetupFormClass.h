//---------------------------------------------------------------------------
#ifndef SpeakerSetupFormClassH
#define SpeakerSetupFormClassH
//---------------------------------------------------------------------------
#include "CommonFormClass.h"
#include "SpeakerSetupClass.h"
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TSpeakerSetupForm : public TCommonForm
{
__published:	// IDE-managed Components
	TGroupBox *SpeakerGroupBox;
	TCheckBox *SpeakerCheckBox0;
	TCheckBox *SpeakerCheckBox1;
	TCheckBox *SpeakerCheckBox2;
	TCheckBox *SpeakerCheckBox3;
	TCheckBox *SpeakerCheckBox4;
	TCheckBox *SpeakerCheckBox5;
	TCheckBox *SpeakerCheckBox6;
	TCheckBox *SpeakerCheckBox7;
	TCheckBox *SpeakerCheckBox8;
	TCheckBox *SpeakerCheckBox9;
	TCheckBox *SpeakerCheckBox10;
	TButton *Speaker20Button;
	TButton *Speaker51Button;
	TButton *Speaker71Button;
	TButton *SpeakerResetButton;
	TButton *FormOKButton;
	TButton *FormCancelButton;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall SpeakerCheckBoxClick(TObject *Sender);
	void __fastcall Speaker20ButtonClick(TObject *Sender);
	void __fastcall Speaker51ButtonClick(TObject *Sender);
	void __fastcall Speaker71ButtonClick(TObject *Sender);
	void __fastcall SpeakerResetButtonClick(TObject *Sender);
private:	// User declarations
	SpeakerSetupClass *SpeakerSetup;
	bool Refreshing;
public:		// User declarations
	__fastcall TSpeakerSetupForm(TComponent *Owner);
	bool Connect(SpeakerSetupClass &);
	bool Refresh(void *);
	bool RefreshSpeakerCheckBoxes();
	bool RefreshSpeakerButtons();
	bool ScaleControls();
};
//---------------------------------------------------------------------------
extern PACKAGE TSpeakerSetupForm *SpeakerSetupForm;
//---------------------------------------------------------------------------
#endif
