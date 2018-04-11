//---------------------------------------------------------------------------
#ifndef AddDIDDataFormH
#define AddDIDDataFormH
//---------------------------------------------------------------------------
#include "CommonFormClass.h"
#include "AddDIDDataClass.h"
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TAddDIDDataForm : public TCommonForm
{
__published:	// IDE-managed Components
	TGroupBox *TypeGroupBox;
	TRadioButton *DetailedResolutionsRadioButton;
	TRadioButton *TiledDisplayTopologyRadioButton;
	TButton *FormOKButton;
	TButton *FormCancelButton;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall DetailedResolutionsRadioButtonClick(TObject *Sender);
	void __fastcall TiledDisplayTopologyRadioButtonClick(TObject *Sender);
private:	// User declarations
	AddDIDDataClass *AddDIDData;
	bool Refreshing;
public:		// User declarations
	__fastcall TAddDIDDataForm(TComponent *Owner);
	bool Connect(AddDIDDataClass &);
	bool Refresh(void *);
	bool RefreshTypeRadioButtons();
	bool ScaleControls();
};
//---------------------------------------------------------------------------
extern PACKAGE TAddDIDDataForm *AddDIDDataForm;
//---------------------------------------------------------------------------
#endif
