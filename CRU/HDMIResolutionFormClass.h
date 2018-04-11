//---------------------------------------------------------------------------
#ifndef HDMIResolutionFormClassH
#define HDMIResolutionFormClassH
//---------------------------------------------------------------------------
#include "CommonFormClass.h"
#include "HDMIResolutionClass.h"
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class THDMIResolutionForm : public TCommonForm
{
__published:	// IDE-managed Components
	TLabel *FormatLabel;
	TLabel *CodeLabel;
	TLabel *CodeRangeLabel;
	TGroupBox *ResolutionGroupBox;
	TComboBox *ModeComboBox;
	TComboBox *FormatComboBox;
	TEdit *Code;
	TButton *FormOKButton;
	TButton *FormCancelButton;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall ModeComboBoxChange(TObject *Sender);
	void __fastcall FormatComboBoxChange(TObject *Sender);
	void __fastcall CodeChange(TObject *Sender);
	void __fastcall CodeExit(TObject *Sender);
private:	// User declarations
	HDMIResolutionClass *HDMIResolution;
	bool Refreshing;
public:		// User declarations
	__fastcall THDMIResolutionForm(TComponent *Owner);
	bool Connect(HDMIResolutionClass &);
	TColor GetTextColor(bool);
	bool Refresh(void *);
	bool InitModeComboBox();
	bool InitFormatComboBox();
	bool ScaleControls();
};
//---------------------------------------------------------------------------
extern PACKAGE THDMIResolutionForm *HDMIResolutionForm;
//---------------------------------------------------------------------------
#endif
