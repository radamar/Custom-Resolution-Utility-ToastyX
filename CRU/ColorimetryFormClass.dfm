object ColorimetryForm: TColorimetryForm
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'Colorimetry'
  ClientHeight = 318
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
  object ColorimetryGroupBox: TGroupBox
    Left = 8
    Top = 6
    Width = 154
    Height = 178
    Caption = ' Colorimetry '
    TabOrder = 0
    object ColorimetryCheckBox0: TCheckBox
      Left = 9
      Top = 17
      Width = 68
      Height = 17
      Caption = 'xvYCC601'
      TabOrder = 0
      OnClick = ColorimetryCheckBoxClick
    end
    object ColorimetryCheckBox1: TCheckBox
      Tag = 1
      Left = 9
      Top = 34
      Width = 68
      Height = 17
      Caption = 'xvYCC709'
      TabOrder = 1
      OnClick = ColorimetryCheckBoxClick
    end
    object ColorimetryCheckBox2: TCheckBox
      Tag = 2
      Left = 9
      Top = 51
      Width = 61
      Height = 17
      Caption = 'sYCC601'
      TabOrder = 2
      OnClick = ColorimetryCheckBoxClick
    end
    object ColorimetryCheckBox3: TCheckBox
      Tag = 3
      Left = 9
      Top = 68
      Width = 103
      Height = 17
      Caption = 'Adobe/opYCC601'
      TabOrder = 3
      OnClick = ColorimetryCheckBoxClick
    end
    object ColorimetryCheckBox4: TCheckBox
      Tag = 4
      Left = 9
      Top = 85
      Width = 85
      Height = 17
      Caption = 'Adobe/opRGB'
      TabOrder = 4
      OnClick = ColorimetryCheckBoxClick
    end
    object ColorimetryCheckBox5: TCheckBox
      Tag = 5
      Left = 9
      Top = 102
      Width = 86
      Height = 17
      Caption = 'BT.2020 cYCC'
      TabOrder = 5
      OnClick = ColorimetryCheckBoxClick
    end
    object ColorimetryCheckBox6: TCheckBox
      Tag = 6
      Left = 9
      Top = 119
      Width = 81
      Height = 17
      Caption = 'BT.2020 YCC'
      TabOrder = 6
      OnClick = ColorimetryCheckBoxClick
    end
    object ColorimetryCheckBox7: TCheckBox
      Tag = 7
      Left = 9
      Top = 136
      Width = 81
      Height = 17
      Caption = 'BT.2020 RGB'
      TabOrder = 7
      OnClick = ColorimetryCheckBoxClick
    end
    object ColorimetryCheckBox8: TCheckBox
      Tag = 8
      Left = 9
      Top = 153
      Width = 52
      Height = 17
      Caption = 'DCI-P3'
      TabOrder = 8
      OnClick = ColorimetryCheckBoxClick
    end
  end
  object MetadataGroupBox: TGroupBox
    Left = 8
    Top = 189
    Width = 154
    Height = 93
    Caption = ' Metadata '
    TabOrder = 1
    object MetadataCheckBox0: TCheckBox
      Left = 9
      Top = 17
      Width = 39
      Height = 17
      Caption = 'MD0'
      TabOrder = 0
      OnClick = MetadataCheckBoxClick
    end
    object MetadataCheckBox1: TCheckBox
      Tag = 1
      Left = 9
      Top = 34
      Width = 39
      Height = 17
      Caption = 'MD1'
      TabOrder = 1
      OnClick = MetadataCheckBoxClick
    end
    object MetadataCheckBox2: TCheckBox
      Tag = 2
      Left = 9
      Top = 51
      Width = 39
      Height = 17
      Caption = 'MD2'
      TabOrder = 2
      OnClick = MetadataCheckBoxClick
    end
    object MetadataCheckBox3: TCheckBox
      Tag = 3
      Left = 9
      Top = 68
      Width = 39
      Height = 17
      Caption = 'MD3'
      TabOrder = 3
      OnClick = MetadataCheckBoxClick
    end
  end
  object FormOKButton: TButton
    Left = 7
    Top = 288
    Width = 75
    Height = 23
    Caption = 'OK'
    Default = True
    ModalResult = 1
    TabOrder = 2
  end
  object FormCancelButton: TButton
    Left = 88
    Top = 288
    Width = 75
    Height = 23
    Cancel = True
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 3
  end
end
