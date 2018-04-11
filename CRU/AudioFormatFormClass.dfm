object AudioFormatForm: TAudioFormatForm
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'Audio Format'
  ClientHeight = 461
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
  object FormatGroupBox: TGroupBox
    Left = 8
    Top = 6
    Width = 154
    Height = 79
    Caption = ' Format '
    TabOrder = 0
    object ChannelsLabel: TLabel
      Left = 9
      Top = 52
      Width = 48
      Height = 13
      Caption = 'Channels:'
    end
    object FormatComboBox: TComboBox
      Left = 9
      Top = 19
      Width = 136
      Height = 21
      Style = csDropDownList
      ItemHeight = 0
      TabOrder = 0
      OnChange = FormatComboBoxChange
    end
    object ChannelsComboBox: TComboBox
      Left = 61
      Top = 48
      Width = 84
      Height = 21
      Style = csDropDownList
      ItemHeight = 0
      TabOrder = 1
      OnChange = ChannelsComboBoxChange
    end
  end
  object SampleRatesGroupBox: TGroupBox
    Left = 8
    Top = 90
    Width = 154
    Height = 144
    Caption = ' Sample rates '
    TabOrder = 1
    object SampleRateCheckBox0: TCheckBox
      Left = 9
      Top = 17
      Width = 60
      Height = 17
      Caption = '32.0 kHz'
      TabOrder = 0
      OnClick = SampleRateCheckBoxClick
    end
    object SampleRateCheckBox1: TCheckBox
      Tag = 1
      Left = 9
      Top = 34
      Width = 60
      Height = 17
      Caption = '44.1 kHz'
      TabOrder = 1
      OnClick = SampleRateCheckBoxClick
    end
    object SampleRateCheckBox2: TCheckBox
      Tag = 2
      Left = 9
      Top = 51
      Width = 60
      Height = 17
      Caption = '48.0 kHz'
      TabOrder = 2
      OnClick = SampleRateCheckBoxClick
    end
    object SampleRateCheckBox3: TCheckBox
      Tag = 3
      Left = 9
      Top = 68
      Width = 60
      Height = 17
      Caption = '88.2 kHz'
      TabOrder = 3
      OnClick = SampleRateCheckBoxClick
    end
    object SampleRateCheckBox4: TCheckBox
      Tag = 4
      Left = 9
      Top = 85
      Width = 60
      Height = 17
      Caption = '96.0 kHz'
      TabOrder = 4
      OnClick = SampleRateCheckBoxClick
    end
    object SampleRateCheckBox5: TCheckBox
      Tag = 5
      Left = 9
      Top = 102
      Width = 66
      Height = 17
      Caption = '176.4 kHz'
      TabOrder = 5
      OnClick = SampleRateCheckBoxClick
    end
    object SampleRateCheckBox6: TCheckBox
      Tag = 6
      Left = 9
      Top = 119
      Width = 66
      Height = 17
      Caption = '192.0 kHz'
      TabOrder = 6
      OnClick = SampleRateCheckBoxClick
    end
  end
  object BitDepthsGroupBox: TGroupBox
    Left = 8
    Top = 239
    Width = 154
    Height = 76
    Caption = ' Bit depths '
    TabOrder = 2
    object BitDepthCheckBox0: TCheckBox
      Left = 9
      Top = 17
      Width = 46
      Height = 17
      Caption = '16-bit'
      TabOrder = 0
      OnClick = BitDepthCheckBoxClick
    end
    object BitDepthCheckBox1: TCheckBox
      Tag = 1
      Left = 9
      Top = 34
      Width = 46
      Height = 17
      Caption = '20-bit'
      TabOrder = 1
      OnClick = BitDepthCheckBoxClick
    end
    object BitDepthCheckBox2: TCheckBox
      Tag = 2
      Left = 9
      Top = 51
      Width = 46
      Height = 17
      Caption = '24-bit'
      TabOrder = 2
      OnClick = BitDepthCheckBoxClick
    end
  end
  object BitRateGroupBox: TGroupBox
    Left = 8
    Top = 320
    Width = 154
    Height = 50
    Caption = ' Maximum bit rate '
    TabOrder = 3
    object BitRateLabel: TLabel
      Left = 45
      Top = 22
      Width = 26
      Height = 13
      Caption = 'kbit/s'
    end
    object BitRate: TEdit
      Left = 9
      Top = 19
      Width = 30
      Height = 21
      MaxLength = 4
      TabOrder = 0
      OnChange = BitRateChange
      OnExit = BitRateExit
    end
  end
  object FlagsGroupBox: TGroupBox
    Left = 8
    Top = 375
    Width = 154
    Height = 50
    Caption = ' Flags '
    TabOrder = 4
    object FlagsRangeLabel: TLabel
      Left = 39
      Top = 22
      Width = 36
      Height = 13
      Caption = '(0-255)'
    end
    object Flags: TEdit
      Left = 9
      Top = 19
      Width = 24
      Height = 21
      MaxLength = 3
      TabOrder = 0
      OnChange = FlagsChange
      OnExit = FlagsExit
    end
  end
  object FormOKButton: TButton
    Left = 7
    Top = 431
    Width = 75
    Height = 23
    Caption = 'OK'
    Default = True
    ModalResult = 1
    TabOrder = 5
  end
  object FormCancelButton: TButton
    Left = 88
    Top = 431
    Width = 75
    Height = 23
    Cancel = True
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 6
  end
end
