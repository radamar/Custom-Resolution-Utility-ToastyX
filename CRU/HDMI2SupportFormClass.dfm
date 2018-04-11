object HDMI2SupportForm: THDMI2SupportForm
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'HDMI 2.0 Support'
  ClientHeight = 305
  ClientWidth = 170
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poOwnerFormCenter
  OnCreate = FormCreate
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object TMDSRateGroupBox: TGroupBox
    Left = 8
    Top = 6
    Width = 154
    Height = 50
    Caption = ' Max TMDS character rate '
    TabOrder = 0
    object TMDSRateLabel: TLabel
      Left = 45
      Top = 22
      Width = 23
      Height = 13
      Caption = 'Mcsc'
    end
    object TMDSRate: TEdit
      Left = 9
      Top = 19
      Width = 30
      Height = 21
      MaxLength = 4
      TabOrder = 0
      OnChange = TMDSRateChange
      OnExit = TMDSRateExit
    end
  end
  object FeaturesGroupBox: TGroupBox
    Left = 8
    Top = 61
    Width = 154
    Height = 127
    Caption = ' Supported features '
    TabOrder = 1
    object FeaturesCheckBox0: TCheckBox
      Left = 9
      Top = 102
      Width = 99
      Height = 17
      Caption = '3D OSD disparity'
      TabOrder = 5
      OnClick = FeaturesCheckBoxClick
    end
    object FeaturesCheckBox1: TCheckBox
      Tag = 1
      Left = 9
      Top = 85
      Width = 64
      Height = 17
      Caption = 'Dual view'
      TabOrder = 4
      OnClick = FeaturesCheckBoxClick
    end
    object FeaturesCheckBox2: TCheckBox
      Tag = 2
      Left = 9
      Top = 68
      Width = 105
      Height = 17
      Caption = 'Independent view'
      TabOrder = 3
      OnClick = FeaturesCheckBoxClick
    end
    object FeaturesCheckBox3: TCheckBox
      Tag = 3
      Left = 9
      Top = 51
      Width = 126
      Height = 17
      Caption = '<= 340 Mcsc scramble'
      TabOrder = 2
      OnClick = FeaturesCheckBoxClick
    end
    object FeaturesCheckBox6: TCheckBox
      Tag = 6
      Left = 9
      Top = 34
      Width = 123
      Height = 17
      Caption = 'Read request capable'
      TabOrder = 1
      OnClick = FeaturesCheckBoxClick
    end
    object FeaturesCheckBox7: TCheckBox
      Tag = 7
      Left = 9
      Top = 17
      Width = 85
      Height = 17
      Caption = 'SCDC present'
      TabOrder = 0
      OnClick = FeaturesCheckBoxClick
    end
  end
  object ColorFormatsGroupBox: TGroupBox
    Left = 8
    Top = 193
    Width = 154
    Height = 76
    Caption = ' YCbCr 4:2:0 deep color '
    TabOrder = 2
    object ColorFormatsCheckBox0: TCheckBox
      Left = 9
      Top = 17
      Width = 89
      Height = 17
      Caption = '30-bit (10 bpc)'
      TabOrder = 0
      OnClick = ColorFormatsCheckBoxClick
    end
    object ColorFormatsCheckBox1: TCheckBox
      Tag = 1
      Left = 9
      Top = 34
      Width = 89
      Height = 17
      Caption = '36-bit (12 bpc)'
      TabOrder = 1
      OnClick = ColorFormatsCheckBoxClick
    end
    object ColorFormatsCheckBox2: TCheckBox
      Tag = 2
      Left = 9
      Top = 51
      Width = 89
      Height = 17
      Caption = '48-bit (16 bpc)'
      TabOrder = 2
      OnClick = ColorFormatsCheckBoxClick
    end
  end
  object FormOKButton: TButton
    Left = 7
    Top = 275
    Width = 75
    Height = 23
    Caption = 'OK'
    Default = True
    ModalResult = 1
    TabOrder = 3
  end
  object FormCancelButton: TButton
    Left = 88
    Top = 275
    Width = 75
    Height = 23
    Cancel = True
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 4
  end
end
