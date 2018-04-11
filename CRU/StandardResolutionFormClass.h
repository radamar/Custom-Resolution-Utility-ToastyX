//---------------------------------------------------------------------------
#ifndef StandardResolutionFormClassH
#define StandardResolutionFormClassH
//---------------------------------------------------------------------------
#include "CommonFormClass.h"
#include "StandardResolutionClass.h"
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TStandardResolutionForm : public TCommonForm
{
__published:	// IDE-managed Components
	TLabel *RateLabel;
	TLabel *ByLabel;
	TLabel *AtLabel;
	TLabel *HzLabel;
	TGroupBox *ResolutionGroupBox;
	TComboBox *ModeComboBox;
	TEdit *Width;
	TEdit *Height;
	TEdit *Rate;
	TButton *FormOKButton;
	TButton *FormCancelButton;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall ModeComboBoxChange(TObject *Sender);
	void __fastcall WidthChange(TObject *Sender);
	void __fastcall WidthExit(TObject *Sender);
	void __fastcall HeightChange(TObject *Sender);
	void __fastcall HeightExit(TObject *Sender);
	void __fastcall RateChange(TObject *Sender);
	void __fastcall RateExit(TObject *Sender);
private:	// User declarations
	StandardResolutionClass *StandardResolution;
	bool Refreshing;
public:		// User declarations
	__fastcall TStandardResolutionForm(TComponent *Owner);
	bool Connect(StandardResolutionClass &);
	TColor GetTextColor(bool);
	bool Refresh(void *);
	bool InitModeComboBox();
	bool ScaleControls();
};
//---------------------------------------------------------------------------
extern PACKAGE TStandardResolutionForm *StandardResolutionForm;
//---------------------------------------------------------------------------
#endif
