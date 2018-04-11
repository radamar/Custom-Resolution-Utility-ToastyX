object AddCEADataForm: TAddCEADataForm
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'Add Data Block'
  ClientHeight = 203
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
  object TypeGroupBox: TGroupBox
    Left = 8
    Top = 6
    Width = 154
    Height = 161
    Caption = ' Type '
    TabOrder = 0
    object TVRadioButton: TRadioButton
      Left = 9
      Top = 17
      Width = 85
      Height = 17
      Caption = 'TV resolutions'
      TabOrder = 0
      OnClick = TVRadioButtonClick
    end
    object AudioRadioButton: TRadioButton
      Left = 9
      Top = 34
      Width = 85
      Height = 17
      Caption = 'Audio formats'
      TabOrder = 1
      OnClick = AudioRadioButtonClick
    end
    object SpeakerRadioButton: TRadioButton
      Left = 9
      Top = 51
      Width = 87
      Height = 17
      Caption = 'Speaker setup'
      TabOrder = 2
      OnClick = SpeakerRadioButtonClick
    end
    object HDMIRadioButton: TRadioButton
      Left = 9
      Top = 68
      Width = 84
      Height = 17
      Caption = 'HDMI support'
      TabOrder = 3
      OnClick = HDMIRadioButtonClick
    end
    object HDMI2RadioButton: TRadioButton
      Left = 9
      Top = 85
      Width = 103
      Height = 17
      Caption = 'HDMI 2.0 support'
      TabOrder = 4
      OnClick = HDMI2RadioButtonClick
    end
    object FreeSyncRadioButton: TRadioButton
      Left = 9
      Top = 102
      Width = 94
      Height = 17
      Caption = 'FreeSync range'
      TabOrder = 5
      OnClick = FreeSyncRadioButtonClick
    end
    object ColorimetryRadioButton: TRadioButton
      Left = 9
      Top = 119
      Width = 73
      Height = 17
      Caption = 'Colorimetry'
      TabOrder = 6
      OnClick = ColorimetryRadioButtonClick
    end
    object VideoCapabilityRadioButton: TRadioButton
      Left = 9
      Top = 136
      Width = 92
      Height = 17
      Caption = 'Video capability'
      TabOrder = 7
      OnClick = VideoCapabilityRadioButtonClick
    end
  end
  object FormOKButton: TButton
    Left = 7
    Top = 173
    Width = 75
    Height = 23
    Caption = 'OK'
    Default = True
    ModalResult = 1
    TabOrder = 1
  end
  object FormCancelButton: TButton
    Left = 88
    Top = 173
    Width = 75
    Height = 23
    Cancel = True
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 2
  end
end
