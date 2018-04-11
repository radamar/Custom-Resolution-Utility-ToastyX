//---------------------------------------------------------------------------
#ifndef VideoCapabilityFormClassH
#define VideoCapabilityFormClassH
//---------------------------------------------------------------------------
#include "CommonFormClass.h"
#include "VideoCapabilityClass.h"
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TVideoCapabilityForm : public TCommonForm
{
__published:	// IDE-managed Components
	TGroupBox *TVGroupBox;
	TRadioButton *TVRadioButton0;
	TRadioButton *TVRadioButton1;
	TRadioButton *TVRadioButton2;
	TRadioButton *TVRadioButton3;
	TGroupBox *PCGroupBox;
	TRadioButton *PCRadioButton0;
	TRadioButton *PCRadioButton1;
	TRadioButton *PCRadioButton2;
	TRadioButton *PCRadioButton3;
	TGroupBox *NativeGroupBox;
	TRadioButton *NativeRadioButton0;
	TRadioButton *NativeRadioButton1;
	TRadioButton *NativeRadioButton2;
	TRadioButton *NativeRadioButton3;
	TGroupBox *QuantizationGroupBox;
	TCheckBox *RGBCheckBox;
	TCheckBox *YCCCheckBox;
	TButton *FormOKButton;
	TButton *FormCancelButton;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall TVRadioButton0Click(TObject *Sender);
	void __fastcall TVRadioButton1Click(TObject *Sender);
	void __fastcall TVRadioButton2Click(TObject *Sender);
	void __fastcall TVRadioButton3Click(TObject *Sender);
	void __fastcall PCRadioButton0Click(TObject *Sender);
	void __fastcall PCRadioButton1Click(TObject *Sender);
	void __fastcall PCRadioButton2Click(TObject *Sender);
	void __fastcall PCRadioButton3Click(TObject *Sender);
	void __fastcall NativeRadioButton0Click(TObject *Sender);
	void __fastcall NativeRadioButton1Click(TObject *Sender);
	void __fastcall NativeRadioButton2Click(TObject *Sender);
	void __fastcall NativeRadioButton3Click(TObject *Sender);
	void __fastcall RGBCheckBoxClick(TObject *Sender);
	void __fastcall YCCCheckBoxClick(TObject *Sender);
private:	// User declarations
	VideoCapabilityClass *VideoCapability;
	bool Refreshing;
public:		// User declarations
	__fastcall TVideoCapabilityForm(TComponent *Owner);
	bool Connect(VideoCapabilityClass &);
	bool Refresh(void *);
	bool RefreshTVRadioButtons();
	bool RefreshPCRadioButtons();
	bool RefreshNativeRadioButtons();
	bool RefreshQuantizationCheckBoxes();
	bool ScaleControls();
};
//---------------------------------------------------------------------------
extern PACKAGE TVideoCapabilityForm *VideoCapabilityForm;
//---------------------------------------------------------------------------
#endif
