object VideoCapabilityForm: TVideoCapabilityForm
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'Video Capability'
  ClientHeight = 395
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
  object TVGroupBox: TGroupBox
    Left = 8
    Top = 6
    Width = 154
    Height = 93
    Caption = ' TV resolutions (CE) '
    TabOrder = 0
    object TVRadioButton0: TRadioButton
      Left = 9
      Top = 17
      Width = 87
      Height = 17
      Caption = 'Not supported'
      TabOrder = 0
      OnClick = TVRadioButton0Click
    end
    object TVRadioButton1: TRadioButton
      Left = 9
      Top = 34
      Width = 117
      Height = 17
      Caption = 'Always overscanned'
      TabOrder = 1
      OnClick = TVRadioButton1Click
    end
    object TVRadioButton2: TRadioButton
      Left = 9
      Top = 51
      Width = 123
      Height = 17
      Caption = 'Always underscanned'
      TabOrder = 2
      OnClick = TVRadioButton2Click
    end
    object TVRadioButton3: TRadioButton
      Left = 9
      Top = 68
      Width = 114
      Height = 17
      Caption = 'Selectable overscan'
      TabOrder = 3
      OnClick = TVRadioButton3Click
    end
  end
  object PCGroupBox: TGroupBox
    Left = 8
    Top = 104
    Width = 154
    Height = 93
    Caption = ' PC resolutions (IT) '
    TabOrder = 1
    object PCRadioButton0: TRadioButton
      Left = 9
      Top = 17
      Width = 87
      Height = 17
      Caption = 'Not supported'
      TabOrder = 0
      OnClick = PCRadioButton0Click
    end
    object PCRadioButton1: TRadioButton
      Left = 9
      Top = 34
      Width = 117
      Height = 17
      Caption = 'Always overscanned'
      TabOrder = 1
      OnClick = PCRadioButton1Click
    end
    object PCRadioButton2: TRadioButton
      Left = 9
      Top = 51
      Width = 123
      Height = 17
      Caption = 'Always underscanned'
      TabOrder = 2
      OnClick = PCRadioButton2Click
    end
    object PCRadioButton3: TRadioButton
      Left = 9
      Top = 68
      Width = 114
      Height = 17
      Caption = 'Selectable overscan'
      TabOrder = 3
      OnClick = PCRadioButton3Click
    end
  end
  object NativeGroupBox: TGroupBox
    Left = 8
    Top = 202
    Width = 154
    Height = 93
    Caption = ' Native resolution (PT) '
    TabOrder = 2
    object NativeRadioButton0: TRadioButton
      Left = 9
      Top = 17
      Width = 125
      Height = 17
      Caption = 'Use TV/PC information'
      TabOrder = 0
      OnClick = NativeRadioButton0Click
    end
    object NativeRadioButton1: TRadioButton
      Left = 9
      Top = 34
      Width = 117
      Height = 17
      Caption = 'Always overscanned'
      TabOrder = 1
      OnClick = NativeRadioButton1Click
    end
    object NativeRadioButton2: TRadioButton
      Left = 9
      Top = 51
      Width = 123
      Height = 17
      Caption = 'Always underscanned'
      TabOrder = 2
      OnClick = NativeRadioButton2Click
    end
    object NativeRadioButton3: TRadioButton
      Left = 9
      Top = 68
      Width = 114
      Height = 17
      Caption = 'Selectable overscan'
      TabOrder = 3
      OnClick = NativeRadioButton3Click
    end
  end
  object QuantizationGroupBox: TGroupBox
    Left = 8
    Top = 300
    Width = 154
    Height = 59
    Caption = ' Quantization '
    TabOrder = 3
    object RGBCheckBox: TCheckBox
      Left = 9
      Top = 17
      Width = 121
      Height = 17
      Caption = 'Selectable RGB range'
      TabOrder = 0
      OnClick = RGBCheckBoxClick
    end
    object YCCCheckBox: TCheckBox
      Left = 9
      Top = 34
      Width = 121
      Height = 17
      Caption = 'Selectable YCC range'
      TabOrder = 1
      OnClick = YCCCheckBoxClick
    end
  end
  object FormOKButton: TButton
    Left = 7
    Top = 365
    Width = 75
    Height = 23
    Caption = 'OK'
    Default = True
    ModalResult = 1
    TabOrder = 4
  end
  object FormCancelButton: TButton
    Left = 88
    Top = 365
    Width = 75
    Height = 23
    Cancel = True
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 5
  end
end
