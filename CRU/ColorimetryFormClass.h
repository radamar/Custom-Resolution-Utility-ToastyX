//---------------------------------------------------------------------------
#ifndef ColorimetryFormClassH
#define ColorimetryFormClassH
//---------------------------------------------------------------------------
#include "CommonFormClass.h"
#include "ColorimetryClass.h"
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TColorimetryForm : public TCommonForm
{
__published:	// IDE-managed Components
	TGroupBox *ColorimetryGroupBox;
	TCheckBox *ColorimetryCheckBox0;
	TCheckBox *ColorimetryCheckBox1;
	TCheckBox *ColorimetryCheckBox2;
	TCheckBox *ColorimetryCheckBox3;
	TCheckBox *ColorimetryCheckBox4;
	TCheckBox *ColorimetryCheckBox5;
	TCheckBox *ColorimetryCheckBox6;
	TCheckBox *ColorimetryCheckBox7;
	TCheckBox *ColorimetryCheckBox8;
	TGroupBox *MetadataGroupBox;
	TCheckBox *MetadataCheckBox0;
	TCheckBox *MetadataCheckBox1;
	TCheckBox *MetadataCheckBox2;
	TCheckBox *MetadataCheckBox3;
	TButton *FormOKButton;
	TButton *FormCancelButton;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall ColorimetryCheckBoxClick(TObject *Sender);
	void __fastcall MetadataCheckBoxClick(TObject *Sender);
private:	// User declarations
	ColorimetryClass *Colorimetry;
	bool Refreshing;
public:		// User declarations
	__fastcall TColorimetryForm(TComponent *Owner);
	bool Connect(ColorimetryClass &);
	bool Refresh(void *);
	bool RefreshColorimetryCheckBoxes();
	bool RefreshMetadataCheckBoxes();
	bool ScaleControls();
};
//---------------------------------------------------------------------------
extern PACKAGE TColorimetryForm *ColorimetryForm;
//---------------------------------------------------------------------------
#endif
