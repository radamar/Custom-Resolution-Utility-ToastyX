//---------------------------------------------------------------------------
#ifndef AddCEADataFormH
#define AddCEADataFormH
//---------------------------------------------------------------------------
#include "CommonFormClass.h"
#include "AddCEADataClass.h"
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TAddCEADataForm : public TCommonForm
{
__published:	// IDE-managed Components
	TGroupBox *TypeGroupBox;
	TRadioButton *TVRadioButton;
	TRadioButton *AudioRadioButton;
	TRadioButton *SpeakerRadioButton;
	TRadioButton *HDMIRadioButton;
	TRadioButton *HDMI2RadioButton;
	TRadioButton *FreeSyncRadioButton;
	TRadioButton *ColorimetryRadioButton;
	TRadioButton *VideoCapabilityRadioButton;
	TButton *FormOKButton;
	TButton *FormCancelButton;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall TVRadioButtonClick(TObject *Sender);
	void __fastcall AudioRadioButtonClick(TObject *Sender);
	void __fastcall SpeakerRadioButtonClick(TObject *Sender);
	void __fastcall HDMIRadioButtonClick(TObject *Sender);
	void __fastcall HDMI2RadioButtonClick(TObject *Sender);
	void __fastcall FreeSyncRadioButtonClick(TObject *Sender);
	void __fastcall ColorimetryRadioButtonClick(TObject *Sender);
	void __fastcall VideoCapabilityRadioButtonClick(TObject *Sender);
private:	// User declarations
	AddCEADataClass *AddCEAData;
	bool Refreshing;
public:		// User declarations
	__fastcall TAddCEADataForm(TComponent *Owner);
	bool Connect(AddCEADataClass &);
	bool Refresh(void *);
	bool RefreshTypeRadioButtons();
	bool ScaleControls();
};
//---------------------------------------------------------------------------
extern PACKAGE TAddCEADataForm *AddCEADataForm;
//---------------------------------------------------------------------------
#endif
