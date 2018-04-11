//---------------------------------------------------------------------------
#ifndef TVResolutionFormH
#define TVResolutionFormH
//---------------------------------------------------------------------------
#include "CommonFormClass.h"
#include "TVResolutionClass.h"
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TTVResolutionForm : public TCommonForm
{
__published:	// IDE-managed Components
	TLabel *FormatLabel;
	TLabel *CodeLabel;
	TLabel *CodeRangeLabel;
	TGroupBox *ResolutionGroupBox;
	TComboBox *ModeComboBox;
	TComboBox *FormatComboBox;
	TEdit *Code;
	TCheckBox *Native;
	TButton *FormOKButton;
	TButton *FormCancelButton;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall ModeComboBoxChange(TObject *Sender);
	void __fastcall FormatComboBoxChange(TObject *Sender);
	void __fastcall CodeChange(TObject *Sender);
	void __fastcall CodeExit(TObject *Sender);
	void __fastcall NativeClick(TObject *Sender);
private:	// User declarations
	TVResolutionClass *TVResolution;
	bool Refreshing;
public:		// User declarations
	__fastcall TTVResolutionForm(TComponent *Owner);
	bool Connect(TVResolutionClass &);
	TColor GetTextColor(bool);
	bool Refresh(void *);
	bool InitModeComboBox();
	bool InitFormatComboBox();
	bool ScaleControls();
};
//---------------------------------------------------------------------------
extern PACKAGE TTVResolutionForm *TVResolutionForm;
//---------------------------------------------------------------------------
#endif
