object StandardResolutionForm: TStandardResolutionForm
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'Standard Resolution'
  ClientHeight = 121
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
  object ResolutionGroupBox: TGroupBox
    Left = 8
    Top = 6
    Width = 154
    Height = 79
    Caption = ' Resolution '
    ParentBackground = False
    TabOrder = 0
    object RateLabel: TLabel
      Left = 22
      Top = 51
      Width = 65
      Height = 13
      Caption = 'Refresh rate:'
    end
    object ByLabel: TLabel
      Left = 43
      Top = 51
      Width = 6
      Height = 13
      Caption = 'x'
    end
    object AtLabel: TLabel
      Left = 88
      Top = 51
      Width = 10
      Height = 13
      Caption = '@'
    end
    object HzLabel: TLabel
      Left = 133
      Top = 51
      Width = 12
      Height = 13
      Caption = 'Hz'
    end
    object ModeComboBox: TComboBox
      Left = 9
      Top = 19
      Width = 136
      Height = 21
      Style = csDropDownList
      ItemHeight = 0
      TabOrder = 0
      OnChange = ModeComboBoxChange
    end
    object Width: TEdit
      Left = 9
      Top = 48
      Width = 30
      Height = 21
      MaxLength = 4
      TabOrder = 1
      OnChange = WidthChange
      OnExit = WidthExit
    end
    object Height: TEdit
      Left = 53
      Top = 48
      Width = 30
      Height = 21
      MaxLength = 4
      TabOrder = 2
      OnChange = HeightChange
      OnExit = HeightExit
    end
    object Rate: TEdit
      Left = 103
      Top = 48
      Width = 24
      Height = 21
      MaxLength = 3
      TabOrder = 3
      OnChange = RateChange
      OnExit = RateExit
    end
  end
  object FormOKButton: TButton
    Left = 7
    Top = 91
    Width = 75
    Height = 23
    Caption = 'OK'
    Default = True
    ModalResult = 1
    TabOrder = 1
  end
  object FormCancelButton: TButton
    Left = 88
    Top = 91
    Width = 75
    Height = 23
    Cancel = True
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 2
  end
end
