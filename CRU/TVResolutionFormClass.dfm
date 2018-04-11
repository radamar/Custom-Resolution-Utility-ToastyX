object TVResolutionForm: TTVResolutionForm
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'TV Resolution'
  ClientHeight = 142
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
    Height = 100
    Caption = ' Resolution '
    TabOrder = 0
    object FormatLabel: TLabel
      Left = 9
      Top = 52
      Width = 38
      Height = 13
      Caption = 'Format:'
    end
    object CodeLabel: TLabel
      Left = 28
      Top = 51
      Width = 29
      Height = 13
      Caption = 'Code:'
    end
    object CodeRangeLabel: TLabel
      Left = 91
      Top = 51
      Width = 36
      Height = 13
      Caption = '(0-255)'
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
    object FormatComboBox: TComboBox
      Left = 51
      Top = 48
      Width = 94
      Height = 21
      Style = csDropDownList
      ItemHeight = 0
      TabOrder = 1
      OnChange = FormatComboBoxChange
    end
    object Code: TEdit
      Left = 61
      Top = 48
      Width = 24
      Height = 21
      MaxLength = 3
      TabOrder = 2
      OnChange = CodeChange
      OnExit = CodeExit
    end
    object Native: TCheckBox
      Left = 36
      Top = 75
      Width = 84
      Height = 17
      Caption = 'Native format'
      TabOrder = 3
      OnClick = NativeClick
    end
  end
  object FormOKButton: TButton
    Left = 7
    Top = 112
    Width = 75
    Height = 23
    Caption = 'OK'
    Default = True
    ModalResult = 1
    TabOrder = 1
  end
  object FormCancelButton: TButton
    Left = 88
    Top = 112
    Width = 75
    Height = 23
    Cancel = True
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 2
  end
end
