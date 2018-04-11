//---------------------------------------------------------------------------
#ifndef AudioFormatFormClassH
#define AudioFormatFormClassH
//---------------------------------------------------------------------------
#include "CommonFormClass.h"
#include "AudioFormatClass.h"
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TAudioFormatForm : public TCommonForm
{
__published:	// IDE-managed Components
	TLabel *ChannelsLabel;
	TLabel *BitRateLabel;
	TLabel *FlagsRangeLabel;
	TGroupBox *FormatGroupBox;
	TComboBox *FormatComboBox;
	TComboBox *ChannelsComboBox;
	TGroupBox *SampleRatesGroupBox;
	TCheckBox *SampleRateCheckBox0;
	TCheckBox *SampleRateCheckBox1;
	TCheckBox *SampleRateCheckBox2;
	TCheckBox *SampleRateCheckBox3;
	TCheckBox *SampleRateCheckBox4;
	TCheckBox *SampleRateCheckBox5;
	TCheckBox *SampleRateCheckBox6;
	TGroupBox *BitDepthsGroupBox;
	TCheckBox *BitDepthCheckBox0;
	TCheckBox *BitDepthCheckBox1;
	TCheckBox *BitDepthCheckBox2;
	TGroupBox *BitRateGroupBox;
	TEdit *BitRate;
	TGroupBox *FlagsGroupBox;
	TEdit *Flags;
	TButton *FormOKButton;
	TButton *FormCancelButton;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormatComboBoxChange(TObject *Sender);
	void __fastcall ChannelsComboBoxChange(TObject *Sender);
	void __fastcall SampleRateCheckBoxClick(TObject *Sender);
	void __fastcall BitDepthCheckBoxClick(TObject *Sender);
	void __fastcall BitRateChange(TObject *Sender);
	void __fastcall BitRateExit(TObject *Sender);
	void __fastcall FlagsChange(TObject *Sender);
	void __fastcall FlagsExit(TObject *Sender);
private:	// User declarations
	AudioFormatClass *AudioFormat;
	bool Refreshing;
public:		// User declarations
	__fastcall TAudioFormatForm(TComponent *Owner);
	bool Connect(AudioFormatClass &);
	TColor GetTextColor(bool);
	bool Refresh(void *);
	bool InitFormatComboBox();
	bool InitChannelsComboBox();
	bool ScaleControls();
};
//---------------------------------------------------------------------------
extern PACKAGE TAudioFormatForm *AudioFormatForm;
//---------------------------------------------------------------------------
#endif
