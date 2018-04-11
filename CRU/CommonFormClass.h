//---------------------------------------------------------------------------
#ifndef CommonFormClassH
#define CommonFormClassH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TCommonForm : public TForm
{
__published:	// IDE-managed Components
private:	// User declarations
public:		// User declarations
	__fastcall TCommonForm(TComponent *Owner);
	TEXTMETRIC Text;
	int Scale;
	int Themed;
	int LabelSpacing;
	int PostLabelSpacing;
	int ComboBoxHeight;
	int NumberWidth;
	int TextBoxPadding;
	int TextBoxHeight;
	int TextBoxSpacing;
	int ButtonWidth;
	int ButtonHeight;
	int ButtonLeft;
	int ButtonRight;
	int ButtonTop;
	int ButtonBottom;
	int LongButtonWidth;
	int LongButtonHeight;
	int ArrowButtonWidth;
	int ArrowButtonHeight;
	int NumGlyphs;
	int CheckBoxWidth;
	int CheckBoxHeight;
	int CheckBoxRight;
	int CheckBoxTop;
	int CheckBoxBottom;
	int CheckBoxSpacing;
	int RadioButtonWidth;
	int RadioButtonHeight;
	int RadioButtonRight;
	int RadioButtonTop;
	int RadioButtonBottom;
	int RadioButtonSpacing;
	int ListBoxWidth;
	int LongListBoxWidth;
	int PaddingWidth;
	int PaddingTop;
	int PaddingBottom;
	int GroupBoxTop;
	int GroupBoxBottom;
	int FormButtonWidth;
	int FormButtonHeight;
	int FormButtonsWidth;
};
//---------------------------------------------------------------------------
extern PACKAGE TCommonForm *CommonForm;
//---------------------------------------------------------------------------
#endif
